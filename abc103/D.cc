#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct rq{
	int l;
	int r;

	bool operator<(const rq &in) const{
		return r!=in.r ? r<in.r : l<in.l;
	};
};

int main(){

	int n, m, ans=0, del=0;
	vector<rq> v;

	cin>> n >> m;
	v.resize(m);

	rep(i, m) {
		int il, ir;
		cin>> il >> ir;
		v[i].l=il;
		v[i].r=ir;
	}
	sort(v.begin(), v.end());
	//rep(i, m) cout<< v[i].l << " " << v[i].r <<endl;

	rep(i, m){
		if(v[i].l+1<=del && del<=v[i].r) continue;
		del=v[i].r;
		ans++;
		//cout<< del <<endl;
	}

	cout<< ans << endl;
 
	return 0;
}