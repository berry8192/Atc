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

	int a, b;
	int va[1010], vb[1010];
	int bod[1010][1010];

	cin>> a >> b;

	rep(i, a) cin>> va[i];
	rep(i, b) cin>> vb[i];

	bod[a][b]=0;
	/*for(int i=1;i<a;i++){
		if((b+i)%2==1) bod[i][b]=va[i];
		else bod[i][b]=0;
	}
	for(int i=1;i<b;i++){
		if((a+i)%2==1) bod[a][i]=vb[i];
		else bod[a][i]=0;
	}*/

	for(int i=a;i>=0;i--){
		for(int j=b;j>=0;j--){
			if(i==a && j==b) continue;
			if((i+j)%2==0){
				if(i==a) bod[i][j]=vb[j]+bod[i][j+1];
				else if(j==b) bod[i][j]=va[i]+bod[i+1][j];
				else bod[i][j]=max(va[i]+bod[i+1][j], vb[j]+bod[i][j+1]);
			}else{
				if(i==a) bod[i][j]=bod[i][j+1];
				else if(j==b) bod[i][j]=bod[i+1][j];
				else bod[i][j]=min(bod[i+1][j], bod[i][j+1]);
			}
		}
	}

	cout<< bod[0][0] <<endl;

	/*or(int i=0;i<=a;i++){
		for(int j=0;j<=b;j++){
			cout<< bod[i][j] << " ";
		}
		cout<< endl;
	}*/
 
	return 0;
}