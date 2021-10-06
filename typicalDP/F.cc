#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;

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

	int n, k;
	LLi su=0;
	vector<LLi> v;

	cin>> n >> k;
	v.resize(n+2);

	v[0]=1;
	su=v[0];

	for(int i=1;i<n+1;i++) {
		v[i]=su;
		if(i==n || i==1) v[i]=0;
		su+=v[i];
		su=su%mod;

		if(i-k>=0){
			su+=mod-v[i-k];
			su=su%mod;
		}

		//cout<< v[i] << " " << su <<endl;
	}

	cout<< su <<endl;
 
	return 0;
}