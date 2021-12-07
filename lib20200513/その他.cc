#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

LLi mod=1000000007;
int imax=2147483647;
long long int lmax=9223372036854775807;
double PI=3.14159265358979323;

//vector<int>を出力
void PV(vector<int> pvv) {
	rep(i, (int)pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[(int)pvv.size()-1] <<endl;
}

//vector<LLi>を出力
void PVL(vector<LLi> pvv) {
	rep(i, (int)pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[(int)pvv.size()-1] <<endl;
}

//vecotr<int>同士の比較
bool VV(vector<int> vv1, vector<int> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, (int)vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<LLi>同士の比較
bool VVL(vector<LLi> vv1, vector<LLi> vv2) {
	if(vv1.size()!=vv2.size()) return false;
	rep(i, (int)vv1.size()) if(vv1[i]!=vv2[i]) return false;

	return true;
}

//vecotr<int>の総和
LLi SM(vector<int> smv) {
	LLi tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

//vecotr<LLi>の総和
LLi SML(vector<LLi> smv) {
	LLi tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

//進数変換10->2 桁指定 10進->2進
string tob(LLi n, int lng, string fil)
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

	//順列全探索
	//巡回セールスマン https://qiita.com/e869120/items/702ca1c1ed6ff6770257
	//sort(v.begin(), v.end());
	do {
		PV(v);
	} while (next_permutation(all(v)));

	//2進数表記にしたときの1の数
	__builtin_popcount(n);

	return 0;
}

//グラフ理論（DFS）
//https://qiita.com/drken/items/4a7869c5e304883f539b

//ヒストグラム中の最大の長方形の面積
//http://algorithms.blog55.fc2.com/blog-entry-132.html