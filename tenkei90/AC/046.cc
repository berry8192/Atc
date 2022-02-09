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

	int n, tmp;
	vector<LLi> a(46), b(46), c(46), d(46), e(46);

	cin>> n;

	rep(i, n){
		cin >> tmp;
		a[tmp%46]++;
	}
	rep(i, n){
		cin >> tmp;
		b[tmp%46]++;
	}
	rep(i, n){
		cin >> tmp;
		c[tmp%46]++;
	}

	rep(i, 46) {
		rep(j, 46){
			d[(i+j)%46]+=a[i]*b[j];
		}
	}
	rep(i, 46){
		rep(j, 46){
			e[(i+j)%46]+=c[i]*d[j];
		}
	}
	//PV(e);

	cout<< e[0] << endl;
 
	return 0;
}