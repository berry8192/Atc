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

	LLi n, flag, cnt=1, aa=1, ab=1, ta, tb, ga, gb, gg, tmp;
	vector<LLi> v, w;
	string s;

	cin>> n;
	v.resize(n);

	rep(i, n){
		cin >> s;
		if(s=="AND") v[i]=1;
		else v[i]=0;
	}

	rep(i, n) {
		if (v[i]==1){
			cnt++;
		}else{
			w.push_back(cnt);
			cnt=1;
		}
	}
	w.push_back(cnt);
	//PVL(w);

	for(int i=0;i<w.size();i++){
		ta=(1<<w[i])-1;
		/*tb=1<<w[i];
		//cout<< ta SP << tb <<endl;
		ga=__gcd(aa, tb);
		gb=__gcd(ab, ta);
		aa/=ga;
		ta/=ga;
		ab/=gb;
		tb/=gb;
		aa*=ta;
		ab*=tb;
		gg=__gcd(aa, ab);
		aa/=gg;
		ab/=gg;*/
		aa*=ta;
		//cout<< aa SP << ab <<endl;
	}
	tmp=2<<n;
	tmp-=aa;

	cout<< tmp << endl;
 
	return 0;
}