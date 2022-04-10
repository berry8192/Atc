#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

int n, p, k;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

vector<LLi> daikusu(vector<vector<LLi>> v, int x){
	int imax=2147483647;
	int N=n, M, S, A[2009], B[2009], C[2009];
	vector<LLi> dist(40);
	vector<pair<int, int>> G[2009];
	priority_queue<pair<int, LLi>, vector<pair<int, LLi>>, greater<pair<int, LLi>>> Q;
	
	rep(i, n){
		rep(j, n){
    		G[i].push_back(make_pair(j, v[i][j]));
		}
	}
	S=x;
	for (int i = 1; i <= N; i++) dist[i] = llimax;

	Q.push(make_pair(0, S));
    dist[S] = 0;
    while (!Q.empty()) {
        int pos = Q.top().second; Q.pop();
        for (int i = 0; i < G[pos].size(); i++) {
            int to = G[pos][i].first, cost = G[pos][i].second;
            if (dist[to] > dist[pos] + cost) {
                dist[to] = dist[pos] + cost;
                Q.push(make_pair(dist[to], to));
            }
        }
    }

	return dist;
}

int main(){

	vector<vector<int>> v, dis;

	cin>> n >> p >> k;
	v.resize(n);
	rep(i, n) v[i].resize(n);
	dis.resize(n);
	rep(i, n) dis[i].resize(n);

	rep(i, n){
		rep(j, n){
			cin >> v[i][j];
		}
	}

	LLi ri, le, mi;
	ri=1000000001;
	le=0;
	while(ri-le>1){
		mi=(ri+le)/2;
		vector<vector<LLi>> e;
		e.resize(n);
		rep(i, n) e[i].resize(n);
		rep(i, n){
			rep(j, n){
				if(v[i][j]!=-1) e[i][j]=v[i][j];
				else e[i][j]=mi;
			}
		}
		int tmp=0;
		rep(i, n){
			vector<LLi> rtn=daikusu(e, i);
			PV(rtn);
			rep(j, n){
				if(i==j) continue;
				if(rtn[j]<=p) tmp++;
			}
		}
cout<< mi SP << tmp <<endl;
		if(tmp<k) le=mi;
		else ri=mi;
	}
	cout<< le <<endl;

	cout<< "No" << endl;
 
	return 0;
}