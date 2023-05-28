#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int t;
	cin>> t;

	rep(lp, t){
		int n, a, b;
		cin>> n;
		vector<set<int>> g(n);
		rep(i, n-1){
			cin>> a >> b;
			g[a-1].insert(b-1);
			g[b-1].insert(a-1);
		}
		string s, ans;
		cin>> s;
		rep(i, n) ans+="n";
		vector<int> c(n); // 隣接頂点がどの程度協力してくれているか

		queue<int> q;
		rep(i, n){
			if(g[i].size()==1){
				q.push(i);
			}
		}

		int flag=0;
		while(!q.empty()){
			int v=q.front();
			q.pop();
			if(g[v].empty()) continue;
			int u=*g[v].begin();
			// cout<< "u, v: " << u SP << v <<endl;
			if(ans[u]!='n' && ans[u]!=s[v]){
				flag=1;
				break;
			}
			ans[u]=s[v];
			if(ans[v]=='n'){
				ans[v]=s[u];
			}
			c[u]++;
			if(ans[v]!=s[u]) c[u]-=2;
			if(-1*c[u]>int(g[u].size())){
				// cout<< c[u] SP << g[u].size() <<endl;
				flag=1;
				break;;
			}
			g[u].erase(v);
			if(g[u].size()==1) q.push(u);
			// cout<< ans <<endl;
		}
		if(flag){
			cout<< -1 <<endl;
			continue;
		}

		cout<< ans <<endl;
	}
 
	return 0;
}