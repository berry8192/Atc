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

	int n, m, k;
	cin>> n >> m;
	vector<int> u(m), v(m), ans(n, 1), dd(n, -1);
	vector<vector<int>> g(n);
	rep(i, m){
		cin >> u[i] >> v[i];
		u[i]--;
		v[i]--;
		g[u[i]].push_back(v[i]);
		g[v[i]].push_back(u[i]);
	}
	cin>> k;
	vector<int> p(k), d(k);
	rep(i, k){
		cin >> p[i] >> d[i];
		dd[p[i]-1]=d[i];
	}

	rep(i, n){
		if(dd[i]==-1) continue;
		if(dd[i]==0 && ans[i]==0){
			cout<< "No" <<endl;
			return 0;
		}
		if(dd[i]==0){
			ans[i]=1;
			continue;
		}
		queue<int> que, dis;
		vector<int> seen(n);
		que.push(i);
		dis.push(0);
		while(!que.empty()){
			int x=que.front();
			int dist=dis.front();
			seen[x]=1;
			que.pop();
			dis.pop();
			if(dist>=dd[i]) break;
			ans[x]=0;
			rep(j, g[x].size()){
				if(seen[g[x][j]]) continue;
				que.push(g[x][j]);
				dis.push(dist+1);
			}
		}
	}
	// PV(ans);

	rep(i, n){
		if(dd[i]==-1) continue;
		queue<int> que, dis;
		vector<int> seen(n);
		que.push(i);
		dis.push(0);
		int flag=1;
		while(!que.empty()){
			int x=que.front();
			int dist=dis.front();
			seen[x]=1;
			que.pop();
			dis.pop();
			if(ans[x]==1 && dist==dd[i]){
				flag=0;
				break;
			}
			rep(j, g[x].size()){
				if(seen[g[x][j]]) continue;
				que.push(g[x][j]);
				dis.push(dist+1);
			}
		}
		if(flag){
			cout<< "No" <<endl;
			return 0;
		}
	}

	cout<< "Yes" << endl;
	rep(i, n) cout<< ans[i];
	cout<< endl;
 
	return 0;
}