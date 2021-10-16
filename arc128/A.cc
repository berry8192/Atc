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

	int n, aum=-1, aui, agm=imax, agi, flag=1;
	//flag1で銀を買う必要がある
	vector<int> v, ans;

	cin>> n;
	v.resize(n);
	ans.resize(n);

	rep(i, n) cin >> v[i];
	v.push_back(imax);

	rep(i, n) {
		if(flag){
			if(v[i]>v[i+1]){
				aui=i;
				flag=0;
			}
		}else{
			if(v[i]<v[i+1]){
				ans[aui]=1;
				ans[i]=1;
				flag=1;
			}
		}
	}

	PV(ans);

	return 0;
}