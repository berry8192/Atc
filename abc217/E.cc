#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int q, c, x, pos=0;
	vector<int> v;
	priority_queue<
      int,                // 要素の型はint
      std::vector<int>,   // 内部コンテナはstd::vector (デフォルトのまま)
      std::greater<int>   // 昇順 (デフォルトはstd::less<T>)
    > que;

	cin>> q;

	rep(i, q){
		cin >> c;
		if(c==1){
			cin>> x;
			v.push_back(x);
		}else if(c==2){
			if(que.size()>0){
				cout<< que.top() <<endl;
				que.pop();
			}else{
				cout<< v[pos] <<endl;
				pos++;
			}
		}else{
			for(int j=pos;j<v.size();j++) que.push(v[j]);
			v.clear();
			pos=0;
		}
	}

	return 0;
}