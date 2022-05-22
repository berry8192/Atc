#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<LLi> pri={1, 2, 3};

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
	}

	return tmp;
}

//オイラーのファイ関数
int eufai(LLi x){
	LLi ml, ans=0;
	map<LLi, int> mp;
	vector<LLi> vx;
	
	mplist((LLi)sqrt(x)+1000);//nまでの素数列挙何度も使うならmain内へ
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
		LLi mul=1;
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