#include <bits/stdc++.h>
using namespace std;

int main(){

	map<string, int> mp;//文字列を入れると数字が出てくる

	int n;
	cin>> n;

	for(int i=0;i<n;i++){
		string tmp;
		cin>> tmp;
		mp[tmp]=i+1;
	}

	cout<< mp.size() <<endl;//mのサイズ:要素の種類数を出力

	cout<< mp["cat"] <<endl;//catがない時はintの初期値0が出る
	cout<< mp.at("cat") <<endl;//catがない時はエラーになる

	mp.erase("cat");

	if(mp.count("cat")){
		//catがある
	}else{
		//catがない
	}

	for(int i=0;i<mp.size();i++){
		//mの要素数だけループ
	}

	// Keyの値が小さい順にループ
	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
  		// key, valueを使う
		cout<< key << " " << value <<endl;
	}

	return 0;
}