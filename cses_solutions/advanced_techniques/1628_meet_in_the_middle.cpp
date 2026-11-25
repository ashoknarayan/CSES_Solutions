#include <bits/stdc++.h>
using namespace std;
#define int         long long
#define endl        '\n'
#define loop(i,n)   for(int i=0; i<n; ++i)
void solve();signed main(){ios::sync_with_stdio(false); cin.tie(NULL);int t = 1;
    //cin >> t;
    while (t--) solve();return 0;}
//////////////////////////////////////////////////////////
void solve()
{
    int n; cin >> n;
    int x; cin >> x;
    vector<int> a(n);
    loop(i, n) cin >> a[i];

    // Split the array into two halves
    int mid = n / 2;
    vector<int> left(a.begin(), a.begin() + mid);
    vector<int> right(a.begin() + mid, a.end());

    // Function to generate all subset sums
    auto generateSubsetSums = [](const vector<int>& arr) {
        vector<int> sums;
        int size = arr.size();
        for (int i = 0; i < (1 << size); ++i) {
            int sum = 0;
            for (int j = 0; j < size; ++j) {
                if (i & (1 << j)) sum += arr[j];
            }
            sums.push_back(sum);
        }
        return sums;
    };

    // Generate subset sums for both halves
    vector<int> leftSums = generateSubsetSums(left);
    vector<int> rightSums = generateSubsetSums(right);

    // Sort the right half sums for binary search
    sort(rightSums.begin(), rightSums.end());

    // Count the number of pairs (from leftSums and rightSums) that sum to x
    int ans = 0;
    for (int sum : leftSums) {
        int target = x - sum;
        ans += upper_bound(rightSums.begin(), rightSums.end(), target) -
               lower_bound(rightSums.begin(), rightSums.end(), target);
    }

    cout << ans << endl;
}

