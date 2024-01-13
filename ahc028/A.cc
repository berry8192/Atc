#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

int imax = 2147483647;
ll llimax = 9223372036854775807;

double TIME_LIMIT = 1950.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

template <class T> void PVV(T pvv) {
    rep(i, pvv.size()) {
        rep(j, pvv[i].size()) { cout << pvv[i][j] SP; }
        cout << endl;
    }
}

struct Pos;

int n, m;
vector<string> a;
vector<string> t;

struct Pos {
    int h, w;

    Pos() {}
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < n && 0 <= w && w < n);
    }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }

    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
};
Pos dir4[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 下右上左

Pos s;
vector<vector<Pos>> alphabet_pos(26);

struct Board {

    void init() {
        // cout<< "init" <<endl;
    }

    int calc_score() {}
    void print_ans() {}
};

void inpt() {
    cin >> n >> m;
    int sh, sw;
    cin >> sh >> sw;
    s = {sh, sw};
    a.resize(n);
    t.resize(m);
    rep(i, n) cin >> a[i];
    rep(i, m) cin >> t[i];
}

// A-Zのアルファベットの場所をalphabet_posに格納する
void make_alphabet_pos() {
    rep(i, n) {
        rep(j, n) {
            int tmp = int(a[i][j] - 'A');
            Pos pos = {i, j};
            alphabet_pos[tmp].push_back(pos);
        }
    }
    rep(i, 26) {
        rep(j, alphabet_pos[i].size()) { alphabet_pos[i][j].print(); }
    }
}

int main() {
    // 開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    make_alphabet_pos();
    return 0;

    Board best;

    int lp = 0;
    while (true) {
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta = chrono::duration_cast<chrono::milliseconds>(current - start)
                    .count();
        if (delta > TIME_LIMIT)
            break;

        Board board;
        board.init();
    }
    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}