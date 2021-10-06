#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, m, tmp, ans, mi=imax;
	vector<int> h, w, l, r;

	cin>> n >> m;
	h.resize(n);
	w.resize(m);
	l.resize(n-1);
	r.resize(n-1);

	rep(i, n) cin >> h[i];
	rep(i, m) cin >> w[i];

	sort(all(h));
	//sort(all(w));
	//PV(h);

	for(int i=0;i<n-1;i+=2) l[i]=h[i+1]-h[i]+l[max(0, i-2)];
	for(int i=n-2;i>=0;i-=2) r[i]=h[i+1]-h[i]+r[min(n-2, i+2)];
	for(int i=1;i<n-1;i+=2) l[i]=l[i-1];
	for(int i=0;i<n-1;i+=2) r[i]=r[i+1];

	//PV(l);
	//PV(r);

	rep(i, m){
		auto lb = lower_bound(all(h), w[i]);
		//cout<< lb-h.begin() <<endl;
		tmp=lb-h.begin();
		ans=0;
		if(tmp-2>-1) ans+=l[tmp-2];
		//cout<< ans <<endl;
		if(tmp<n-1) ans+=r[tmp];
		//cout<< ans <<endl;
		ans+=abs(w[i]-h[tmp-(tmp%2)]);
		//cout<< ans <<endl;
		mi=min(mi, ans);

		auto ub = upper_bound(all(h), w[i]);
		//cout<< ub-h.begin() <<endl;
		tmp=ub-h.begin();
		ans=0;
		if(tmp-2>-1) ans+=l[tmp-2];
		//cout<< ans <<endl;
		if(tmp<n-1) ans+=r[tmp];
		//cout<< ans <<endl;
		ans+=abs(w[i]-h[tmp-(tmp%2)]);
		//cout<< ans << endl;
		mi=min(mi, ans);
	}

	cout<< mi <<endl;

	return 0;
}