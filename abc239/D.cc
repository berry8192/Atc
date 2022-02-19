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
		//cout<< "isp: pri size is small" <<endl;

		//priのサイズが足りないときは地道にチェックする
		for(LLi i=pri[pri.size()-1]+2;i*i<=x;i+=2){
			if(x%i==0) return false;
		}
		return true;
	}

	return ub!=lb;
}

int main(){

	int a, b, c, d;
	mplist(300);

	cin>> a >> b >> c >> d;

	rep3(i, b+1, a){
		int flag=1;
		rep3(j, d+1, c){
			if(isp(i+j)){
				flag=0;
				break;
			}
		}
		if(flag){
			cout<< "Takahashi" <<endl;
			return 0;
		}
	}

	cout<< "Aoki" << endl;
 
	return 0;
}