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

	LLi n, mi=imax, dlt;
	LLi ans=0, ami;
	vector<LLi> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		v[i]-=i+1;
		mi=min(mi, v[i]);
	}

	rep(i, n) ans+=v[i]-mi;
	ami=ans;
	sort(v.begin(), v.end());
	//cout<< ans <<endl;//

	for(int i=1;i<n;i++){
		dlt=v[i]-v[i-1];
		ans+=dlt*i;
		ans-=dlt*(n-i);
		ami=min(ami, ans);
		//cout<< ans <<endl;//
	}

	cout<< ami <<endl;
 
	return 0;
}