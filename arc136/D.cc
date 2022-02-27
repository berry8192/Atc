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

	int n, tmp, flg;
	LLi ans=0;
	vector<int> v, d(6);
	int bo[11][11][11][11][11][11];
	rep(i1, 11){
		rep(i2, 11){
			rep(i3, 11){
				rep(i4, 11){
					rep(i5, 11){
						rep(i6, 11) bo[i1][i2][i3][i4][i5][i6]=0;
					}
				}
			}
		}
	}

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		tmp=v[i];
		rep(j, 6){
			d[j]=tmp%10;
			tmp/=10;
		}
		bo[d[0]][d[1]][d[2]][d[3]][d[4]][d[5]]++;
		//PV(d);
	}

	// while(1){
	// 	cout<< "search" <<endl;
	// 	rep(i, 6) cin>> d[i];
	// 	cout<< bo[d[0]][d[1]][d[2]][d[3]][d[4]][d[5]] <<endl;
	// }

	for (int bit = 1; bit < (1<<6); ++bit) {
        vector<int> s(6, 0), t(6);
		//全ての桁に対する処理
		for (int j = 0; j < 6; ++j) {
			if(bit & (1<<j)) t[j]=1;
		}
		//PV(t);
		
		// rep(i, 10){
		// 	//cout<< 10-s[0]-t[0] SP << 10-s[0] <<endl;
		// 	if(bo[10-s[0]][10-s[1]][10-s[2]][10-s[3]][10-s[4]][10-s[5]]) cout<< "!" <<endl;
		// 	bo[10-s[0]-t[0]][10-s[1]-t[1]][10-s[2]-t[2]][10-s[3]-t[3]][10-s[4]-t[4]][10-s[5]-t[5]]+=bo[10-s[0]][10-s[1]][10-s[2]][10-s[3]][10-s[4]][10-s[5]];
		// 	for (int j = 0; j < 6; ++j) {
		// 		if(bit & (1<<j)) s[j]++;
		// 	}
		// }
		//PV(s);
		repr(i1, 10){
			repr(i2, 10){
				repr(i3, 10){
					repr(i4, 10){
						repr(i5, 10){
							repr(i6, 10) bo[i1][i2][i3][i4][i5][i6]=0;
						}
					}
				}
			}
		}
    }

	rep(i, n) {
		tmp=v[i];
		rep(j, 6){
			d[j]=tmp%10;
			tmp/=10;
		}
		ans+=bo[9-d[0]][9-d[1]][9-d[2]][9-d[3]][9-d[4]][9-d[5]];
		flg=1;
		rep(j, 6){
			if(d[j]>=5) flg=0;
		}
		if(flg) ans--;
		//PV(d);
	}

	cout<< ans << endl;
 
	return 0;
}