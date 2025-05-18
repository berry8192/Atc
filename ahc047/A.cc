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
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cerr << pvv[i] << ", ";
    // rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
    cerr << pvv[pvv.size() - 1] << endl;
}

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

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M, L;
vector<string> S;
vector<int> P;

struct Model {
    vector<char> C;
    vector<vector<int>> A;
    Model() {
        C.assign(M, 'a');
        A.assign(M, vector<int>(M, 0));
    }
    void print_ans() {
        for (int i = 0; i < M; i++) {
            cout << C[i];
            for (int j = 0; j < M; j++) {
                cout << " " << A[i][j];
            }
            cout << endl;
        }
    }
    double
    compute_word_probability(const std::vector<char> &word, int L,
                             const std::vector<char> &C,
                             const std::vector<std::vector<int>> &A) const {
        int M = C.size();
        int n = 0;
        std::map<std::pair<int, int>, int> states;
        for (int j = 0; j < M; ++j) {
            states[{0, j}] = n++;
            for (int i = 0; i + 1 < word.size(); ++i) {
                if (word[i] == C[j]) {
                    states[{i + 1, j}] = n++;
                }
            }
        }
        std::vector<double> X(n * n, 0.0);
        for (const auto &kv : states) {
            int len = kv.first.first, u = kv.first.second, j = kv.second;
            for (int v = 0; v < M; ++v) {
                std::vector<char> next(word.begin(), word.begin() + len);
                next.push_back(C[v]);
                int s = 0;
                while (s < next.size() &&
                       std::vector<char>(next.begin() + s, next.end()) !=
                           std::vector<char>(word.begin(),
                                             word.begin() + next.size() - s)) {
                    ++s;
                }
                if (next.size() - s != word.size()) {
                    int i2 = states[{int(next.size() - s), v}];
                    X[i2 * n + j] += A[u][v] / 100.0;
                }
            }
        }
        // 行列累乗
        int power = L - 1;
        std::vector<double> Y(n * n, 0.0);
        for (int i = 0; i < n; ++i)
            Y[i * n + i] = 1.0;
        auto mul = [&](const std::vector<double> &a,
                       const std::vector<double> &b) {
            std::vector<double> c(n * n, 0.0);
            for (int i = 0; i < n; ++i)
                for (int k = 0; k < n; ++k)
                    for (int j = 0; j < n; ++j)
                        c[i * n + j] += a[i * n + k] * b[k * n + j];
            return c;
        };
        std::vector<double> Xpow = X;
        while (power > 0) {
            if (power & 1)
                Y = mul(Y, Xpow);
            Xpow = mul(Xpow, Xpow);
            power >>= 1;
        }
        int init;
        if (C[0] == word[0]) {
            init = states[{1, 0}];
        } else {
            init = states[{0, 0}];
        }
        double ret = 1.0;
        for (int i = 0; i < n; ++i)
            ret -= Y[i * n + init];
        if (ret < 0.0)
            ret = 0.0;
        if (ret > 1.0)
            ret = 1.0;
        return ret;
    }
    // 得点計算
    long long compute_score(const vector<string> &S, const vector<int> &P,
                            int N, int M, int L, string &err) const {
        for (int i = 0; i < M; ++i) {
            int sum = 0;
            for (int j = 0; j < M; ++j)
                sum += A[i][j];
            if (sum != 100) {
                err = "Sum of A[" + to_string(i) + "] is not 100 (" +
                      to_string(sum) + ")";
                return 0;
            }
        }
        double total_score = 0.0;
        for (int i = 0; i < N; ++i) {
            vector<char> word(S[i].begin(), S[i].end());
            double prob = compute_word_probability(word, L, C, A);
            total_score += prob * P[i];
        }
        err = "";
        return static_cast<long long>(round(total_score));
    }
    // 最もPが高いSを100%で生成するモデルに書き換える
    void set_best_string_model(const vector<string> &S, const vector<int> &P) {
        int idx = max_element(P.begin(), P.end()) - P.begin();
        const string &best = S[idx];
        int len = best.size();
        // C: 先頭から順にbestの文字、余りは'a'
        for (int i = 0; i < M; ++i) {
            if (i < len)
                C[i] = best[i];
            else
                C[i] = 'a';
        }
        // A: i→i+1に100%, 最後は自身に100%
        for (int i = 0; i < M; ++i)
            fill(A[i].begin(), A[i].end(), 0);
        for (int i = 0; i < len - 1 && i + 1 < M; ++i) {
            A[i][i + 1] = 100;
        }
        if (len - 1 < M) {
            A[len - 1][len - 1] = 100;
        }
        for (int i = len; i < M; ++i) {
            A[i][i] = 100;
        }
    }
    // 指定したindexの文字列のループ遷移頻度に基づき、a-f状態の遷移確率を最適化
    void set_selected_string_model_freq(const vector<string> &S,
                                        const vector<int> &indices) {
        // 文字ごとの出現頻度をカウント
        vector<int> freq_map(6);
        int sum_c = 0;
        for (int idx : indices) {
            for (char ch : S[idx]) {
                freq_map[int(ch - 'a')]++;
                sum_c++;
            }
        }
        // 頻度でMを分配
        vector<int> freq_size(6);
        C.clear();
        for (int i = 0; i < M - 1; ++i) {
            int fig = min(4.0, round(1.0 * M * freq_map[i] / sum_c));
            freq_size[i] = fig;
            rep(lp, fig) { C.push_back('a' + i); }
        }
        while (C.size() < M) {
            C.push_back('a' + (M - 1));
            freq_size[M - 1]++;
        }

        // string s_cat;
        // vector<int> s_cat_owner; // s_catの各文字がどのindicesのものか
        // for (int k = 0; k < indices.size(); ++k) {
        //     int idx = indices[k];
        //     s_cat += S[idx];
        //     s_cat_owner.insert(s_cat_owner.end(), S[idx].size(), k);
        // }
        // int sz = s_cat.size();

        vector<vector<ll>> freq(M, vector<ll>(M));
        rep(j, indices.size()) {
            string s = S[indices[j]];
            for (int i = 0; i < s.size() - 1; ++i) {
                int c = s[i] - 'a';
                int nc = s[i + 1] - 'a';
                int nnc;
                if (i == s.size() - 2) {
                    nnc = s[i] - 'a';
                } else {
                    nnc = s[i + 2] - 'a';
                }
                // Cのindexに変換
                int cidx = find(C.begin(), C.end(), s[i]) - C.begin();
                int ncidx = find(C.begin(), C.end(), s[i + 1]) - C.begin();
                int nncidx = find(C.begin(), C.end(),
                                  s[(i == s.size() - 2) ? i : i + 2]) -
                             C.begin();
                if (ncidx >= 3) {
                    cidx += M / 2;
                }
                if (nncidx >= 3) {
                    ncidx += M / 2;
                }
                if (cidx >= M || ncidx >= M)
                    continue;
                freq[cidx][ncidx] += (P[indices[j]]) * 10000;
            }
        }
        // 遷移確率を100%に正規化
        for (int i = 0; i < M; ++i) {
            ll sum1 = 1;
            ll sum1o = 0;
            rep(j, M) { sum1 += freq[i][j]; }
            rep(j, M - 1) {
                A[i][j] = 100 * freq[i][j] / sum1;
                sum1o += A[i][j];
            }
            A[i][M - 1] = 100 - sum1o;
        }
    }
};

