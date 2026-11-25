#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
#define endl "\n"
#define int  long long
#define fio ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)

signed main() 
{
    // This was solved by whatsapp AI.
    // I do not have any rights to claim this as my idea
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        int dx1 = x2 - x1;
        int dy1 = y2 - y1;
        int dx2 = x3 - x1;
        int dy2 = y3 - y1;
        int cross_product = dx1 * dy2 - dx2 * dy1;
        if (cross_product > 0) {
            cout << "LEFT" << endl;
        } else if (cross_product < 0) {
            cout << "RIGHT" << endl;
        } else {
            cout << "TOUCH" << endl;
        }
    }
    return 0;
}
