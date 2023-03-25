#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
using mint = modint998244353;

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

vector<mint> fac(1), facin(1);
mint conb(ll x, ll y){
	if(x<y) cout<< "conb x<y" << x SP << y <<endl;
	return ((fac[x]*facin[y])*facin[x-y]);
}

int main(){

	int n, m, k, ze=0, tmp;
	mint ans=0;
	vector<int> v, fig(2010);

	mint mtmp;
	fac[0]=1;
	facin[0]=1;
	for(int i=1;i<=2010;i++){
		mtmp=fac[i-1];
		mtmp*=i;
		fac.push_back(tmp);
		facin.push_back(mtmp.inv());
		//cout<< fac[i] << " " << facin[i] << " " << (fac[i]*facin[i])%mod <<endl;
	}

	cin>> n >> m >> k;

	rep(i, n){
		cin>> tmp;
		if(tmp!=0){
			v.push_back(tmp);
			fig[tmp]++;
		}else{
			ze++;
		}
	}
	sort(all(v));

	rep3(i, 6, 1) {
		cout<< "i: " << i <<endl;
		// 答えがiになる
		auto lb=lower_bound(all(v), i);
		cout<< "sm: " << int(lb-v.begin()) <<endl;
		int sm=int(lb-v.begin());
		rep(j, ze+1){
			cout<< "j: " << j <<endl;
			// 0からiはj個できる
			mint base=(mint(m).inv()).pow(j);
			cout<< "1/" << m << "^" << j <<endl;
			int ifig=j+fig[i];
			if(ifig==0) continue;
			cout<< "ifig: " << ifig <<endl;
			// iはifig個
			// 目的の数字未満の数字を何回出すのか、mi<=x<=ma
			int mi=max(0, k-(sm+ifig));
			int ma;
			if(k-(sm+1)<0) continue;
			ma=k-(sm+1);
			if(ze-j<mi) continue;
			cout<< mi SP << ma <<endl;
			mint mip=(i-1)/mint(m);
			ans+=i*base*conb(ze-j, mi)*(mip.pow(mi))*(mint(m-i-1)/mint(m)).pow(ze-j-mi);
			if(ze-j>=ma+1) ans-=i*base*conb(ze-j, mi)*(mip.pow(ma+1))*(mint(m-i-1)/mint(m)).pow(ze-j-mi);
			cout<< "# " << ans.val() <<endl;
		}
	}

	cout<< ans.val() << endl;
 
	return 0;
}