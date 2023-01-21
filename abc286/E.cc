#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
int64_t INF=9223372036854775807;
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

typedef pair<int64_t, int> P;
struct edge{int to; int64_t cost;};
vector<int64_t> dijkstra(vector<vector<edge>> graph, int n, int start, int64_t INF){
    priority_queue< P, vector<P>, greater<P> > que;
    vector<int64_t> dst(n, INF);
    dst[start] = 0;
    que.push(P(0, start));
    while(que.size()){
        int64_t d = que.top().first;
        int u = que.top().second;
        que.pop();
        if(dst[u] < d) continue;
        for(int i=0;i<graph[u].size();++i){
            int v = graph[u][i].to;
            int64_t cost = graph[u][i].cost;
            if(dst[v] > d + cost){
                dst[v] = d + cost;
                que.push(P(dst[v], v));
            }
        }
    }
    return dst;
}

int main(){

	int n, q;
	cin>> n;
	vector<int> a(n);
	vector<string> s(n);
	vector<vector<edge>> g(n);
	rep(i, n) cin >> a[i];
	rep(i, n){
		cin >> s[i];
		rep(j, n){
			if(s[i][j]=='Y'){
				g[i].push_back({j, 100000000000000-a[j]});
			}
		}
	}
	cin>> q;
	vector<int> u(q), v(q);
	rep(i, q){
		cin >> u[i] >> v[i];
		u[i]--;
		v[i]--;
	}

	queue<int> que;
	queue<ll> dep, sco;
	queue<bitset<300>> pat;
	rep(i, q) {
		// que.push(u[i]);
		// dep.push(0);
		// sco.push(a[u[i]]+a[v[i]]);
		// bitset<300> bs;
		// bs.set(u[i]);
		// pat.push(bs);
		// ll goal_dep=imax;
		// ll ma=0;
		// while(!que.empty()){
		// 	int uu=que.front();
		// 	que.pop();
		// 	ll de=dep.front();
		// 	dep.pop();
		// 	ll sc=sco.front();
		// 	sco.pop();
		// 	bitset<300> pa=pat.front();
		// 	pat.pop();

		// 	if(de>goal_dep) break;
		// 	rep(j, g[uu].size()){
		// 		if(pa[g[uu][j]]) continue;
		// 		if(g[uu][j]==v[i]){
		// 			ma=max(ma, sc);
		// 			goal_dep=de;
		// 			continue;
		// 		}
		// 		pa.set(g[uu][j]);
		// 		que.push(g[uu][j]);
		// 		dep.push(de+1);
		// 		sco.push(sc+a[g[uu][j]]);
		// 		pat.push(pa);
		// 	}
		// }
		// if(goal_dep!=imax){
		// 	cout<< goal_dep+1 SP << ma <<endl;
		// }else{
		// 	cout<< "Impossible" <<endl;
		// }
	}
	vector<vector<int64_t>> ans(n);
	vector<int> seen(n);
	rep(i, q){
		if(!seen[u[i]]) ans[u[i]]=dijkstra(g, n, u[i], INF);
		seen[u[i]]=1;
		int64_t tmp=ans[u[i]][v[i]];
		// cout<< tmp <<endl;
		if(tmp!=INF){
			cout<< tmp/100000000000000+1 SP << 100000000000000-tmp%100000000000000+a[u[i]] <<endl;
		}else{
			cout<< "Impossible" <<endl;
		}
	}

	return 0;
}