#include <iostream>
#include <vector>
#include <map>
#define ll long long
using namespace std;
 
int arr[200005];
 
int main() {
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    map<int, vector<int>> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        m[arr[i]].push_back(i);
    }
    ll res = 0;
    for (auto [k, v] : m) {
        ll cnt = 0;
        v.insert(v.begin(), -1);
        v.push_back(n);
        for (int i = 0; i < v.size()-1; i++) {
            ll d = v[i+1] - v[i];
            cnt += d*(d-1)/2;
        }
        res += n*(n+1)/2 - cnt;
    }
    cout << res << endl;
    return 0;
}
