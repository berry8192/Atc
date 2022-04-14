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

int n, x, y;

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

LLi calc(vector<int> v){
	//PV(v);
	LLi tmp=0;
	vector<int> px, py;
	rep(i, v.size()){
		if(v[i]==x) px.push_back(i);
		if(v[i]==y) py.push_back(i);
	}
	px.push_back(imax);
	py.push_back(imax);
	//PV(px);
	//PV(py);
	rep(i, v.size()){
		auto xlb=lower_bound(all(px), i);
		auto ylb=lower_bound(all(py), i);
		//cout<< i SP << *xlb SP << *ylb <<endl;
		if(*xlb!=imax && *ylb!=imax){
			tmp+=v.size()-max(*xlb, *ylb);
		}
	}
	return tmp;
}

int main(){

	LLi ans=0;
	vector<int> a, tmp;

	cin>> n >> x >> y;
	a.resize(n);

	rep(i, n){
		cin >> a[i];
		if(a[i]<y || x<a[i]) a[i]=0;
	}
	a.push_back(0);

	rep(i, n+1) {
		if(a[i]){
			tmp.push_back(a[i]);
		}else{
			if(tmp.size()>0){
				ans+=calc(tmp);
			}
			tmp.clear();
		}
	}

	cout<< ans << endl;
 
	return 0;
}