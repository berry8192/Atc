#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

vector<int> bi;
long long int n, m, x, mi=99999999;
vector< vector<int> > v;

void bitgen(int len){

	//生成完了時の処理
	if(len==0){
		long long int tmp;
		vector<int> stu(m);
		tmp=0;
		rep(i, m) stu[i]=0;

		for(int i=0;i<n;i++){
			//cout<< bi[i];
			if(bi[i]){
				tmp+=v[i][0];
				rep(j, m) stu[j]+=v[i][j+1];
			}
		}
		//cout<< endl;
		
		int flag;
		flag=1;

		rep(i, m){
			//cout<< stu[i] << " ";
			if(stu[i]<x) flag=0;
		}
		//cout<< endl;

		if(flag){
			mi=min(mi, tmp);
		}

		return;
	}

	//再帰部分
	for(int i=0;i<2;i++){
		bi[len-1]=i;
		bitgen(len-1);
	}
}

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	cin>> n >> m >> x;
	v.resize(n);
	rep(i, n) v[i].resize(m+1);

	rep(i, n){
		rep(j, m+1){
			cin>> v[i][j];
		}
	}
	
	bi.resize(n);
	bitgen(n);

	if(mi==99999999) cout<< "-1" << endl;
	else cout<< mi << endl;
 
	return 0;
}