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

	LLi n, tmp;
	set<LLi> s;

	cin>> n;

	for(LLi i=2;i<100000;i++){
		tmp=i;
		for(LLi j=2;j<40;j++){
			tmp*=i;
			if(tmp<=n) {
				s.insert(tmp);
			}else{
				break;
			}
		}
	}

	cout<< n-s.size() <<endl;
 
	return 0;
}