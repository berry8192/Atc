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

	int n, q, sft=0, t, x, y;
	vector<int> v, ans;

	cin>> n >> q;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, q) {
		cin>> t >> x >> y;
		x--;
		y--;
		if(t==1){
			swap(v[(x+sft+n)%n], v[(y+sft)%n]);
		}else if(t==2){
			sft--;
			sft=(sft+n)%n;
		}else{
			ans.push_back(v[(x+sft)%n]);
		}
		//PV(v);
	}

	rep(i, ans.size()) cout<< ans[i] << endl;
 
	return 0;
}
