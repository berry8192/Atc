#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

// 定数周り
int imax = 2147483647;
ll lmax = 9223372036854775807;

// 焼きなましの定数
double TIME_LIMIT = 1900;
double start_temp = 50.0;
double end_temp = 10.0;

// 乱数の準備
int seed = 10000;
mt19937 mt(seed);

// 入力など
constexpr int n = 50;
int si, sj;
vector<vector<int>> t(n, vector<int>(n));
vector<vector<int>> p(n, vector<int>(n));

int ansi;
vector<int> ans1, ans2;
ll sco1 = 0, sco2 = 0;

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

struct Pos {
    int h;
    int w;

    Pos(){};
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
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * n + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
};
vector<Pos> d4 = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
string move_alphabet = "RULD";

char calc_dir(Pos from, Pos to) {
    rep(i, 4) {
        if (from + d4[i] == to)
            return move_alphabet[i];
    }
    // 一致しない場合
    assert(0);
}

Pos prev_pos(Pos pos, char c) {
    int idx = -1;
    rep(i, 4) {
        if (c == move_alphabet[i]) {
            idx = i;
            break;
        }
    }
    // 一致しない場合
    assert(idx != -1);
    idx = (idx + 2) % 4;
    return pos + d4[idx];
}

void gutyoku(string &ans, int &got_score) {
    set<int> st;
    vector<set<int>> used(n * n);
    int turn = 0;
    string max_ans;

    Pos cpos = {si, sj};
    st.insert(t[cpos.h][cpos.w]);
    got_score += p[cpos.h][cpos.w];
    while (1) {
        vector<Pos> poses = cpos.around_pos(d4);

        int max_score = -1;
        int max_index;
        rep(i, poses.size()) {
            int score = p[poses[i].h][poses[i].w];
            // 同じ状況で同じ選択肢を選ばないようにする
            if (used[turn].find(i) != used[turn].end())
                continue;
            // 乱択のため、候補が1つ以上あるときは一定の確率で回答を捨てる
            if (max_score != -1 && mt() % 2 == 0)
                continue;

            // 下方向に行きたくない
            // if (max_score != -1 && calc_dir(cpos, poses[i]) == 'D' &&
            //     mt() % 2 == 0)
            //     continue;

            // 訪れたタイルか
            if (st.find(t[poses[i].h][poses[i].w]) != st.end())
                continue;
            max_score = score;
            max_index = i;
            // 上方向に優先的に遷移
            if (calc_dir(cpos, poses[i]) == 'U')
                break;
        }
        if (max_score == -1) {
            // cout << "score-1" << endl;
            // break;

            // 詰んだら切り戻す
            if (ans.size() == 0) {
                ans = max_ans;
                return;
            }
            st.erase(t[cpos.h][cpos.w]);
            cpos = prev_pos(cpos, ans[ans.size() - 1]);
            ans.pop_back();
            used[turn + 1].clear();
            turn--;
            if (ans.size() + 50 < max_ans.size()) {
                ans = max_ans;
                return;
            }
            continue;
        }
        used[turn].insert(max_index);
        got_score += max_score;
        ans += calc_dir(cpos, poses[max_index]);
        cpos = poses[max_index];
        st.insert(t[poses[max_index].h][poses[max_index].w]);
        turn++;
        if (max_ans.size() < ans.size())
            max_ans = ans;
        // cout << ans << endl;
    }
    // cout << ans << endl;
    // cerr << "score: " << got_score << endl;
}

// スコアの計算
ll calc_score(int idx) {
    ll rtn = 0;
    if (idx == 1) {

    } else {
    }
    return rtn;
}

void inpt() {
    cin >> si >> sj;
    rep(i, n) {
        rep(j, n) { cin >> t[i][j]; }
    }
    rep(i, n) {
        rep(j, n) { cin >> p[i][j]; }
    }
}

int main() {

    // 入力
    inpt();
    string best_ans;
    int best_score = 0;

    int loop = 0;
    while (1) {
        if (timer.progress() > 1.0)
            break;
        loop++;

        string ans;
        int score = 0;
        gutyoku(ans, score);
        score = ans.size();
        if (best_score < score) {
            best_ans = ans;
            best_score = score;
            // cout << best_ans << endl;
            // cout << best_score << endl;
        }
    }

    cout << best_ans << endl;
    // cout << best_score << endl;

    return 0;
}