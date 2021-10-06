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

	int n, ans=0;
	vector<int> t;
	vector<double> l, r;

	cin>> n;
	t.resize(n);
	l.resize(n);
	r.resize(n);

	rep(i, n){
		cin >> t[i] >> l[i] >> r[i];
		if(t[i]>=3) l[i]+=0.1;
		if(t[i]%2==0) r[i]-=0.1;
	}

	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(l[i]<=l[j] && l[j]<=r[i]){
				ans++;
			}else if(l[j]<=l[i] && l[i]<=r[j]){
				ans++;
			}
		}
	}
	cout<< ans << endl;
 
	return 0;
}