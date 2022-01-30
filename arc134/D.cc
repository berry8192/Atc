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

//2 factor sort
struct nu{
	int l;
	int r;
	int pos;

	bool operator<(const nu &in) const{
		return l!=in.l ? l<in.l : r<in.r;
	};
};

int main(){

	int n, el=imax, ep=-1, flag=1;
	nu tmp;
	vector<int> a, b, slc, ans;
	vector<nu> v;

	cin>> n;
	a.resize(n);
	b.resize(n);
	v.resize(n+1);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];
	rep(i, n){
		tmp.l=a[i];
		tmp.r=b[i];
		tmp.pos=i;
		v[i]=tmp;
	}
	tmp.l=imax;
	v[n]=tmp;

	sort(all(v));

	rep(i, n) {
		//cout<< v[i].l SP << v[i].r SP << v[i].pos <<endl;
	}
	
	rep(i, n) {
		rep3(j, n, i){
			if(v[j].l!=v[j+1].l){
				//i~jまで同じlを持つ
				rep3(m, j+1, i){
					if(flag && v[m].l>v[m].r){
						//cout<< v[m].l SP << v[m].r <<endl;
						return 0;
					}
					if(flag || (v[m].l<=el && ep<v[m].pos)){
						slc.push_back(m);
						el=v[m].l;
						ep=max(v[m].pos, ep);
					}
				}
				//end
				i=j+1;
				flag=0;
				break;
			}
		}

	}

	rep(i, slc.size()){
		ans.push_back(v[slc[i]].l);
	}
	rep(i, slc.size()){
		ans.push_back(v[slc[i]].r);
	}

	PV(ans);
 
	return 0;
}