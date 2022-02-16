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

int cal(LLi x){
	string y=to_string(x);
	int z=0;

	rep(i, y.size()) z+=int(y[i]-'0');
	return z;
}

int main(){

	LLi n, k, pos, i=1;
	vector<int> v;

	cin>> n >> k;
	v.resize(100000);

	while(n && k){
		pos=n;
		n+=cal(n);
		n%=100000;
		if(v[pos] && k%(i-v[pos])) k%=i-v[pos];
		v[pos]=i;
		i++;
		k--;
		//cout<< n <<endl;
	}

	cout<< n << endl;
 
	return 0;
}