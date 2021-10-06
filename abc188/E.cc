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

struct ld{
	int l;
	int r;

	bool operator<(const ld &in) const{
		return l!=in.l ? l>in.l : r>in.r;
	};
};

int main(){

	int n, m, ans=0, ma=-imax, tmp;
	vector<int> a, vmi;
	vector<ld> v;

	cin>> n >> m;
	a.resize(n);
	vmi.resize(n, -imax);
	v.resize(m);

	rep(i, n) cin >> a[i];
	rep(i, m){
		cin >> v[i].l >> v[i].r;
		v[i].l--;
		v[i].r--;
	}
	
	sort(v.begin(), v.end());

	rep(i, m) {
		//cout<< v[i].l SP << v[i].r <<endl;
		tmp=a[v[i].r]-a[v[i].l];
		if(vmi[v[i].r]>0) tmp+=vmi[v[i].r];
		vmi[v[i].l]=max(vmi[v[i].l], tmp);
	}

	rep(i, n) ma=max(ma, vmi[i]);
	cout<< ma <<endl;

	return 0;
}