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

	int x;
	cin>> x;

	if(x<600) cout<< "8" << endl;
	else if(x<800) cout<< "7" << endl;
	else if(x<1000) cout<< "6" << endl;
	else if(x<1200) cout<< "5" << endl;
	else if(x<1400) cout<< "4" << endl;
	else if(x<1600) cout<< "3" << endl;
	else if(x<1800) cout<< "2" << endl;
	else cout<< "1" << endl;
 
	return 0;
}