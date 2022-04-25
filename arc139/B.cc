#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

struct num{
	ll va;
	ll co;

	bool operator<(const num &in) const{
		return va*in.co>in.va*co;
	};
};

int main(){

	int t, ans=0;
	vector<ll> n;
	vector<num> x, y, z, tmp(3);

	cin>> t;
	n.resize(t);
	x.resize(t);
	y.resize(t);
	z.resize(t);

	rep(i, t){
		cin >> n[i] >> y[i].va >> z[i].va >> x[i].co >> y[i].co >> z[i].co;
		x[i].va=1;
	}

	rep(i, t) {
		tmp[0]=x[i];
		tmp[1]=y[i];
		tmp[2]=z[i];
		sort(all(tmp));
		//rep(j, 3) cout<< tmp[j].va SP << tmp[j].co <<endl;
		//一番効率がいいやつで割り切れるなら、それだけを使う
		if(n[i]%tmp[0].va==0){
			cout<< n[i]/tmp[0].va*tmp[0].co <<endl;
			continue;
		}
		//一番効率がいいやつでできるだけ減らした後で2番目で割り切れるならそうする
		if((n[i]%tmp[0].va)%tmp[1].va==0){
			cout<< n[i]/tmp[0].va*tmp[0].co+(n[i]%tmp[0].va)/tmp[1].va*tmp[1].co <<endl;
			continue;
		}
		//一番効率がいいやつでできるだけ減らした後で2番目をできるだけ使う
		//このとき1は必ず一番効率が悪い->できるだけ1を使わないようにする
		//1を使わないメリットと2番目を使ってしまうデメリットのバランスがわからない
		//全部線形になる気がするので、できるだけ2番目を使うパターンとできるだけ1の個数を減らすパターンをかんがえてみる
		ll tmp1=n[i]/tmp[0].va*tmp[0].co+(n[i]%tmp[0].va)/tmp[1].va*tmp[1].co+(n[i]%tmp[0].va)%tmp[1].va*tmp[2].co;
		ll tmp2=lmax;
		rep(j, 100000){
			if(j*tmp[0].va>n[i]) break;
			ll tn=n[i]-j*tmp[0].va;
			ll tmp20=j*tmp[0].co;
			tmp20+=tn/tmp[1].va*tmp[1].co;
			tn=tn%tmp[1].va;
			tmp20+=tn*tmp[2].co;
			tmp2=min(tmp2, tmp20);
		}
		rep(j, 100000){
			if(j*tmp[1].va>n[i]) break;
			ll tn=n[i]-j*tmp[1].va;
			ll tmp20=j*tmp[1].co;
			tmp20+=tn/tmp[0].va*tmp[0].co;
			tn=tn%tmp[0].va;
			tmp20+=tn*tmp[2].co;
			tmp2=min(tmp2, tmp20);
		}
		cout<< min(tmp1, tmp2) <<endl;
	}

	return 0;
}