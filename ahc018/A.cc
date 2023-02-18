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

//焼きなましの定数
double TIME_LIMIT=4900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;

//入力
int N, W, K, C;
int S[210][210];
vector<int> a, b, c, d;

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
    rep(i, W){
        cin>> a[i] >> b[i];
    }
    rep(i, K){
        cin>> c[i] >> d[i];
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    Land city;
    city.init();

    rep(i, 200){
        rep(j, 200){
            if(i==c[0] && j==d[0]) continue;
            while(1){
                cout<< i SP << j SP << 1 <<endl;
                int tmp;
                cin>> tmp;
                if(tmp==1) break;
            }
        }
    }
    while(1){
        cout<< c[0] SP << d[0] SP << 1 <<endl;
        int tmp;
        cin>> tmp;
        if(tmp==2) break;
    }

    return 0;
}
