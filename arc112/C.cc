#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<int> v, w, c, se;

int imax=2147483647;
long long int llimax=9223372036854775807;

void dfs(int x){
	//cout<< x SP;
	if(x==1) return;
	if(se[v[x]]!=1) c[v[x]]+=c[x]+1;
	se[x]=1;

	dfs(v[x]);
}

int main(){

	int n, tmp, ans=0;

	cin>> n;
	v.resize(n+1);
	w.resize(n+1);
	c.resize(n+1);
	se.resize(n+1);


	rep(i, n-1){
		cin >> v[i+2];
		w[v[i+2]]=1;
	}

	for(int i=2;i<=n;i++) {
		if (w[i]==0) {
			//cout<< i SP;
			c[i]=1;
		}
	}

	for(int i=2;i<=n;i++) {
		if (w[i]==0) {
			//cout<< i SP;
			dfs(i);
			//cout<< endl;
		}
	}

	for(int i=1;i<=n;i++){
		cout<< c[i] <<endl;
	}

	return 0;
}