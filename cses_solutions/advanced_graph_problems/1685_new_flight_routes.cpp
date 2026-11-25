#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
 
#include <stdio.h>
 
#define N 200001
 
static inline int getint() {
    int x, y;
    while((x = getchar_unlocked()) < '0') {}
    x -= '0';
    while((y = getchar_unlocked()) >= '0') { x = x * 10 + y - '0'; }
    return x;
}
 
static inline void putint(int x) {
    char s[10];
    short i = 0;
    if(x == 0) {
        putchar_unlocked('0');
        return;
    }
    while(x) {
        s[i++] = (x % 10) + '0';
        x /= 10;
    }
    while(i--) {
        putchar_unlocked(s[i]);
    }
}
 
static inline int min(int a, int b) {
    return a < b ? a : b;
}
 
static inline int max(int a, int b) {
    return a > b ? a : b;
}
 
void solve() {
    static int p[N], e[N], ne[N];
 
    static int index[N], lowlink[N], parent[N], next[N], cs[N];
    int csp = 0;
    // cs = component stack for Tarjan SCC
 
    static int scc[N], sp[N], se[N], sne[N], sid[N], sv[N];
    // scc = component of node
    // sp, se, sne describe edges between components
    // sid = component in-degree, sv = component visited
    static int sr[N]; // sr = component representative node
 
    static int cn[N], ei[N], eo[N];
    int ncn = 0, nei = 0, neo = 0;
 
    int n = getint(), m = getint();
 
    // Read edges
    for(int j = 1; j <= m; j++) {
        int a = getint(), b = getint();
 
        e[j] = b;
        ne[j] = p[a];
        p[a] = j;
    }
 
    // Tarjan SCC
    int c = 0;
    for(int i = 1; i <= n; i++) {
        if(!index[i]) {
            int v = i, l = 1;
            parent[v] = -1;
            while(v != - 1) {
                if(!index[v]) {
                    lowlink[v] = index[v] = l++;
                    next[v] = p[v];
                    cs[++csp] = v;
                }
 
                if(next[v]) {
                    int k = next[v];
                    next[v] = ne[k];
 
                    int w = e[k];
                    if(!index[w]) {
                        parent[w] = v;
                        v = w;
                    } else if(parent[w]) {
                        // w is on stack
                        lowlink[v] = min(lowlink[v], lowlink[w]);
                    }
                } else {
                    int pv = parent[v];
 
                    if(lowlink[v] == index[v]) {
                        // SCC root node found
                        c++;
                        int f;
                        do {
                            f = cs[csp--];
                            scc[f] = c;
                            sr[c] = f;
                            parent[f] = 0;
                        } while(f != v);
                    }
 
                    if(pv > 0) {
                        lowlink[pv] = min(lowlink[v], lowlink[pv]);
                    }
                    v = pv;
                }
            }
            parent[i] = 0;
        }
    }
 
    // One component found
    if(c == 1) {
        puts("0");
        return;
    }
 
    // Form DAG from components
    int sj = 1;
    for(int a = 1; a <= n; a++) {
        for(int j = p[a]; j; j = ne[j]) {
            int b = e[j];
 
            int sa = scc[a], sb = scc[b];
 
            if(sa != sb) {
                se[sj] = sb;
                sne[sj] = sp[sa];
                sp[sa] = sj;
                sid[sb]++;
                sj++;
            }
        }
    }
 
    // Classify nodes as cycle / ear
    for(int i = 1; i <= c; i++) {
        if(sid[i] == 0) {
            int v = i;
            int ft = 0; // found terminal
            next[v] = sp[v];
            parent[v] = -1;
            sv[v] = 1;
            while(v != -1) {
                if(sp[v] == 0) {
                    // Terminal node
                    if(ft) {
                        eo[neo++] = sr[v]; // Ear out
                    } else {
                        cn[ncn++] = sr[i];
                        cn[ncn++] = sr[v];
                        ft = 1;
                    }
                }
 
                if(next[v]) {
                    int k = next[v];
                    next[v] = sne[k];
 
                    int w = se[k];
                    if(!sv[w]) {
                        if(ft && sid[w] > 1) {
                            // When searching for the first terminal node (ft==0) we always follow edges.
                            // when searching for subsequent terminal nodes, we need to make sure the node
                            // is not reachable by some other path, otherwise we may incorrectly classify
                            // it as an ear-out node when it needs to be a cycle node.
                            sid[w]--;
                        } else {
                            parent[w] = v;
                            next[w] = sp[w];
                            sv[w] = 1;
                            v = w;
                        }
                    }
                } else {
                    int pv = parent[v];
                    v = pv;
                }
            }
            if(!ft) {
                ei[nei++] = sr[i];
            }
        }
    }
 
    // Output edges
    putint(ncn / 2 + max(neo, nei));
    putchar_unlocked('\n');
 
    cn[ncn] = cn[0];
    for(int i = 1; i <= ncn; i += 2) {
        putint(cn[i]);
        putchar_unlocked(' ');
        putint(cn[i + 1]);
        putchar_unlocked('\n');
    }
 
    while(nei < neo) {
        ei[nei++] = cn[0];
    }
 
    while(neo < nei) {
        eo[neo++] = cn[0];
    }
 
    for(int i = 0; i < nei; i++) {
        putint(eo[i]);
        putchar_unlocked(' ');
        putint(ei[i]);
        putchar_unlocked('\n');
    }
}
 
int main() {
    solve();
}
