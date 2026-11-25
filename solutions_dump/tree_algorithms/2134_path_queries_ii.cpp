#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
class segtree{
    private:
        ll size;
        vector<ll> prefix;
    public:
        segtree(ll n){
            size=1;
            while(size < n) size*=2;
            prefix.assign(2*size, 0);
        }
        // set value at 1-based index
        void set_(ll val , ll index){
            ll curr = index + size - 1; // leaves are [size .. 2*size-1], index is 1-based
            prefix[curr] = val;
            curr /= 2;
            while(curr >= 1){
                prefix[curr] = max(prefix[2*curr], prefix[2*curr+1]);
                curr /= 2;
            }
        }
        // range max on inclusive 1-based indices [l, r]
        ll get_( ll l , ll r){
            if(l > r) std::swap(l, r);
            l += (size - 1);
            r += (size - 1);
            ll res = 0;
            while(l <= r){ // Updated here 
                if(l % 2 == 1){ res = max(res, prefix[l]); l++; }
                if(r % 2 == 0){ res = max(res, prefix[r]); r--; }
                l /= 2; r /= 2;
            }
            // res = max(res, prefix[l]);
            return res;
        }
};
 
ll balance( ll node, ll d1 , ll d_req , vector<vector<ll>>& ansector , vector<ll>& depth){
    if(d1 <= d_req) return node;
    ll dif = d1 - d_req;
    // apply binary lifting according to bits of dif
    for(int k = 0; k < 21; ++k){
        if(dif & (1LL << k)){
            node = ansector[node][k];
            if(node == -1) return -1;
        }
    }
    return node;
}
 
ll lca( ll a , ll b , vector<vector<ll>>& ansector , vector<ll>& depth){
    a = balance(a, depth[a], depth[b], ansector, depth);
    b = balance(b, depth[b], depth[a], ansector, depth);
    if(a == b) return a;
    for(int k = 20; k >= 0; --k){
        if(ansector[a][k] != -1 && ansector[a][k] != ansector[b][k]){
            a = ansector[a][k];
            b = ansector[b][k];
        }
    }
    return ansector[a][0];
}
 
int glo_time = 1;
vector<ll> vis;
vector<ll> counter; // global index mapping used by HLD
 
void do_dfs( vector<ll>& wt , ll node , vector<vector<ll>>& adj , int parent , vector<ll>& top){
    ll heavy_child = -1, max_size = -1;
    for(auto it : adj[node]) {
        if(it != parent && wt[it] > max_size) {
            max_size = wt[it];
            heavy_child = it;
        }
    }
    if(heavy_child != -1) {
        top[heavy_child] = top[node];
        counter[heavy_child] = glo_time++;
        do_dfs(wt, heavy_child, adj, node, top);
    }
    for(auto it : adj[node]) {
        if(it != parent && it != heavy_child) {
            top[it] = it;
            counter[it] = glo_time++;
            do_dfs(wt, it, adj, node, top);
        }
    }
}
 
void do_initiate(vector<ll>& wt , ll node , vector<vector<ll>>& adj , ll parent , vector<ll>& par , vector<ll>& depth , ll dep){
    ll sum = 0;
    par[node] = parent;
    depth[node] = dep;
    for(auto it : adj[node]){
        if(it != parent){
            do_initiate(wt, it, adj, node, par, depth, dep+1);
            sum += wt[it];
        }
    }
    sum += 1;
    wt[node] = sum;
    return;
}
 
// query max value on path from a up to node (node is ancestor of a)
ll find_val( segtree& st , ll a , ll node , vector<ll>& top , vector<ll>& counter_local , vector<ll>& parent){
    ll val = 0;
    while(top[a] != top[node]){
        ll par_top = top[a];
        val = max(val, st.get_(counter_local[a], counter_local[par_top]));
        a = parent[par_top];
    }
    val = max(val, st.get_(counter_local[a], counter_local[node]));
    return val;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t = 1;
    // If multiple testcases are required, uncomment next line:
    // cin >> t;
    while(t--){
        ll n, q;
        if(!(cin >> n >> q)) return 0;
        vector<ll> v(n+1);
        for(int i=1;i<=n;i++) cin >> v[i];
 
        vis.assign(n+1, 0);
        counter.assign(n+1, 0);
        vector<vector<ll>> adj(n+1);
        for(int i=0;i<n-1;i++){
            ll a,b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
 
        vector<ll> weight(n+1,0);
        vector<ll> depth(n+1,0);
        vector<ll> top(n+1), par(n+1);
        vector<vector<ll>> ansector(n+1, vector<ll>(21, -1));
 
        // initialize HLD ordering and sizes
        glo_time = 1;
        counter[1] = glo_time++;
        top[1] = 1;
        do_initiate(weight, 1, adj, -1, par, depth, 0);
        do_dfs(weight, 1, adj, -1, top);
 
        // build binary lifting table
        for(int i=1;i<=n;i++) ansector[i][0] = par[i];
        for(int k=1;k<21;k++){
            for(int j=1;j<=n;j++){
                int mid = ansector[j][k-1];
                ansector[j][k] = (mid == -1) ? -1 : ansector[mid][k-1];
            }
        }
 
        // build array according to HLD order (1-based indices)
        vector<ll> seq(n+1);
        for(int i=1;i<=n;i++){
            seq[counter[i]] = v[i];
        }
 
        segtree st(n);
        for(int i=1;i<=n;i++){
            st.set_(seq[i], i);
        }
 
        while(q--){
            int query;
            cin >> query;
            if(query == 1){
                ll s, x; cin >> s >> x;
                seq[counter[s]] = x;
                v[s] = x;
                st.set_(x, counter[s]);
            } else {
                ll a,b;
                cin >> a >> b;
                ll node = lca(a, b, ansector, depth);
                ll v1 = find_val(st, a, node, top, counter, par);
                ll v2 = find_val(st, b, node, top, counter, par);
                cout << max(v1, v2) << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}
