#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

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

int main(){

	int n, Q;
	vector<LLi> x, y, v, w, q;

	cin>> n >> Q;
	x.resize(n);
	y.resize(n);
	v.resize(n);
	w.resize(n);
	q.resize(n);

	rep(i, n){
		cin >> x[i] >> y[i];
		v[i]=x[i]+y[i];
		w[i]=x[i]-y[i];
	}
	
	sort(all(v));
	sort(all(w));
	//PV(v);
	//PV(w);

	rep(i, Q){
		cin >> q[i];
		q[i]--;
	}
	
	rep(i, Q){
		cout<< max(max(abs(x[q[i]]+y[q[i]]-v[0]), abs(x[q[i]]+y[q[i]]-v[n-1])), max(abs(x[q[i]]-y[q[i]]-w[0]), abs(x[q[i]]-y[q[i]]-w[n-1]))) << endl;
	}
 
	return 0;
}
