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

	int n;
	vector<int> v, x={-1}, y={-1}, ans;

	cin>> n;
	v.resize(n);
	ans.resize(n+1);
	ans[0]=0;

	rep(i, n){
		cin >> v[i];
		if(x[x.size()-1]!=v[i]){
			x.push_back(v[i]);
			y.push_back(1);
			ans[i+1]=ans[i]+1;
		}else{
			y[y.size()-1]++;
			ans[i+1]=ans[i]+1;
			if(x[x.size()-1]==y[y.size()-1]){
				ans[i+1]-=y[y.size()-1];
				x.erase(x.end()-1);
				y.erase(y.end()-1);
			}
		}
	}

	rep(i, n) {
		cout<< ans[i+1] <<endl;
	}

	return 0;
}