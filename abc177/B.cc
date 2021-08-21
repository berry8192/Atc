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

	int mi=imax, tmp;
	string s, t;
	cin>> s >> t;

	for(int i=0;i<=s.size()-t.size();i++){
		tmp=0;
		for(int j=0;j<t.size();j++){
			if(s[i+j]!=t[j]) tmp++;
		}
		mi=min(mi, tmp);
	}

	cout<< mi <<endl;
 
	return 0;
}