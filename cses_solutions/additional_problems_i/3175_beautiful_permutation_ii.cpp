#include <bits/stdc++.h>
using namespace std;
 
const int N = 1e6 + 10;
bool used[N];
int n, p[N];
void rec(int i, int xmin) {
    if (i == n) {
        for (int j = 0; j < n; j++) {
            cout << p[j] << " \n"[j+1==n];
        }
        exit(0);
    }
    while (used[xmin]) xmin++;
    for (int x = xmin; x <= n; x++) {
        if (used[x] || (i > 0 && abs(x-p[i-1]) <= 1)) continue;
        used[x] = 1;
        p[i] = x;
        rec(i+1, xmin);
        used[x] = 0;
    }
}
 
int main() {
    cin >> n;
    rec(0, 1);
    cout << "NO SOLUTION" << '\n';
}
