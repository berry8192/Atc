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

	int n, q, fl=0, t, a, b, ans=0;
	string s;
	char tmp;

	cin>> n;
	cin>> s;
	cin>> q;

	rep(i, q) {
		cin>> t >> a >> b;
		if(t==1){
			if(fl==0){
				tmp=s[a-1];
				s[a-1]=s[b-1];
				s[b-1]=tmp;
			}else{
				if(a<=n) a=a+n;
				else a=a-n;
				if(b<=n) b=b+n;
				else b=b-n;
				tmp=s[a-1];
				s[a-1]=s[b-1];
				s[b-1]=tmp;
			}
		}else{
			fl=1-fl;
		}
	//cout<< s <<endl;
	}

	if(fl){
		for(int i=n;i<2*n;i++) cout<< s[i];
		for(int i=0;i<n;i++) cout<< s[i];
	}else{
		cout<< s <<endl;
	}

	return 0;
}