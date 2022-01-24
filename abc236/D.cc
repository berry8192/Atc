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
LLi n, ans=0;
LLi v[18][18];

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, 4){
		rep(j, 4){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

void dfs(vector<bool> p, LLi x){
	//PV(p);
	//cout<< x <<endl;
	int flag=0;
	LLi tmp, fst, snd;
	rep(i, 2*n){
		if(p[i] && flag==0){
			fst=i;
			flag=1;
			p[i]=false;
		}else if(p[i] && flag){
			snd=i;
			if(fst>snd) swap(fst, snd);
			tmp=v[fst][snd-fst-1];
			//cout<< "dfs " << fst SP <<snd SP << tmp <<endl;
			tmp=x^tmp;
			p[i]=false;
			dfs(p, tmp);
			p[i]=true;
		}
	}
	if(flag==0) ans=max(ans, x);
}

int main(){

	vector<bool> p;

	cin>> n;
	p.resize(2*n, true);

	rep(i, 2*n){
		rep(j, 2*n-i-1) cin >> v[i][j];
	}
	
	//PVV(v);

	dfs(p, 0);

	cout<< ans << endl;
 
	return 0;
}