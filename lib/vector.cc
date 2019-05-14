#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

	int n;
	vector<int> vdash;

	//初期化
	vector<int> v(10, 5);//要素数10、全ての要素の値5 で初期化
	v.assign(3, 1);//vの内容は {1, 1, 1} になる

	//入力
	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	//ソート
	sort(v.begin(), v.end());
	sort(v.begin(), v.end(), greater<int>());

	//コピー
        vdash.resize(v.size());
        copy(v.begin(), v.end(), vdash.begin());

	//末尾に挿入
	v.emplace_back(123);

	//途中に挿入
	v.insert(v.begin() + 4, 7);       //  [4] の位置に 7 を挿入
	// 結果は {3, 3, 3, 3, 7, 3, 3, 3, 3, 3, 3} となる

	//最後尾を消去
	v.pop_back();

	//途中を消去
	//std::vector<int> v{3, 1, 9, 4};
	v.erase(v.begin() + 2);       //  3番目の要素（9）を削除

	//複数消去
	//std::vector<int> v{3, 1, 4, 2, 5};
	v.erase(v.begin() + 1, v.begin() + 3);       // 1, 4 を削除

	//空か判定
	if(!v.empty()) cout<< "not empty, size:" << v.size() << endl;

	//個数を数える
	vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
	cout << count(v.begin(), v.end(), 5) << "\n";    //  要素5の個数を返す

	//出力
	for(int i=0;i<v.size();i++) cout<< v[i] << endl;

	cout<< n << endl;
	cout<< x[0] << " " << x[1] << endl;


}
