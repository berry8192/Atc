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

struct tw{
	int x, xs;
	int y, ys;


	bool operator<(const tw &in) const{
		return x!=in.x ? x<in.x : xs!=in.xs ? xs<in.xs : y!=in.y ? y<in.y : ys<in.ys;
	};
};

int main(){

	int n, ans=0, gc;
	tw tmp;
	vector<int> x, y;
	//vector<int> xx, yy;
	set<tw> st;

	cin>> n;
	x.resize(n);
	y.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	rep(i, n) {
		rep(j, n){
			if(i==j) continue;
			//xx.push_back(x[i]-x[j]);
			//yy.push_back(y[i]-y[j]);
			tmp.x=abs(x[i]-x[j]);
			tmp.y=abs(y[i]-y[j]);
			gc=__gcd(tmp.x, tmp.y);
			tmp.x/=gc;
			tmp.y/=gc;
			if(x[i]-x[j]>=0){
				tmp.xs=1;
			}else{
				tmp.xs=-1;
			}
			if(y[i]-y[j]>=0){
				tmp.ys=1;
			}else{
				tmp.ys=-1;
			}
			st.insert(tmp);
		}
	}
	//rep(i, n*(n-1)) cout<< xx[i] SP <<yy[i] <<endl;

	cout<< st.size() << endl;
 
	return 0;
}