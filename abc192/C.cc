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

	int n, k, tmp1, tmp2, ans, t;
	vector<int> d;
	string s;

	cin>> n >> k;
	ans=n;

	rep(i, k){
		if(ans==0) break;
		s=to_string(ans);
		d.clear();
		d.resize(10);
		for(int j=0;j<s.size();j++){
			d[(int)(s[j]-'0')]++;
		}
		//PV(d);
		tmp1=0;
		tmp2=0;
		t=1;
		for(int j=0;j<10;j++){
			for(int l=0;l<d[j];l++){
				tmp1+=j*t;
				t*=10;
			}
		}
		t=1;
		for(int j=9;j>=0;j--){
			for(int l=0;l<d[j];l++){
				tmp2+=j*t;
				t*=10;
			}
		}
		//cout<< tmp1 SP <<tmp2 <<endl;
		ans=tmp1-tmp2;
	}
	
	cout<< ans << endl;
 
	return 0;
}