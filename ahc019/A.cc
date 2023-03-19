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
double TIME_LIMIT=5900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

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

//入力
int D;
vector<vector<vector<int>>> f, r;
Pos d6[]={{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> D;

    f.resize(2);
    rep(i, 2) f[i].resize(D);
    rep(i, 2) rep(j, D) f[i][j].resize(D);
    r.resize(2);
    rep(i, 2) r[i].resize(D);
    rep(i, 2) rep(j, D) r[i][j].resize(D);

    rep(i, 2){
        rep(j, D){
            rep(k, D){
                cin>> f[i][j][k];
            }
        }
        rep(j, D){
            rep(k, D){
                cin>> r[i][j][k];
            }
        }
    }
}

// 構造体
struct Pos{
    int x;
    int y;
    int z;

    Pos(){};
    Pos(int xx, int yy, int zz){
        x=xx;
        y=yy;
        z=zz;
    }
};

struct Field{
    vector<vector<vector<int>>> val; //-1のときNG、0のとき空、それ以外block
    Field(){}
    Field(vector<vector<int>> sif, vector<vector<int>> sir){
        rep(i, D){
            rep(j, D){
                if(sif[i][j]==0){
                    rep(k, D) val[i][k][j]=-1;
                }
                if(sir[i][j]==0){
                    rep(k, D) val[k][i][j]=-1;
                }
            }
        }
    }

    void print_val(){
        rep(i, D) rep(j, D) rep(k, D) cout<< val[i][j][k] SP;
        cout<<endl;
    }
};

struct Puzzle{
    Field f1=Field(f[0], r[0]), f2=Field(f[1], r[1]);
    Puzzle(){}
    void init(){

    }
    void print_ans(){
        f1.print_val();
        f2.print_val();
    }
};

void init(){
    inpt();
}

void get_argv(int argc, char* argv[]){
    vector<double> args;
    rep3(i, argc, 1){
        string tmp;
        tmp.assign(argv[i]);
        args.push_back(stof(tmp));
        // cout<< args[i-1] <<endl;
    }
}

int main(int argc, char* argv[]){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    init();
    // get_argv(argc, argv);

    return 0;
}

