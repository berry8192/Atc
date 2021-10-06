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

	int x, n, c1, c2, tmp;
	vector<int> v(110);

	cin>> x >> n;

	rep(i, n){
		cin >> tmp;
		v[tmp]=1;
	}

	c1=x;
	c2=x;

	while(1){
		if(v[c1]==0){
			cout<< c1 <<endl;
			return 0;
		}
		if(v[c2]==0){
			cout<< c2 <<endl;
			return 0;
		}
		c1--;
		c2++;
	}
}