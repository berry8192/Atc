#include <bits/stdc++.h>
using namespace std;

int n, mi=99999999;
vector<int> v, c;
vector<int> bi;

//0~pa-1を長さnで生成、合計pa^n個生成
void bitgen(int len){

	//生成完了時の処理
	if(n==0){
		for(int i=0;i<bi.size();i++) cout<< bi[i] << " ";
		cout<< endl;

		int su, cost;
		su=0;
		cost=0;

		for(int i=0;i<bi.size();i++){
			if(bi[i]){
				su+=v[i];
				cost+=c[i];
			}
		}

		if(su>100) mi=min(mi, cost);

		return;
	}

	//再帰部分
	for(int i=0;i<pa;i++){
		bi[len-1]=i;
		bitgen(len-1);
	}
}

int main(){

	cin>> n;
	v.resize(n);
	c.resize(n);
	for(int i=0;i<n;i++) cin>> v[i] >> c[i];

	bi.resize(n);
	bitgen(n);

	cout<< mi <<endl;

	return 0;
}