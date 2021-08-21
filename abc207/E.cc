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

	int n;
	LLi ans=0;
	vector<LLi> v, w;
	vector< vector<LLi> > bo;

	cin>> n;
	v.resize(n);
	w.resize(n+1);
	bo.resize(n+1);

	rep(i, n+1) bo[i].resize(n+1);

	rep(i, n){
		cin >> v[i];
		w[i+1]=w[i]+v[i];
	}
	//PVL(w);
	bo[0][0]=1;

	//for(int i=1;i<n+1;i++) bo[i]=1;

	for(int i=1;i<n+1;i++) {
		for(int j=i-1;j<n+1;j++){
			for(int l=j+1;l<n+1;l++){
				if((w[l]-w[j])%i==0){
					bo[i][l]+=bo[i-1][j];
					bo[i][l]=bo[i][l]%mod;
				}
			}
		}
	}

	/*for(int i=0;i<n+1;i++) {
		for(int j=0;j<n+1;j++){
			cout<< bo[i][j] <<" ";
		}
		cout<< endl;
	}*/
	rep(i, n+1){
		ans+=bo[i][n];
		ans=ans%mod;
	}

	cout<< ans <<endl;
 
	return 0;
}