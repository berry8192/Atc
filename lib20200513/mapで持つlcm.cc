//ABC152-E Flatten より
#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<LLi> pri={1, 2, 3};
LLi mod=1000000007;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}
 
LLi modinv(LLi a) {
    LLi b = mod, u = 1, v = 0;
    while (b) {
        LLi t = a / b;
        a -= t * b; swap(a, b);
        u -= t * v; swap(u, v);
    }
    u %= mod;
    if (u < 0) u += mod;
    return u;
}

LLi gcd(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcd(b, a%b);
}

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

LLi defac(map<LLi, int> mp){
	LLi tmp=1;

	/*for(int i=1;i<v.size();i++){
		if(v[i]!=0) tmp*=pow(pri[i], v[i]);
	}*/

	for (auto p : mp) {
  		LLi key = p.first;
  		int value = p.second;
		tmp*=pow(key, value);
      	tmp=tmp%mod;//mod算
	}

	return tmp;
}

int main(){

	//n個からなる整数たちをvに保持
	//mlは素因数分解に使う
	//mpに各数字の素因数分解を保持
	//lcmpが最小公倍数の素因数分解を表すmap
	LLi n, lc, ml, ans=0;
  	vector<LLi> v;
	map<LLi, int> mp, lcmp;
  
  	cin>> n;
  	v.resize(n);
  	rep(i, n) cin>> v[i];
  
	//v[i]<=1e9 だろうし1e5までの素数列挙
  	mplist(101000);
  
	//n個の要素についてlcmを求める
  	rep(i, n){
		//素数リストpriを用いて素因数分解
  		mp=rpfac(v[i]);
		//v[i]が√v[i]を超える約数を持っていた場合の処理
  		ml=defac(mp);
      	if(v[i]!=ml) mp[v[i]/ml]++;
      
	  	//mpの各keyに対する最大の指数を求めていくことが原理的に最小公倍数を求める行為になる
		//v={2, 4, 6} のとき、
		//key=2の指数は{1, 2, 1}でmax=2
		//key=3の指数は{0, 0, 1}でmax=1
		//（補足として）key=5はmax=0
		//それぞれのmaxを合わせると2^2*3^1*5^0=12となり、これがlcmとなる
      	for (auto p : mp) {
  			auto key = p.first;
  			auto value = p.second;
          	lcmp[key]=max(lcmp[key], value);
        }
	}
  	
  	lc=defac(lcmp);
	//defacにmod算を入れてある
  
  	rep(i, n){
      	ans+=lc*modinv(v[i]);
      	ans=ans%mod;
    }
  
  	cout<< ans << endl;
  
	return 0;
}
