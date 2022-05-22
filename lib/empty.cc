#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

void PVL(vector<ll> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

bool VVL(vector<ll> vv1, vector<ll> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<ll>の総和
ll SML(vector<ll> smv) {
	ll tmp=0;
	rep(i, smv.size()) tmp+=smv[i];

	return tmp;
}

int main(){

	int n;
	cin>> n;

	return 0;
}