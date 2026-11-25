#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
#define endl '\n'
 
template <typename T>
using seto = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;



int find(int n, int k)
{
    if (n==1){return 1;}
    if (2*k <= (n+1))
    {
        // I want to reduce the odd -> even 
        // So I have to consider the 1 that comes after all even numbers in round 1 
        // Thus,
        if (2*k == n+1){return 1;}
        return (2*k);
        // |^| Automatically executed only when Else 
    }
    // There has been no return untill now ! 
    // Call the function again and whatever you get
        // Give the 2*n + 1 for Odd  value 
        // Give the 2*n - 1 for Even value

    int t = find((n/2) , (k-(n+1)/2));

    if (n%2==0){return 2*t - 1;}
    if (n%2==1){return 2*t + 1;}
    // I tried this again by myself
    // Let's see how this goes !

}
 
signed main()
{
    // Learnt from CoWo
    // https://www.youtube.com/watch?v=lIr78Tj1qww

    int q; cin>>q;
    while(q--)
    {
        // Process each query in logn time !
        int n,k; cin>>n>>k;
        // Use the recursion alg !
        cout << find(n,k) << endl;
    }

}
