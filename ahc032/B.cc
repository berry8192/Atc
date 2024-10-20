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

int calc_idx(int t, int h, int w) { return t * 100 + h * 10 + w; }
void calc_ans(int &t, int &h, int &w, int idx) {
    w = idx % 10;
    idx /= 10;
    h = idx % 10;
    idx /= 10;
    t = idx;
}

struct Grid {
    vector<vector<int>> board;
    int ans[2010];
    int rest_use;

    void init() {
        board = a;
        rest_use = K;
        rep(i, 2010) { ans[i] = 0; }
    }

    void maximize() {
        bool updated;
        tuple<int, int, int> use;
        while (rest_use) {
            updated = false;
            rep(i, N - 2) {
                rep(j, N - 2) {
                    ll max_score = 0;
                    rep(l, STAMP_SIZE) {
                        rep(m, STAMP_SIZE) { max_score += board[i + l][j + m]; }
                    }
                    rep(k, M) {
                        ll score = 0;
                        rep(l, STAMP_SIZE) {
                            rep(m, STAMP_SIZE) {
                                score +=
                                    (board[i + l][j + m] + s[k][l][m]) % mod;
                            }
                        }
                        if (max_score < score) {
                            max_score = score;
                            use = {k, i, j};
                            updated = true;
                        }
                    }
                }
            }
            if (updated) {
                ans[calc_idx(get<0>(use), get<1>(use), get<2>(use))]++;
                auto [t, h, w] = use;
                rep(i, STAMP_SIZE) {
                    rep(j, STAMP_SIZE) {
                        board[i + h][j + w] =
                            (board[i + h][j + w] + s[t][i][j]) % mod;
                    }
                }
                rest_use--;
            } else {
                break;
            }
        }
    }
    void ul() {
        rep(i, N - 2) {
            rep(j, N - 2) {
                int best_score = board[i][j];
                int best_type = -1;
                rep(k, M) {
                    int score = (board[i][j] + s[k][0][0]) % mod;
                    if (best_score < score) {
                        best_score = score;
                        best_type = k;
                    }
                }
                if (best_type != -1) {
                    rep(l, STAMP_SIZE) {
                        rep(m, STAMP_SIZE) {
                            board[i + l][j + m] =
                                (board[i + l][j + m] + s[best_type][l][m]) %
                                mod;
                        }
                    }
                    ans[calc_idx(best_type, i, j)]++;
                    rest_use--;
                    // cerr << board[i][j] << endl;
                }
            }
        }
    }

    ll calc_score() {
        ll score = 0;
        rep(i, N) {
            rep(j, N) {
                assert(board[i][j] < mod);
                score += board[i][j];
            }
        }
        return score;
    }
    void print_ans() {
        cout << K - rest_use << endl;
        rep(i, 2010) {
            if (ans[i]) {
                int t, h, w;
                calc_ans(t, h, w, i);
                rep(j, ans[i]) { cout << t SP << h SP << w << endl; }
            }
        }
    }
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
    best.ul();
    best.maximize();
    best.print_ans();
    cerr << best.calc_score() << endl;
    return 0;

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
