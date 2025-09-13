#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// int型vectorを出力
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] SP;
    cout << pvv[pvv.size() - 1] << endl;
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

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M;
long long L, U;

struct Game {
    vector<long long> A;
    vector<long long> B;
    vector<int> X;

    void prepare_cards() {
        // 最初の50個の値を配列で定義 (線形補間)
        // A[0] = 9.98×10^14, A[10] = 9.982×10^14, A[20] = 9.988×10^14,
        // A[30] = 9.996×10^14, A[40] = 1.0005×10^15, A[49] = 1.0015×10^15
        vector<long long> first_50 = {
            998000000000000,  998071428571429,  998142857142858,
            998214285714287,  998285714285716,  998357142857145,
            998428571428574,  998500000000003,  998571428571432,
            998642857142861,  998714285714290,  998785714285719,
            998857142857148,  998928571428577,  999000000000006,
            999071428571435,  999142857142864,  999214285714293,
            999285714285722,  999357142857151,  999428571428580,
            999500000000009,  999571428571438,  999642857142867,
            999714285714296,  999785714285725,  999857142857154,
            999928571428583,  1000000000000012, 1000071428571441,
            1000142857142870, 1000214285714299, 1000285714285728,
            1000357142857157, 1000428571428586, 1000500000000015,
            1000571428571444, 1000642857142873, 1000714285714302,
            1000785714285731, 1000857142857160, 1000928571428589,
            1001000000000018, 1001071428571447, 1001142857142876,
            1001214285714305, 1001285714285734, 1001357142857163,
            1001428571428592, 1001500000000021};

        for (int i = 0; i < 50; i++) {
            A.push_back(first_50[i]);
        }

        // 残りの450個をMIN_VAL~MAX_VALで均等に割り振り
        const long long MIN_VAL = 100000000LL;
        const long long MAX_VAL = 100000000000LL;

        // 線形補間バージョン
        // repr(i, 450) {
        //     long long value = MIN_VAL + (MAX_VAL - MIN_VAL) * i / 449;
        //     A.push_back(value);
        // }

        // 指数補間バージョン（コメントアウト）

        double min_exp = log10(MIN_VAL);
        double max_exp = log10(MAX_VAL);

        repr(i, 450) {
            // 指数をmin_expからmax_expまで連続的に変化させる
            double exponent = min_exp + (max_exp - min_exp) * i / 449.0;
            long long value = (long long)pow(10.0, exponent);
            A.push_back(value);
        }
    }

    void output_cards() {
        for (int i = 0; i < N; i++) {
            cout << A[i];
            if (i < N - 1)
                cout << " ";
            cout << endl;
        }
        cout << endl;
    }

    void read_targets() {
        B.resize(M);
        for (int i = 0; i < M; i++) {
            cin >> B[i];
        }
    }

    long long calculate_score() {
        vector<long long> pile_sum(M, 0);

        // 各山の合計を計算
        for (int i = 0; i < N; i++) {
            if (X[i] > 0) {
                pile_sum[X[i] - 1] += A[i];
            }
        }

        // 誤差Eを計算
        long long E = 0;
        long long min_error = LLONG_MAX;
        long long max_error = 0;

        for (int j = 0; j < M; j++) {
            long long error = abs(pile_sum[j] - B[j]);
            E += error;
            min_error = min(min_error, error);
            max_error = max(max_error, error);
        }

        // // 誤差情報を出力
        // cerr << "Error sum: " << E << ", Min error: " << min_error
        //      << ", Max error: " << max_error << endl;

        // 得点を計算: round((20-log10(1+E))*5*10^7)
        double score_d = (20.0 - log10(1.0 + E)) * 5.0 * 1e7;
        return (long long)round(score_d);
    }

