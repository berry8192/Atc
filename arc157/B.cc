#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	int n;
	cin>> n;
	int k;
	cin>> k;
	string s;
	cin>> s;
	int x=0;
	int ans=0;

	rep(i, n){
		if(s[i]=='X') x++;
	}
	if(x==n && k==1){
		cout<< 0 <<endl;
		return 0;
	}
	int y=-1;
	vector<int> v;
	rep(i, n){
		if(s[i]=='Y'){
			if(y!=-1){
				v.push_back(i-y-1);
			}
			y=i;
		}
	}
	sort(all(v));

	if(k<=x){
		if(k==x){
			cout<< n-1 <<endl;
			return 0;
		}
		rep(i, v.size()){
			if(v[i]<=k){
				ans+=v[i]+1;
				k-=v[i];
			}else{
				break;
			}
		}
		ans+=k;
		if(n==x) ans--;
	}else{
		ans=n-1;
		int l=0;
		rep(i, n){
			l=i;
			if(s[i]=='X'){
				break;
			}
			if(i==n-1) l=n;
		}
		reverse(all(s));
		int r=0;
		rep(i, n){
			r=i;
			if(s[i]=='X'){
				break;
			}
			if(i==n-1) r=0;
		}
		// cout<< l SP << r <<endl;
		reverse(all(s));
		int yy=-1;
		int cnt=0;
		vector<int> w;
		rep3(i, n-r, l){
			if(s[i]=='Y'){
				cnt++;
				yy=i;
			}else{
				w.push_back(cnt);
				cnt=0;
			}
		}
		sort(all(w), greater<int>());
		// PV(w);
		// cout<< k <<endl;
		k-=x;
		// cout<< k <<endl;
		if(k>l+r){
			k-=l+r;
			ans-=l+r;
		}else{
			ans-=k;
			cout<< max(0, ans) <<endl;
			return 0;
		}
		rep(i, w.size()){
			if(w[i]<=k){
				k-=w[i];
				ans-=w[i]+1;
			}else{
				if(k!=0) ans-=k+1;
				break;
			}
		}
	}

	cout<< max(0, ans) << endl;
 
	return 0;
}