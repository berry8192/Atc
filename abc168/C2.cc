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

	double a, b, h, m;
	double hx, hy, mx, my;

	cin>> a >> b >> h >> m;
	cout << fixed << setprecision(12);

	hx=a*cos((h/12.0+m/60.0/12.0)*2*3.1415926539793);
	hy=a*sin((h/12.0+m/60.0/12.0)*2*3.1415926539793);
	mx=b*cos((m/60.0)*2*3.1415926539793);
	my=b*sin((m/60.0)*2*3.1415926539793);

	cout<< sqrt((hx-mx)*(hx-mx)+(hy-my)*(hy-my)) << endl;
 
	return 0;
}