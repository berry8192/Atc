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

int main(){

	int n, sx, sy, tx, ty, a, b, c, d, xsz=0, ysz=0;
	vector<int> x, y;

	cin>> sx >> sy >> tx >> ty >> a >> b >> c >> d;
	if(abs(sx-(a+b)/2)>abs(tx-(a+b)/2)) xsz=1;
	if(abs(sy-(c+d)/2)>abs(ty-(c+d)/2)) ysz=1;

	if(sx%2!=tx%2 || sy%2!=ty%2){
		cout<< "No" <<endl;
		return 0;
	}
	if(sx!=tx){
		if(a==b && tx-a!=a-sx){
			cout<< "No" <<endl;
			return 0;
		}
		while(sx!=tx){
			int ideal=(sx+tx)/2;
			if(a<=ideal && ideal<=b){
				x.push_back(ideal);
				break;
			}else{
				if(xsz){
					sx=a+a-sx;
					x.push_back(a);
				}else{
					sx=b+b-sx;
					x.push_back(b);
				}
			}
		}
	}
	if(sy!=ty){
		if(c==d && ty-c!=c-sy){
			cout<< "No" <<endl;
			return 0;
		}
		while(sy!=ty){
			int ideal=(sy+ty)/2;
			if(c<=ideal && ideal<=d){
				y.push_back(ideal);
				break;
			}else{
				if(ysz){
					y.push_back(c);
					sy=c+c-sy;
				}else{
					sy=d+d-sy;
					y.push_back(d);
				}
			}
		}
	}
	if(x.size()%2!=y.size()%2){
		if(a<=tx && tx<=b){
			x.push_back(x[x.size()-1]);
		}else if(c<=ty && ty<=d){
			y.push_back(y[y.size()-1]);
		}else{
			cout<< "No" <<endl;
			return 0;
		}
	}
	if(x.size()<y.size()){
		if(a<=tx && tx<=b){
			while(x.size()<y.size()){
				x.push_back(x[x.size()-1]);
			}
		}else if((y.size()-x.size())%2==0){
			while(x.size()<y.size()){
				x.push_back(a);
				x.push_back(a);
			}
		}
	}else{
		if(c<=ty && ty<=d){
			while(y.size()<x.size()){
				y.push_back(y[y.size()-1]);
			}
		}else if((x.size()-y.size())%2==0){
			while(y.size()<x.size()){
				y.push_back(c);
				y.push_back(c);
			}
		}
	}

	cout<< "Yes" << endl;
	rep(i, x.size()) cout<< x[i] SP << y[i] <<endl;
 
	return 0;
}