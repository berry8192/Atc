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

	int n, k, s, pos, rem, shu, flag;
	LLi ans=0, ma=-llimax;
	vector<int> p, v;

	cin>> n >> k;
	p.resize(n+1);
	v.resize(n+1);

	rep(i, n) cin >> p[i+1];
	rep(i, n) cin >> v[i+1];

	rep(i, n) {
		s=i+1;
		pos=s;
		rem=k;
		ans=0;
		flag=0;
		while(rem>0){
			ans+=v[p[pos]];
			pos=p[pos];
			rem--;
			ma=max(ma, ans);
			if(pos==s && flag==0){
				shu=k-rem;
				if(rem>shu){
					ans*=rem/shu;
					rem=rem%shu+shu;
				}
				flag=1;
			}
		}
	}

	cout<< ma << endl;
 
	return 0;
}