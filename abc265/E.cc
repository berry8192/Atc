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
ll mod=998244353;

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

struct pos{
	ll x;
	ll y;

	bool operator<(const pos &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
};

ll dp[310][310][310];
ll pox[310][310][310];
ll poy[310][310][310];

int main(){

	ll n, m, ans=0;
	vector<ll> v(6), x, y;
	set<pos> st;

	cin>> n >> m;
	x.resize(m);
	y.resize(m);

	// ll jjj=1;
	// rep(i, n){
	// 	jjj*=3;
	// 	jjj%=mod;
	// }
	// cout<< jjj <<endl;
	// return 0;

	rep(i, 6) cin>> v[i];
	rep(i, m){
		cin>> x[i] >> y[i];
		pos tmp;
		tmp.x=x[i];
		tmp.y=y[i];
		st.insert(tmp);
	}
	
	dp[0][0][0]=1;
	rep(i, 310){
		rep(j, 310){
			rep(k, 310){
				dp[i][j][k]=0;
				pox[i][j][k]=v[0]*i+v[2]*j+v[4]*k;
				poy[i][j][k]=v[1]*i+v[3]*j+v[5]*k;
			}
		}
	}

	dp[0][0][0]=1;

	rep3(i, n+1, 1) {
		//cout<< "i:" << i <<endl;
	//rep3(i, 301, 1) {
		int c;
		pos tmp;
		//int cnt=0;
		rep(a, i+1){
			//cout<< "a:" << a <<endl;
			rep(b, i+1-a){
				//cout<< "b:" << b <<endl;
				c=i-a-b;
				if(c<0 && i<c) continue;
				//cout<< a SP << b SP << c SP;
				//cnt++;
				tmp.x=pox[a][b][c];
				tmp.y=poy[a][b][c];
				bool flag=st.find(tmp)!=st.end();
				if(flag && m!=0) continue;

				if(a!=0){
					// tmp.x=pox[a-1][b][c];
					// tmp.y=poy[a-1][b][c];
					// bool aa=st.find(tmp)==st.end();
					//if(!aa) cout<<"#"<<endl;
					//if(v[0]!=0 || v[1]!=0) 
					dp[a][b][c]+=dp[a-1][b][c];
				}
				if(b!=0){
					// tmp.x=pox[a][b-1][c];
					// tmp.y=poy[a][b-1][c];
					// bool bb=st.find(tmp)==st.end();
					//if(!bb) cout<<"#"<<endl;
					//if(v[2]!=0 || v[3]!=0) 
					dp[a][b][c]+=dp[a][b-1][c];
				}
				if(c!=0){
					// tmp.x=pox[a][b][c-1];
					// tmp.y=poy[a][b][c-1];
					// bool cc=st.find(tmp)==st.end();
					//if(!cc) cout<<"#"<<endl;
					//if(v[4]!=0 || v[5]!=0) 
					dp[a][b][c]+=dp[a][b][c-1];
				}
				//cout<< dp[a][b][c] <<endl;
				dp[a][b][c]%=mod;
				if(i==n){
					ans+=dp[a][b][c];
					ans%=mod;
				}
			}
		}
		//cout<< cnt <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}