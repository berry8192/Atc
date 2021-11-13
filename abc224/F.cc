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
LLi mod=998244353;
vector<LLi> two(1), ten(1);

template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n;
	LLi tmp, ans=0;
	string s;
	vector<int> v;

	cin>> s;
	reverse(all(s));
	n=s.size();
	rep(i, n) v.push_back(int(s[i]-'0'));
	//PV(v);

    two[0]=1;
    ten[0]=1;
  	rep(i, n+1) two.push_back((two[i]*2)%mod);
  	rep(i, n+1) ten.push_back((ten[i]*10)%mod);
	//PV(ten);
	//PV(ten);

	tmp=two[n-1];

	rep(i, n) {
		//cout<< tmp SP << ans <<endl;
		ans+=tmp*v[i];
		ans=ans%mod;
		tmp+=(ten[i+1]*two[n-i-2])%mod;
		tmp-=(ten[i]*two[n-i-2])%mod;
		tmp=(tmp+mod)%mod;
	}

	cout<< ans << endl;
 
	return 0;
}
/*
8
4 4
4 2 2
4 2 1 1
*/