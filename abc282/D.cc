#include <iostream>
#include <vector>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

vector<vector<int>> g;
vector<int> c, one, par;

void dfs(int x, int col){
	c[x]=col;
	if(col) one[par[x]]++;
	for(int i=0;i<g[x].size();i++){
		if(c[g[x][i]]==col){
			cout<< 0 <<endl;
			exit(0);
		}else if(c[g[x][i]]!=-1){
			continue;
		}
		dfs(g[x][i], 1-col);
	}
}

int main(){
  int n, m;
  cin>> n >> m;
  g.resize(n);
  c.resize(n, -1);
  one.resize(n);
  par.resize(n);
  dsu d(n);
  vector<int> u(m), v(m);
  
  for(int i=0;i<m;i++){
  	  cin>> u[i] >> v[i];
  	  u[i]--;
  	  v[i]--;
  	  g[u[i]].push_back(v[i]);
  	  g[v[i]].push_back(u[i]);
  	  d.merge(u[i], v[i]);
  }
  
  for(int i=0;i<n;i++){
  	  par[i]=d.leader(i);
  }
  
  for(int i=0;i<n;i++){
  	  if(c[i]==-1) dfs(i, 0);
  }
  
  long long ans=0;
  for(int i=0;i<n;i++){
  	  ans+=n-d.size(i);
  	  if(c[i]){
  	      ans+=d.size(i)-one[d.leader(i)];
  	  }else{
  	  	  ans+=one[d.leader(i)];
  	  }
  }
  ans-=2*m;

  cout<<ans/2<<endl;

  return 0;
}
