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

struct kb{
	int l;
	int r;

	bool operator<(const kb &in) const{
		return r!=in.r ? r<in.r : l<in.l;
	};
};

bool sec_dup(int xl, int xr, int yl, int yr){
	if(xr<yl || yr<xl) return false;
	else return true;
}

int main(){

	int n, d, pos=-imax, ans=0;
	vector<kb> v;

	cin>> n >> d;
	v.resize(n);

	rep(i, n) cin >> v[i].l >> v[i].r;
	sort(all(v));

	rep(i, n) {
		//cout<< v[i].l SP << v[i].r <<endl;
		if(!sec_dup(pos, pos+d-1, v[i].l, v[i].r)){
			pos=v[i].r;
			ans++;
		}
	}

	cout<< ans << endl;
 
	return 0;
}