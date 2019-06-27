#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<int> bi;
int pa;

//0~pa-1を長さnで生成、合計pa^n個生成
void bitgen(int n){

	//生成完了時の処理
	if(n==0){
		for(int i=0;i<bi.size();i++) cout<< bi[i] << " ";
		cout<< endl;

		return;
	}

	//再帰部分
	for(int i=0;i<pa;i++){
		bi[n-1]=i;
		bitgen(n-1);
	}
}

int main(){

	int n;
	cin>> n >> pa;

	bi.resize(n);
	bitgen(n);

}
