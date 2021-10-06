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

	int r, c, k;
	LLi ri, ci, vi, ma=0;
	vector< vector<LLi> > bo;
	vector< vector<LLi> > a1, a2, a3, asu;

	cin>> r >> c >> k;
	bo.resize(r);
	rep(i, r) bo[i].resize(c, 0);
	a1.resize(r);
	rep(i, r) a1[i].resize(c, 0);
	a2.resize(r);
	rep(i, r) a2[i].resize(c, 0);
	a3.resize(r);
	rep(i, r) a3[i].resize(c, 0);
	asu.resize(r+1);
	rep(i, r+1) asu[i].resize(c, 0);

	rep(i, k){
		cin >> ri >> ci >> vi;
		bo[ri-1][ci-1]=vi;
	}

	rep(i, r){
		rep(j, c){
			if(j>0){
				a3[i][j]=a3[i][j-1];
				a2[i][j]=a2[i][j-1];
				a1[i][j]=a1[i][j-1];
			}

			if(a1[i][j]<bo[i][j]){
				a3[i][j]=a2[i][j];
				a2[i][j]=a1[i][j];
				a1[i][j]=bo[i][j];
			}else if(a2[i][j]<bo[i][j]){
				a3[i][j]=a2[i][j];
				a2[i][j]=bo[i][j];
			}else if(a3[i][j]<bo[i][j]) a3[i][j]=bo[i][j];
			asu[i][j]=a1[i][j]+a2[i][j]+a3[i][j];
			if(i>0) asu[i][j]=max(asu[i-1][j], asu[i][j]);
			//cout<< asu[i][j] <<endl;
		}
	}

	rep(i, c){
		ma=max(ma, asu[r][i]);
	}

	cout<< ma <<endl;
 
	return 0;
}