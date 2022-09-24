#include <iostream>
#include <vector>

using namespace std;

int n,x,y;
vector<int> u,v,ans,seen(200010);;
vector<vector<int>> g(200010);

bool dfs(int a){
	if(seen[a]) return false;
	seen[a]=1;
	if(a==y){
		return true;
	}
	for(int i=0;i<g[a].size();i++){
		if(dfs(g[a][i])){
			ans.push_back(g[a][i]);
			return true;
		}
	}
	return false;
}

int main(){
  cin>> n>>x>>y;
  
  u.resize(n);
  v.resize(n);
  for(int i=0;i<n-1;i++){
  	cin>> u[i]>>v[i];
  	g[u[i]].push_back(v[i]);
  	g[v[i]].push_back(u[i]);
  }
  
  dfs(x);

  cout<< x <<" ";
  for(int i=ans.size()-1;i>=0;i--) cout<< ans[i] <<" ";
  cout<< endl;

  return 0;
}
