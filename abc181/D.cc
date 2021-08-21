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

	int d=0, flag, tmp;
	string s;
	vector<int> v(10), ob;

	cin>> s;

	v[0]=max(0, 3-(int)(s.size()));

	rep(i, s.size()) v[(int)(s[i]-'0')]++;
	//PV(v);

	while(d<1000){
		ob.clear();
		ob.resize(10);
		tmp=d;
		ob[tmp%10]++;
		tmp/=10;
		ob[tmp%10]++;
		tmp/=10;
		ob[tmp%10]++;

		//cout<< d <<endl;
		//rep(i, 10) cout<< ob[i] <<" ";
		//cout<< endl;
		d+=8;

		if(s.size()<3 && d>100 && ob[0]>0) continue;

		flag=1;
		if(v[0]!=ob[0]) flag=0;
		for(int i=1;i<10;i++){
			//cout<< v[i] << " " << ob[i] <<endl;
			if(v[i]<ob[i]){
				flag=0;
				break;
			}
		}
		if(flag){
			cout<< "Yes" <<endl;
			return 0;
		}
	}
 
	cout<< "No" <<endl;

	return 0;
}