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

	int ha, hb, hx, wa, wb, wx;
	cin>> ha >> wa;
	vector<string> a(ha);
	rep(i, ha) cin>> a[i];

	cin>> hb >> wb;
	vector<string> b(hb);
	rep(i, hb) cin>> b[i];

	cin>> hx >> wx;
	vector<string> x(hx);
	rep(i, hx) cin>> x[i];

	string tmp;
	rep(i, wx) tmp+='.';
	vector<string> bla(hx, tmp);


	rep3(fha, 10, -10){
		rep3(fwa, 10, -10){
			vector<string> se=bla;
			int flag=0;
			rep(i, ha){
				rep(j, wa){
					if(a[i][j]=='#'){
						if(i+fha<0 || hx<=i+fha || j+fwa<0 || wx<=j+fwa){
							flag=1;
							i=100;
							j=100;
						}else{
							if(x[i+fha][j+fwa]=='.'){
								flag=1;
								i=100;
								j=100;
								break;
							}else{
								se[i+fha][j+fwa]='#';
							}
						}
					}
				}
			}
			if(flag) continue;
						// cout<< "a ook" <<endl;
			rep3(fhb, 10, -10){
				rep3(fwb, 10, -10){
					flag=0;
					rep(i, hb){
						rep(j, wb){
							if(b[i][j]=='#'){
								if(i+fhb<0 || hx<=i+fhb || j+fwb<0 || wx<=j+fwb){
									flag=1;
									i=100;
									j=100;
								}else{
									if(x[i+fhb][j+fwb]=='.'){
										flag=1;
										i=100;
										j=100;
										break;
									}else{
										se[i+fhb][j+fwb]='#';
									}
								}
							}
						}
					}
					if(flag) continue;
						// cout<< "b ook" <<endl;
					if(x==se){
						cout<< "Yes" << endl;
						return 0;
					}
				}
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}