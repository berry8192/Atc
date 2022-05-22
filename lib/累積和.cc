#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 
#define ll long long int

using namespace std;

vector<ll> Cumulative_sum(vector<int> iv){
    vector<ll> rtn(iv.size()+1);
    rtn[0]=0;
    for(int i=0;i<iv.size();i++) rtn[i+1]=rtn[i]+iv[i];
    return rtn;
}

//ll型vectorを出力
void PVL(vector<ll> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	PVL(Cumulative_sum(v));
 
	return 0;
}