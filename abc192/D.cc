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

	string x;
	LLi m, tmp, d, pd, flag;
	int dma=0;

	cin>> x;
	cin>> m;

	for(int i=0;i<x.size();i++){
		dma=max(dma, (int)(x[i]-'0'));
	}

	reverse(x.begin(), x.end());
	//cout<< x <<endl;
	
	LLi ri, le, mi;
	ri=1000000000000000002;
	le=-1;
	while(ri-le>1){
		mi=(ri+le)/2;
		//cout<< mi SP;
		//mi sinhou
		tmp=0;
		d=1;
		flag=0;
		for(int i=0;i<x.size();i++){
			// || (m<mi*d && i!=x.size()-1)
			if(m<d){
				flag=1;
				break;
			}
			tmp+=d*(int)(x[i]-'0');
			pd=d;
			d*=mi;
			//cout<< tmp <<endl;
			if(i!=x.size()-1 && d/pd!=mi){
				flag=1;
				break;
			}
			if(m<tmp || tmp<0){
				flag=1;
				break;
			}
		}
		//cout<< tmp <<endl;

		if(flag) ri=mi;
		else le=mi;
	}

	LLi zr=0;
	cout<< max(zr, min(m, le)-dma) <<endl;
 
	return 0;
}