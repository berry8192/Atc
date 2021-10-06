#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector<LLi> pri={1, 2, 3};

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

bool VVL(vector<LLi> vv1, vector<LLi> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

int main(){

	int n, tmp, ans=0;
	vector<int> v, che;
	cin>> n;

	v.resize(1000100);
	che.resize(1000100);
	rep(i, n){
		cin >> tmp;
		v[tmp]++;
	}
	
	for(int i=1;i<=1000000;i++){
		if(che[i]) continue;
		if(v[i]>0){
			for(int j=2;i*j<=1000000;j++) che[i*j]=1;
		}
		if(v[i]==1) ans++;
	}

	cout<< ans <<endl;

	return 0;
}

//0と1のコーナーケースに気をつける