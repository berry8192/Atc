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

LLi popcount1(LLi x) {  
 LLi ret = 0;  
  
 for (int i = 0; i < 32; i++)  
     ret += x >> i & 1;  
  
 return ret;  
}  

int main(){

	LLi x, y, tmp1, tmp2, cnt=0, ans1, ans2;
	bitset<64> bi1, bi2;

	cin>> x >> y;

	if(x>=y){
		cout<< x-y <<endl;
		return 0;
	}

	tmp1=x;
	tmp2=x;
	while(1){
		tmp2*=2;
		cnt++;
		if(tmp2==y){
			cout<< cnt <<endl;
			return 0;
		}else if(tmp2>y){
			break;
		}
		tmp1=tmp2;
	}

	tmp1=popcount1(tmp1);
	tmp2=popcount1(tmp2);

	ans1=tmp1+cnt-1;
	ans2=tmp2+cnt;

	cout<< min(ans1, ans2) << endl;
	//cout<< ans1 SP << ans2 << endl;
 
	return 0;
}