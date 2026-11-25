// legrende's 3 sq thm based
// Lagrange's 4 sq thm
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pii pair<int,int>
#define vvi vector<vector<int>>
using ll = long long;
vector<int> solve3(int n){
    int sq = sqrtl(n);
    for (int i = 0; i <= sq; i++)
        for (int j = 0; j <= sq; j++){
            int d1 = n-i*i-j*j;
            int sq1 = sqrtl(d1);
            if (sq1*sq1 == d1) return {sq1,i,j};
        }
    return {-1};
}
vector<int> solve(int n){
    int sq = sqrtl(n);
    if (sq*sq == n) return {sq,0,0,0};
    if (n%4 == 0){
        vector<int> v1 = solve(n/4);
        for (int i = 0; i < 4; i++)
            v1[i] *= 2;
        return v1;
    } 
    if (n%8 == 7){
        vector<int> v1 = solve3(n-4);
        v1.push_back(2);
        return v1;
    }
    vector<int> v1 = solve3(n);
    v1.push_back(0);
    return v1;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        vector<int> ans = solve(n);
        for (auto c : ans)
            cout << c << " ";
        cout << endl;
    }
    return 0;
}
