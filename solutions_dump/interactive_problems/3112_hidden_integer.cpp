#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define endl '\n'

void solve(){
	int l,m,r; string res;
	l = 0; r = 1e9+1;
	while(l<r){
		m = (l+r)/2;
		cout << "? " << m << endl; cin >> res;
		if (res == "YES") l = m+1;
		else r = m;
	}
	cout <<"! " << r << endl;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); int t = 1;
	//	cin >> t;
	while(t--) solve();
}
