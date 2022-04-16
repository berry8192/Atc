#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;
//using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;
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

	int y, m, d;
	string s;

	cin>> s;
	y=stoi(s.substr(0, 4));
	m=stoi(s.substr(5, 2));
	d=stoi(s.substr(8, 2));

	//cout<< y SP << m SP << d <<endl;

	while(1){
		vector<int> u(10);

		// yで2種類以上使わないかを見る
		string yy=to_string(y);
		rep(i, 4){
			u[int(yy[i]-'0')]=1;
		}
		int su=0;
		rep(i, 10) su+=u[i];
		if(su>2){
			y++;
			m=1;
			d=1;
			continue;
		}

		// mで2種類以上使わないかを見る
		string mm=to_string(m);
		if(mm.size()==1) mm="0"+mm;
		rep(i, 2){
			u[int(mm[i]-'0')]=1;
		}
		su=0;
		rep(i, 10) su+=u[i];
		if(su>2){
			m++;
			d=1;
			if(m==13){
				m=1;
				y++;
			}
			continue;
		}

		// dで2種類以上使わないかを見る
		string dd=to_string(d);
		if(dd.size()==1) dd="0"+dd;
		rep(i, 2){
			u[int(dd[i]-'0')]=1;
		}
		su=0;
		rep(i, 10) su+=u[i];
		if(su>2){
			d++;
			if(d==32){
				d=1;
				m++;
				if(m==13){
					m=1;
					y++;
				}
			}
			continue;
		}
		cout<< yy << "/" << mm << "/" << dd <<endl;
		return 0;
	}
 
	return 0;
}