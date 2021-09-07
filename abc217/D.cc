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

// struct kuk{
// 	int a;
// 	int b;
// };

int main(){

	int l, q, c, x, a, b;
	set<int> li;
	vector<int> v;

	cin>> l >> q;
	li.insert(0);
	li.insert(l);

	rep(i, q){
		cin >> c >> x;
		if(c==1){
			li.insert(x);
		}else{
			decltype(li)::iterator it = li.lower_bound(x);
    		decltype(li)::iterator last = li.upper_bound(x);
			//cout<< distance(li.begin(), it) <<endl;
			//cout<< distance(li.begin(), last) <<endl;
			a=*it;
			it--;
			b=*it;
			cout<< a-b <<endl;
			//v.push_back(a-b);
		}
	}

	//PV(v);
 
	return 0;
}