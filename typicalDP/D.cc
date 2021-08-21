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
	cout << fixed << setprecision(12);

	int n, d2=0, d3=0, d5=0;
	LLi d;
	double dp[70][50][30];

	cin>> n >> d;

	while(d%2==0){
		d2++;
		d/=2;
	}
	while(d%3==0){
		d3++;
		d/=3;
	}
	while(d%5==0){
		d5++;
		d/=5;
	}
	//cout<< "2^" << d2 << " 3^" << d3 << " 5^" << d5 <<endl;
	
	if(d!=1){
		cout<< 0 <<endl;
		return 0;
	}

	dp[0][0][0]=1.0;

	rep(i, n){
		for(int j2=d2;j2>=0;j2--){
			for(int j3=d3;j3>=0;j3--){
				for(int j5=d5;j5>=0;j5--){
					//cout<< j2 << " " << j3 << " " << j5 <<endl;
					double ad=dp[j2][j3][j5];
					dp[min(d2, j2+1)][min(d3, j3+1)][min(d5, j5)]+=ad;
					dp[min(d2, j2)][min(d3, j3)][min(d5, j5+1)]+=ad;
					dp[min(d2, j2+2)][min(d3, j3)][min(d5, j5)]+=ad;
					dp[min(d2, j2)][min(d3, j3+1)][min(d5, j5)]+=ad;
					dp[min(d2, j2+1)][min(d3, j3)][min(d5, j5)]+=ad;
					//dp[min(d2, j2)][min(d3, j3)][min(d5, j5)]+=ad;
				}
			}
		}
	}

	//cout<< dp[d2][d3][d5] << endl;
	cout<< dp[d2][d3][d5]/pow(6.0, n) << endl;
 
	return 0;
}