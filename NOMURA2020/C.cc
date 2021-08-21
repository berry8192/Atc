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

LLi SM(vector<LLi> smv) {
	LLi tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

int main(){

	LLi n, wid, k=1, ans=0;
	vector<LLi> a, v;

	cin>> n;
	a.resize(n+1);
	v.resize(n+1);

	rep(i, n+1) cin >> a[i];

	if(n==0){
		if(a[0]==1)	cout<< "1" <<endl;
		else cout<< "-1" <<endl;
		return 0;
	}

	if(a[0]!=0){
		cout<< "-1" <<endl;
		return 0;
	}

	wid=SM(a);
	//cout<< wid <<endl;

	v[0]=1;

	for(int i=0;i<n;i++){
		/*if(v[i-1]*2<a[i]){
			cout<< "-1" <<endl;
			return 0;
		}*/

		wid-=a[i];

		v[i+1]=2*(v[i]-a[i]);

		if(v[i+1]<a[i+1]){
			cout<< "-1" <<endl;
			return 0;
		}

		if(v[i+1]>=wid){
			v[i+1]=wid;
			i++;
			while(i<n){
				v[i+1]=v[i]-a[i];
				i++;
			}
			break;
		}
	}

	//PVL(a);
	//PVL(v);
	cout<< SM(v) <<endl;
 
	return 0;
}