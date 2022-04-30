#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

int main(){

	int t, n, s, ans;
	cin>> t;
	rep(lp, t){
		multiset<int> st;
		ans=0;
		cin>> n;
		rep(i, n){
			cin >> s;
			st.insert(s);
		}

		cout<< "Case #" << lp+1 << ": ";
		//cout<< st.size() <<endl;
		rep(i, n){
			if(ans<*st.begin()) ans++;
			st.erase(st.begin());
			//cout<< st.size() <<endl;
		}
		cout<< ans <<endl;
	}

	return 0;
}