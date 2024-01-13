#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long
#define T_LENGTH 5

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

int find_common_string(const string &s1, const string &s2) {
    for (int k = T_LENGTH - 1; k >= 1; k--) {
        // s1の後ろk文字とs2の先頭k文字が一致するかどうか
        if (s1.substr(T_LENGTH - k) == s2.substr(0, k)) {
            return k;
        }
    }
    return 0;
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
    int manhattan(Pos a) {
        // cout<< "manhattan" <<endl;
        return (abs(a.h - h) + abs(a.w - w));
    }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    void ans_print() { cout << h << " " << w << endl; }

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
    vector<int> t_permutation;
    vector<Pos> ans;
    int score;

    void init() {
        t_permutation.resize(m);
        score = -1;
    }

    void set_random_t_permutation() {
        rep(i, m) { t_permutation[i] = i; }
        shuffle(all(t_permutation), mt);
    }

    void t_permutation_to_output() {
        // ansを初期化する
        ans.clear();

        Pos current_pos = s;
        string obj_string;
        char next_char;
        int next_char_index;
        int min_dist;
        int dist;
        Pos next_pos;
        int cost = 0;

        rep(i, m) {
            // 次の文字列
            obj_string = t[t_permutation[i]];
            // 前の文字列と共通部分があればそこは作らない
            int skip_index = 0;
            if (i != 0) {
                skip_index =
                    find_common_string(t[t_permutation[i - 1]], obj_string);
            }
            rep3(j, T_LENGTH, skip_index) {
                // 次の文字
                next_char = obj_string[j];
                next_char_index = int(next_char - 'A');
                // 最も近い次の文字の座標を探す
                min_dist = 100000;
                rep(k, alphabet_pos[next_char_index].size()) {
                    // マンハッタン距離で判定
                    dist =
                        current_pos.manhattan(alphabet_pos[next_char_index][k]);
                    if (dist < min_dist) {
                        min_dist = dist;
                        next_pos = alphabet_pos[next_char_index][k];
                    }
                }
                // 文字が決まったらansに格納
                current_pos = next_pos;
                ans.push_back(current_pos);
                cost += min_dist + 1;
            }
        }
        score = max(1001, 10000 - cost);
    }
    void random_swap_permutation() {
        int u = mt() % m;
        int v = (u + mt() % (m - 1)) % m;
        swap(t_permutation[u], t_permutation[v]);
    }
    void random_move_permutation() {
        int u = mt() % m;
        int v = (u + mt() % (m - 1)) % m;
        if (v < u) {
            t_permutation.insert(t_permutation.begin() + v, t_permutation[u]);
            t_permutation.erase(t_permutation.begin() + u + 1);
        } else {
            t_permutation.insert(t_permutation.begin() + v + 1,
                                 t_permutation[u]);
            t_permutation.erase(t_permutation.begin() + u);
        }
    }

    void print_t_permutation() {
        rep(i, m) { cout << t_permutation[i] SP; }
        cout << endl;
    }
    void print_ans() {
        rep(i, ans.size()) { ans[i].ans_print(); }
    }
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

// 2文字以上の今日共通部分を持つものがあるのか
void find_common() {
    rep(i, m) {
        rep(j, m) {
            if (i == j)
                continue;
            for (int k = T_LENGTH - 1; k >= 2; k--) {
                // t[i]の後ろk文字とt[j]の先頭k文字が一致するかどうか
                if (t[i].substr(T_LENGTH - k) == t[j].substr(0, k)) {
                    cout << k SP << t[i] SP << t[j] << endl;
                }
            }
        }
    }
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
    // rep(i, 26) {
    //     rep(j, alphabet_pos[i].size()) { alphabet_pos[i][j].print(); }
    // }
}

int main() {
    // 開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    // find_common();
    make_alphabet_pos();

    Board best;
    best.init();
    best.set_random_t_permutation();
    // best.print_t_permutation();
    best.t_permutation_to_output();
    // best.print_ans();

    int lp = 0;
    while (true) {
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta = chrono::duration_cast<chrono::milliseconds>(current - start)
                    .count();
        if (delta > TIME_LIMIT)
            break;

        Board board = best;
        board.random_move_permutation();
        board.t_permutation_to_output();
        if (best.score < board.score) {
            // cout << lp SP << board.score << endl;
            best = board;
        }
    }
    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}