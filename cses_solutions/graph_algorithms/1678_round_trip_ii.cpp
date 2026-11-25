#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
 
    int n,m; cin>>n>>m;
	
	vector<vector<int>> g(n+1);
	vector<int> par(n+1);
	vector<string> lbl(n+1, "virgin");
	
	int a,b;
	for (int i=0; i<m; ++i){cin>>a>>b; g[a].push_back(b);}
	
	int start=-1,end=-1;
	for(int i=1; i<=n; ++i){
		if (lbl[i] == "sigma") continue;
		
		stack<int> st; st.push(i);
		while(!st.empty()){
			int dad = st.top();
			if (lbl[dad] == "sex"){
				lbl[dad] = "sigma";
				st.pop();
				continue;
			}
			lbl[dad] = "sex";
			for (int kid:g[dad]){
				if (lbl[kid] == "virgin"){
					par[kid] = dad;
					st.push(kid);
					continue;
				}
				if (lbl[kid] == "sigma") continue;
				
				
				start = dad; end = kid; break;
			}
		}
		if (start!=-1) break;
	}
	
	if (start == -1){
		cout << "IMPOSSIBLE" << endl;
		return 0;
	}
	
	vector<int> cyc;
	int node = start;
	while (node != end) cyc.push_back(node), node = par[node];
	cyc.push_back(end); cyc.push_back(start);
	reverse(cyc.begin(), cyc.end());
	
	cout << cyc.size() << endl;
	for (int i:cyc) cout << i << ' ';
	cout << endl;
	
	return 0;
}
