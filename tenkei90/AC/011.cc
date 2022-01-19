#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
struct tsk{
	int d;
	int c;
	int s;

	bool operator<(const tsk &in) const{
		return d<in.d;
	};
};

int main(){

	int n, d, c, s;
	LLi ma=0;
	vector<tsk> v;
	cin>> n;
	vector< vector<LLi> > ans(n+1);

	rep(i, n){
		cin >> d >> c >> s;
		v.push_back({d, c, s});
	}
	sort(all(v));

	//ans[i][j]=x i個目の仕事を見た後で、これまでに仕事をした時間がjのときの給料がx
	rep(i, n+1) ans[i].resize(5001);

	rep(i, n){
		rep(j, 5001){
			//今見てる仕事をしない場合
			ans[i+1][j]=max(ans[i][j], ans[i+1][j]);
			//cout<< i+1 SP << key SP << val <<endl;
			//今見てる仕事をする場合
			if(v[i].d>=j+v[i].c){
				ans[i+1][j+v[i].c]=max(ans[i][j]+v[i].s, ans[i+1][j+v[i].c]);
				//cout<< i+1 SP << key+v[i].c SP << val+v[i].s <<endl;
			}
		}
		//cout<< endl;
	}

	rep(i, 5001) ma=max(ma, ans[n][i]);
	cout<< ma <<endl;
 
	return 0;
}