void inpt() {
    cin >> N >> M >> L;
    S.resize(N);
    P.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> P[i];
    }
}

int main() {
    inpt();
    Model model, best_model;
    best_model.set_best_string_model(S, P);
    vector<int> indices, best_indices;
    string err;
    long long best_score = -1;
    // Pが高い順のindexリストを作成
    vector<pair<int, int>> pidx;
    rep(i, N) pidx.emplace_back(P[i], i);
    sort(pidx.rbegin(), pidx.rend());
    vector<int> sorted_idx;
    for (auto &pi : pidx)
        sorted_idx.push_back(pi.second);

    // 2個から10個まで全探索＋1個だけ/2個だけ間を抜かすパターン
    for (int select_size = 2; select_size <= 2; ++select_size) {
        if (N < select_size)
            break;
        // 連続パターン (1,2,...,select_size)
        indices.clear();
        for (int i = 0; i < select_size; ++i)
            indices.push_back(sorted_idx[i]);
        model.set_selected_string_model_freq(S, indices);
        long long score = model.compute_score(S, P, N, M, L, err);
        if (score > best_score) {
            best_score = score;
            best_indices = indices;
            best_model = model;
            // PV(indices);
            // cerr << "best_score: " << best_score << endl;
        }
        break;
        // 1個だけ間を抜かすパターン
        for (int skip = 0; skip < select_size; ++skip) {
            if (select_size >= N)
                break;
            indices.clear();
            for (int i = 0; i < select_size + 1; ++i) {
                if (i == skip)
                    continue;
                indices.push_back(sorted_idx[i]);
            }
            model.set_selected_string_model_freq(S, indices);
            long long score2 = model.compute_score(S, P, N, M, L, err);
            if (score2 > best_score) {
                best_score = score2;
                best_indices = indices;
                best_model = model;
            }
        }
        // 2個だけ間を抜かすパターン
        if (select_size + 2 <= N) {
            for (int skip1 = 0; skip1 < select_size + 1; ++skip1) {
                for (int skip2 = skip1 + 1; skip2 < select_size + 2; ++skip2) {
                    indices.clear();
                    for (int i = 0; i < select_size + 2; ++i) {
                        if (i == skip1 || i == skip2)
                            continue;
                        indices.push_back(sorted_idx[i]);
                    }
                    model.set_selected_string_model_freq(S, indices);
                    long long score3 = model.compute_score(S, P, N, M, L, err);
                    if (score3 > best_score) {
                        best_score = score3;
                        best_indices = indices;
                        best_model = model;
                    }
                }
            }
        }
    }
    cerr << "Best score: " << best_score << endl;
    best_model.print_ans();
    return 0;
}
