#include <bits/stdc++.h>

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
int seed = 1;
mt19937 mt(seed);

int N, M;
long long L, U;

struct Game {
    vector<long long> A;
    vector<long long> B;
    vector<int> X;

    void prepare_cards() {
        A.resize(N);

        // 998000000000000から1002000000000000まで均等に50個のカードに分布
        long long min_val = 998000000000000LL;
        long long max_val = 1002000000000000LL;

        for (int i = 0; i < 50; i++) {
            A[i] = min_val + (max_val - min_val) * i / 49;
        }

        // 残りのカードは1にしておく（使わない）
        for (int i = 50; i < N; i++) {
            A[i] = 1;
        }
    }

    void output_cards() {
        for (int i = 0; i < N; i++) {
            cout << A[i];
            if (i < N - 1)
                cout << " ";
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

        // 誤差情報を出力
        cerr << "Error sum: " << E << ", Min error: " << min_error
             << ", Max error: " << max_error << endl;

        // 得点を計算: round((20-log10(1+E))*5*10^7)
        double score_d = (20.0 - log10(1.0 + E)) * 5.0 * 1e7;
        return (long long)round(score_d);
    }

    void solve() {
        X.resize(N, 0);

        // 初期配置: 1~50のカードを1~Mの山に配る
        for (int i = 0; i < 50; i++) {
            X[i] = (i % M) + 1;
        }
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