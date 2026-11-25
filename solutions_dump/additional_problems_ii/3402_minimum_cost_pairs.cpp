#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#pragma GCC optimize("O3,unroll-loops")

struct Node {
    long long c;
    int p, n;
    bool a;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    std::sort(x.begin(), x.end());

    if (n <= 1) {
        return 0;
    }

    int m = n - 1;
    std::vector<Node> v(m);
    std::set<std::pair<long long, int>> s;

    for (int i = 0; i < m; ++i) {
        v[i].c = x[i + 1] - x[i];
        v[i].p = i - 1;
        v[i].n = i + 1;
        v[i].a = true;
        s.insert({v[i].c, i});
    }
    v[m - 1].n = -1;

    long long cost = 0;

    for (int k = 0; k < n / 2; ++k) {
        std::pair<long long, int> top;
        while (true) {
            top = *s.begin();
            s.erase(s.begin());
            if (v[top.second].a) {
                break;
            }
        }

        long long c = top.first;
        int idx = top.second;

        cost += c;
        std::cout << cost << (k == n / 2 - 1 ? "" : " ");

        v[idx].a = false;
        long long new_c = -v[idx].c;
        int p_idx = v[idx].p;
        int n_idx = v[idx].n;

        if (p_idx != -1) {
            new_c += v[p_idx].c;
            v[p_idx].a = false;
        }
        if (n_idx != -1) {
            new_c += v[n_idx].c;
            v[n_idx].a = false;
        }

        if (p_idx != -1 && n_idx != -1) {
            v[idx].c = new_c;
            v[idx].a = true;
            
            int pp_idx = v[p_idx].p;
            v[idx].p = pp_idx;
            if (pp_idx != -1) {
                v[pp_idx].n = idx;
            }

            int nn_idx = v[n_idx].n;
            v[idx].n = nn_idx;
            if (nn_idx != -1) {
                v[nn_idx].p = idx;
            }
            s.insert({v[idx].c, idx});
        } else {
            if (p_idx != -1) {
                int pp_idx = v[p_idx].p;
                if (pp_idx != -1) {
                    v[pp_idx].n = n_idx;
                }
            }
            if (n_idx != -1) {
                if (v[n_idx].n != -1) {
                    v[v[n_idx].n].p = p_idx;
                }
            }
        }
    }
    std::cout << std::endl;

    return 0;
}
