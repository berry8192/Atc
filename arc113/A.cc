#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int k, tmp;
	LLi ans=0;
	vector<int> v, w;
	cin>> k;
	v.resize(k+1);
	w.resize(k+1);
	w[0]=0;

	for(int i=1;i<=k;i++){
		tmp=0;
		for(int j=1;j*j<=i;j++){
			if(i%j==0) tmp+=2;
			if(j*j==i) tmp--;
		}
		v[i]=tmp;
		w[i]=v[i]+w[i-1];
	}
	//PV(v);
	//PV(w);

	for(int i=1;i<=k;i++){
		ans+=w[k/i];
	}

	cout<< ans <<endl;
 
	return 0;
}