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
LLi mod=998244353;
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

	int h, w, k, cnt=0;
	LLi x1, y1, x2, y2;
	vector<LLi> ans(4, 0), nxt(4);
	//none, h, w hw

	cin>> h >> w >> k;
	cin>> x1 >> y1 >> x2 >> y2;

	if(x1==x2) cnt+=1;
	if(y1==y2) cnt+=2;
	//cout<< cnt <<endl;
	ans[cnt]++;

	rep(i, k){
		nxt[0]=(ans[0]*(h+w-4))%mod;
		nxt[0]+=(ans[1]*(h-1))%mod;
		nxt[0]+=(ans[2]*(w-1))%mod;
		nxt[0]=nxt[0]%mod;

		nxt[1]=ans[0];
		nxt[1]+=(ans[1]*(w-2))%mod;
		nxt[1]+=(ans[3]*(w-1))%mod;
		nxt[1]=nxt[1]%mod;

		nxt[2]=ans[0];
		nxt[2]+=(ans[2]*(h-2))%mod;
		nxt[2]+=(ans[3]*(h-1))%mod;
		nxt[2]=nxt[2]%mod;

		nxt[3]=ans[1]+ans[2];
		nxt[3]=nxt[3]%mod;

		// PV(nxt);
		// PV(ans);
		// cout<< endl;
		rep(j, 4){
			ans[j]=nxt[j];
			//ans[j]=ans[j]%mod;
		}
	}

	cout<< ans[3] << endl;
 
	return 0;
}