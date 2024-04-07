#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

#define STAMP_SIZE 3

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
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

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}
template <typename T> T rand(T a, T b) {
    assert(a <= b);
    ll len = (b - a + 1);
    return randxor() % len + a;
}

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

int N, M, K;
ll mod = 998244353;
vector<vector<int>> a;
vector<vector<vector<int>>> s;

struct Grid {
    vector<vector<int>> board;

    void init() { board = a; }
};

void inpt() {
    cin >> N >> M >> K;
    a.resize(N, vector<int>(N));
    s.resize(M, vector<vector<int>>(STAMP_SIZE, vector<int>(STAMP_SIZE)));
    rep(i, N) {
        rep(j, N) { cin >> a[i][j]; }
    }
    rep(i, M) {
        rep(j, STAMP_SIZE) {
            rep(k, STAMP_SIZE) { cin >> s[i][j][k]; }
        }
    }
}

int main() {
    inpt();

    Grid best;
    best.init();

    // int loop = 0;
    // while (1) {
    //     current = chrono::system_clock::now();
    //     if (chrono::duration_cast<chrono::milliseconds>(current - start)
    //             .count() > TIME_LIMIT) {
    //         // break;
    //     }
    //     loop++;

    //     Grid grid;

    //     if (best.score < grid.score) {
    //         best = grid;
    //         // cout<< "loop: " << loop <<endl;
    //         // best.print_ans();
    //         // cout<< "score: " << space.score SP << space.score*25 <<endl;
    //     }
    // }
    // // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
