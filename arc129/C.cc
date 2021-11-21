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
	vector<int> v, mg, usd, usn, ts(8), d7={1, 3, 2, 6, 4, 5};
	string ans="";

	cin>> n;
	if(n==2){
		cout<< "717" <<endl;
		return 0;
	}
	
	rep(i, 10000){
		tmp=(i+2)*(i+1)/2;
		if(tmp>n) break;
		v.push_back(tmp);
	}
	//PV(v);

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
	//cout<< cnt <<endl;
	rep(i, mg.size()){
		rep(j, mg[i]) ans+="7";
		// rep(j, 7) ts[i+1]=1;
		// rep(j, usd.size()){
		// 	rep3(l, 7, 1){
		// 		if( (usn[j] + d7[(ans.size()+1-usd[j])%6+1]*l)%7==0) ts[l]=0;
		// 	}
		// }
		// rep(j, 7){
		// 	if(ts[j+1]){
		// 		ans+=to_string(j+1);
		// 		usd.push_back(ans.size());
		// 		usn.push_back(j+1);
		// 		break;
		// 	}
		// }
		ans+=to_string(5-i+1);
	}

	cout<< ans <<endl;
 
	return 0;
}