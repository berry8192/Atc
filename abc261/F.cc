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

// BIT と転倒数を求める部分
// https://scrapbox.io/pocala-kyopro/%E8%BB%A2%E5%80%92%E6%95%B0
struct BIT {
  private:
   vector<int> bit;
   int N;
 
  public:
   BIT(int size) {
     N = size;
     bit.resize(N + 1);
   }
 
   // 一点更新です
   void add(int a, int w) {
     for (int x = a; x <= N; x += x & -x) bit[x] += w;
   }
 
   // 1~Nまでの和を求める。
   int sum(int a) {
     int ret = 0;
     for (int x = a; x > 0; x -= x & -x) ret += bit[x];
     return ret;
   }
 };

// 座標圧縮
// https://qiita.com/kemkemG0/items/e2de71014b23d1e78b8d
vector<int> compress(vector<int> vv){
	//PV(vv);
	vector<int> ww=vv;
	vector<int> rtn;
	sort(ww.begin(),ww.end());
	auto itr=unique(ww.begin(),ww.end());//重複した要素を消す
	//これだと消されたところが穴になる。
	//unique()の戻り値は消されたところの次のイテレータ
	ww.erase(itr,ww.end());//穴を消してあげる
	for(auto vvv:vv){
		int ret=lower_bound(ww.begin(),ww.end(),vvv) - ww.begin();
		rtn.push_back(ret+1);
	}
//PV(rtn);
	return rtn;
}

int main(){

	int n;
	vector<int> c, x;
	vector<vector<int>> v;

	cin>> n;
	c.resize(n);
	x.resize(n);
	v.resize(n+1);

	rep(i, n) cin >> c[i];
	rep(i, n) cin >> x[i];
	rep(i, n) v[c[i]].push_back(x[i]);

	// BIT と転倒数を求める部分
	// https://scrapbox.io/pocala-kyopro/%E8%BB%A2%E5%80%92%E6%95%B0
	ll ans = 0;
	BIT b(n+1);
	for (int i = 0; i < n; i++) {
    	ans += i - b.sum(x[i]); // BITの総和 - 自分より左側 ＝ 自分より右側
    	b.add(x[i], 1); // 自分の位置に1を足す(ダジャレではないです)
	}

	rep(i, n+1){
		int sz=v[i].size();
		if(sz>1){
			vector<int> w=compress(v[i]);
			BIT bi(sz+1);
			for (int j = 0; j < sz; j++) {
				ans -= j - bi.sum(w[j]); // BITの総和 - 自分より左側 ＝ 自分より右側
				bi.add(w[j], 1); // 自分の位置に1を足す(ダジャレではないです)
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}