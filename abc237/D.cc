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

	int n, tmp;
	string s;
	list<int> li;

	cin>> n;
	cin>> s;

	li.push_front(0);
	auto itr=li.begin();
	itr++;

	rep(i, n){
		if(s[i]=='L'){
			itr--;
			li.insert(itr, i+1);
		}else{
			li.insert(itr, i+1);
			//itr++;
		}
		// auto itr2=li.begin();
		// rep(j, i+2) {
		// 	cout<< *itr2 SP;
		// 	itr2++;
		// }
		// cout<< endl;
	}

	auto itr2=li.begin();

	rep(i, n+1) {
		cout<< *itr2 SP;
		itr2++;
	}

	cout<< endl;
 
	return 0;
}