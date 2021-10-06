#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct sb{
	int val;
	int num;
	int a;
	int b;

	bool operator<(const sb &in) const{
		return val>in.val;
	};
};

int main(){

	int n, ua=0, ub=0, eve=0;
	LLi ans=0;
	vector<sb> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i].a;
	rep(i, n) cin >> v[i].b;
	rep(i, n){
		v[i].val=abs(v[i].a-v[i].b);
		v[i].num=i;
	}

	sort(v.begin(), v.end());

	rep(i, n) cout<< v[i].a <<" ";
	cout<< endl;
	rep(i, n) cout<< v[i].b <<" ";
	cout<< endl;


	rep(i, n){
		if(v[i].a<v[i].b){
			ans+=v[i].b;
			ub++;
		}
		if(v[i].a>v[i].b){
			ans+=v[i].a;
			ua++;
		}
		if(v[i].a==v[i].b){
			ans+=v[i].a;
			eve++;
		}
		if(ua-ub==n-i-1+eve){
			for(int j=i+1;j<n;j++) ans+=v[j].b;
			break;
		}
		if(ub-ua==n-i-1+eve){
			for(int j=i+1;j<n;j++) ans+=v[j].a;
			break;
		}
		cout<< ans <<endl;
	}

	cout<< ans <<endl;

	return 0;
}