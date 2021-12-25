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

	int tmp, su=0, dup, cnt, lp=0, sz;
	string x, ans;
	vector<int> v(500010);

	cin>> x;
	sz=x.size();
	reverse(all(x));
	
	rep(i, sz) su+=int(x[i]-'0');
	cout<< su <<endl;//

	for(int i=0;i<max(sz, lp);i++){
		dup=su+v[i];
		cnt=0;
		while(dup){
			v[i+cnt]=dup%10;
			dup/=10;
			lp=max(lp, i+cnt);
			cnt++;
			cout<< "cnt " << cnt <<endl;
		}
		ans+='0'+v[i];
		if(su) su-=int(x[i]-'0');
		cout<< su <<endl;
	}

	reverse(all(ans));
	cout<< ans << endl;
 
	return 0;
}