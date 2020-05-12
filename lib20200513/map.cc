#include <bits/stdc++.h>
using namespace std;

int main(){

	map<string, int> m;//文字列を入れると数字が出てくる

	int n;
	cin>> n;

	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		m[tmp]=i+1;
	}

	cout<< m["cat"] <<endl;//catがない時はintの初期値0が出る
	cout<< m.at("cat") <<endl;//catがない時はエラーになる

	m.erase("cat");

	if(m.count("cat")){
		//catがある
	}else{
		//catがない
	}

	for(int i=0;i<m.size();i++){
		//mの要素数だけループ
	}

	// Keyの値が小さい順にループ
	for (auto p : m) {
  		auto key = p.first;
  		auto value = p.second;
  		// key, valueを使う
		cout<< key << " " << value <<endl;
	}

	return 0;
}