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

struct poi{
	int x;
	int y;

	bool operator<(const poi &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
};

int main(){

	int n, flag, fai;
	vector<poi> a, b;
	vector<int> x, y, X, Y;

	cin>> n;
	x.resize(n);
	y.resize(n);
	X.resize(n);
	Y.resize(n);
	a.resize(n);
	b.resize(n);
	rep(i, n) cin >> x[i] >> y[i];
	rep(i, n) cin >> X[i] >> Y[i];

	rep(i, n){
		a[i].x=x[i];
		a[i].y=y[i];
		b[i].x=X[i];
		b[i].y=Y[i];
	}
	poi bk;
	bk.x=imax;
	bk.y=imax;
	a.push_back(bk);
	b.push_back(bk);
	sort(all(a));
	sort(all(b));
	
	// もともと一致パターン
	flag=1;
	rep(i, n){
		if(a[i].x!=b[i].x || a[i].y!=b[i].y){
			flag=0;
			break;
		}
	}
	if(flag){
		cout<< "Yes" <<endl;
		return 0;
	}

	// x軸反転パターン
	flag=1;
	rep(i, n){
		if(a[i].x!=b[i].x){
			flag=0;
			break;
		}
	}
	if(flag){
		fai=0;
		int m=imax;
		vector<int> ap, bp;
		rep(i, n){
			ap.push_back(a[i].y);
			bp.push_back(b[i].y);
			if(a[i].x!=a[i+1].x){
				sort(all(ap));
				sort(all(bp), greater<int>());
				rep(j, ap.size()){
					if(m==imax){
						m=(bp[j]+ap[j]);
					}else if(m!=(bp[j]+ap[j])){
						fai=1;
						break;
					}
				}
				ap.clear();
				bp.clear();
			}
			if(fai) break;
		}
		if(fai==0){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	// xとy入れ替え作業
	a.clear();
	b.clear();
	a.resize(n);
	b.resize(n);
	rep(i, n){
		a[i].x=y[i];
		a[i].y=x[i];
		b[i].x=Y[i];
		b[i].y=X[i];
	}
	a.push_back(bk);
	b.push_back(bk);
	sort(all(a));
	sort(all(b));
	
	// y軸反転パターン
	flag=1;
	rep(i, n){
		if(a[i].x!=b[i].x){
			flag=0;
			break;
		}
	}
	if(flag){
		fai=0;
		int m=imax;
		vector<int> ap, bp;
		rep(i, n){
			ap.push_back(a[i].y);
			bp.push_back(b[i].y);
			if(a[i].x!=a[i+1].x){
				sort(all(ap));
				sort(all(bp), greater<int>());
				rep(j, ap.size()){
					if(m==imax){
						m=(bp[j]+ap[j]);
					}else if(m!=(bp[j]+ap[j])){
						fai=1;
						break;
					}
				}
				ap.clear();
				bp.clear();
			}
			if(fai) break;
		}
		if(fai==0){
			cout<< "Yes" <<endl;
			return 0;
		}
	}

	cout<< "No" <<endl;
 
	return 0;
}