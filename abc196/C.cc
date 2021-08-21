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

	LLi n, tmp, sz, ans=0;
	LLi tn[]={1, 10, 100, 1000, 10000, 100000, 1000000};

	cin>> n;

	for(LLi i=1;i<1000000;i++){
		sz=to_string(i).size();
		tmp=tn[sz]*i+i;
		if(n<tmp) break;
		ans++;
		//cout<<tmp<<endl;
	}

	cout<< ans << endl;
 
	return 0;
}