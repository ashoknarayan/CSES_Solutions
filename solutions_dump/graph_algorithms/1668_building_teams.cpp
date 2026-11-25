#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m; cin>>n>>m;
	
    vector<vector<int>> adj(n+1);
    
    int a,b;
	for(int i=0; i<m; ++i){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<int> label(n+1, 0);
	
	for(int i=1; i<=n; ++i){
		if (label[i] == 0){
			// Check bipartite here
			queue<int> q;
			q.push(i); 
			label[i] = 1;
			while(!q.empty()){
				int dad = q.front(); q.pop();
				for (int kid : adj[dad]){
					if (label[kid] == label[dad]){
						cout << "IMPOSSIBLE" << endl;
						return 0;
					}
					if (label[kid] == 0){
						label[kid] = 3-label[dad];
						q.push(kid);
					}
				}
			}   
		}
	}
	for (int i=1; i<=n; ++i){
		cout << label[i] << ' ';
	}
	return 0;
}
