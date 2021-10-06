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

	int n, ans=0, tmp;
	vector<int> v;

	cin>> n;
	v.resize(n+1);

	for(int i=1;i<100;i++){
		for(int j=1;j<100;j++){
			for(int k=1;k<100;k++){
				tmp=i*i+j*j+k*k+i*j+j*k+k*i;
				if(tmp<=n) v[tmp]++;
			}
		}
	}

	for(int i=1;i<=n;i++) cout<< v[i] <<endl;
 
	return 0;
}