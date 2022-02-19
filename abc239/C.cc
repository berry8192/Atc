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

int main(){

	int x1, y1, x2, y2, tx, ty;
	vector<int> mx, my;

	cin>> x1 >> y1 >> x2 >> y2;

	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if(abs(i)+abs(j)==3){
				//cout<< i SP << j <<endl;
				mx.push_back(x1+i);
				my.push_back(y1+j);
			}
		}
	}

	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if(abs(i)+abs(j)==3){
				//cout<< i SP << j <<endl;
				tx=x2+i;
				ty=y2+j;
				rep(k, 8){
					if(mx[k]==tx && my[k]==ty){
						cout<< "Yes" <<endl;
						return 0;
					}
				}
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}