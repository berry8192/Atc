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

	LLi q, c, x, k, flag, ext=0;
	multiset<LLi> st;

	cin>> q;
	st.insert(llimax);
	st.insert(llimax);
	st.insert(llimax);
	st.insert(llimax);
	st.insert(llimax);
	st.insert(llimax);
	st.insert(-1);
	st.insert(-1);
	st.insert(-1);
	st.insert(-1);
	st.insert(-1);
	st.insert(-1);

	rep(i, q){
		cin>> c >> x;
		flag=1;
		if(c==1){
			st.insert(x);
		}else if(c==2){
			cin>> k;
			x++;
			auto lb = st.lower_bound(x);
			rep(j, k){
				lb--;
			}
			if(*lb!=-1) cout<< *lb <<endl;
			else cout<< -1 <<endl;
		}else{
			cin>> k;
			k--;
			auto lb = st.lower_bound(x);
			rep(j, k){
				lb++;
			}
			if(*lb!=llimax) cout<< *lb <<endl;
			else cout<< -1 <<endl;
		}
		// cout<< "st=";
		// for(auto itr = st.begin(); itr != st.end(); ++itr) {
		// 	auto tmp=st.end();
		// 	tmp--;
		// 	if(itr==tmp) cout<<"last" <<endl;
        // 	std::cout << *itr << " ";      // イテレータの指す先のデータを表示
    	// }
		// cout<< endl;
	}

	return 0;
}