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

vector<ll> pri={1, 2, 3};

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

//n以下の素数を配列に{1, 2, 3, 5, 7, ...} make_prime_list
//i, j, flag, sqx, xを使用
void mplist(ll x){
	int flag;

	for(int i=5;i<=x;i+=2){
		flag=0;
		for(int j=1;j<(int)pri.size();j++){
			if(i%pri[j]==0){
				flag=1;
				break;
			}
			if(x<pri[j]*pri[j]) break;
		}
		if(flag==0) pri.emplace_back(i);
	}
}

//nを素因数分解 root_prime_fac
//i, tmp, bin, lmt, xを使用
map<ll, int> rpfac(ll x){
	int sqx=ceil(sqrt(x));
	//cout<< "sqx=" << sqx SP << sqx*sqx << endl;//
	auto bin = lower_bound(all(pri), sqx);
	int lmt=bin-pri.begin()+1;
	map<ll, int> tmp;
	//cout<< "lmt=" << lmt SP << pri[lmt] SP << pri[lmt]*pri[lmt] <<endl;//
	if((int)pri.size()<lmt) cout<< "rpfac: pri size is small" <<endl;

	for(int i=1;i<lmt;i++){
		while(x%pri[i]==0){
			x/=pri[i];
			tmp[pri[i]]++;
			//cout<< x <<endl;
			//tmp[0]++;//0番に何個の積でできてるかをメモれる
		}
		if(x==1) break;
	}

	//if(x!=1) cout<< "prime_fac x=" << x <<endl;
	return tmp;
}

//階乗を素因数分解
map<ll, int> facfac(ll x){
	map<ll, int> tmp;
	auto bin = lower_bound(all(pri), x);
	int lmt=bin-pri.begin()+1;
  	//cout<< "lmt=" << lmt SP << pri[lmt] SP << pri[lmt]*pri[lmt] <<endl;//

	for(ll i=1;i<lmt;i++){
		int lp=0, di=0;
		while(pow(pri[i], lp)<x){
			lp++;
			di+=x/pow(pri[i], lp);
		}
		if(di>0) tmp[pri[i]]=di;
	}
	
	return tmp;
}

//約数列挙
//i, j, k, tmp, mul, mを使用
vector<ll> getfac(map<ll, int> mp){
	vector<ll> tmp={1}, ad;
	ll mul;
	
	for (auto p : mp) {
		mul=1;
		ad.clear();
  		ll key = p.first;
  		int value = p.second;
		  
		rep(j, value){
			mul*=key;
			rep(k, tmp.size()) ad.push_back(tmp[k]*mul);
		}
		rep(j, ad.size()) tmp.push_back(ad[j]);
		//PV(tmp);//
	}

	/*for(int i=1;i<v.size();i++){
		if(v[i]==0) continue;
		mul=1;
		ad.clear();
		rep(j, v[i]){
			mul*=pri[i];
			rep(k, tmp.size()){
				ad.push_back(tmp[k]*mul);
			}
		}
		//PV(tmp);
		rep(j, ad.size()) tmp.push_back(ad[j]);
	}*/

	sort(all(tmp));
	return tmp;
}

//素因数の積を計算
//i, tmp, vを使用
ll defac(map<ll, int> mp){
	ll tmp=1;

	/*for(int i=1;i<v.size();i++){
		if(v[i]!=0) tmp*=pow(pri[i], v[i]);
	}*/

	for (auto p : mp) {
  		ll key = p.first;
  		int value = p.second;
		tmp*=pow(key, value);
	}

	return tmp;
}

bool isp(ll x){
	//if(x==1) return false;//1を素数としないなら有効化
	auto ub = upper_bound(all(pri), x);
	auto lb = lower_bound(all(pri), x);

	//xがでかいときは素数リストで割ってみる
	if(lb==pri.end()){
		for(int i=1;i<(int)pri.size();i++){
			if(x%pri[i]==0) return false;
			if(x<pri[i]*pri[i]) return true;
		}
		//cout<< "isp: pri size is small" <<endl;

		//priのサイズが足りないときは地道にチェックする
		for(ll i=pri[pri.size()-1]+2;i*i<=x;i+=2){
			if(x%i==0) return false;
		}
		return true;
	}

	return ub!=lb;
}

int main(){

	ll m, ans=1;

	ll ml, ma=0;
	vector<ll> v;
	map<ll, int> mp;

	cin>> m;

	mplist(1100000);//nまでの素数列挙
	//PVL(pri);//
	mp=rpfac(m);//mを√mまで素因数分解
	ml=defac(mp);//mlにmpの総積を代入
	//cout<< "m/ml=" << m/ml SP << isp(m/ml) <<endl;//
	if(m!=ml) mp[m/ml]++;//mpにm/mlを追加(√m以上の素数が約数の場合に必要な処理)
	//mの約数で√m以上の素数は1つしかないのでこれでOK

	//mp=facfac(n);

	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
		ma=key;
		// cout<< key << "^" << value SP;//mpの内訳を表示

	}
	// cout<< endl;//
	//cout<< defac(mp) <<endl;//
	if(ma>int(sqrt(m))){
		cout<< ma <<endl;
		return 0;
	}

	ll lp=1;
	while(1){
		lp++;
		ll tmp=__gcd(lp, m);
		m/=tmp;
		if(m==1){
			cout<< lp <<endl;
			return 0;
		}
	}
 
	return 0;
}