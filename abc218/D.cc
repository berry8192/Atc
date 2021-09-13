#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct poi{
	int x;
	int y;

	bool operator<(const poi &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
};

int main(){

	int n, tx, ty, pos=0;
	LLi ans=0;
	vector<poi> v;
	map<poi, LLi> st;
	poi tmp;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i].x >> v[i].y;
	}
	sort(v.begin(), v.end());
	tmp.x=-1;
	tmp.y=0;
	v.push_back(tmp);
	//rep(i, n+1) cout<< v[i].x SP << v[i].y <<endl;

	for(int i=1;i<n+1;i++) {
		if(v[i-1].x!=v[i].x){
			//cout<< "! " << i <<endl;
			for(int j=pos;j<i-1;j++){
				for(int k=j+1;k<i;k++){
					tmp.x=v[j].y;
					tmp.y=v[k].y;
					st[tmp]++;
					ans+=st[tmp]-1;
					//cout<< tmp.x SP << tmp.y SP << ans <<endl;
				}
			}
			pos=i;
			//cout<< "setpoi " << pos <<endl;
		}
	}

	cout<< ans << endl;
 
	return 0;
}