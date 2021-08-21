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

	LLi n, d3, d5;
	cin>> n;

	for(LLi i=1;i<38;i++){
		for(LLi j=1;j<26;j++){
			//cout<< pow(3, i) << " " << pow(5, j) << " " << pow(3, i)+pow(5, j)<<endl;
			d3=1;
			rep(k, i) d3*=3;
			d5=1;
			rep(k, j) d5*=5;
			if(d3==n-d5){
				cout<< i << " " << j <<endl;
				return 0;
			}
		}
	}

	cout<< "-1" << endl;
 
	return 0;
}