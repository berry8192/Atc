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

	string a, s, t, u;
	cin>> a;
	s=a[0];
	t=a[1];
	u=a[2];
	set<string> st;

	st.insert(""+s+t+u);
	st.insert(""+s+u+t);
	st.insert(""+t+s+u);
	st.insert(""+t+u+s);
	st.insert(""+u+s+t);
	st.insert(""+u+t+s);

	cout<< st.size() <<endl;
 
	return 0;
}