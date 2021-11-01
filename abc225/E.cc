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

struct fu{
	LLi x;
	LLi y;
	// double xyl;
	// double xyr;

	bool operator<(const fu &in) const{
		return (in.x-1)*y<(x-1)*in.y;
		//return xyl!=in.xyl ? xyl<in.xyl : xyr>in.xyr;
	};
};

int main(){

	int n, ans=0;
	LLi posx, posy;
	vector<fu> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i].x >> v[i].y;
		// v[i].xyl=1.0*v[i].y/(v[i].x-1);
		// v[i].xyr=1.0*(v[i].y-1)/v[i].x;
		// v[i].xyl=atan2(v[i].y, v[i].x-1);
		// v[i].xyr=atan2(v[i].y-1, v[i].x);
	}
	sort(all(v));

	posx=v[0].x;
	posy=v[0].y;
	ans=1;

	rep(i, n){
		//cout<< v[i].x SP << v[i].y SP << v[i].xyl SP << v[i].xyr <<endl;
	}

	rep3(i, n, 1) {
		//if((posx-1)*(v[i].y-1)>=posy*v[i].x){
		if((posx-1)*(v[i].y-1)>=posy*v[i].x){
			ans++;
			posx=v[i].x;
			posy=v[i].y;
		}
	}

	cout<< ans << endl;
 
	return 0;
}