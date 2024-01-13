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
struct Node;
struct Pyra;

int n = 30;
vector<Node> b(500);
int rot;

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
Pos pos6[6] = {{1, 0}, {1, 1}, {0, -1}, {0, 1}, {-1, -1}, {-1, 0}};

struct Node {
    int num;
    Pos pos;
    int want_down = 0;

    Node() {}
    Node(int nu, Pos ipos) {
        num = nu;
        pos = ipos;
    }
};

struct Want {
    int val;
    int h;
    int w;

    Want() {}
    Want(int ival, int hh, int ww) {
        val = ival;
        h = hh;
        w = ww;
    }

    bool operator<(const Want &in) const {
        return val != in.val ? val > in.val : h != in.h ? h < in.h : w < in.w;
    };
};

struct Pyra {
    vector<Node> node;
    vector<pair<Pos, Pos>> mov;
    set<Want> move_list;

    void init() {
        // cout<< "init" <<endl;
        node = b;
        rep(i, n) {
            rep(j, i + 1) { is_err(i, j, false); }
        }
    }

    void swp(Pos p1, Pos p2) {
        swap(node[(p1.h * (p1.h + 1) / 2) + p1.w],
             node[p2.h * (p2.h + 1) / 2 + p2.w]);
        mov.push_back({p1, p2});
        // cout<< "end swp" <<endl;
    }
    void move(Pos p1, int dir) {
        // assert(0<=dir);
        // assert(dir<6);
        // cout<< "move" <<endl;
        Pos npos = p1 + pos6[dir];
        // assert(!p1.is_oob());
        // assert(!npos.is_oob());
        // cout<< "end move" <<endl;
        swp(p1, npos);
    }
    void reset_move_list(int hh, int ww) {
        auto itr =
            move_list.find({node[hh * (hh + 1) / 2 + ww].want_down, hh, ww});
        if (itr != move_list.end())
            move_list.erase(itr);
        is_err(hh, ww, false);
    }
    int is_err(int hh, int ww, bool exec) {
        // cout<< "is_err" <<endl;
        int max_diff = 0;
        int max_diff_idx = -1;

        // rep(i, 3){
        rep(i, 2) {
            Pos npos = Pos({hh, ww}) + pos6[i];
            // npos.print();
            if (npos.is_oob())
                continue;

            // 自分の数字が対象よりいくつ大きいか
            int diff = node[hh * (hh + 1) / 2 + ww].num -
                       node[npos.h * (npos.h + 1) / 2 + npos.w].num;
            diff = 1 + diff * (mt() % 8 + 100) / 100;
            // cout<< "is err diff: " << diff <<endl;
            if (i >= 2) {
                // // 左のノードが比較対象
                // int bal=(hh/2)-ww; // 左度
                // diff=-0.001*diff*bal;
                // if(0<diff){
                // 	if(max_diff<diff){
                // 		max_diff=diff;
                // 		max_diff_idx=i;
                // 	}
                // }
            } else {
                // 子のノードが比較対象
                if (0 < diff) {
                    if (max_diff < diff) {
                        max_diff = diff;
                        max_diff_idx = i;
                    }
                }
            }
        }
        // cout<< "end is_err" <<endl;
        if (max_diff_idx != -1 && exec) {
            move(Pos({hh, ww}), max_diff_idx);

            Pos chipos = Pos({hh, ww}) + pos6[max_diff_idx];
            reset_move_list(chipos.h, chipos.w);
            Pos npos = chipos + pos6[4];
            if (!npos.is_oob())
                reset_move_list(npos.h, npos.w);
            npos = chipos + pos6[5];
            if (!npos.is_oob())
                reset_move_list(npos.h, npos.w);
            npos = Pos({hh, ww}) + pos6[4];
            if (!npos.is_oob())
                reset_move_list(npos.h, npos.w);
            npos = Pos({hh, ww}) + pos6[5];
            if (!npos.is_oob())
                reset_move_list(npos.h, npos.w);
        }
        if (max_diff_idx != -1 && !exec) {
            node[hh * (hh + 1) / 2 + ww].want_down = max_diff;
            move_list.insert({max_diff, hh, ww});
        }

        return max_diff_idx;
    }
    bool random_move(int hh, int ww) {
        // cout<< "random_move" <<endl;
        return is_err(hh, ww, true) > 0;
    }

    int calc_score() {
        if (mov.size() == 0)
            return 11111;
        else
            return mov.size();
    }
    void print_ans() {
        cout << mov.size() << endl;
        rep(i, mov.size()) cout << mov[i].first.h SP << mov[i].first.w SP
                                << mov[i].second.h SP << mov[i].second.w
                                << endl;
    }
};

void inpt() {
    int tmp;
    int lop = 0;
    rep(i, n) {
        rep(j, i + 1) {
            cin >> tmp;
            b[lop] = {tmp, {i, j}};
            lop++;
        }
    }
}

int main() {
    // 開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();

    Pyra best;

    int lp = 0;
    while (true) {
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta = chrono::duration_cast<chrono::milliseconds>(current - start)
                    .count();
        if (delta > TIME_LIMIT)
            break;

        Pyra pyra;
        pyra.init();

        rot = 0;
        while (!pyra.move_list.empty()) {
            rot++;
            auto ml = *pyra.move_list.begin();
            // cout<< ml.val SP << ml.h SP << ml.w <<endl;
            pyra.move_list.erase(pyra.move_list.begin());
            pyra.random_move(ml.h, ml.w);
        }

        // cout<< pyra.calc_score() <<endl;
        if (pyra.calc_score() < best.calc_score()) {
            best = pyra;
            // cout<< best.calc_score() <<endl;
            // cout<< "rot" << rot <<endl;
        }
    }
    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    // 誕生日を祝うコメントを出力
    cout << "Happy Birthday!" << endl;

    return 0;
}