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

	int n;
	double su=0.0;
	vector<double> v;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		//su+=v[i];
	}
	// printf("%.12lf", su/n);
	// return 0;

	double ri, le, m1, m2, del=0.0000001;
	ri=1000000000.0;
	le=0.0;
	while(ri-le>del){
		m1=le+(ri-le)/3;
		m2=ri-(ri-le)/3;
		//cout<< le SP << m1 SP << m2 SP << ri <<endl;
		double tmp1=0.0, tmp2=0.0;
		rep(i, n){
			tmp1+=1.0/n*(m1+v[i]-min(v[i], 2*m1));
			tmp2+=1.0/n*(m2+v[i]-min(v[i], 2*m2));
		}
		if(tmp1<tmp2) ri=m2;
		else le=m1;
	}
	//cout<< le SP << ri <<endl;
	double ans=0.0;
	rep(i, n) ans+=1.0/n*(le+v[i]-min(v[i], 2*le));
	printf("%.12lf", ans);
 
	return 0;
}