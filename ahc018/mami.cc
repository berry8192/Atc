// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
// using namespace atcoder;

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;
int dr[4]={0, -1, 0, 1}, dc[4]={-1, 0, 1, 0};

//焼きなましの定数
double TIME_LIMIT=4900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;
int excavation_count=0; //testtest
int score=0; //testtest

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
	cout<< pvv[pvv.size()-1] <<endl;
}

//グローバル
int N, W, K, C;
int S[210][210]; //testtest
vector<int> a, b, c, d;
int HYPER_V_IDX =40000;

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> N >> W >> K >> C;
    rep(i, 200){
        rep(j, 200){
            cin>> S[i][j];
        }
    }
    a.resize(W);
    b.resize(W);
    c.resize(K);
    d.resize(K);
    
    vector<int> ss;
    rep(i, W){
        cin>> a[i] >> b[i];
        ss.push_back(S[a[i]][b[i]]);
    }
    rep(i, K){
        cin>> c[i] >> d[i];
        ss.push_back(S[c[i]][d[i]]);
    }
    sort(all(ss));
    PV(ss);
    exit(0);
}

void init(){
    inpt();
}

int main(){

    init();

    return 0;
}
