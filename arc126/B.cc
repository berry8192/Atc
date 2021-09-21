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

struct ee{
	int a;
	int b;

	bool operator<(const ee &in) const{
		return b!=in.b ? b<in.b : a<in.a;
	};
};

int main(){

	int n, m, ai, bi;
	vector<ee> v;

	cin>> n >> m;
	v.resize(n);

	rep(i, m){
		cin>> ai >> bi;
		v[i].a=min(ai, bi);
		v[i].b=max(ai, bi);
	}

	if(0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}