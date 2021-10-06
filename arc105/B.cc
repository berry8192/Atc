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

int gcdi(int a, int b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

int main(){

	int n, ans;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];
	ans=v[0];

	rep(i, n) {
		ans=gcdi(ans, v[i]);
	}

	cout<< ans << endl;
 
	return 0;
}