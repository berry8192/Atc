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

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()) cout << pvv[i].val SP << pvv[i].ind << endl;
}
//by num sort
struct num{
	int val;
	int ind;

	bool operator<(const num &in) const{
		return val>in.val;
	};
};

int main(){

	map<int, int> mp;
	int n, k, tmp, mii=1000000, rpos=0, ans=imax;
	vector<num> l, r;
	cin>> n >> k;
	l.resize(k);
	r.resize(n-k);

	rep(i, k){
		cin>> tmp;
		l[i].val=tmp;
		l[i].ind=k-i;
	}
	rep(i, n-k){
		cin>> tmp;
		r[i].val=tmp;
		r[i].ind=i;
	}
	sort(all(l));
	sort(all(r));
	// PV(l);
	// PV(r);

	rep(i, k){
		//int flag=0;
		while(l[i].val<r[rpos].val){
			mii=min(mii, r[rpos].ind);
			rpos++;
			//flag=1;
		}
		//cout<< "i=" << i SP << "mii=" << mii <<endl;
		ans=min(ans, mii+l[i].ind);
	}

	if(ans<=1000000) cout<< ans << endl;
	else cout<< -1 << endl;
 
	return 0;
}