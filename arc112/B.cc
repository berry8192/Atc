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

	LLi b, c, l1, r1, l2, r2, ans;

	cin>> b >> c;

		r1=-b+(c-1)/2;
		l1=-b-(c-1)/2;
		l2=b-c/2;
		r2=b+(c-2)/2;

	if(l1>=l2){
		swap(l1, l2);
		swap(r1, r2);
	}

	//cout<< l1 SP << r1 <<endl;
	//cout<< l2 SP << r2 <<endl;

	if(r1<l2){
		ans=r1-l1+1+r2-l2+1;
	}else{
		ans=max(r2, r1)-l1+1;
	}
	
	cout<< ans << endl;
 
	return 0;
}