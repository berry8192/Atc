#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

struct ang{
	double val;
	int num;

	bool operator<(const ang &in) const{
		return val<in.val;
	};
};

int main(){

	int n;
	ang tmp;
	vector<int> x, y;
	vector<ang> v;

	cin>> n;

	rep(i, n) cin >> x[i] >> y[i];

	//i番目の頂点から走査する
	rep(i, n) {
		//ang列を作成
		v.clear();
		rep(j, n){
			if(j==i) continue;
			tmp.val=atan2(y[j]-y[i], x[j]-x[i]);
			tmp.num=j;
			v.push_back(tmp);
		}
		sort(all(v));
		rep(j, n-2){
			
		}
	}

	if(n==0) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}