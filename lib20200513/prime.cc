#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<int> pri={1};

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

bool VVL(vector<LL1> vv1, vector<LLi> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//n以下の素数を配列に{1, 2, 3, 5, 7, ...} make_prime_list
//i, j, flag, sqx, xを使用
void mplist(LLi x){
	int flag, sqx;
	pri.emplace_back(2);

	for(int i=3;i<=x;i+=2){
		flag=0;
		sqx=(int)sqrt(x)+1;
		for(int j=1;j<(int)pri.size();j++){
			if(i%pri[j]==0){
				flag=1;
				break;
			}
			if(sqx<pri[j]) break;
		}
		if(flag==0) pri.emplace_back(i);
	}
}

//nを素因数分解 root_prime_fac
//i, tmp, bin, lmt, xを使用
map<LLi, int> rpfac(LLi x){
	int sqx=ceil(sqrt(x));
	//cout<< "sqx=" << sqx SP << sqx*sqx << endl;//
	auto bin = lower_bound(pri.begin(), pri.end(), sqx);
	int lmt=bin-pri.begin()+1;
	map<LLi, int> tmp;
	//cout<< "lmt=" << lmt SP << pri[lmt] SP << pri[lmt]*pri[lmt] <<endl;//
	if(pri.size()<lmt) cout<< "rpfac: pri size is small" <<endl;

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

//約数列挙
//i, j, k, tmp, mul, mを使用
vector<LLi> getfac(map<LLi, int> mp){
	vector<LLi> tmp={1}, ad;
	LLi mul;
	
	for (auto p : mp) {
		mul=1;
		ad.clear();
  		LLi key = p.first;
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

//素数判定 is_prime
//ub, lb, x, iを使用
bool isp(LLi x){
	//if(x==1) return false;//1を素数としないなら有効化
	auto ub = upper_bound(all(pri), x);
	auto lb = lower_bound(all(pri), x);

	//xがでかいときは素数リストで割ってみる
	if(lb==pri.end()){
		for(int i=1;i<(int)pri.size();i++){
			if(x%pri[i]==0) return false;
			if(x<pri[i]*pri[i]) return true;
		}
		cout<< "isp: pri size is small" <<endl;
	}

	return ub!=lb;
}

int main(){

	LLi n, m, ml;
	vector<LLi> v;
	map<LLi, int> mp;

	cin>> n >> m;

	mplist(n);//nまでの素数列挙
	//PV(pri);//

	mp=rpfac(m);//mを√mまで素因数分解

	ml=defac(mp);//mlにmpの総積を代入
	//cout<< "m/ml=" << m/ml SP << isp(m/ml) <<endl;//
	if(m!=ml) mp[m/ml]++;//mpにm/mlを追加(√m以上の素数が約数の場合に必要な処理)
	//mの約数で√m以上の素数は1つしかないのでこれでOK

	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
		cout<< key << "^" << value SP;//mpの内訳を表示
	}
	cout<< endl;//

	//cout<< isp(m) <<endl;//素数判定
	
	v=getfac(mp);//素因数分解から約数を列挙
	PVL(v);

	//愚直に約数を判定
	/*for(int i=1;i<=m;i++){
		if(m%i==0) cout<< i SP;
	}
	cout<< endl;*/

	//O(√m)で約数を判定
	int fsz;
	vector<LLi> f;
	for(LLi i=1;i<=ceil(sqrt(m));i++){
		if(m%i==0) f.push_back(i);
	}
	fsz=f.size();
	reverse(all(f));
	rep(i, fsz) f.push_back(m/f[i]);
	sort(all(f));
	PVL(f);

	return 0;
}