#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
using mint = modint1000000007;
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

/* BIT: 区間和の更新や計算を行う構造体
    初期値は a_1 = a_2 = ... = a_n = 0
    ・add(i,x): a_i += x とする
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    計算量は全て O(logn)
*/
template <typename T>
struct BIT {
    int n;          // 配列の要素数(数列の要素数+1)
    vector<T> bit;  // データの格納先
    BIT(int n_) : n(n_ + 1), bit(n, 0) {}

    void add(int i, T x) {
        for (int idx = i; idx < n; idx += (idx & -idx)) {
            bit[idx] += x;
        }
    }

    T sum(int i) {
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx)) {
            s += bit[idx];
        }
        return s;
    }

	int lower_bound(T w) { // a_1 + a_2 + ... + a_x >= w となるような最小の x を求める(ただし a_i >= 0)
    if (w <= 0) {
        return 0;
    } else {
        int x = 0, r = 1;
        while (r < n) r = r << 1;
        for (int len = r; len > 0; len = len >> 1) { // 長さlenは1段下るごとに半分に
            if (x + len < n && bit[x + len] < w) { // 採用するとき
                w -= bit[x + len];
                x += len;
            }
        }
        return x + 1;
    }
}
};

int main(){

	int n, q, t, a, x, r;
	vector<int> p;
	map<int, int> rp;

	cin>> n >> q;
	BIT<int> b=BIT<int>(n);
	p.resize(n);

	rep(i, n){
		cin >> p[i];
		rp[p[i]]=i;
		b.add(p[i], 1);
	}

	rep(i, q) {
		cin>> t;
		if(t==1){
			cin>> a >> x;
			b.add(p[a-1], -1);
			p[a-1]=x;
			rp[x]=a-1;
			b.add(x, 1);
		}else if(t==2){
			cin>> a;
			cout<< n-b.sum(p[a-1])+1 <<endl;
		}else{
			cin>> r;
			cout<< rp[b.lower_bound(n-r-1)] <<endl;
		}
	}

	return 0;
}