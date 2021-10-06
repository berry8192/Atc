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

	int n, k, tmp;
	double mi=9999999999.0;
	string su;
	vector<int> v;

	cin>> n >> k;

	for(int i=n;i>0;i--){
		//if(i%100!=9) continue;
		tmp=0;
		su=to_string(i);
		rep(j, su.size()) tmp+=(int)(su[j]-'0');
		if((double)(i)/tmp<mi) cout<< i SP << tmp SP << (double)(i)/tmp <<endl;
	}

 
	return 0;
}