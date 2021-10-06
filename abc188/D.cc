#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

struct num{
	int ti;
	int co;

	bool operator<(const num &in) const{
		return ti<in.ti;
	};
};

int main(){

	LLi n, c, ans=0, ai, bi, ci, nc=0, pt=1;
	num tmp;
	vector<num> v;

	cin>> n >> c;

	rep(i, n){
		cin >> ai >> bi >> ci;
		tmp.ti=ai;
		tmp.co=ci;
		v.push_back(tmp);
		tmp.ti=bi+1;
		tmp.co=-ci;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end());

	rep(i, 2*n) {
		//cout<< v[i].ti SP << v[i].co <<endl;
		ans+=min(nc, c)*(v[i].ti-pt);
		pt=v[i].ti;
		nc+=v[i].co;
		//cout<< ans SP << nc <<endl;
	}

	cout<< ans <<endl;
 
	return 0;
}