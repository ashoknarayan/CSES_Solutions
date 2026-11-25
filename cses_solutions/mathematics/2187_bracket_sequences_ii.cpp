#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define MOD 1000000007

int exp(int b, int e)
{
    if(e==0) return 1;
    int res=exp(b,e/2);
    res = (res*res)%MOD;
    if (e%2==1) return (res*b)%MOD;
    return res;
}

//! Convoluted Catalan Sequence
// https://codeforces.com/blog/entry/87585

signed main()
{
    int l; cin>>l;
    string s; cin>>s;
    int k=0;
    for(char x:s)
    {
        if (x=='(') ++k;
        if (x==')') --k;
        if (k<0){cout << 0 << endl; return 0;}
        // This is important at any point if k is -ve then there is no solution
    }
    int n = (l-s.size()-k);
    if (n%2==1 || n<0){cout << 0 << endl; return 0;} n/=2;


    // Now it is just the convoluted catalan! Lets go
    int f[2*n+k+1]; f[0]=1;
    for (int i=1; i<=2*n+k; ++i)
        f[i] = (f[i-1]*i)%MOD;

    int ans = (k+1);
    ans*= exp(n+k+1, MOD-2);    ans%=MOD;
    ans*= f[2*n+k];             ans%=MOD;
    ans*= exp(f[n], MOD-2);     ans%=MOD;
    ans*= exp(f[n+k], MOD-2);   ans%=MOD;
    cout << ans << endl;
    return 0;
}

/*
Spme analysis
Concoluted catalan sequence formula is to form 2*(n+k) length bracket sequences where the first k of them are
open braces. For this the formula is, [(k+1)/(n+k+1)] * [(2n+k)C(n)]
Now we need to convert the given problem to this format.
We can do k = "(" - in prefix - ")"- int prefix
and n = ((total len - s.size())-k)/2

now if k is -ve -- no ans
if n-k%2==1 no ans
n-k <0 no ans

then the formula !
super !

*/
