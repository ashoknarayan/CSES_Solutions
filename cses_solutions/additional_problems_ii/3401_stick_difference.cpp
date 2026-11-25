#include <cstdio>
#include <algorithm>
static char in[1<<22],out[1<<23];static int ip,op,a[100001],parts[100001],lower[200001],when[200002],upper[200002],capMin[200002],dq[200002],n;
struct Node{int key,id;};static Node h[100001];
int read(){while(in[ip]<=' ')++ip;int x=0;while(in[ip]>='0')x=x*10+in[ip++]-'0';return x;}
void write(int x){char b[12];int k=0;do{b[k++]='0'+x%10;x/=10;}while(x);while(k)out[op++]=b[--k];out[op++]=' ';}
void down(int u,Node x){int v;while((v=2*u)<=n){if(v<n&&h[v+1].key>h[v].key)++v;if(h[v].key<=x.key)break;h[u]=h[v];u=v;}h[u]=x;}
int main(){fread(in,1,sizeof(in),stdin);n=read();int m=read(),small=1000000000;for(int i=1;i<=n;i++){a[i]=read();small=std::min(small,a[i]);parts[i]=1;h[i]={a[i]/2,i};}for(int i=n/2;i;i--)down(i,h[i]);int L=small;for(int k=1;k<=m;k++){int id=h[1].id;L=std::min(L,h[1].key);lower[k]=L;++parts[id];down(1,{a[id]/(parts[id]+1),id});}
for(int i=1;i<=n;i++){parts[i]=1;h[i]={a[i],i};}for(int i=n/2;i;i--)down(i,h[i]);long long total=n;int mn=small,c=0;for(;;){when[c]=int(total-n);upper[c]=h[1].key;capMin[c++]=mn;if(h[1].key==1)break;int bound=h[1].key-1;while(h[1].key>bound){int id=h[1].id,q=(a[id]+bound-1)/bound;total+=q-parts[id];parts[id]=q;mn=std::min(mn,a[id]/q);down(1,{(a[id]+q-1)/q,id});if(total>n+m)break;}if(total>n+m)break;}
int active=-1,boundary=0,front=0,back=0;for(int k=1;k<=m;k++){while(active+1<c&&when[active+1]<=k){++active;int d=upper[active]-capMin[active];while(front<back&&upper[dq[back-1]]-capMin[dq[back-1]]>=d)--back;dq[back++]=active;}int x=lower[k];while(boundary<=active&&capMin[boundary]>x)++boundary;while(front<back&&dq[front]<boundary)++front;int ans=1000000000;if(front<back)ans=upper[dq[front]]-capMin[dq[front]];if(boundary)ans=std::min(ans,upper[boundary-1]-x);write(ans);}fwrite(out,1,op,stdout);}

