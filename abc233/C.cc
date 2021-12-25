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

	LLi n, x, tmp, a, cnt=0;
	vector<vector<LLi>> v, ans;
	vector<LLi> nx;

	cin>> n >> x;
	v.resize(n);
	ans.resize(100010);

	rep(i, n){
		cin>> tmp;
		rep(j, tmp){
			cin >> a;
			v[i].push_back(a);
		}
	}

	rep(i, v[0].size()) ans[0].push_back(v[0][i]);

	rep3(i, n, 1) {
		nx.clear();
		rep(j, ans[i-1].size()){
			rep(k, v[i].size()){
				if(v[i][k]*ans[i-1][j]<=x) nx.push_back(v[i][k]*ans[i-1][j]);
			}
		}
		//rep(j, nx.size()) ans[i].push_back(nx[j]);
		ans[i]=nx;
	}

	rep(i, ans[n-1].size()){
		if(ans[n-1][i]==x) cnt++;
	}

	cout<< cnt <<endl;
 
	return 0;
}