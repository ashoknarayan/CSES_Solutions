#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m;
	cin >> n >> m;
	
	vector<vector<int>> A(n, vector<int>(m,INT_MAX)), M(n, vector<int>(m,INT_MAX));
	vector<vector<pair<int,int>>> par(n, vector<pair<int,int>>(m));
	
	queue<pair<int,int>> qA, qM;
	pair<int,int> AA;
	
	char x;
	for (int i=0; i<n; ++i) for (int j=0; j<m; ++j){
		cin >> x;
		if (x == '.') continue;
		if (x == 'A') A[i][j] = 0, qA.push({i,j}), AA = {i,j};
		if (x == 'M') M[i][j] = 0, qM.push({i,j});
		if (x == '#') A[i][j] = M[i][j] = -1;
	}
	
	vector<pair<int,int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}}; // D, U, R, L
	pair<int,int> dad, kid, esc = {-1,-1};
	
	while(!qA.empty()){
		dad = qA.front(); qA.pop();
		for (int i=0; i<4; ++i){
			kid.first  = dad.first  + dir[i].first;
			kid.second = dad.second + dir[i].second;
			if (kid.first >=0 && kid.first < n && kid.second >=0 && kid.second <m){ 
			    if (A[kid.first][kid.second] > A[dad.first][dad.second]+1){
				    A[kid.first][kid.second] = A[dad.first][dad.second]+1;
				    par[kid.first][kid.second] = dad;
				    qA.push(kid);
			    }
			}	
		}
	}
	
	while(!qM.empty()){
		dad = qM.front(); qM.pop();
		for (int i=0; i<4; ++i){
			kid.first  = dad.first  + dir[i].first;
			kid.second = dad.second + dir[i].second;
			if (kid.first >=0 && kid.first < n && kid.second >=0 && kid.second <m){ 
			    if (M[kid.first][kid.second] > M[dad.first][dad.second]+1){
				    M[kid.first][kid.second] = M[dad.first][dad.second]+1;
				    qM.push(kid);
			    }
            }
		}
	}
	
	for (int i=0; i<m; ++i) if(A[  0][i] < M[  0][i]) {esc = {  0,i}; break;}
	for (int i=0; i<m; ++i) if(A[n-1][i] < M[n-1][i]) {esc = {n-1,i}; break;}
	for (int i=0; i<n; ++i) if(A[i][  0] < M[i][  0]) {esc = {i,  0}; break;}
	for (int i=0; i<n; ++i) if(A[i][m-1] < M[i][m-1]) {esc = {i,m-1}; break;}
	
	if (esc.first == -1){
		cout << "NO" << endl;
		return 0;
	}
	
	// Track 
	kid = esc;
	vector<pair<int,int>> path; 
	while(kid != AA){
		path.push_back(kid);
		kid = par[kid.first][kid.second];
	}
	path.push_back(AA);
	reverse(path.begin(), path.end());
	
	string ans = ""; 
	int dx,dy;
	for(int i=1; i<path.size(); ++i){
		dx = path[i].first  - path[i-1].first;
		dy = path[i].second - path[i-1].second;
		
		if (dx ==  1) ans += 'D';
		if (dx == -1) ans += 'U';
		if (dy ==  1) ans += 'R';
		if (dy == -1) ans += 'L';
	}
	
	cout << "YES" << endl << ans.size() << endl << ans << endl;
	return 0;
}
