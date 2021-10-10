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

struct peo{
	int wi;
	int nu;

	bool operator<(const peo &in) const{
		return wi!=in.wi ? wi<in.wi : nu>in.nu;
	};
};

int main(){

	int n, m, ans=0;
	char cn;
	vector< vector<int> > v;
	vector<peo> p;
	peo tmp;

	cin>> n >> m;
	v.resize(2*n);
	p.resize(2*n);
	rep(i, 2*n) v[i].resize(m);

	rep(i, 2*n){
		rep(j, m){
			cin>> cn;
			if(cn=='G') v[i][j]=0;
			if(cn=='C') v[i][j]=1;
			if(cn=='P') v[i][j]=2;
		}
	}

	rep(i, 2*n){
		tmp.wi=0;
		tmp.nu=i;
		p[i]=tmp;
	}

	rep(i, m) {
		for(int j=0;j<2*n;j+=2){
			if((3+v[p[j].nu][i]-v[p[j+1].nu][i])%3==1) p[j+1].wi++;
			if((3+v[p[j].nu][i]-v[p[j+1].nu][i])%3==2) p[j].wi++;
		}
		sort(all(p));
		// rep(j, 2*n){
		// 	cout<< p[j].wi SP << p[j].nu+1 <<endl;
		// }
	}

	for(int i=2*n-1;i>=0;i--) cout<< p[i].nu+1 <<endl;
 
	return 0;
}