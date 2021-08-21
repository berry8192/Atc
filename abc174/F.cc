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

	int n, q, l, r;
	vector<int> v, me, dl, dr;

	cin>> n >> q;
	v.resize(n);
	me.resize(n);
	dl.resize(n);
	dr.resize(n);

	rep(i, n){
		cin >> v[i];
		if(i!=0) dl[i]=dl[i-1];
		if(me[v[i]-1]==1) dl[i]++;
		else me[v[i]-1]=1;
	}
	rep(i, n) me[i]=0;

	for(int i=n-1;i>=0;i--){
		if(i!=n-1) dr[i]=dr[i+1];
		if(me[v[i]-1]==1) dr[i]++;
		else me[v[i]-1]=1;
	}

	rep(i, q) {
		cin>> l >> r;
		cout<< max(r-l+1-(dr[l-1]-dr[r-1]), r-l+1-(dl[r-1]-dl[l-1])) << endl;
	}

	return 0;
}