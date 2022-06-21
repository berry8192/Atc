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
	string s, ans;
	vector<int> v;

	cin>> s;
	n=s.size();
	v.resize(n);

	v[0]=int(s[0]-'0');
	rep3(i, n, 1) {
		v[i]+=v[i-1]+int(s[i]-'0');
	}
	reverse(all(v));
	rep(i, 10) v.push_back(0);

	rep(i, n+5){
		ans+=to_string(v[i]%10);
		v[i+1]+=v[i]/10;
	}

	while(1){
		if(ans[ans.size()-1]=='0') ans.pop_back();
		else break;
	}

	reverse(all(ans));

	cout<< ans << endl;
 
	return 0;
}