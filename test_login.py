import getpass
import requests
from bs4 import BeautifulSoup

LOGIN_URL = "https://cses.fi/login"
LIST_URL = "https://cses.fi/problemset/list/"


def main():
    username = input("CSES Username: ").strip()
    password = getpass.getpass("CSES Password: ")

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
    print("Fetched csrf_token:", csrf_token[:12] + "..." if csrf_token else "MISSING")

    payload = {
        "csrf_token": csrf_token,
        "nick": username,
        "pass": password,
    }
    post_resp = session.post(LOGIN_URL, data=payload, timeout=15, allow_redirects=True)
    print("After POST -> URL:", post_resp.url, "Status:", post_resp.status_code)

    post_soup = BeautifulSoup(post_resp.text, "html.parser")
    title = post_soup.find("title")
    print("Page title after POST:", title.get_text(strip=True) if title else "None")

    # Check for any error message on the page
    for p in post_soup.find_all(["p", "div", "span"]):
        txt = p.get_text(" ", strip=True)
        if any(w in txt.lower() for w in ["incorrect", "invalid", "wrong", "error", "failed"]):
            if len(txt) < 160:
                print("Possible message:", txt)

    check_resp = session.get(LIST_URL, timeout=15)
    print("Cookies in session:", session.cookies.get_dict())
    print("Final URL for problemset list:", check_resp.url)


if __name__ == "__main__":
    main()