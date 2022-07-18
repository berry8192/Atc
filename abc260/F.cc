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

	int s, t, m;
	vector<int> u, v;

	cin>> s >> t >> m;
	vector<bitset<300000>> b(t);
	u.resize(m);
	v.resize(m);

	rep(i, m){
		cin >> u[i] >> v[i];
		b[v[i]-s-1].set(u[i]-1);
	}

	rep(i, t) {
		//cout<< b[i] <<endl;
		rep3(j, t, i+1){
			if((b[i]&b[j]).count()==2){
				cout<< i SP << j SP;
				int cnt=0;
				rep(k, 300000){
					if(b[i][k]&&b[j][k]){
						cout<< k+1 SP;
						cnt++;
						if(cnt==2) break;
					}
				}
				cout<< endl;
				return 0;
			}
		}
	}

	cout<< -1 << endl;
 
	return 0;
}