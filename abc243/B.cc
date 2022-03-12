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

	int n, hi=0, bl=0;
	vector<int> a, b, c, d;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	rep(i, n) {
		if (a[i]==b[i]){
			hi++;
		}else{
			c.push_back(a[i]);
			d.push_back(b[i]);
		}
	}

	rep(i, c.size()){
		rep(j, d.size()){
			if(c[i]==d[j]){
				bl++;
				break;
			}
		}
	}

	cout<< hi << endl;
	cout<< bl << endl;
 
	return 0;
}