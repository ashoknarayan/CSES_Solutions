#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

class DSU { // Got this from Codenzyme
    private:
        vector<int> p,rank,setSize;
        int numSets;
        int mx; // NEWLY FOR THIS TASK
    public:
        DSU(int n) {
            p.assign(n,0);
            for (int i = 0; i < n; i++) {
                p[i] = i;
            }
            rank.assign(n,0); // height of all trees are 0.
            setSize.assign(n,1); // size of individual sets are 1
            numSets = n;
            mx=1; // INITIAL VALUE
        }

        int find(int x) {
            if (p[x]==x) return x;
            return p[x] = find(p[x]); // path compression
        }

        bool same(int x, int y) {return find(x)==find(y);}

        void merge(int i, int j) {
            if (same(i,j)) return;
            int x = find(i);
            int y = find(j);
            if (rank[x]>rank[y]) swap(x,y);
            p[x] = y;
            if (rank[x]==rank[y]) rank[y]++;
            setSize[y] += setSize[x];
            mx = max(mx,setSize[y]); // <- mx gets modified
            numSets--;

        }

        int size(int x) {
            return setSize[x];
        }

        int setcount() {
            return numSets;
        }

        int maxset(){       // ONLY FOR THIS TASK
            return mx;
        }
};

// Spanning Trees
signed main()
{
    // Directly a implication of DSU.
    // So I have used the template
    int n,m;
    cin>>n>>m;
    DSU d(n);
    //
    int a,b;
    for (int i=0; i<m; ++i)
    {
        cin>>a>>b;
        d.merge(--a,--b);
        cout << d.setcount() << " " << d.maxset() << endl;
    }

}
