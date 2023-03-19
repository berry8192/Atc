#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

struct itv{
	ll l;
	ll r;

	bool operator<(const itv &in) const{
		return l<in.l;
	};
	void print(){
		cout<< "[" << l << "," << r << "]";
	}
};

int main(){

	ll l, n1, n2;
	cin>> l >> n1 >> n2;
	vector<ll> v1(n1), l1(n1), v2(n2), l2(n2);
	map<int, vector<itv>> mp1, mp2;
	set<ll> st;
	ll ans=0;

	ll pos=1;
	rep(i, n1){
		cin >> v1[i] >> l1[i];
		mp1[v1[i]].push_back({pos, pos+l1[i]-1});
		pos+=l1[i];
		st.insert(v1[i]);
	}
	pos=1;
	rep(i, n2){
		cin >> v2[i] >> l2[i];
		mp2[v2[i]].push_back({pos, pos+l2[i]-1});
		pos+=l2[i];
		st.insert(v2[i]);
	}

	for(auto itr=st.begin();itr!=st.end();itr++){
		vector<itv> vv1=mp1[*itr];
		vector<itv> vv2=mp2[*itr];
		// cout<< *itr <<endl;
		// rep(i, vv1.size()) vv1[i].print();
		// cout<< endl;
		// rep(i, vv2.size()) vv2[i].print();
		// cout<< endl;
		if(vv1.size()==0 || vv2.size()==0) continue;
		vv1.push_back({10000000000000001, 10000000000000001});
		vv2.push_back({10000000000000002, 10000000000000002});
		int p1=0, p2=0, cur;
		// if(vv1[0].l<vv2[0].l){
		// 	cur=1;
		// }else{
		// 	cur=2;
		// }
		rep(i, vv1.size()+vv2.size()){
			ll overlap = min(vv1[p1].r, vv2[p2].r) - max(vv1[p1].l, vv2[p2].l) + 1;
			if (overlap < 0) {
				overlap = 0;
			}
			ans+=overlap;
			if(vv1[p1].r<vv2[p2].r){
				p1++;
			}else{
				p2++;
			}
		}
	}

	cout<< ans <<endl;
 
	return 0;
}