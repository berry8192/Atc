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

	int n, ans=0, flag=0;
	string s, x;
	vector<int> ten(1), v;
	bool dp[7][200010];
	bool dp2[7][200010];

	cin>> n;
	cin>> s >> x;

    ten[0]=1;
  	rep(i, n-1) ten.push_back((ten[i]*10)%7);
	//reverse(ten.begin(), ten.end());
	//PV(ten);
	
	reverse(s.begin(), s.end());
	reverse(x.begin(), x.end());
	x.push_back('0');

	rep(i, n){
		v.push_back((ten[i]*(int)(s[i]-'0'))%7);
	}
	PV(v);

	//cout<< s <<endl;
	//cout<< x <<endl;

	rep(i, 7) dp[i][0]=false;
	rep(i, 7) dp2[i][0]=false;
	rep(i, n){
		if(flag==0){
			if(x[i]=='A' && v[i]!=0){
				cout<< "Aoki" <<endl;
				return 0;
			}
			if(x[i]=='T') flag=1;
		}

		rep(j, 7){
			if(x[i]=='T') dp[j][i+1]=dp[j][i];
			else dp[j][i+1]=false;
		}
		rep(j, 7){
			if(x[i]=='A') dp2[j][i+1]=dp2[j][i];
			else dp2[j][i+1]=false;
		}
		rep(j, 7){
			if(x[i]=='T' && dp[j][i]){
				dp[j][i+1]=true;
				dp[(j+v[i])%7][i+1]=true;
			}
		}
		rep(j, 7){
			if(x[i]=='A' && dp2[j][i]){
				dp2[j][i+1]=true;
				dp2[(j+v[i])%7][i+1]=true;
			}
		}
		if(x[i]=='T' && x[i]!=x[i+1]){

		}
		if(x[i]=='A' && x[i]!=x[i+1]){
			
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}