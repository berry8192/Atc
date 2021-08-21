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

	int tmp;
	vector<int> v(1);
	string s, t;

	cin>> s >> t;
	v[0]=0;

	rep(i, t.size()) {
		if ((int)(s[i]-'0')) v[0]++; 
	}
	for(int i=t.size();i<s.size();i++){
		tmp=v[v.size()-1];
		if((int)(s[i]-'0')) tmp++;
		if((int)(s[i-t.size()]-'0')) tmp--;
		v.push_back(tmp);
	}
	PV(v);

	cout<< "No" << endl;
 
	return 0;
}