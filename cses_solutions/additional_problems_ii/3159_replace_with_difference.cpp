#include "bits/stdc++.h"
using namespace std;

const int N = 50001, M = N/2;
bitset<N> dp[1001];
int a[1001];
unsigned char is_add[1001];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if(!(cin >> n)) return 0;
    for(int i = 0; i < n; ++i) cin >> a[i];

    // optional shuffle (commented out for speed; uncomment if you need randomness)
    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // shuffle(a, a + n, rng);

    dp[0].reset();
    dp[0][M] = 1;
    for(int i = 0; i < n; ++i) dp[i + 1] = (dp[i] >> a[i]) | (dp[i] << a[i]);

    if(!dp[n][M]) { cout << -1 << '\n'; return 0; }

    int s = M;
    for(int i = n; i > 0; --i){
        int val = a[i-1];
        if (s >= val && dp[i-1][s - val]) s -= val;
        else { s += val; is_add[i-1] = 1; }
    }

    vector<int> add, sub;
    add.reserve(n); sub.reserve(n);
    for(int i = 0; i < n; ++i) (is_add[i] ? add : sub).push_back(a[i]);

    // sanity: accepted code assumed both non-empty
    if(add.empty() || sub.empty()){ cout << -1 << '\n'; return 0; }

    cout << add.back() << ' ' << sub.back() << '\n';
    int cur = add.back() - sub.back();
    add.pop_back(); sub.pop_back();

    while(!add.empty() || !sub.empty()){
        if(cur >= 0 && !sub.empty()){
            cout << abs(cur) << ' ' << sub.back() << '\n';
            cur -= sub.back(); sub.pop_back();
        } else {
            cout << abs(cur) << ' ' << add.back() << '\n';
            cur += add.back(); add.pop_back();
        }
    }
    return 0;
}
