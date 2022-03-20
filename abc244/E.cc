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
//LLi mod=1000000007;
LLi mod=998244353;

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

	int n, m, k, s, t, x;
	LLi ans=0;
	vector< map<LLi, LLi> > q0, q1, q2, q3;
	vector<LLi> a0, a1;
	vector<int> u, v, d;
	vector< vector<int> > e;

	cin>> n >> m >> k >> s >> t >> x;
	q0.resize(k+2);
	q1.resize(k+2);
	q2.resize(k+2);
	q3.resize(k+2);
	a0.resize(n+1);
	a1.resize(n+1);
	u.resize(m);
	v.resize(m);
	//d.resize(n+1);
	e.resize(n+1);

	rep(i, m){
		cin >> u[i] >> v[i];
		e[u[i]].push_back(v[i]);
		e[v[i]].push_back(u[i]);
	}
	// rep(i, n){
	// 	if(e[i+1].size()==1 && i+1!=s && i+1!=t && i+1!=x){
	// 		sort(all(e[e[i+1][0]]));
	// 		auto lb=lower_bound(all(e[e[i+1][0]]), i+1);
	// 		e[e[i+1][0]].erase(lb);
	// 		d[e[i+1][0]]++;
	// 	} 
	// }

	q0[0][s]=1;
	rep(i, k/2) {
		for (auto p : q0[i]) {
			auto key = p.first;
			auto val = p.second;
			// key, valを使う
			//cout<< key << " " << val <<endl;
			rep(j, e[key].size()){
				if(e[key][j]==x){
					q1[i+1][e[key][j]]+=val;
					q1[i+1][e[key][j]]%=mod;
				}else{
					q0[i+1][e[key][j]]+=val;
					q0[i+1][e[key][j]]%=mod;
				}
			}
			// if(d[key]){
			// 	if(key==x){
			// 		q1[i+2][key]+=d[key]*val;
			// 		q1[i+2][key]%=mod;
			// 	}else{
			// 		q0[i+2][key]+=d[key]*val;
			// 		q0[i+2][key]%=mod;
			// 	}
			// }
		}
		for (auto p : q1[i]) {
			auto key = p.first;
			auto val = p.second;
			// key, valを使う
			//cout<< key << " " << val <<endl;
			rep(j, e[key].size()){
				if(e[key][j]==x){
					q0[i+1][e[key][j]]+=val;
					q0[i+1][e[key][j]]%=mod;
				}else{
					q1[i+1][e[key][j]]+=val;
					q1[i+1][e[key][j]]%=mod;
				}
			}
			// if(d[key]){
			// 	if(key==x){
			// 		q0[i+2][key]+=d[key]*val;
			// 		q0[i+2][key]%=mod;
			// 	}else{
			// 		q1[i+2][key]+=d[key]*val;
			// 		q1[i+2][key]%=mod;
			// 	}
			// }
		}
	}

	q2[0][t]=1;
	rep(i, k-k/2) {
		for (auto p : q2[i]) {
			auto key = p.first;
			auto val = p.second;
			// key, valを使う
			//cout<< key << " " << val <<endl;
			rep(j, e[key].size()){
				if(key==x){
					q3[i+1][e[key][j]]+=val;
					q3[i+1][e[key][j]]%=mod;
				}else{
					q2[i+1][e[key][j]]+=val;
					q2[i+1][e[key][j]]%=mod;
				}
			}
			// if(d[key]){
			// 	if(key==x){
			// 		q1[i+2][key]+=d[key]*val;
			// 		q1[i+2][key]%=mod;
			// 	}else{
			// 		q0[i+2][key]+=d[key]*val;
			// 		q0[i+2][key]%=mod;
			// 	}
			// }
		}
		for (auto p : q3[i]) {
			auto key = p.first;
			auto val = p.second;
			// key, valを使う
			//cout<< key << " " << val <<endl;
			rep(j, e[key].size()){
				if(key==x){
					q2[i+1][e[key][j]]+=val;
					q2[i+1][e[key][j]]%=mod;
				}else{
					q3[i+1][e[key][j]]+=val;
					q3[i+1][e[key][j]]%=mod;
				}
			}
			// if(d[key]){
			// 	if(key==x){
			// 		q0[i+2][key]+=d[key]*val;
			// 		q0[i+2][key]%=mod;
			// 	}else{
			// 		q1[i+2][key]+=d[key]*val;
			// 		q1[i+2][key]%=mod;
			// 	}
			// }
		}
	}

	rep(i, n){
		ans+=q0[k/2][i+1]*q2[k-k/2][i+1];
		ans%=mod;
		ans+=q1[k/2][i+1]*q3[k-k/2][i+1];
		ans%=mod;
	}
	//cout<< q0[k][t] << endl;
	cout<< ans << endl;
 
	return 0;
}