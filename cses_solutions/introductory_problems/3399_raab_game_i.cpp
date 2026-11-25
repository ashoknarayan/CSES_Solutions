#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

void solve(){
	int n,a,b; cin>>n>>a>>b;
	if ((a==0 && b!=0) || (a!=0 && b==0) || (a+b > n)){
		cout << "NO" << endl;
		return;
	}
	cout << "YES\n";
	for(int i=n; i>=1; --i){
		cout << i << ' ';
	}
	cout << endl;
	for (int i=n; i>a+b; --i){
		cout << i << ' ';
	}
	n = a+b;
	for (int i=a; i>=1; --i){
		cout << i << ' ';
	}
	for (int i=n; i>a; --i){
		cout << i << ' ';
	}
	cout << endl;
	return;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); int t=1;
	 cin>>t; 
	while(t--) solve();
	return 0;
}
