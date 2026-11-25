#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m; cin>>n>>m;
	
	vector<vector<int>> dist(n+2, vector<int>(m+2,-2));
	
	pair<int,int> A,B;
	for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j){
		char x; cin>>x;
		if (x == '#') continue;
		
		dist[i][j] = INT_MAX;
		if (x=='A') A.first = i, A.second = j;
		if (x=='B') B.first = i, B.second = j;
	}
	
	int dx[4] = {0,0,1,-1};
	int dy[4] = {1,-1,0,0};
	
	 
	dist[A.first][A.second] = 0;
	vector<vector<pair<int,int>>> par(n+2, vector<pair<int,int>>(m+2));
	
	queue<pair<int,int>> q;
	q.push(A);
	
	pair<int,int> dad, kid;
	while(!q.empty()){
		dad = q.front(); q.pop();
		
		for (int i=0; i<4; ++i){
			kid.first = dad.first + dx[i];
			kid.second = dad.second + dy[i];
			// Update condition
			if (dist[kid.first][kid.second] > dist[dad.first][dad.second] + 1){
				dist[kid.first][kid.second] = dist[dad.first][dad.second] + 1;
				par[kid.first][kid.second] = dad;
				q.push(kid);
			}
		}
	}
	
	// BFS Over
	if (dist[B.first][B.second] == INT_MAX){
		cout << "NO" << endl;
		return 0;
	}
	
	vector<pair<int,int>> path;
	pair<int,int> node = B;
	while(node != A){
		path.push_back(node);
		node = par[node.first][node.second];
	}
	path.push_back(A);
	
	reverse(path.begin(), path.end());
	string ans = "";
	
	for (int i=1; i<path.size(); ++i){
		int xx = path[i].first - path[i-1].first;
		int yy = path[i].second - path[i-1].second;
		if (xx== 1 && yy== 0) ans += 'D';
		if (xx==-1 && yy== 0) ans += 'U';
		if (xx== 0 && yy== 1) ans += 'R';
		if (xx== 0 && yy==-1) ans += 'L';
	}
	
	cout << "YES" << endl << ans.size() << endl << ans << endl;
	
	return 0;
}
