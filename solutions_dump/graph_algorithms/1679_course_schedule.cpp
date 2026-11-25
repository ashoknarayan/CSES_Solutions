#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m;
	cin >> n >> m;
	vector<int> ind(n+1, 0);
	vector<vector<int>> g(n+1);
	int a,b;
	for(int i=0; i<m; ++i){
		cin >> a >> b;
		ind[b]++;
		g[a].push_back(b);
	}
	
	vector<int> ans;
	
	queue<int> q;
	for (int i=1; i<=n; ++i)
	    if (ind[i] == 0)
		    q.push(i), ans.push_back(i);
		
    int dad;
    
	while(!q.empty()){
		dad = q.front(); q.pop();
		for(int kid : g[dad]){
			--ind[kid];
			if (ind[kid] == 0){
				ans.push_back(kid);
				q.push(kid);
			}
		}
	}
	
	if (ans.size() < n){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	for (int i:ans) cout << i << ' ';
	cout << endl;
	return 0;
}
