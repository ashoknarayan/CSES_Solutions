#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")
#include<bits/stdc++.h>
using namespace std;
constexpr int MAXN = 1e5, MAXM = 2e5, BUF_SIZE = 1 << 24, INF = 3e5;
struct Edge{
unsigned to;
unsigned nxt;
};
static alignas(64) Edge edges[2 * MAXM + 5];
static alignas(64) unsigned head[MAXN + 5];
static alignas(64) unsigned source[MAXN + 5], highlighted[MAXN + 5];
static int ans[MAXN + 5];
static char input[BUF_SIZE], output[BUF_SIZE], s[10];
static unsigned q[MAXN + 5];
static unsigned n, m, k, input_idx, output_idx, ecnt, q_head, q_tail;
static void multiSourceBfs(){
while(q_head < q_tail){
unsigned u = q[q_head++];
for(unsigned e = head[u]; e; e = edges[e].nxt){
unsigned v = edges[e].to;
if(ans[v] == -1){
 ans[v] = (u == source[u] ? 1 : ans[u] + 1);
 source[v] = source[u];
 q[q_tail++] = v;
}
else if(source[u] != source[v]){
int source_dist = (u == source[u] ? 0 : ans[u]) + (v == source[v] ? 0 : ans[v]) + 1;
 ans[source[u]] = min(ans[source[u]], source_dist);
 ans[source[v]] = min(ans[source[v]], source_dist);
}
}
}
for(unsigned i = 0; i < k; ++i){
if(ans[highlighted[i]] == INF) ans[highlighted[i]] = -1;
}
}
static inline int getint(){
unsigned x, y;
while((x = input[input_idx++]) < '0') {}
 x -= '0';
while((y = input[input_idx++]) >= '0') { x = x * 10 + y - '0'; }
return x;
}
static inline void putint(int num){
if(num == -1){
 output[output_idx++] = '-';
 output[output_idx++] = '1';
}
else{
unsigned i = 0;
while(num){
 s[i++] = (num % 10) + '0';
 num /= 10;
}
while(i--) output[output_idx++] = s[i];
}
 output[output_idx++] = ' ';
}
int main(){
 fread(input, 1, BUF_SIZE, stdin);
 n = getint(), m = getint(), k = getint();
for(unsigned i = 1; i <= n; ++i) ans[i] = -1;
for(unsigned i = 0; i < k; ++i){
 highlighted[i] = getint();
 q[q_tail++] = highlighted[i];
 ans[highlighted[i]] = INF;
 source[highlighted[i]] = highlighted[i];
}
while(m--){
unsigned u = getint(), v = getint();
 edges[++ecnt] = {v, head[u]};
 head[u] = ecnt;
 edges[++ecnt] = {u, head[v]};
 head[v] = ecnt;
}
 multiSourceBfs();
for(unsigned i = 1; i <= n; ++i) putint(ans[i]);
 fwrite(output, 1, output_idx, stdout);
return 0;

}
