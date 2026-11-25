#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,e,j; cin>>n;
    vector<int> a;
    for(int i=0; i<n; ++i){
        cin>>e;
        j=lower_bound(a.begin(), a.end(), e)-a.begin();
        if (j==a.size()) a.push_back(e);
        else a[j]=e;
    }
    cout << a.size() << endl;
}
