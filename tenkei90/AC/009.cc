#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int main(){

	int n;
	double tmp, ans=9000.0;
	vector<int> x, y;
	vector<double> v;

	cin>> n;

	x.resize(n);
	y.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	//i番目の頂点から走査する
	rep(i, n) {
		v.clear();
		//ang列を作成
		rep(j, n){
			if(j==i) continue;
			//cout<< x[j]-x[i] SP << y[j]-y[i] <<endl;
			tmp=atan2(y[j]-y[i], x[j]-x[i])*180.0/M_PI;
			v.push_back(tmp);
			if(tmp<0) v.push_back(tmp+360.0);
			//cout<< i SP << j SP << tmp <<endl;
		}
		sort(all(v));
		//cout<< endl;
		//rep(j, v.size()) cout<< v[j] SP;
		//cout<< endl;
		rep(j, n-1){
			auto ub = lower_bound(all(v), v[j]+180.0);
			if(ub!=v.end()){
				tmp=abs(180.0-(*ub-v[j]));
				//cout<< *ub SP << v[j] <<endl;
				ans=min(ans, tmp);
			}
			ub--;
			tmp=abs(180.0-(*ub-v[j]));
			//cout<< *ub SP << v[j] <<endl;
			ans=min(ans, tmp);
			//cout<< ans <<endl;
			//printf("%.15lf\n", v[j]);
		}
	}

	printf("%.15lf\n", 180.0-ans);
 
	return 0;
}