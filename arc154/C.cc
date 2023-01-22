#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

	int t;

	cin>> t;
	rep(lp, t){
		// cout<< "lp: " << lp <<endl;
		int n;
		cin>> n;
		vector<int> a(n), b(n);
		rep(i, n) cin >> a[i];
		rep(i, n) cin >> b[i];
		int flag=1;
		rep(i, n){
			if(a[i]!=b[i]){
				flag=0;
				break;
			}
		}
		if(flag){
			cout<< "Yes" <<endl;
			continue;
		}
		vector<int> aa, bb;
		int prv=-1;
		rep(i, n){
			if(prv!=a[i]) aa.push_back(a[i]);
			prv=a[i];
		}
		if(aa.size()>1 && aa[0]==aa[aa.size()-1]) aa.pop_back();
		aa.push_back(aa[0]);
		prv=-1;
		rep(i, n){
			if(prv!=b[i]) bb.push_back(b[i]);
			prv=b[i];
		}
		if(bb.size()>1 && bb[0]==bb[bb.size()-1]) bb.pop_back();
		// cout<< "A ";
		// PV(aa);
		// cout<< "B ";
		// PV(bb);
		if(bb.size()==n){
			cout<< "No" <<endl;
			continue;
		}
		flag=0;
		rep(i, bb.size()){
			// i=スタート地点
			int pos=0;
			rep(j, bb.size()){
				while(pos<aa.size()){
					// cout<< s[i] SP << t[pos] <<endl;
					if(bb[(j+i)%bb.size()]==aa[pos]){
						if(j==bb.size()-1){
							cout<< "Yes" <<endl;
							flag=1;
							break;
						}
						pos++;
						break;
					}else{
						pos++;
					}
				}
				if(pos==n && flag==0){
					break;
				}
			}
			if(flag) break;
		}
		if(flag) continue;
		cout<< "No" << endl;
	}
 
	return 0;
}