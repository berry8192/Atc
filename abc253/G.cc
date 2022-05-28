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

	ll n, l, r, pos=0;
	vector<int> v;

	cin>> n >> l >> r;

	rep(i, n) v.push_back(i+1);
	//PV(v);

	rep3(i, n, 1){
		int cnt=n-i;
		//cout<< "i=" << i << " pos=" << pos <<endl;
		if(l<pos && pos+cnt<r){
			ll ro=pos;
			int sk=0;
			int li=i;
			while(1){
				cnt=n-i;
				if(ro+cnt>=r) break;
				ro+=cnt;
				i++;
				sk++;
			}
			reverse(v.begin()+li, v.end());
			reverse(v.begin()+li+sk, v.end());
			//cout<< "rotate" <<endl;
			//PV(v);
		}else if(pos+cnt<l || r<pos){
			//cout<< "none" <<endl;
		}else if(l<=pos+cnt){
			//if(pos+cnt<=r){
				rep3(j, cnt+1, 1){
					if(l<=pos+j && pos+j<=r){
						swap(v[i-1], v[i+j-1]);
						//cout<< "swap" <<endl;
						//PV(v);
					}
				}
			//}
		}
		pos+=cnt;
	}

	PV(v);
 
	return 0;
}