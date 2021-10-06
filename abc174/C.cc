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

	LLi k, tmp=0;
	vector<int> md;
	vector<LLi> ten(1);

	cin>> k;
	md.resize(k);

	if(k%2==0){
		cout<< "-1" <<endl;
		return 0;
	}

    ten[0]=7;
  	rep(i, 10000000) ten.push_back((ten[i]*10)%k);

	rep(i, 10000000){
		tmp+=ten[i];
		tmp=tmp%k;
		//cout<< tmp << endl;
		if(tmp==0){
			cout<< i+1 <<endl;
			return 0;
		}
	}

	cout<< "-1" << endl;
 
	return 0;
}