    void solve() {
        X.resize(N, 0);

        // 初期解を貪欲法で作成
        vector<long long> pile_sum(M + 1, 0);
        vector<pair<long long, int>> cards;
        for (int i = 0; i < N; i++) {
            cards.push_back({A[i], i});
        }
        sort(cards.rbegin(), cards.rend());

        // 初期配置
        // 先頭50個はそのままBに順序で割り当て
        for (int i = 0; i < min(50, M); i++) {
            X[i] = i + 1;
            pile_sum[i + 1] += A[i];
        }

        // 残りのカードは貪欲法で配置
        for (auto &card : cards) {
            long long value = card.first;
            int idx = card.second;

            // 先頭50個は既に配置済みなのでスキップ
            if (idx < 50)
                continue;

            int best_pile = 0;
            long long min_error = LLONG_MAX;

            for (int pile = 1; pile <= M; pile++) {
                long long new_sum = pile_sum[pile] + value;
                long long error = abs(new_sum - B[pile - 1]);
                long long current_error = abs(pile_sum[pile] - B[pile - 1]);

                if (error < current_error && error < min_error) {
                    min_error = error;
                    best_pile = pile;
                }
            }

            if (best_pile > 0) {
                X[idx] = best_pile;
                pile_sum[best_pile] += value;
            }
        }

        // 現在の解を保存
        vector<int> best_X = X;
        long long best_score = calculate_score();

        // 焼きなまし法
        while (timer.progress() < 1.0) {
            double progress = timer.progress();
            double temp = start_temp * pow(end_temp / start_temp, progress);

            vector<int> old_X = X;

            // ランダムな山を選択して、その山のカードを全て0の山（捨て札）に戻す
            int target_pile = (mt() % M) + 1;
            vector<int> removed_cards;

            for (int i = 0; i < N; i++) {
                if (X[i] == target_pile) {
                    removed_cards.push_back(i);
                    X[i] = 0; // 0の山に戻す
                }
            }

            // 0の山のカードだけを使って元の山を最善に再構築
            vector<long long> pile_sum(M + 1, 0);

            // 現在の各山の合計を計算
            for (int i = 0; i < N; i++) {
                if (X[i] > 0) {
                    pile_sum[X[i]] += A[i];
                }
            }

            // 0の山にあるカードを価値順にソート
            vector<pair<long long, int>> available_cards;
            for (int i = 0; i < N; i++) {
                if (X[i] == 0) {
                    available_cards.push_back({A[i], i});
                }
            }
            sort(available_cards.rbegin(), available_cards.rend());

            // 貪欲法で再配置
            for (auto &card : available_cards) {
                long long value = card.first;
                int idx = card.second;

                int best_pile = 0;
                long long min_error = LLONG_MAX;

                for (int pile = 1; pile <= M; pile++) {
                    long long new_sum = pile_sum[pile] + value;
                    long long error = abs(new_sum - B[pile - 1]);
                    long long current_error = abs(pile_sum[pile] - B[pile - 1]);

                    if (error < current_error && error < min_error) {
                        min_error = error;
                        best_pile = pile;
                    }
                }

                if (best_pile > 0) {
                    X[idx] = best_pile;
                    pile_sum[best_pile] += value;
                }
            }

            // 新しい解の評価
            long long new_score = calculate_score();

            // 受容判定
            bool accept = false;
            if (new_score > best_score) {
                accept = true;
                best_score = new_score;
                best_X = X;
                // 予想得点を出力
                cerr << "Expected score: " << best_score << endl;
            } else {
                double delta = new_score - best_score;
                double prob = exp(delta / temp);
                if ((double)mt() / mt.max() < prob) {
                    accept = true;
                }
            }

            if (!accept) {
                X = old_X; // 元に戻す
            }
        }

        // 最良解を復元
        X = best_X;
    }

    void output_assignment() {
        for (int i = 0; i < N; i++) {
            cout << X[i];
            if (i < N - 1)
                cout << " ";
        }
        cout << endl;
    }
};

void inpt() { cin >> N >> M >> L >> U; }

int main() {
    start = chrono::system_clock::now();

    inpt();

    Game game;
    game.prepare_cards();
    game.output_cards();
    game.read_targets();
    game.solve();
    game.output_assignment();

    return 0;
}
