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

	LLi x, y, a, b, ans=0;

	cin>> x >> y >> a >> b;

	while(1){
		if((a-1)<(double)b/x && a<(double)y/x){
			x*=a;
		}else{
			if(x+b<y) ans+=(y-1-x)/b;
			break;
		}
		ans++;
	}

	cout<< ans << endl;
 
	return 0;
}