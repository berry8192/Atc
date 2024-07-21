#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

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
double TIME_LIMIT = 1000.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000.0;
double end_temp = 100.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M, T;
int HEIGHT, WIDTH;

// 構造体
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

struct Seed {
    vector<int> value;

    Seed() {}
    Seed(vector<int> &v) { value = v; }

    void inpt(int sz) {
        value.resize(sz);
        rep(i, sz) cin >> value[i];
    }
    int sum_value() {
        int rtn = 0;
        rep(i, value.size()) rtn += value[i];
        return rtn;
    }
    int sum_double_value() {
        int rtn = 0;
        rep(i, value.size()) rtn += value[i] * value[i];
        return rtn;
    }
};

Seed base_seed;

struct Prod {
    vector<Seed> seeds;
    vector<vector<int>> seed_yotei;

    Prod() {}

    void get_input() {
        seed_yotei.resize(N, vector<int>(N));
        seeds.resize(2 * N * (N - 1));
        rep(i, 2 * N * (N - 1)) {
            seeds[i].inpt(M);
            // rep(j, M) {
            //     base_seed.value[j] = max(base_seed.value[j],
            //     seeds[i].value[j]);
            // }
        }
    }
    void random_output() {
        rep(i, N) {
            rep(j, N) { cout << i * N + j SP; }
            cout << endl;
        }
    }
    void greedy_yotei(int turn) {
        vector<vector<int>> max_seed_index(M);
        vector<int> max_sum_seed_index;
        vector<bool> used_seed(2 * N * (N - 1), false);
        rep(lp, 2) {
            rep(i, M) {
                int max_value = -1;
                int max_value_idx = -1;
                rep(j, 2 * N * (N - 1)) {
                    if (used_seed[j]) {
                        continue;
                    }
                    if (max_value < seeds[j].value[i]) {
                        max_value = seeds[j].value[i];
                        max_value_idx = j;
                    }
                }
                max_seed_index[i].emplace_back(max_value_idx);
                used_seed[max_value_idx] = true;
            }
        }
        rep(i, N * N - 2 * M) {
            int max_value = -1;
            int max_value_idx = -1;

            rep(j, 2 * N * (N - 1)) {
                if (used_seed[j]) {
                    continue;
                }
                if (max_value < seeds[j].sum_double_value()) {
                    max_value = seeds[j].sum_double_value();
                    max_value_idx = j;
                }
            }
            max_sum_seed_index.emplace_back(max_value_idx);
            used_seed[max_value_idx] = true;
        }
        int SEPALATE = 2;
        rep(i, SEPALATE) {
            rep(j, N) {
                int index = i * N + j;
                // cout
                //     << max_seed_index[(index / 2 + turn * 2) % M][index % 2]
                //     SP;
                seed_yotei[i][j] =
                    max_seed_index[(index / 2 + turn * 2) % M][index % 2];
            }
            // cout << endl;
        }
        rep(i, N) {
            // cout << max_sum_seed_index[i] SP;
            seed_yotei[SEPALATE][i] = max_sum_seed_index[i];
        }
        // cout << endl;
        rep3(i, N - 1, SEPALATE) {
            rep(j, N) {
                int index = i * N + j;
                // cout
                // << max_seed_index[(index / 2 + turn * 2) % M][index % 2] SP;
                seed_yotei[i + 1][j] =
                    max_seed_index[(index / 2 + turn * 2) % M][index % 2];
            }
            // cout << endl;
        }
    }
    int calc_max_params_sum() {
        vector<int> max_params(M), max_params2(M);
        int max_params_sum = 0;
        rep(i, N) {
            rep(j, N - 1) {
                rep(k, M) {
                    int tmp = seeds[seed_yotei[i][j]].value[k] +
                              seeds[seed_yotei[i][j + 1]].value[k];
                    if (max_params[k] < tmp) {
                        max_params2[k] = max_params[k];
                        max_params[k] = tmp;
                    } else if (max_params2[k] < tmp) {
                        max_params2[k] = tmp;
                    }
                }
            }
        }
        rep(i, N - 1) {
            rep(j, N) {
                rep(k, M) {
                    int tmp = seeds[seed_yotei[i][j]].value[k] +
                              seeds[seed_yotei[i + 1][j]].value[k];
                    if (max_params[k] < tmp) {
                        max_params2[k] = max_params[k];
                        max_params[k] = tmp;
                    } else if (max_params2[k] < tmp) {
                        max_params2[k] = tmp;
                    }
                }
            }
        }
        rep(i, M) { max_params_sum += max_params[i] + max_params2[i]; }
        // cerr << max_params_sum SP;
        return max_params_sum;
    }
    int calc_center_score() {
        int rtn = 0;
        rep3(i, 5, 1) {
            rep3(j, 4, 2) { rtn += seeds[seed_yotei[i][j]].sum_double_value(); }
        }
        // cerr << rtn SP;
        return rtn;
    }
    int calc_center_max_params_sum() {
        vector<int> max_params(M);
        int max_params_sum = 0;
        rep3(i, 5, 1) {
            rep3(j, 4, 1) {
                rep(k, M) {
                    int tmp = seeds[seed_yotei[i][j]].value[k] *
                              seeds[seed_yotei[i][j + 1]].value[k];
                    max_params[k] = max(max_params[k], tmp);
                }
            }
        }
        rep3(i, 5, 0) {
            rep3(j, 4, 2) {
                rep(k, M) {
                    int tmp = seeds[seed_yotei[i][j]].value[k] *
                              seeds[seed_yotei[i + 1][j]].value[k];
                    max_params[k] = max(max_params[k], tmp);
                }
            }
        }
        rep(i, M) { max_params_sum += max_params[i]; }
        // cerr << max_params_sum SP;
        return max_params_sum;
    }
    int calc_center_max_params_increase_sum() {
        vector<int> max_params(M);
        int max_params_sum = 0;
        rep3(i, 5, 1) {
            rep3(j, 2, 1) {
                rep(k, M) {
                    int tmp = max(0, seeds[seed_yotei[i][j]].value[k] -
                                         seeds[seed_yotei[i][j + 1]].value[k]);
                    max_params[k] = max(max_params[k], tmp * tmp);
                }
            }
            rep3(j, 4, 3) {
                rep(k, M) {
                    int tmp = max(0, seeds[seed_yotei[i][j + 1]].value[k] -
                                         seeds[seed_yotei[i][j]].value[k]);
                    max_params[k] = max(max_params[k], tmp * tmp);
                }
            }
        }
        rep3(i, 1, 0) {
            rep3(j, 4, 2) {
                rep(k, M) {
                    int tmp = max(0, seeds[seed_yotei[i][j]].value[k] -
                                         seeds[seed_yotei[i + 1][j]].value[k]);
                    max_params[k] = max(max_params[k], tmp * tmp);
                }
            }
        }
        rep3(i, 5, 4) {
            rep3(j, 4, 2) {
                rep(k, M) {
                    int tmp = max(0, seeds[seed_yotei[i + 1][j]].value[k] -
                                         seeds[seed_yotei[i][j]].value[k]);
                    max_params[k] = max(max_params[k], tmp * tmp);
                }
            }
        }
        rep(i, M) { max_params_sum += max_params[i]; }
        // cerr << max_params_sum << endl;
        return max_params_sum;
    }
    int calc_score_yotei() {
        vector<int> c4(4);
        c4[0] = calc_max_params_sum() * 75;
        c4[1] = calc_center_score() * 2;
        c4[2] = calc_center_max_params_sum() * 5;
        c4[3] = calc_center_max_params_increase_sum() * 6;
        // cerr << c4[0] << " " << c4[1] << " " << c4[2] << " " << c4[3] <<
        // endl;
        return c4[0] + c4[1] + c4[2] + c4[3];
    }

