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

	LLi r1,r2,c1,c2, x, y;

	cin>> r1 >> c1 >> r2 >> c2;

	if(r1==r2 && c1==c2) {
		cout<< 0 <<endl;
		return 0;
	}

	if(r1+c1==r2+c2 || r1-c1==r2-c2 || abs(r1-r2)+abs(c1-c2)<=3){
		cout<< 1 <<endl;
		return 0;
	}

	if(abs(r1-r2)+abs(c1-c2)<=6){
		cout<< 2 <<endl;
		return 0;
	}

	for(LLi i=-3;i<=3;i++){
		for(LLi j=-3;j<=3;j++){
			if(abs(i)+abs(j)>3) continue;
			x=r1+i;
			y=c1+j;
			if(x+y==r2+c2 || x-y==r2-c2 || abs(x-r2)+abs(y-c2)<=3){
				cout<< 2 <<endl;
				return 0;
			}
		}
	}

	if((r1+c1)%2==(r2+c2)%2){
		cout<< 2 <<endl;
		return 0;
	}

	cout<< 3 << endl;
 
	return 0;
}