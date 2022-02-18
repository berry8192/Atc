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

//2 factor sort
struct sr{
	int x1;
	int x2;

	bool operator<(const sr &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

int main(){

	LLi k, n, m;
	LLi su=0, ans=0;
	vector<LLi> a, b;
	vector<sr> v;
	sr tmp;

	cin>> k >> n >> m;
	a.resize(k);
	b.resize(k);

	rep(i, k) cin >> a[i];

	rep(i, k) {
		b[i]=a[i]*m/n;
		tmp.x1=-abs(b[i]*n-a[i]*m);
		tmp.x2=i;
		//cout<< tmp.x1 SP << tmp.x2 <<endl;
		v.push_back(tmp);
	}
	//PV(b);
	sort(all(v));
	rep(i, k) su+=b[i];
	rep(i, m-su) b[v[i].x2]++;

	PV(b);
 
	return 0;
}