    void annearing_yotei(int turn) {
        int best_score = calc_score_yotei();
        int loop = 0;
        while (timer.progress() < 0.1 * (turn + 1)) {
            loop++;
            int index1 = mt() % (N * N);
            int index2 = (index1 + mt() % (N * N - 1)) % (N * N);
            swap(seed_yotei[index1 / N][index1 % N],
                 seed_yotei[index2 / N][index2 % N]);
            int score = calc_score_yotei();

            // 温度関数
            double temp = start_temp +
                          (end_temp - start_temp) * timer.progress() -
                          0.1 * turn;
            double prob = exp((score - best_score) / temp);

            if (prob > (mt() % imax) / (double)imax) {
                // cerr << score << endl;
                best_score = score;
            } else {
                swap(seed_yotei[index1 / N][index1 % N],
                     seed_yotei[index2 / N][index2 % N]);
            }
        }
        // cerr << loop << endl;
    }

    void output_yotei() {
        rep(i, N) {
            rep(j, N) { cout << seed_yotei[i][j] SP; }
            cout << endl;
        }
    }
};
void inpt() { cin >> N >> M >> T; }

int main() {
    start = chrono::system_clock::now();

    inpt();

    vector<Prod> prods(T + 1);
    rep(i, T) {
        // cerr << i << endl;
        prods[i].get_input();
        prods[i].greedy_yotei(i);
        prods[i].annearing_yotei(i);
        prods[i].output_yotei();
    }
    prods[T].get_input();

    return 0;
}
