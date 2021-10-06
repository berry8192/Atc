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

LLi gcdi(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

int main(){

	LLi l, ans=1, tmp;
	vector<LLi> a, b;

	cin>> l;

	rep(i, 11) a.push_back(l-1-i);
	rep(i, 11) b.push_back(i+1);
	reverse(b.begin(), b.end());

	//PVL(a);
	//PVL(b);

	rep(i, 11) {
		rep(j, 11){
			tmp=gcdi(a[i], b[j]);
			a[i]/=tmp;
			b[j]/=tmp;
		}
	}

	rep(i, 11) ans*=a[i];
	//PVL(a);
	//PVL(b);

	cout<< ans << endl;
 
	return 0;
}