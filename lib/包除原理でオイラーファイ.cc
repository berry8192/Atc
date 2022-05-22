#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

vector<ll> pri={1, 2, 3};

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

//オイラーのファイ関数
int eufai(ll x){
	ll ml, ans=0;
	map<ll, int> mp;
	vector<ll> vx;
	
	mplist((ll)sqrt(x)+1000);//nまでの素数列挙何度も使うならmain内へ
	mp=rpfac(x);//xを√xまで素因数分解
	ml=defac(mp);
	if(x!=ml) mp[x/ml]++;

	for (auto p : mp) {
  		auto key = p.first;
		vx.push_back(key);
	}

	int M=vx.size();
	for(int bit=1;bit<(1<<M);bit++){
		int popcnt=__builtin_popcount(bit);
		ll mul=1;
		for(int i=0;i<M;i++){
			if(bit>>i&1) mul*=vx[i];
		}
		if(popcnt%2==1) ans+=x/mul;
		else ans-=x/mul;
	}

	ans=x-ans;
	return ans;
}

int main(){

	int n;
	cin>> n;

	//オイラーのファイ関数を返す
	cout<< eufai(n) <<endl;

	return 0;
}