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
	string s;
	cin>> n >> m;
	vector<int> v, prev={1};
	int e[110][110];
	rep(i, 110){
		rep(j, 110){
			e[i][j]=0;
		}
	}
	rep(lp, n*2){
		cin>> k;
		if(k==-1) return 1;
		v.clear();
		v.resize(k);
		rep(i, k){
			cin>> v[i];
			if(v[i]==n){
				cout<< n <<endl;
				cin>> s;
				return 0;
			}
		}
		int pre=prev[prev.size()-1];
		int flag=0;
		rep(i, k){
			if(e[pre][v[i]]==0 && e[v[i]][pre]==0){
				e[pre][v[i]]=1;
				cout<< v[i] <<endl;
				prev.push_back(v[i]);
				flag=1;
				break;
			}
		}
		if(flag) continue;
		cout<< pre <<endl;
		prev.pop_back();

	}
	cout<< "WA" <<endl;
 
	return 0;
}