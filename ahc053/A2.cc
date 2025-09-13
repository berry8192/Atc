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

void inpt() { cin >> N >> M >> L >> U; }

int main() {
    inpt(); // 最初に N, M, L, U を読み込む

    rep(i, N) { cout << 1 + i SP; }
    cout << endl;

    vector<ll> B(M);
    rep(i, M) { cin >> B[i]; }

    // ll EXPECT_MIN_B = 998000000000000LL;
    // ll EXPECT_MAX_B = 1002000000000000LL;
    // ll delta_b = EXPECT_MAX_B - EXPECT_MIN_B;
    // rep(i, M) { assert(B[i] <= EXPECT_MIN_B + delta_b * (i + 1) / 50); }
    PV(B);

    return 0;
}
