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
	
	int ans = -1;
	vector<bool> vis(n+1, false);
	vector<int> cluster;
	for (int i=1; i<=n; ++i){
		if (!vis[i]){
			++ans; cluster.push_back(i);
			queue<int> q;
			q.push(i);
			vis[i] = true;
			
			while(!q.empty()){
				int dad = q.front(); q.pop();
				for (int kid : adj[dad]){
					if (!vis[kid]){
						q.push(kid);
						vis[kid] = true;
					}
				}
			}
		}
	}
	
	cout << ans << endl;
	for (int i=1; i<cluster.size(); ++i){
		cout << cluster[i-1] << ' ' << cluster[i] << endl;
	}
	return 0;
}
