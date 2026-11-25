#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

const int mxN = 1e6+6;

vector<int> dp = {0, 0, 0};
int mex(vector<int> v) {
    set<int> s;
    for (auto i: v)
        s.insert(i);
    for (int i = 0; i < mxN; i++) {
        if (s.count(i) == 0) return i;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int t; cin>>t;
    for (int i = 3; i < 2000; i++) {
        vector<int> v;
        for (int j = 1; i-j > j; j++) {
            v.push_back(dp[j]^dp[i-j]);
        }
        dp.push_back(mex(v));
    }
    while(t--) {
        int n; cin>>n;
        if (n >= 2000) cout<<"first"<<endl;
        else cout<< (dp[n] > 0 ? "first" : "second")<<endl;
    }
}



/*
Just submitting for closing the stuff.
Total 4 submissions like this where I just am closing it

those are
1. Grundy game
2. Coprime pairs
3. Divisor Analysis
4. Prime multiples

These are just submitted for referenec while I did nto understand much

also Inversion prob was done with a jugaad which is not acceptable

and nim game 1,2
another game  -> For these I just learnt the formula

And maths section is going to be closed.

Will revise these properly. But for now this is enough !

*/
/*!
Further plan
Today -> 20-09-2024 - Mathematics over
Sat & Sunday -> Finish Graphs
Next week complete Range Queries and Trees
May change the plan too
*/
