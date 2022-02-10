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

//2 factor sort
struct poi{
	LLi a;
	LLi b;

	bool operator<(const poi &in) const{
		return b!=in.b ? b>in.b : a>in.a;
	};
};

int main(){

	int n, k, ia, ib;
	LLi ans=0;
	set<poi> st;
	poi tmp;
	vector<int> v;

	cin>> n >> k;

	rep(i, n){
		cin >> ia >> ib;
		v.push_back(ia-ib);
		v.push_back(ib);
		/*
		tmp.a=ia-ib;
		tmp.b=ib;
		st.insert(tmp);*/
	}
	sort(all(v), greater<int>());

	/*
	rep(i, k){
		auto itr=st.begin();
		poi tmp2=*itr;
		ans+=tmp2.b;
		tmp.b=tmp2.a;
		tmp.a=0;
		st.erase(itr);
		st.insert(tmp);
	}
	*/
	
	rep(i, k) ans+=v[i];
	cout<< ans <<endl;
 
	return 0;
}
