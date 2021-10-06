#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct que{
	int x1;
	int x2;
	int x3;

	bool operator<(const que &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

int main(){

	int n, m, ma, ans=0;
	vector<que> v;

	cin>> n >> m;
	for(int i=2;i<=n;i++) ma*=i;
	v.resize(m);

	rep(i, m) cin >> v[i].x >> v[i].y >> v[i].z;

	sort(v.begin(), v.end());

	rep(i, m){
		
	}
 
	return 0;
}