import sys

# It's good practice to increase the recursion limit for deep graphs in Python.
sys.setrecursionlimit(200000)

def solve():
    try:
        n, m = map(int, input().split())
    except (IOError, ValueError):
        return

    # adj will be our graph's adjacency list
    # adj[u] -> [(v, weight), ...]
    adj = [[] for _ in range(n + 1)]

    for _ in range(m):
        l, r, s = map(int, input().split())
        # Add edges for the constraint p[r] - p[l-1] = s
        # Edge from l-1 to r with weight s
        adj[l - 1].append((r, s))
        # Edge from r to l-1 with weight -s
        adj[r].append((l - 1, -s))

    # p will store prefix sums. None means unvisited.
    p = [None] * (n + 1)
    # This flag will be set to False if a contradiction is found.
    possible = True

    def dfs(u):
        nonlocal possible
        # Check all neighbors of the current node u
        for v, weight in adj[u]:
            if not possible:
                return

            if p[v] is None:
                # If v is unvisited, set its value and recurse
                p[v] = p[u] + weight
                dfs(v)
            elif p[v] != p[u] + weight:
                # If v is visited, check for contradiction
                possible = False
                return

    # Iterate through all potential nodes (0 to n)
    for i in range(n + 1):
        if not possible:
            break
        if p[i] is None:
            # If a node is part of an unvisited component,
            # anchor the component by setting p[i] = 0 and start DFS.
            p[i] = 0
            dfs(i)

    if not possible:
        print("NO")
    else:
        print("YES")
        # Construct x from p: x_i = p_i - p_{i-1}
        result = [p[i] - p[i - 1] for i in range(1, n + 1)]
        print(*result)

solve()
