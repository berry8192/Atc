#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long int

using namespace std;

ll mod=1000000007;
int imax=2147483647;
long long int lmax=9223372036854775807;
double PI=3.14159265358979323;

//vector<int>を出力
void PV(vector<int> pvv) {
	rep(i, (int)pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[(int)pvv.size()-1] <<endl;
}

//vector<ll>を出力
void PVL(vector<ll> pvv) {
	rep(i, (int)pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[(int)pvv.size()-1] <<endl;
}

//vecotr<int>同士の比較
bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, (int)vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<ll>同士の比較
bool VVL(vector<ll> vv1, vector<ll> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, (int)vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<int>の総和
ll SM(vector<int> smv) {
	ll tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

//vecotr<ll>の総和
ll SML(vector<ll> smv) {
	ll tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

//進数変換10->2 桁指定 10進->2進
string tob(ll n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

int main(){

	int n;
	vector<int> v;
	cin>> n;

	v.resize(n);
	rep(i, n) cin>> v[i];

	//小数点桁数指定
	cout << fixed << setprecision(12);
	printf("%.15lf\n", n);

	//順列全探索
	//巡回セールスマン https://qiita.com/e869120/items/702ca1c1ed6ff6770257
	//sort(v.begin(), v.end());
	vector<int> p;
	rep(i, n) p.push_back(i);
	do {
		PV(p);
	} while (next_permutation(all(p)));

	//2進数表記にしたときの1の数
	__builtin_popcount(n);

	// 区間の交差判定、(a, b)と(c, d)
	int a, b, c, d;
	if(max(a, c)<min(b, d)){
		cout<< "交差" << min(b, d)-max(a, c) <<endl;
	}else{
		cout<< "交差しない" <<endl;
	}
	cout<< "共有部分は" << max(0, min(b, d)-max(a, c)) <<endl;

	return 0;
}

//グラフ理論（DFS）
//https://qiita.com/drken/items/4a7869c5e304883f539b

//ヒストグラム中の最大の長方形の面積
//http://algorithms.blog55.fc2.com/blog-entry-132.html