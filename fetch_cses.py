import getpass
import re
import time
from pathlib import Path
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup

BASE_URL = "https://cses.fi"
LOGIN_URL = f"{BASE_URL}/login"
LIST_URL = f"{BASE_URL}/problemset/list/"


def slugify(text: str) -> str:
    text = re.sub(r"[^\w\s-]", "", text).strip().lower()
    return re.sub(r"[-\s]+", "_", text)


def login(username: str, password: str) -> requests.Session:
    session = requests.Session()
    session.headers.update({
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
        "Referer": LOGIN_URL,
    })

    resp = session.get(LOGIN_URL, timeout=15)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, "html.parser")

    csrf_input = soup.find("input", {"name": "csrf_token"})
    csrf_token = csrf_input.get("value", "") if csrf_input else ""
    if not csrf_token:
        raise RuntimeError("Could not find csrf_token on login page.")

    payload = {
        "csrf_token": csrf_token,
        "nick": username,
        "pass": password,
    }
    post_resp = session.post(LOGIN_URL, data=payload, timeout=15, allow_redirects=True)
    post_resp.raise_for_status()

    if "PHPSESSID" not in session.cookies.get_dict():
        raise RuntimeError("Login failed: no PHPSESSID cookie received. Check credentials.")

    return session


def get_solved_tasks(session: requests.Session) -> list[dict]:
    resp = session.get(LIST_URL, timeout=15)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, "html.parser")

    content = soup.find("div", class_="content") or soup
    tasks = []
    current_category = "uncategorized"
    seen_ids = set()

    for el in content.find_all(["h2", "a"]):
        if el.name == "h2":
            current_category = slugify(el.get_text(" ", strip=True)) or "uncategorized"
        elif el.name == "a":
            href = el.get("href", "")
            match = re.search(r"/problemset/task/(\d+)/?", href)
            if not match:
                continue

            task_id = match.group(1)
            if task_id in seen_ids:
                continue

            # Check whether this task entry has the green full-score icon
            parent = el.parent
            is_solved = bool(
                el.find("span", class_="full")
                or (parent and parent.find("span", class_="full"))
            )
            if not is_solved:
                continue

            # Remove trailing icon text if any, keeping clean problem title
            title_parts = [t for t in el.stripped_strings]
            title = title_parts[0] if title_parts else f"task_{task_id}"

            seen_ids.add(task_id)
            tasks.append({
                "id": task_id,
                "title": title,
                "category": current_category,
                "url": urljoin(BASE_URL, href),
            })

    return tasks


def get_latest_accepted_result_url(session: requests.Session, task_url: str) -> str | None:
    resp = session.get(task_url, timeout=15)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, "html.parser")

    accepted_subs = []
    for a in soup.find_all("a", href=True):
        href = a["href"]
        match = re.search(r"/problemset/result/(\d+)/?", href)
        if not match:
            continue

        # Only keep submissions with the green accepted/full-score icon
        if a.find("span", class_="full"):
            result_id = int(match.group(1))
            text = a.get_text(" ", strip=True)
            # Extract timestamp string (YYYY-MM-DD HH:MM:SS) if present for reliable sorting
            ts_match = re.search(r"\d{4}-\d{2}-\d{2}\s+\d{2}:\d{2}:\d{2}", text)
            timestamp = ts_match.group(0) if ts_match else ""
            accepted_subs.append((timestamp, result_id, urljoin(BASE_URL, href)))

    if not accepted_subs:
        return None

    # Sort by timestamp first, then result_id descending to pick the latest accepted run
    accepted_subs.sort(key=lambda x: (x[0], x[1]), reverse=True)
    return accepted_subs[0][2]


def detect_extension(soup: BeautifulSoup) -> str:
    table = soup.find("table", class_="summary-table")
    if table:
        for row in table.find_all("tr"):
            cells = [c.get_text(" ", strip=True) for c in row.find_all(["th", "td"])]
            if len(cells) >= 2 and cells[0].lower().startswith("language"):
                lang = cells[1].lower()
                if "python" in lang or "pypy" in lang:
                    return ".py"
                if "java" in lang:
                    return ".java"
                if "rust" in lang:
                    return ".rs"
                if "c++" in lang or "gcc" in lang or "clang" in lang:
                    return ".cpp"
                if lang.startswith("c ") or lang == "c":
                    return ".c"
    return ".cpp"


def fetch_code_from_result(session: requests.Session, result_url: str) -> tuple[str | None, str]:
    resp = session.get(result_url, timeout=15)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, "html.parser")

    ext = detect_extension(soup)
    pre = soup.find("pre", class_="prettyprint") or soup.find("pre")
    if not pre:
        return None, ext

    # CSES renders each line inside <div class="L0">, <div class="L1">, ... inside div.linenums
    line_divs = pre.select("div.linenums > div")
    if line_divs:
        lines = [div.get_text() for div in line_divs]
        code = "\n".join(lines)
    else:
        code = pre.get_text()

    code = code.replace("\r\n", "\n")
    if not code.endswith("\n"):
        code += "\n"
    return code, ext


def main():
    username = input("CSES Username: ").strip()
    password = getpass.getpass("CSES Password: ")

    out_dir = Path("cses_solutions")
    out_dir.mkdir(exist_ok=True)

    session = login(username, password)
    print("Logged in successfully. Fetching problem list...")

    tasks = get_solved_tasks(session)
    print(f"Found {len(tasks)} solved problems.")

    saved = 0
    for idx, task in enumerate(tasks, start=1):
        try:
            result_url = get_latest_accepted_result_url(session, task["url"])
            if not result_url:
                print(f"[{idx}/{len(tasks)}] SKIP {task['id']} ({task['title']}): no accepted result link found")
                continue

            code, ext = fetch_code_from_result(session, result_url)
            if not code:
                print(f"[{idx}/{len(tasks)}] SKIP {task['id']} ({task['title']}): code block missing")
                continue

            category_dir = out_dir / task["category"]
            category_dir.mkdir(parents=True, exist_ok=True)

            filepath = category_dir / f"{task['id']}_{slugify(task['title'])}{ext}"
            filepath.write_text(code, encoding="utf-8")
            saved += 1
            print(f"[{idx}/{len(tasks)}] SAVED -> {filepath}")

            # Polite delay so we don't overload CSES servers (~2 requests per problem)
            time.sleep(0.5)
        except Exception as exc:
            print(f"[{idx}/{len(tasks)}] ERROR on {task['id']} ({task['title']}): {exc}")

    print(f"\nFinished! Saved {saved}/{len(tasks)} solutions inside {out_dir.resolve()}")


if __name__ == "__main__":
    main()