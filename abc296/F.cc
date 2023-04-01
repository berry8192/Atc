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

 // 1-indexedなので注意。
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

int main(){

	int n;
	vector<int> a, b;
	set<int> st;

	cin>> n;
	a.resize(n);
	b.resize(n);

	rep(i, n){
		cin >> a[i];
		st.insert(a[i]);
	}
	rep(i, n) cin >> b[i];
	sort(all(a));
	sort(all(b));
	if(a!=b){
		cout<< "No" <<endl;
		return 0;
	}

	// cout<< aa SP << bb << endl;
	if(st.size()!=n) cout<< "Yes" <<endl;
	else{
		ll aaa = 0;
		BIT aa(n);  // これまでの数字がどんな風になってるのかをメモる為のBIT
		for (int i = 0; i < n; i++) {
			aaa += i - aa.sum(a[i]); // BITの総和 - 自分より左側 ＝ 自分より右側
			aa.add(a[i], 1); // 自分の位置に1を足す(ダジャレではないです)
		}
		ll bbb = 0;
		BIT bb(n);  // これまでの数字がどんな風になってるのかをメモる為のBIT
		for (int i = 0; i < n; i++) {
			bbb += i - bb.sum(b[i]); // BITの総和 - 自分より左側 ＝ 自分より右側
			bb.add(b[i], 1); // 自分の位置に1を足す(ダジャレではないです)
		}
		if(aaa!=bbb){
			cout<< "Yes" <<endl;
			return 1;
		}else cout<< "No" <<endl;
		return 0;
	}
 
	return 0;
}