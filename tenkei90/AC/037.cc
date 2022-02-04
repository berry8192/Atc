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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, 20){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

LLi dp[510][10010];
//vector< multiset<LLi> > st;
multiset<LLi> st;

int main(){

	int w, n;
	LLi ans=-1;
	vector<int> l, r, v;

	cin>> w >> n;
	l.resize(n);
	r.resize(n);
	v.resize(n);

	rep(i, n){
		cin >> l[i] >> r[i] >> v[i];
		//cout<< i <<endl;
	}

	rep(i, 510) {
		rep(j, 10010) dp[i][j]=-1;
		dp[i][0]=0;
	}

	rep(i, n){
		//cout<< "i=" << i <<endl;
		rep(j, w+1) dp[i+1][j]=dp[i][j];
		st.clear();
		for(int j=l[i];j<=w;j++){
			//cout<< "j=" << j <<endl;
			st.insert(dp[i][j-l[i]]);
			//cout<< "add " << dp[i][j-l[i]] <<endl;
			LLi itr=*st.rbegin();
			if(j-r[i]>=0){
				auto dl=st.find(dp[i][j-r[i]]);
				st.erase(dl);
				//cout<< "remove " << dp[i][j-r[i]] <<endl;
			}
			if(itr!=-1) dp[i+1][j]=max(dp[i+1][j], itr+v[i]);

			// for(auto itr2 = st.begin(); itr2 != st.end(); ++itr2) {
        	// 	std::cout << *itr2 << " ";      // イテレータの指す先のデータを表示
    		// }
			// cout<< endl;
		}
	}

	//rep(i, w+1) ans=max(ans, dp[n][i]);
	cout<< dp[n][w] << endl;
 
	return 0;
}
