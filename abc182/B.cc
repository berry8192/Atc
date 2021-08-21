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

	int n, ans, ma=0, mai;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	for(int i=2;i<=1000;i++){
		ans=0;
		for(int j=0;j<n;j++){
			if(v[j]%i==0) ans++;
		}
		if(ma<ans){
			ma=ans;
			mai=i;
		}
	}

	cout<< mai << endl;
 exit(0);
	return 0;
}