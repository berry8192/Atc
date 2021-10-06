#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

vector<LLi> ruiseki(vector<int> vv){
//vector<int> ruiseki(vector<int>){
	vector<LLi> xx;
	//vector<int> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
	}
	return xx;
}

int main(){

	int n;
	vector<int> vdash;

	//初期化
	vector<int> v(10, 5);//要素数10、全ての要素の値5 で初期化
	v.assign(3, 1);//vの内容は {1, 1, 1} になる
    fill( vec_a.begin(), vec_a.end(), 71 );//71で埋める

	//dp配列を-1か0で初期化
	memset(dp, -1, sizeof(dp));

	//入力
	cin>> n;
	v.resize(n);
	for(int i=0;i<n;i++) cin>> v[i];

	//ソート
	sort(v.begin(), v.end());
	sort(v.begin(), v.end(), greater<int>());

	//逆順
	reverse(v.begin(), v.end());

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

	//全消去
	v.clear();

	//空か判定
	if(!v.empty()) cout<< "not empty, size:" << v.size() << endl;

	//個数を数える
	vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
	cout << count(v.begin(), v.end(), 5) << "\n";    //  要素5の個数を返す

	//vectorを線形探索して初めて100が出てきた場所を返す
	auto itr = find(all(v), 100);
	ans+=itr-v.begin();

	//O(log(v.size))で100の個数を数える
	auto lb = lower_bound(all(v), 100);
	auto ub = upper_bound(all(v), 100);
	ans+=ub-lb;
	//O(log(v.size))で100があるかみる
	cout<< binary_search(all(v), 100) <<endl;

	//0~9からなる文字列sをvに格納
  	rep(i, n) v[i]=(int)(s[i]-'0');

	//出力
	for(int i=0;i<v.size();i++) cout<< v[i] << endl;

	return 0;
}