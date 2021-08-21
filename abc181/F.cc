#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct pos{
	int x;
	int y;

	bool operator<(const pos &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
};

int main(){

	int n, ans=0;
	vector<pos> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		if (v[i]) ans++;
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}