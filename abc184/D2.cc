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

int a, b, c, ta, tb, tc;
double dp[110][110][110], ans=0.0, am=0.0;
int sn[110][110][110];
	
int main(){

	cin>> a >> b >> c;

	rep(i, 110){
		rep(j, 110){
			rep(k, 110){
				dp[i][j][k]=0.0;
				sn[i][j][k]=0;
			}
		}
	}

	queue<int> qa, qb, qc;
	qa.push(a);
	qb.push(b);
	qc.push(c);
	while (!qa.empty()) {
		ta=qa.front();
		tb=qb.front();
		tc=qc.front();
    	qa.pop();
    	qb.pop();
    	qc.pop();
		sn[ta][tb][tc]=1;
		double cr=dp[ta][tb][tc];
		int su=ta+tb+tc;
		if(sn[ta+1][tb][tc]==0 && ta<=100){
			qa.push(ta+1);
			qb.push(tb);
			qc.push(tc);
			dp[ta+1][tb][tc]+=(cr)*ta/su+1.0;
		}
		if(sn[ta][tb+1][tc]==0 && tb<=100){
			qa.push(ta);
			qb.push(tb+1);
			qc.push(tc);
			dp[ta][tb+1][tc]+=(cr)*tb/su+1.0;
		}
		if(sn[ta][tb][tc+1]==0 && tc<=100){
			qa.push(ta);
			qb.push(tb);
			qc.push(tc+1);
			dp[ta][tb][tc+1]+=(cr)*tc/su+1.0;
		}
  	}

	rep(i, 100){
		rep(j, 100){
			if(dp[100][i][j]){
				ans+=dp[100][i][j];
				am+=1.0;
			}
			if(dp[i][100][j]){
				ans+=dp[i][100][j];
				am+=1.0;
			}
			if(dp[i][j][100]){
				ans+=dp[i][j][100];
				am+=1.0;
			}
		}
	}
	cout<< ans/am << endl;
 
	return 0;
}