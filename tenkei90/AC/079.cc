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

int main(){

	int h, w, tmp;
	LLi ans=0;
	vector< vector<int> > a, b;

	cin>> h >> w;
	a.resize(h);
	b.resize(h);
	rep(i, h) a[i].resize(w);
	rep(i, h) b[i].resize(w);

	rep(i, h){
		rep(j, w){
			cin>> a[i][j];
		}
	}
	rep(i, h){
		rep(j, w){
			cin>> b[i][j];
		}
	}

	rep(i, h-1){
		rep(j, w-1){
			tmp=b[i][j]-a[i][j];
			rep(k, 2){
				rep(l, 2) a[i+k][j+l]+=tmp;
			}
			ans+=abs(tmp);
		}
	}
	
	rep(i, h){
		rep(j, w){
			if(a[i][j]!=b[i][j]){
				cout<< "No" << endl;
				return 0;
			}
		}
	}

	cout<< "Yes" << endl;
	cout<< ans <<endl;
 
	return 0;
}