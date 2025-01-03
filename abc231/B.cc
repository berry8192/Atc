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

	map<string, int> m;//文字列を入れると数字が出てくる

	int n, ma=0;
	string ans;
	cin>> n;

	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		m[tmp]++;
	}

	for (auto p : m) {
  		auto key = p.first;
  		auto value = p.second;
  		// key, valueを使う
		//cout<< key << " " << value <<endl;
		if(ma<value){
			ans=key;
			ma=value;
		}
	}

	cout<< ans << endl;
 
	return 0;
}