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

	LLi n, m, s;
	double tmp, ans=0;
	vector<int> v;
	
	cout << fixed << setprecision(12);

	cin>> n >> m >> s;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		//iから本気出す
		//cout<< "i=" << i SP << "m=" << 1.0*s/(n-i) <<endl;
		if(s>(n-i)*m) continue;
		tmp=0.0;
		rep(j, n){
			if(i<=j){
				tmp+=1.0*s/(n-i)*v[j];
			}
		}
		//cout<< tmp <<endl;
		ans=max(ans, tmp);
	}
	tmp=0.0;
	repr(i, n){
		tmp+=1.0*min(s, m)*v[i];
		s=max(s-m, 0LL);
		//cout SP << s <<endl;
	}
	ans=max(ans, tmp);

	cout<< ans << endl;
 
	return 0;
}
// blue 639th
// cyan 1053rd
// now 1195th

// 3ac fast 111st 2497
// 3ac last 489th 1784
// 2ac fast 518th 1747
// 2ac last 1187th 1091
// 1ac fast 1192nd 1087

