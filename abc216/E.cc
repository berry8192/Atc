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

	int n, k;
	LLi ans=0, su=0, sua=0;
	vector<LLi> v;

	cin>> n >> k;
	v.resize(n);

	rep(i, n){
		cin >> v[i];
		su+=v[i]*(v[i]+1)/2;
		sua+=v[i];
	}
	if(sua<=k){
		cout<< su <<endl;
		return 0;
	}

	LLi ri, le, mi, tmp, amo, cnt;
	ri=2000000001;
	le=0;
	while(1){
		cnt=0;
		tmp=0;
		amo=0;
		mi=(ri+le)/2;
		//cout<< mi <<endl;
		rep(i, n){
			if(v[i]>=mi){
				cnt++;
				tmp+=(v[i]-mi)*(v[i]+mi+1)/2;
				double vrf=1.0*(v[i]-mi)*(v[i]+mi+1);
				if(0.999*vrf/(v[i]-mi)>(v[i]+mi+1) || (v[i]+mi+1)>1.001*vrf/(v[i]-mi)){
					amo=k+1;
					break;
				}
				amo+=v[i]-mi;
			}
		//cout<< tmp SP << cnt SP << amo <<endl;
		}

		if(amo+cnt<k) ri=mi;
		else if(k<amo) le=mi;
		else{
			tmp+=mi*(k-amo);
			break;
		}
	}

	cout<< tmp << endl;
 
	return 0;
}