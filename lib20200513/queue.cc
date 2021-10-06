#include <bits/stdc++.h>
using namespace std;

int main(){

	int n;
  	queue<int> q;
  	stack<int> s;
	deque<int> dq;//両端キュー
	cin>> n;
	
	for(int i=0;i<n;i++){
		int tmp;
		cin>> tmp;
		q.push(tmp);
	}

	cout<< q.size() <<endl;//qのサイズ

  	// 空でない間繰り返す
  	while (!q.empty()) {
    	cout << q.front() << endl;  // 先頭の値を出力
    	q.pop();  // 先頭の値を削除
  	}

	//両端キュー
	dq.push_back(値);   // 末尾への値の追加
	dq.push_front(値);  // 先頭への値の追加
	dq.front();  // 先頭の値へのアクセス
	dq.back();   // 末尾の値へのアクセス
	dq.at(i);  // i番目へのアクセス
	dq.pop_front();  // 先頭の要素の削除
	dq.pop_back();   // 末尾の要素の削除
	dq.size();
	dq.empty();

	return 0;
}