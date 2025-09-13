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
        A.resize(N);
        int idx = 0;

        // 50個の9.8*10^12
        long long base_value = 980000000000000LL;
        for (int i = 0; i < 50; i++) {
            A[idx++] = base_value;
        }

        // 4*10^12を512で割った値を1,2,4,8,16,32,64,128,256倍したものをそれぞれ50個
        long long unit = 4000000000000LL / 512;
        for (int mult = 1; mult <= 256; mult *= 2) {
            for (int i = 0; i < 50; i++) {
                A[idx++] = unit * mult;
            }
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

    void solve() {
        X.resize(N);
        // 簡単な貪欲解法: 各カードを最も近い目標値の山に割り当て
        for (int i = 0; i < N; i++) {
            X[i] = 0; // とりあえず捨てる
        }

        // より良い割り当てを実装可能
        // 今は簡単のため全て捨てる
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
