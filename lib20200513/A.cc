#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

vector<LLi> Cumulative_sum(vector<int> iv){
    vector<LLi> rtn(iv.size()+1);
    rtn[0]=0;
    for(int i=0;i<iv.size();i++) rtn[i+1]=rtn[i]+iv[i];
    return rtn;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
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