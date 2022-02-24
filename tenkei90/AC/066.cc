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

	int n;
	LLi a, b;
	double ans=0.0;
	vector<int> l, r;
	cout << fixed << setprecision(12);

	cin>> n;
	l.resize(n);
	r.resize(n);

	rep(i, n){
		cin >> l[i] >> r[i];
		//b+=r[i]-l[i]+1;
	}

	rep3(i, n, 1) {
		rep(j, i){
			a=0;
			b=0;
			rep3(k, r[i]+1, l[i]){
				rep3(m, r[j]+1, l[j]){
					if(m>k) a++;
					b++;
				}
				//a+=max(0, r[j]-max(j, l[j]));
			}
			ans+=double(a)/b;
		}
	}

	cout<< ans <<endl;
 
	return 0;
}