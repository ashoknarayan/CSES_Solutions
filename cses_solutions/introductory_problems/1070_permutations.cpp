#include <bits/stdc++.h>
using namespace std;
#define loop(i,a,b,s) for (int i=a; i<b; i+=s)
#define endl "\n"
typedef long long ll;
const ll MOD = 1e9+7;

int main()
{
    int n; cin>>n;
    if (n==4){cout << "2 4 1 3";}
    else if (n==1){cout << "1";}
    else if (n>4)
    { 
        loop(i,1,n+1,2){cout << i << " ";}
        loop(i,2,n+1,2){cout << i << " ";}
    }
    else {cout << "NO SOLUTION";}
    return 0;
}
