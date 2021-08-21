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

	LLi n, tmp=0;
	vector<LLi> v;
	cin>> n;

	for(LLi i=1;i*i<=n;i++){
		if(n%i==0){
			v.push_back(i);
			if(n!=i*i) v.push_back(n/i);
		}
	}

	for(LLi i=0;i<v.size();i++){
		//cout<< n%i <<endl;
		if(v[i]%2){
			if(n%v[i]==0) tmp++;
		}else{
			if(n%v[i]==v[i]/2) tmp++;
		}
		//cout<< i SP << tmp <<endl;
	}
	
	cout<< tmp*2 << endl;
 
	return 0;
}