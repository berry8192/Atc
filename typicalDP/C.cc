#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<double> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){
	cout << fixed << setprecision(10);

	int k;
	vector<double> v;
	double dp[1040][15];
	bool che[1040][1040];

	cin>> k;
	v.resize(1<<k);
	//cout<< (1<<k) <<endl;

	rep(i, 1<<k){
		cin>> v[i];
		dp[i][0]=1.0;
	}

	for(int i=1;i<=k;i++){
		for(int j=0;j<(1<<k);j++){
			dp[j][i]=0;
			for(int l=0;l<(1<<k);l++){
				if(j/(1<<i)!=l/(1<<i) || (j%(1<<i))==(l%(1<<i))) continue;
				if(che[j][l]) continue;
				che[j][l]=true;
				//cout<< j << " VS " << l <<endl;
				dp[j][i]+=dp[j][i-1]*dp[l][i-1]/(1.0+pow(10.0, (v[l]-v[j])/400.0));
			}
		}
	}

	rep(i, 1<<k) cout<< dp[i][k] <<endl;

	/*int k, ene, pos;
	double tmp;
	vector< vector<double> > vp, vr;

	cin>> k;
	vp.resize(pow(2, k+1));
	vr.resize(pow(2, k+1));

	rep(i, pow(2, k+1)) vp[i].resize(1, 1.0);

	//cout<< (int)pow(2, k)-1 <<endl;
	//cout<< (int)pow(2, k+1)-1 <<endl;
	for(int i=(int)pow(2, k)-1;i<(int)pow(2, k+1)-1;i++){
		cin>> tmp;
		vr[i].push_back(tmp);
	}

	for(int i=k-1;i>=0;i--){
		for(int j=(int)pow(2, i)-1;j<(int)pow(2, i+1)-1;j++){
			//v[(j-1)/2]=v[j]*(1.0/(1.0+pow(10.0, (v[j+1]-v[j])/400.0)))+v[j+1]*(1.0/(1.0+pow(10.0, (v[j]-v[j+1])/400.0)));
			//cout<< j <<" ";
			for(int l=0;l<vp[j*2+1].size();l++){
				for(int m=0;m<vp[j*2+2].size();m++){
					vp[j].push_back(vp[j*2+1][l]);
				}
			}
		}
		//cout<< endl;
	}*/

	/*for(int i=(int)pow(2, k)-1;i<(int)pow(2, k+1)-1;i++){
		tmp=1.0;
		pos=i;
		for(int j=k;j>0;j--){
			ene=(pos-1)/2;
			if(pos%2==0) ene=ene*2+1;
			else ene=ene*2+2;
			pos=(pos-1)/2;
			tmp/=1.0+pow(10.0, (v[ene]-v[i])/400.0);
			cout<< i << " VS " << ene <<endl;
		}
		//cout<< tmp <<endl;
		cout<< v[i] << " " << tmp <<endl;
	}*/

	return 0;
}