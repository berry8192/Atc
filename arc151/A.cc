#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int main(){

	int n;
	cin>> n;
	string s, ans;
	cin>> s;
	string t;
	cin>> t;
	vector<int> ss, tt;

	int tmp=0;
	rep(i, n){
		ans+="0";
		if(s[i]!=t[i]){
			tmp++;
			if(s[i]=='0') ss.push_back(i);
			else tt.push_back(i);
		}
	}

	if(tmp%2){
		cout<< -1 <<endl;
		return 0;
	}

	int sz;
	if(ss.size()<=tt.size()){
		sz=(tt.size()-ss.size())/2+ss.size();
		rep3(i, tt.size(), sz){
			ans[tt[i]]='1';
		}
	}else{
		sz=(ss.size()-tt.size())/2+tt.size();
		rep3(i, ss.size(), sz){
			ans[ss[i]]='1';
		}
	}

	cout<< ans << endl;
 
	return 0;
}