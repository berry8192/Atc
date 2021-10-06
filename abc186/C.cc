#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, ans=0, flag;

	cin>> n;

	for(int i=1;i<=n;i++){
		flag=1;
		stringstream ss;
		ss << oct << i;
		string s = ss.str();
		//cout<< s <<endl;
		for(int j=0;j<s.size();j++){
			if(s[j]=='7') flag=0;
		}

		s=to_string(i);
		//cout<< s <<endl;
		for(int j=0;j<s.size();j++){
			if(s[j]=='7') flag=0;
		}

		if(flag) ans++;
	}

	cout<< ans << endl;
 
	return 0;
}