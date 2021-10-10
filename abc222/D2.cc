#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=998244353;

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
	LLi cnt, ans=0;
	vector<LLi> a, b, v;

	cin>> n;
	a.resize(3010);
	b.resize(3010);
	v.resize(3010);

	rep(i, n) cin >> a[i];
	rep(i, n) cin >> b[i];

	if(n==1){
		cout<< b[0]-a[0]+1 <<endl;
		return 0;
	}

	for(int i=0;i<=3010;i++){
		if(a[0]<=i && i<=b[0]){
			v[i]=1;
		}else{
			v[i]=0;
		}
	}
	//PVL(v);

	for(int i=1;i<n;i++){
		cnt=0;
		for(LLi j=1;j<=3010;j++){
			if(j<a[i]){
				cnt+=v[j];
				cnt=cnt%mod;
				v[j]=0;
			}else if(a[i]<=j && j<=b[i]){
				//max(0LL, min(b[i-1]-a[i-1], j-a[i-1]));
				if(j==a[i]){
					cout<< "cnt " << cnt << ", v[j] " << v[j] <<endl;
					v[j]=(cnt+v[j])%mod;
				}else{
					if(v[j-1]+v[j]) cout<< "v[j-1] " << v[j-1] << ", v[j] " << v[j] <<endl;
					v[j]=(v[j-1]+v[j])%mod;
				}
			}else{
				v[j]=0;
			}
		}
		//PVL(v);
	}

	for(int i=0;i<=3010;i++){
		//cout<< v[i] <<endl;
		if(a[n-1]<=i && i<=b[n-1]){
			ans+=v[i];
			ans=ans%mod;
		}
	}

	cout<< ans <<endl;
 
	return 0;
}
