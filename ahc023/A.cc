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

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] SP;
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
// 		rep(j, pvv[i].size()){
// 			outputFile << pvv[i][j] SP;
// 		}
// 		outputFile << endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax=2147483647;
long long llimax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=1900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int T, K, H, W, i0;
int S[4010], D[4010];
int h[21][21], v[21][21];

// 構造体
struct Pos{
    int h;
    int w;

    Pos(){};
    Pos(int hh, int ww){
        h=hh;
        w=ww;
    }

    void print(){
        cout<< "(" << h << ", " << w << ")" <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.h=h+pos.h;
        rtn.w=w+pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.h=h-pos.h;
        rtn.w=w-pos.w;
        return rtn;
    }
};

Pos d4[]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
Pos crops[4010];

struct Space{

    void init(){
        
    }

    void print_placement(){

    }
    void print_ans(){
    }
};

void inpt(){
    cin >> T >> H >> W >> i0;
    for (int i = 0; i < H - 1; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W; ++j) h[i][j] = s[j];
    }
    for (int i = 0; i < H; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W - 1; ++j) v[i][j] = s[j];
    }
    cin >> K;
    for (int i = 0; i < K; ++i) cin >> S[i] >> D[i];
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Space space;
    space.init();

    space.print_ans();

    return 0;
}
