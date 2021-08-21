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
	cin>> n;

	if(n%10==0) cout<< "pon" << endl;
	if(n%10==1) cout<< "pon" << endl;
	if(n%10==6) cout<< "pon" << endl;
	if(n%10==8) cout<< "pon" << endl;
	if(n%10==2) cout<< "hon" << endl;
	if(n%10==4) cout<< "hon" << endl;
	if(n%10==5) cout<< "hon" << endl;
	if(n%10==7) cout<< "hon" << endl;
	if(n%10==9) cout<< "hon" << endl;
	if(n%10==3) cout<< "bon" << endl;
 
	return 0;
}