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

int gcdi(int a, int b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

int gcdv(vector<int> gv){
	int tmp=gv[0];
	for(int i=1;i<(int)gv.size();i++) tmp=gcdi(tmp, gv[i]);
	return tmp;
}

int main(){

	int n, m, tmp, pr=0, han, ans=0;
	vector<int> v, inp;

	cin>> n >> m;
	if(n==m){
		cout<< 0 << endl;
		return 0;
	}

	inp.resize(m);
	rep(i, m) cin>> inp[i];
	sort(inp.begin(), inp.end());

	rep(i, m){
		tmp=inp[i];
		if(tmp-pr-1>0) v.push_back(tmp-pr-1);
		pr=tmp;
	}
	if(n+1-pr-1>0) v.push_back(n+1-pr-1);
	//PV(v);
	han=v[0];
	for(int i=1;i<v.size();i++){
		han=min(han, v[i]);
	}

	rep(i, (int)v.size()) ans+=(v[i]+han-1)/han;

	cout<< ans <<endl;
 
	return 0;
}