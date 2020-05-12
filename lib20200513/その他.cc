#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//vector<int>を出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//vector<LLi>を出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//vecotr<int>同士の比較
bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<LLi>同士の比較
bool VVL(vector<LL1> vv1, vector<LLi> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

int gcd(int a, int b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcd(b, a%b);
}

LLi gcd(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcd(b, a%b);
}

int lcm(int a, int b) {
    return a/gcd(a, b)*b;
}

LLi lcm(LLi a, LLi b) {
    return a/gcd(a, b)*b;
}

int main(){

	int n;
	vector<int> v;
	cin>> n;

	v.resize(n);
	rep(i, n) cin>> v[i];

	//小数点桁数指定
	cout << fixed << setprecision(桁数);

	//順列全探索
	//sort(v.begin(), v.end());
	do {
		PV(v);
	} while (next_permutation(v.begin(), v.end()));

	return 0;
}