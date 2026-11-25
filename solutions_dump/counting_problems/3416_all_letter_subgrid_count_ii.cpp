#include <bits/stdc++.h>
using namespace std;
#pragma GCC target "avx,avx2"
#pragma GCC optimize "Ofast"
 
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef complex<double> cpx;
template <typename T> using minPq = priority_queue<T, vector<T>, greater<T>>;
#define ms(a, x) memset(a, x, sizeof(a))
#define pb push_back
#define fs first
#define sn second
#define ALL(v) begin(v), end(v)
#define SZ(v) ((int) (v).size())
#define lbv(v, x) (lower_bound(ALL(v), x) - (v).begin())
#define ubv(v, x) (upper_bound(ALL(v), x) - (v).begin())
template <typename T> inline void UNIQUE(vector<T> &v){sort(ALL(v)); v.resize(unique(ALL(v)) - v.begin());}
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1);
#define FR(i, n) for(int i = 0; i < (n); i++)
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORR(i, a, b) for(int i = (a); i >= (b); i--)
#define dbg(x) {cerr << #x << ' ' << x << endl;}
#define dbgArr(arr, n) {cerr << #arr; FR(_i, n) cerr << ' ' << (arr)[_i]; cerr << endl;}
template <typename T, typename U>
ostream& operator<<(ostream &os, pair<T, U> p){return os << "(" << p.fs << ", " << p.sn << ")";}
 
const int MN = 505;
const int MZ = 32;
int n, z;
string grid[MN];
short mnU[MN][MZ];
short curMn[MZ];
ll ans;
 
ll f(int row, int l){
    ll res = 0;
    ms(curMn, INF);
    FOR(r, l, n){
        FR(k, MZ) curMn[k] = min(curMn[k], mnU[r][k]);
        short mx = 0x8000;
        FR(k, MZ) mx = max(mx, curMn[k]);
        res += mx;
    }
    return (row+1)*(n-l) - res;
}
 
int main(){
    cin.sync_with_stdio(0); cin.tie(0);
    cin >> n >> z;
 
    FR(i, n){
        cin >> grid[i];
        for(char &ch : grid[i]) ch -= 'A';
    }
 
    FR(i, n){
        FR(j, n){
            FR(k, z) mnU[j][k]++;
            mnU[j][grid[i][j]] = 0;
        }
        FR(l, n) ans += f(i, l);
    }
 
    cout << ans << '\n';
}
