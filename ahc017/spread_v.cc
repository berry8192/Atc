// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp;
double end_temp=0.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

template <class T> void PS(T ps) {
    cout<< "{";
	for(auto itr = ps.begin(); itr != ps.end(); ++itr) cout<< *itr SP;
	cout<< "}" <<endl;
}

template <class T> T v_inv(T pvv) {
    vector<pair<int, int>> pa;
	// rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i)); // 昇順の場合
	rep(i, pvv.size()) pa.push_back(make_pair(-pvv[i], i));
    sort(all(pa));
    vector<int> rtn;
    rep(i, pa.size()) rtn.push_back(pa[i].second);
    return rtn;
}

//入力
int n, m, d, k;
vector<int> u, v, w;

// 構造体
struct edge{
    int from;
    int to;
    int id;
    
	bool operator<(const edge &in) const{
		return from!=in.from ? from<in.from : to<in.to;
	};
};

vector<edge> vv;
vector<int> ans;
void inpt(){
    // cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    ans.resize(m);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        vv.push_back({u[i], v[i], i});
    }
}

int main(){
    inpt();
    sort(all(vv));
    rep(i, m) ans[vv[i].id]=i%d+1;
    PV(ans);

    return 0;
}
