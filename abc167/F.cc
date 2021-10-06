#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

struct lr{
	int l;
	int r;

	bool operator<(const lr &in) const{
		return r!=in.r ? r<in.r : l>in.l;
	};
};

int main(){

	int n, ans=0, ll, rr, oll, orr, flag=1;
	string s;
	vector<lr> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >>s;
		ll=0;
		rr=0;
		rep(j, s.size()){
			if(s[j]=='('){
				ll++;
				if(0<rr) rr--;
			}else{
				rr++;
				if(0<ll) ll--;
				if(ll<=0) orr++;
			}
		}
		v[i].l=max(0, ll-rr-orr);
		v[i].r=orr;
		cout<< v[i].l SP << v[i].r <<endl;
	}

	sort(v.begin(), v.end());

	rep(i, n){
		ans-=v[i].r;
		if(ans<0){
			flag=0;
			break;
		}
		ans+=v[i].l;
	}

	if(flag && ans==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}