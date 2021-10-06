#include <bits/stdc++.h>
using namespace std;

int main(){

	int n, tmp;
	priority_queue<int> pq;//でかいのから出てくる
	priority_queue<int, vector<int>, greater<int>> pq;//小さいのから出てくる
	cin>> n;
	
	//1だったら入力クエリ
	//2だったら出力クエリ
	for(int i=0;i<n;i++){
		cin>> tmp;
		if(tmp==1){
			cin>> tmp;
			pq.push(tmp);
		}else{
			cout<< pq.top() <<endl;
			pq.pop();
		}
		cout<< pq.size() <<endl;
	}

	while(!pq.empty()){
		//空でない限り繰り返す
	}

	return 0;
}