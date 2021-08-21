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

int main(){
	cout << fixed << setprecision(12);
	int n, ans=0;
	vector<double> x, y;
	double d1, d2, d3, q=0.0000000001;

	cin>> n;
	x.resize(n);
	y.resize(n);

	rep(i, n) cin >> x[i] >> y[i];

	for(int i=0;i<n;i++) {
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<n;k++){
				d1=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
				d2=(x[i]-x[k])*(x[i]-x[k])+(y[i]-y[k])*(y[i]-y[k]);
				d3=(x[j]-x[k])*(x[j]-x[k])+(y[j]-y[k])*(y[j]-y[k]);
				d1=sqrt(d1);
				d2=sqrt(d2);
				d3=sqrt(d3);
				//cout<< d1 << " " << d2 << " " << d3 <<endl;
				if(abs(d1+d2-d3)<q || abs(d1+d3-d2)<q || abs(d2+d3-d1)<q){
					cout<< "Yes" << endl;
					return 0;
				}
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}