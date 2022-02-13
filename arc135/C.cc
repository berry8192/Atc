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
string tob(LLi n, int lng=0, string fil="0")
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

	LLi n, cal, ans=0;
	string s;
	vector<LLi> v, d, tmp;

	cin>> n;
	v.resize(n);
	d.resize(32);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		s=tob(v[i], 32);
		rep(j, 32){
			if(s[j]=='1') d[j]++;
		}
		//cout<< s <<endl;
	}
	//PV(d);
	rep(i, n+1){
		if(i!=n) s=tob(v[i], 32);
		else s=tob(0LL, 32);
		tmp=d;
		cal=0;
		rep(j, 32){
			if(s[j]=='1'){
				tmp[j]=n-tmp[j];
			}
			cal+=tmp[j]*(1<<j);
		}
		ans=max(ans, cal);
	}

	cout<< ans << endl;
 
	return 0;
}