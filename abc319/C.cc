#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

bool is_sad(int x, vector<int> &v){
	if(v.size()==1 && v[0]==x) return true;
	v.push_back(x);
	return false;
}

int main(){

	int c[3][3];
	rep(i, 3) rep(j, 3) cin>> c[i][j];
	vector<int> perm={0, 1, 2, 3, 4, 5, 6, 7, 8};

	int cnt=0;
	do {
		vector<int> h0, h1, h2, w0, w1, w2, s0, s1;
		bool takahashi_sad=false;
		rep(i, 9){
			int h=perm[i]/3, w=perm[i]%3;
			int val=c[h][w];
			if(h==0) takahashi_sad=(takahashi_sad | is_sad(val, h0));
			if(h==1) takahashi_sad=(takahashi_sad | is_sad(val, h1));
			if(h==2) takahashi_sad=(takahashi_sad | is_sad(val, h2));
			if(w==0) takahashi_sad=(takahashi_sad | is_sad(val, w0));
			if(w==1) takahashi_sad=(takahashi_sad | is_sad(val, w1));
			if(w==2) takahashi_sad=(takahashi_sad | is_sad(val, w2));
			if(h==w) takahashi_sad=(takahashi_sad | is_sad(val, s0));
			if(h+w==2) takahashi_sad=(takahashi_sad | is_sad(val, s1));
		}
		if(!takahashi_sad) cnt++;
	} while (next_permutation(all(perm)));

	double div=1;
	rep3(i, 10, 1) div*=i;
	printf("%.12lf\n", cnt/div);
 
	return 0;
}