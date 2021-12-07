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

//10->2 桁指定 10進->2進
string tob(LLi n, int lng, string fil)
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	int n, xr=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		xr=xr^v[i];
	}

	rep(i, n){
		if(xr==v[i]){
			cout<< "Win" <<endl;
			return 0;
		}
	}

	if(n%2) cout<< "Win" << endl;
	else cout<< "Lose" << endl;

	// rep(i, n) {
	// 	cout<< tob(v[i], 35, "0") <<endl;
	// }

	/*for (int bit = 0; bit < (1<<n); ++bit) {
        //vector<int> S(35);
		int tmp=0;
		//for(int i=0;i<35;i++) S[i]=0;
		//全ての桁に対する処理
        for (int i = 0; i < n; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				tmp=tmp^v[i];
				cout<< v[i] << " ";
			}
        }
		cout<< endl << tmp <<endl;
    }*/
 
	return 0;
}