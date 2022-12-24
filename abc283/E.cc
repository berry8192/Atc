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

	int h, w, vv=0, zz=1;
	cin>> h >> w;

	vector<bitset<1000>> v(h), z(h);

	rep(i, h){
		rep(j, w){
			int tmp;
			cin>> tmp;
			if(tmp){
				v[i].set(tmp);
				z[i].set(tmp);
			}
		}
	}
	z[0].flip();

	rep(i, h){
		rep(j, w){
			int tmp=0;
			if(i!=0 && v[i-1][j]==v[i][j]) tmp++; 
			if(j!=0 && v[i][j-1]==v[i][j]) tmp++; 
			if(i!=h-1 && v[i+1][j]==v[i][j]) tmp++;
			if(j!=w-1 && v[i][j+1]==v[i][j]) tmp++;
			if(tmp==0){
				if(i==h-1){
					vv=-1;
					break;
				}
				v[i+1].flip();
				vv++;
				break;
			}
		}
	}

	rep(i, h){
		int flag=0;
		int d=0;
		rep(j, w){
			int tmp=0;
			if(i!=0 && v[i-1][j]==v[i][j]) tmp++; 
			if(j!=0 && v[i][j-1]==v[i][j]) tmp++; 
			if(i!=h-1 && v[i+1][j]==v[i][j]) tmp+=10;
			if(j!=w-1 && v[i][j+1]==v[i][j]) tmp++;
			if(tmp==0){
				if(i==h-1){
					vv=-1;
					break;
				}
				flag=1;
			}
			if(tmp==10) d=1;
		}
		if(flag){
			if(d){
				vv=-1;
				break;
			}
			v[i+1].flip();
			vv++;
			break;
		}
	}
	rep(i, h){
		int flag=0;
		int d=0;
		rep(j, w){
			int tmp=0;
			if(i!=0 && z[i-1][j]==z[i][j]) tmp++; 
			if(j!=0 && z[i][j-1]==z[i][j]) tmp++; 
			if(i!=h-1 && z[i+1][j]==z[i][j]) tmp+=10;
			if(j!=w-1 && z[i][j+1]==z[i][j]) tmp++;
			if(tmp==0){
				if(i==h-1){
					vv=-1;
					break;
				}
				flag=1;
			}
			if(tmp==10) d=1;
		}
		if(flag){
			if(d){
				vv=-1;
				break;
			}
			z[i+1].flip();
			zz++;
			break;
		}
	}

	cout<< min(vv, zz) << endl;
 
	return 0;
}