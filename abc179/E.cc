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

	LLi n, x, m, tmp, del, rp, ans=0, flag=1;
	vector<LLi> v, va;

	cin>> n >> x >> m;
	v.resize(m+1);
	va.resize(m+1);

	for(LLi i=1;i<=n;i++){
		tmp=x;
		ans+=x;
		x=x*x;
		x=x%m;
		if(v[tmp]>0 && flag){
			flag=0;
			del=i-v[tmp];
			rp=(n-i)/del;
			//cout<< del << "#" << rp << "#" << i << "#" << v[x] << "#" << ans << "#" << va[x] <<endl;
			i+=rp*del;
			ans+=rp*(ans-va[tmp]);
		}
		v[tmp]=i;
		va[tmp]=ans;
	}

	cout<< ans << endl;
 
	return 0;
}
//492443256176507