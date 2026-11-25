#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
constexpr int N = 100001;
 
int rt[N], sz[N], a[N * 2]; 
array<int, 3> e[N * 2];
 
int root(int x){
    while(x != rt[x]){
        x = rt[x] = rt[rt[x]];
    }
    return x;
}
bool connected(int x, int y){
    return root(x) == root(y);
}
void connect(int x, int y){
    x = root(x), y = root(y);
    if(x == y) return;
    if(sz[x] > sz[y]) swap(x, y);
    sz[y] += sz[x];
    rt[x] = y;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int n, m, q;
    cin >> n >> m >> q;
    for(int i = 0; i < m; ++i){
        cin >> e[i][1] >> e[i][2] >> e[i][0];
        a[i] = i;
    }
    iota(rt, rt + n + 1, 0);
    fill(sz, sz + n + 1, 1);
    sort(a, a + m, [](int x, int y){
        return e[x][0] < e[y][0];
    });
    for(int l = 0, r = 0; l < m; ++l){
        while(r < m && e[a[r]][0] == e[a[l]][0]){
            e[a[r]][1] = root(e[a[r]][1]);
            e[a[r]][2] = root(e[a[r]][2]);
            ++r;
        }
        connect(e[a[l]][1], e[a[l]][2]);
    }
    iota(rt, rt + n + 1, 0);
    fill(sz, sz + n + 1, 1);
    while(q--){
        int k;
        cin >> k;
        for(int i = 0; i < k; ++i){
            cin >> a[i];
            --a[i];
        }
        sort(a, a + k, [](int x, int y){
            return e[x][0] < e[y][0];
        });
        bool ok = 1;
        for(int l = 0, r = 0; l < k;){
            while(r < k && e[a[r]][0] == e[a[l]][0]){
                ok &= !connected(e[a[r]][1], e[a[r]][2]);
                connect(e[a[r]][1], e[a[r]][2]);
                ++r;
            }
            r = l;
            while(r < k && e[a[r]][0] == e[a[l]][0]){
                rt[e[a[r]][1]] = e[a[r]][1];
                rt[e[a[r]][2]] = e[a[r]][2];
                sz[e[a[r]][1]] = sz[e[a[r]][2]] = 1;
                ++r;
            }
            l = r;
        }
        if(ok) cout << "YES\n";
        else cout << "NO\n";
    }
}
