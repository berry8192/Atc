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

	int n, m;
	LLi x, y, z, ma=-1, tmp;
	vector<LLi> v1, v2, v3, v4;

	cin>> n >> m;
	v1.resize(n);
	v2.resize(n);
	v3.resize(n);
	v4.resize(n);

	rep(i, n){
		cin >> x >> y >> z;
		v1[i]=x+y+z;
		v2[i]=-x+y+z;
		v3[i]=x-y+z;
		v4[i]=x+y-z;
	}

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	sort(v3.begin(), v3.end());
	sort(v4.begin(), v4.end());

	tmp=0;
	rep(i, m) tmp+=v1[i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v2[i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v3[i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v4[i];
	ma=max(ma, abs(tmp));

	tmp=0;
	rep(i, m) tmp+=v1[n-1-i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v2[n-1-i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v3[n-1-i];
	ma=max(ma, abs(tmp));
	tmp=0;
	rep(i, m) tmp+=v4[n-1-i];
	ma=max(ma, abs(tmp));
	
	cout<< ma << endl;
 
	return 0;
}