#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int n, tmp;
	cin>> n;
	
	//定義
	multiset<int> st;
	multiset<int> st{3, 1, 4}; //初期化 {1, 3, 4}となる
	multiset<int> st{3, 1, 4, 1}; //重複可 {1, 1, 3, 4}となる
	multiset<int> st2(st); //st2をstの内容で生成

	//要素の追加
	rep(i, n){
		cin>> tmp;
		st.insert(tmp);
	}

	//要素の削除
	st.erase(3); //3をすべて消去
	int era=st.erase(1); //1をすべて削除して消した数を代入
	cout<< era <<endl;
	erase(st.begin()); //先頭を消去(イテレータが引数)
	erase(st.begin(), st.end()); //すべて消去(少し動かせば1つだけ残したりできる)
	for(auto itr = st.begin(); itr != st.end();) {
        if( *itr % 2 == 0 )      // 偶数ならば
            itr = st.erase(itr);       //  削除
        else
            ++itr;
    }
	st.clear();

	//要素へアクセス
	auto itr = st.begin(); //最初の要素へのイテレータを取得
    cout<< *itr <<endl;
	itr++; //イテレータずらし
    cout<< *itr <<endl;
	
	//全要素表示
	for(auto itr = st.begin(); itr != st.end(); ++itr) {
        cout << *itr << "\n";      // イテレータの指す先のデータを表示
    }

	//要素を検索
	auto itr=st.find(3); //3のイテレータを返す
	auto itr=st.lower_bound(3);
	auto itr=st.upper_bound(3);
	if(itr!=st.end()){
		//あった場合
		cout<< *itr <<endl;
	}else{
		//ない場合
		cout<< "ないです" <<endl;
	}
	cout<< st.count(3) <<endl; //3の個数

	//その他
	if(!st.empty()) cout<< "not empty" <<endl;
	if(st.size()>0) cout<< "not empty" <<endl;

	return 0;
}