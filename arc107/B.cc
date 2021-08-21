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
	LLi ans=0, le, ri;
	cin>> n >> k;
	k=abs(k);

	for(int i=2;i<=2*n;i++){
		le=min(abs(i-1), abs(2*n+1-i));
		//cout<< le << " " << ri << " " << i <<endl;
		if(i-k<2 || i-k>2*n) continue;
		ri=min(abs(i-k-1), abs(2*n+1-i+k));
		ans+=le*ri;
	}

	cout<< ans <<endl;
 
	return 0;
}