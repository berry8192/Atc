#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

int main(){

	LLi n, ans=100000;
	vector<LLi> v(3);

	cin>> n;
	cin>> v[0] >> v[1] >> v[2];
	
	sort(all(v));

	rep(i, 10000) {
		if(i*v[2]+(9999-i)*v[1]<n) continue;
		if(i*v[2]>n) break;
		//cout<< "i=" << i SP << i*v[2] <<endl;
		for(int j=0;j+i<10000;j++){
			// if(i*v[2]+j*v[1]+(9999-i-j)*v[0]<n) continue;
			if(i*v[2]+j*v[1]>n) break;
			//cout<< "j=" << j SP << j*v[1] <<endl;
			//cout<< "left=" << n-i*v[2]-j*v[1] <<endl;
			if((n-i*v[2]-j*v[1])%v[0]==0){
				//cout<< "ans=" << i+j+(n-i*v[2]-j*v[1])/v[0] <<endl;
				ans=min(ans, i+j+(n-i*v[2]-j*v[1])/v[0]);
			}
		}
	}

	cout<< ans << endl;
 
	return 0;
}