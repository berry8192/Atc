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
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
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

	LLi x;
	int flag, prv, xhd, xlen;
	string tmp, ans;

	cin>> x;

	if(x<100000){
		while(1){
			//cout<< x <<endl;
			flag=1;
			tmp=to_string(x);
			rep(j, tmp.size()-1){
				if(j && int(tmp[j]-tmp[j+1])!=prv){
					flag=0;
					break;
				}
				prv=int(tmp[j]-tmp[j+1]);
			}
			if(flag){
				cout<< x <<endl;
				return 0;
			}
			x++;
		}
	}else{
		tmp=to_string(x);
		xhd=int(tmp[0]-'0');
		xlen=tmp.size();
		while(1){
			if(xhd>=xlen-1){
				//down
				ans="";
				rep(i, xlen){
					ans+=to_string(xhd-i);
				}
				if(x<=stoll(ans)){
					cout<< ans <<endl;
					return 0;
				}
			}

			//same
			ans="";
			rep(i, xlen){
				ans+=to_string(xhd);
			}
			if(x<=stoll(ans)){
				cout<< ans <<endl;
				return 0;
			}

			if(10-xhd>=xlen){
				//up
				ans="";
				rep(i, xlen){
					ans+=to_string(xhd+i);
				}
				if(x<=stoll(ans)){
					cout<< ans <<endl;
					return 0;
				}
			}
			xhd++;
			if(xhd==10){
				xhd=1;
				xlen++;
			}
		}
	}
 
	return 0;
}