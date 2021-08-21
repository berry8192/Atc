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

	double pi = 3.141592653589793;
	double a, b, h, m, ax, ay, bx, by, d;
	cin>> a >> b >> h >> m;

	cout << fixed << setprecision(11);

	ax=a*cos(2*pi*(h/12.0+m/720.0));
	ay=a*sin(2*pi*(h/12.0+m/720.0));
	bx=b*cos(2*pi*(m/60.0));
	by=b*sin(2*pi*(m/60.0));
	d=sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));

/*cout<< ax <<endl;
cout<< ay <<endl;
cout<< bx <<endl;
cout<< by <<endl;*/
	cout<< d <<endl;
 
	return 0;
}