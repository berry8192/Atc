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

double calc(ll a, ll b, ll c){
	return 1.0*(a+b+c)/(a*b*c);
}

int main(){

	int n, ps=0, ms=0;
	vector<ll> v, pu, mi, vv;
	vector<double> ans;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		if(v[i]>0){
			pu.push_back(v[i]);
			ps++;
		}else{
			mi.push_back(v[i]);
			ms++;
		}
	}
	sort(all(pu));
	sort(all(mi));

	// if(ps>=3){
	// 	ans.push_back(calc(pu[0], pu[1], pu[2]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], pu[ps-3]));
	// }
	// if(ms>=3){
	// 	ans.push_back(calc(mi[0], mi[1], mi[2]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], mi[ms-3]));
	// }
	// if(ps>=2 && ms>=1){
	// 	ans.push_back(calc(pu[0], pu[1], mi[ms-1]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], mi[0]));
	// 	ans.push_back(calc(pu[0], pu[1], mi[0]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], mi[ms-1]));
	// }
	// if(ps>=1 && ms>=2){
	// 	ans.push_back(calc(mi[0], mi[1], pu[ps-1]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], pu[0]));
	// 	ans.push_back(calc(mi[0], mi[1], pu[0]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], pu[ps-1]));
	// }

	// if(ps>=4){
	// 	ans.push_back(calc(pu[0], pu[1], pu[3]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], pu[ps-4]));
	// }
	// if(ms>=3){
	// 	ans.push_back(calc(mi[0], mi[1], mi[3]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], mi[ms-4]));
	// }
	// if(ps>=2 && ms>=1){
	// 	ans.push_back(calc(pu[0], pu[1], mi[ms-1]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], mi[0]));
	// 	ans.push_back(calc(pu[0], pu[1], mi[0]));
	// 	ans.push_back(calc(pu[ps-1], pu[ps-2], mi[ms-1]));
	// }
	// if(ps>=1 && ms>=2){
	// 	ans.push_back(calc(mi[0], mi[1], pu[ps-1]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], pu[0]));
	// 	ans.push_back(calc(mi[0], mi[1], pu[0]));
	// 	ans.push_back(calc(mi[ms-1], mi[ms-2], pu[ps-1]));
	// }
	rep(i, min(4, ps)){
		if(i>ps-1-i) break;
		vv.push_back(pu[i]);
		if(i==ps-1-i) break;
		vv.push_back(pu[ps-1-i]);
	}
	// PV(vv);
	rep(i, min(4, ms)){
		if(i>ms-1-i) break;
		vv.push_back(mi[i]);
		if(i==ms-1-i) break;
		vv.push_back(mi[ms-1-i]);
	}
	// PV(vv);
	rep(i, vv.size()){
		rep3(j, vv.size(), i+1){
			rep3(k, vv.size(), j+1){
				ans.push_back(calc(vv[i], vv[j], vv[k]));
			}
		}
	}
	sort(all(ans));

	printf("%.13lf\n", ans[0]);
	printf("%.13lf\n", ans[ans.size()-1]);
 
	return 0;
}