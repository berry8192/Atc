#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod2=1000000007;
ll mod=998244353;

int main(){

	int t, n;
	ll k;
	string s;
	cin>> t;
	rep(lp, t){
		cin>> n >> k;
		cin>> s;
		int flag=1;
		rep(i, n-1){
			if(s[i]!=s[i+1]){
				flag=0;
				break;
			}
		}
		if(flag || n==k){
			cout<< "Yes" <<endl;
			continue;
		}
		int tmp2=-1;
		rep(i, n){
			int flag=1;
			// cout<< "i:" << i <<endl;
			rep(j, (n-i)/2){
				// cout<< s[j] SP << s[n-1-i-j] <<endl;
				if(s[j]!=s[n-1-i-j]){
					flag=0;
					break;
				}
			}
			if(flag){
				tmp2=i;
				break;
			}
		}
		// cout<< tmp2 <<endl;
		// cout<< k%n <<endl;
		if(tmp2==0 || n<k && k%tmp2==0){
			cout<< "Yes" <<endl;
			continue;
		}
		// cout<< k%n <<endl;
		string tmp;
		repr(i, k) tmp+=s[i];
		tmp+=s;
		// cout<< tmp <<endl;
		flag=1;
		rep(i, tmp.size()/2){
			if(tmp[i]!=tmp[tmp.size()-1-i]){
				// cout<< tmp[i] SP << tmp[tmp.size()-1-i] << endl;
				flag=0;
				break;
			}
		}
		if(flag){
			cout<< "Yes" <<endl;
		}else{
			cout<< "No" << endl;
		}
	}

	return 0;
}