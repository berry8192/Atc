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

	int n, k, tmp, ans=0;
	vector<int> v, ba, fr;

	cin>> n >> k;
	v.resize(k+1);
	ba.resize(k+1);
	fr.resize(k+1);

	rep(i, k){
		cin >> tmp;
		ba[tmp]=
		v[tmp]=1;
	}

	for(int i=1;i<=n;i++){
		if(v[i]==1) continue;

	}

	for(auto itr = lst.begin(); itr != lst.end(); ++itr) {
        std::cout << *itr << "\n";
    }
 
	return 0;
}