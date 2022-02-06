#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <map>
#include <cmath>

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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

vector<LLi> pri={1, 2, 3};

//n以下の素数を配列に{1, 2, 3, 5, 7, ...} make_prime_list
//i, j, flag, sqx, xを使用
void mplist(LLi x){
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
map<LLi, int> rpfac(LLi x){
	int sqx=ceil(sqrt(x));
	//cout<< "sqx=" << sqx SP << sqx*sqx << endl;//
	auto bin = lower_bound(all(pri), sqx);
	int lmt=bin-pri.begin()+1;
	map<LLi, int> tmp;
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


//素因数の積を計算
//i, tmp, vを使用
LLi defac(map<LLi, int> mp){
	LLi tmp=1;

	/*for(int i=1;i<v.size();i++){
		if(v[i]!=0) tmp*=pow(pri[i], v[i]);
	}*/

	for (auto p : mp) {
  		LLi key = p.first;
  		int value = p.second;
		tmp*=pow(key, value);
	}

	return tmp;
}

int main(){

	LLi n, m, ml, q;
	vector<LLi> v, l, r;
	vector< vector<LLi> > bo(10000);
	map<LLi, int> mp;

	cin>> n >> q;
	v.resize(n);
	l.resize(q);
	r.resize(q);

	mplist(100100);//nまでの素数列挙
	//cout<< pri.size() <<endl;

	rep(i, n) cin>> v[i];
	rep(i, q) cin>> l[i] >> r[i];

	rep(i, n){
		mp.clear();
		mp=rpfac(m);//mを√mまで素因数分解
		ml=defac(mp);//mlにmpの総積を代入

	}
	//cout<< "m/ml=" << m/ml SP << isp(m/ml) <<endl;//
	if(m!=ml) mp[m/ml]++;//mpにm/mlを追加(√m以上の素数が約数の場合に必要な処理)
	//mの約数で√m以上の素数は1つしかないのでこれでOK

	//mp=facfac(n);

	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
		cout<< key << "^" << value SP;//mpの内訳を表示
	}
	cout<< endl;//
	//cout<< defac(mp) <<endl;//

	// if(isp(m)) cout<< "Yes" <<endl;
    // else cout<< "No" <<endl;
	
	// v=getfac(mp);//素因数分解から約数を列挙
	// PVL(v);

	//愚直に約数を判定
	/*for(int i=1;i<=m;i++){
		if(m%i==0) cout<< i SP;
	}
	cout<< endl;*/

	//O(√m)で約数を判定
	int fsz;
	vector<LLi> f;
	for(LLi i=1;i*i<m;i++){
		if(m%i==0) f.push_back(i);
	}
	fsz=f.size();
	if((int)sqrt(m)*(int)sqrt(m)==m) f.push_back((int)sqrt(m));//平方根が約数の場合
	rep(i, fsz) f.push_back(m/f[fsz-1-i]);

	return 0;
}
