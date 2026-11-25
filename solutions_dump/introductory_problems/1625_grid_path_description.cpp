#include <bits/stdc++.h>
using namespace std;
#define ll long long 
 
bool v[7][7];
string r;
int ans=0;
 
#define act(x,y) (x>=0&&x<=6&&y>=0&&y<=6&&!v[x][y])
#define anc(x,y) (act(x-1,y)+act(x+1,y)+act(x,y-1)+act(x,y+1))
#define dcc(x,y) (!act(x,y) || (x==6&&y==0) || anc(x,y)>1)
#define scs(x,y) (dcc(x-1,y-1) && dcc(x+1,y-1) && dcc(x-1,y+1) && dcc(x+1,y+1))
#define tcs(x,y) !(((!act(x-1,y))&&(!act(x+1,y))&&(act(x,y-1))&&(act(x,y+1)))||((act(x-1,y))&&(act(x+1,y))&&(!act(x,y-1))&&(!act(x,y+1))))
// These are all the cases
void dfs(int x, int y, int s)
{
    // 4th case
    if (x==6 && y==0)
    {
        if (s==48){ans++;}
        return;
    }
    // 3rd case
    if (!tcs(x,y)){return;}
    // 2nd case
    if (!scs(x,y)){return;}
    v[x][y]=1;
    // U D L R
    if (act(x-1,y)&&(r[s]=='U'||r[s]=='?')){dfs(x-1,y,s+1);}
    if (act(x+1,y)&&(r[s]=='D'||r[s]=='?')){dfs(x+1,y,s+1);}
    if (act(x,y-1)&&(r[s]=='L'||r[s]=='?')){dfs(x,y-1,s+1);}
    if (act(x,y+1)&&(r[s]=='R'||r[s]=='?')){dfs(x,y+1,s+1);}
 
    v[x][y]=0;
}
 
int main()
{
    cin>>r;
    dfs (0,0,0);
    cout << ans << endl;
    return 0;
}
