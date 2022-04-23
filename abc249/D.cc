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

	int n;
	LLi ans=0;
	vector<LLi> v, d;

	cin>> n;
	v.resize(n);
	d.resize(200001);
	
	rep(i, n){
		cin >> v[i];
		d[v[i]]++;
	}

	rep(lp, 200001){
		if(d[lp]==0) continue;
		int m=lp;
		int fsz;
		for(LLi i=1;i*i<=m;i++){
			if(m%i==0){
				if(i*i!=m){
					ans+=d[i]*d[m/i]*d[m]*2;
				}else{
					ans+=d[i]*d[i]*d[m];
				}
			}
		}

	}

	cout<< ans << endl;
 
	return 0;
}