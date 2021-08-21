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

	LLi n, mon=1000, kab=0, buy=-1, bv, tmp;
	vector<LLi> v, ko;

	cin>> n;
	v.resize(n+1);
	ko.resize(n+1);

	rep(i, n) cin >> v[i];
	v[n]=-1;

	ko[0]=-1;

	for(int i=1;i<=n;i++){
		if(v[i-1]<v[i]) ko[i]=1;
		if(v[i-1]>v[i]) ko[i]=-1;
		if(v[i-1]==v[i]) ko[i]=ko[i-1];
	}

	for(int i=1;i<=n;i++){
		if(ko[i-1]==-1 && ko[i]==1){
			buy=1;
			bv=v[i-1];
			//cout<< i << " " << bv <<endl;
		} 
		if(ko[i-1]==1 && ko[i]==-1 && buy==1){
			//cout<< mon << " " << kab <<endl;
			buy=-1;
			tmp=mon/bv;
			mon-=tmp*bv;
			kab+=tmp;
			//cout<< mon << " " << kab <<endl;

			mon+=kab*v[i-1];
			kab=0;
			//cout<< mon << " " << kab <<endl;
		}
		/*if(i==n-1 && bv<v[i] && buy==1){
			tmp=mon/bv;
			mon-=tmp*bv;
			kab+=tmp;
			mon+=kab*v[i-1];
		}*/
		//cout<< endl;
	}

	cout<< mon << endl;
 
	return 0;
}