#include <bits/stdc++.h>
using namespace std;
const int N = 500;
 
char a[N][N];
long long res[26];
bool h[N];
 
 
int main(){
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];
    }
 
    for (int t = 0; t < n; ++t){
        fill(h, h + n, 1);
        for (int b = t; b < n; ++b){
            for (int i = 0; i < n; ++i)
                if (a[b][i] != a[t][i]) h[i] = 0;
 
            int cnt = 0;
            for (int i = 0; i < n; ++i){
                if ((i && a[b][i] != a[b][i - 1]) || a[t][i] != a[b][i]) cnt = 0;
                if (h[i]) ++cnt, res[a[b][i] - 'A'] += cnt;
            }
        }
    }
 
    for (int i = 0; i < k; ++i)
        cout << res[i] << '\n';

    return 0;
}
