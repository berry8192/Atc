#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

struct ni{
	int x1;
	int x2;
	int usd;

	bool operator<(const ni &in) const{
		return x2!=in.x2 ? x2>in.x2 : x1>in.x1;
	};
};

int main(){

	int n, m, q, ans=0, l, r;
	vector<ni> v;
	vector<int> x, tmp;

	cin>> n >> m >> q;
	v.resize(n);
	x.resize(m);

	rep(i, n){
		cin >> v[i].x1 >> v[i].x2;
	}
	sort(v.begin(), v.end());

	rep(i, m) cin>> x[i];

	rep(i, q){
		cin>> l >> r;
		l--;
		r--;
		tmp.clear();
		ans=0;
		rep(j, n) v[j].usd=0;
		rep(j, m){
			if(j<l || r<j) tmp.push_back(x[j]);
		}
		sort(tmp.begin(), tmp.end());
		//PV(tmp);

		rep(j, tmp.size()){
			//cout<< "touch" << tmp[j] <<endl;
			rep(l, v.size()){
				//cout<< "show" << v[l].x1 SP << v[l].x2 SP << v[l].usd <<endl;
				if(v[l].usd==0 && tmp[j]>=v[l].x1){
					ans+=v[l].x2;
					v[l].usd=1;
					//cout<< "add" << v[l].x2 <<endl;
					break;
				}
			}
		}

		cout<< ans <<endl;
	}
 
	return 0;
}