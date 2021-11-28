#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	int n, tmp, cnt=1;
	vector<int> v, mg;
	string ans="";

	cin>> n;
	
	//PV(v);
int m=n;
rep3(j, m, 1){
	mg.clear();
	v.clear();
	n=j;
	cnt=1;
	
	rep(i, 10000){
		tmp=(i+2)*(i+1)/2;
		if(tmp>n) break;
		v.push_back(tmp);
	}

	n-=v[v.size()-1];
	mg.push_back(v.size());

	while(n>0){
		rep(i, v.size()){
			if(v[i]<=n && n<v[i+1]){
				n-=v[i];
				mg.push_back(i+1);
				cnt++;
				break;
			}
		}
	}
	//PV(mg);
	cout<< j SP << cnt <<endl;
}
 
	return 0;
}