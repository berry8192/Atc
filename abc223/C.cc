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

	int n;
	double su=0.0;
	vector<double> a, b;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n){
		cin >> a[i] >> b[i];
		su+=a[i];
	}

	double ri, le, mi, ans;
	ri=su;
	le=0.0;
	while(ri-le>0.0000001){
		mi=(ri+le)/2;
		//cout<< mi <<endl;
		double lt=0.0, ld=0.0, rt=0.0, rd=0.0;
		rep(i, n){
			if(ld+a[i]<mi){
				lt+=a[i]/b[i];
				ld+=a[i];
			}else{
				lt+=(mi-ld)/b[i];
				break;
			}
		}
		repr(i, n){
			if(rd+a[i]<su-mi){
				rt+=a[i]/b[i];
				rd+=a[i];
			}else{
				rt+=((su-mi)-rd)/b[i];
				break;
			}
		}
		if(lt<rt) le=mi;
		else ri=mi;
	}
	printf("%.12lf", (ri+le)/2);
 
	return 0;
}