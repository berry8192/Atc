#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

int ima=2147483647;
long long int lma=9223372036854775807;
ll mod=1000000007;
//LLi mod=998244353;

int main(){

	int n, q;
	ll ans=0;
	vector<ll> a, b, l, r, v;

	cin>> n >> q;
	a.resize(n+1);
	b.resize(n);
	l.resize(q+1);
	r.resize(q+1);
	v.resize(q+1);

	rep3(i, n+1, 1) cin>> a[i];
	rep3(i, n, 1){
		b[i]=a[i+1]-a[i];
		ans+=abs(b[i]);
	}
	rep3(i, q+1, 1){
		cin>> l[i] >> r[i] >> v[i];
		l[i]--;
		//r[i]++;
	}

	rep3(i, q+1, 1){
		ll tl=abs(b[l[i]])+abs(b[r[i]]);
		if(l[i]>=1) b[l[i]]+=v[i];
		if(r[i]<=n-1) b[r[i]]-=v[i];
		ll tr=abs(b[l[i]])+abs(b[r[i]]);
		ans+=tr-tl;
		cout<< ans << endl;
	}

	return 0;
}