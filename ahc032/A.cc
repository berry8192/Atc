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
    multiset<tuple<int, int, int>> ans;
    int rest_use;
    ll score;

    void init() {
        board = a;
        rest_use = K;
        score = -1;
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
                        ll tmp_score = 0;
                        rep(l, STAMP_SIZE) {
                            rep(m, STAMP_SIZE) {
                                tmp_score +=
                                    (board[i + l][j + m] + s[k][l][m]) % mod;
                            }
                        }
                        if (max_score < tmp_score) {
                            max_score = tmp_score;
                            use = {k, i, j};
                            updated = true;
                        }
                    }
                }
            }
            if (updated) {
                ans.insert(use);
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
                    ans.insert({best_type, i, j});
                    rest_use--;
                    // cerr << board[i][j] << endl;
                }
            }
        }
    }
    void fill_rc(int r_idx, int c_idx, int s_idx) {
        rep(l, STAMP_SIZE) {
            rep(m, STAMP_SIZE) {
                // score -= board[r_idx + l][c_idx + m];
                board[r_idx + l][c_idx + m] =
                    (board[r_idx + l][c_idx + m] + s[s_idx][l][m]) % mod;
                // score += board[r_idx + l][c_idx + m];
            }
        }
        ans.insert({s_idx, r_idx, c_idx});
        rest_use--;
    }

    void calc_score(int r_idx, int c_idx) {
        score = 0;
        if (r_idx != N - 3) {
            rep(i, r_idx + 1) {
                if (i == r_idx && c_idx != N - 3) {
                    rep(j, c_idx + 1) {
                        assert(board[i][j] < mod);
                        score += board[i][j];
                    }
                } else {
                    rep(j, N) {
                        assert(board[i][j] < mod);
                        score += board[i][j];
                    }
                }
            }
        } else {
            rep(i, N) {
                if (i == r_idx && c_idx != N - 3) {
                    rep(j, c_idx + 1) {
                        assert(board[i][j] < mod);
                        score += board[i][j];
                    }
                } else {
                    rep(j, N) {
                        assert(board[i][j] < mod);
                        score += board[i][j];
                    }
                }
            }
        }
    }
    void print_ans() {
        cout << ans.size() << endl;
        for (auto use : ans) {
            cout << get<0>(use) << " " << get<1>(use) << " " << get<2>(use)
                 << endl;
        }
    }

    bool operator<(const Grid &in) const {
        return score != in.score ? score < in.score : rest_use < in.rest_use;
    };
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

int beam_width = 100;
set<Grid> grids0, grids1;

int main() {
    inpt();

    // Grid best;
    // best.init();
    // best.ul();
    // best.maximize();
    // best.print_ans();
    // cerr << best.calc_score() << endl;
    // return 0;

    Grid base;
    base.init();
    base.calc_score(N - 3, N - 3);
    grids0.insert(base);
    rep(i, N + 10) {
        rep(j, N - 2) {
            // cerr << i SP << j << endl;
            if ((i * (N - 2) + j) % 2 == 0) {
                grids1.clear();
                for (auto grid : grids0) {
                    rep(k, M + 1) {
                        Grid tmp = grid;
                        if (k != M) {
                            tmp.fill_rc(min(N - 3, i), j, k);
                        }
                        tmp.calc_score(min(N - 3, i), j);
                        grids1.insert(tmp);
                        if (grids1.size() > beam_width) {
                            auto itr = grids1.begin();
                            grids1.erase(itr);
                        }
                    }
                }
            } else {
                grids0.clear();
                for (auto grid : grids1) {
                    rep(k, M + 1) {
                        Grid tmp = grid;
                        if (k != M) {
                            tmp.fill_rc(min(N - 3, i), j, k);
                        }
                        tmp.calc_score(min(N - 3, i), j);
                        grids0.insert(tmp);
                        if (grids0.size() > beam_width) {
                            auto itr = grids0.begin();
                            grids0.erase(itr);
                        }
                    }
                }
            }
        }
    }
    auto itr = grids1.rbegin();
    Grid best = *itr;
    best.maximize();
    best.print_ans();
    best.calc_score(N - 3, N - 3);
    cerr << best.score << endl;

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
    //         // cout<< "score: " << space.score SP << space.score*25
    //         <<endl;
    //     }
    // }
    // // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
