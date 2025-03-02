#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(x) x.begin(), x.end()
typedef long long ll;
using P = pair<int, int>;

const ll INF = 1LL << 60;
const int imax = 1 << 30;
const int Inf = 1000000000;
const int MaxOperation = 10000;

const int di[] = {0, 1, 0, -1}, dj[] = {1, 0, -1, 0};
template <typename T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return 1;
    }
    return 0;
}
template <typename T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}

unsigned int randxor() {
    static unsigned int x = 123456789, y = 362436069, z = 521288629,
                        w = 88675123;
    unsigned int t;
    t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}
template <typename T> T rand(T a, T b) {
    assert(a <= b);
    ll len = (b - a + 1);
    return randxor() % len + a;
}

class Timer {
  private:
    static const int LAZY_MASK = 0xFF;

    chrono::system_clock::time_point start;
    int call_cnt = 0;
    int prev_time;
    bool is_lazy;

  public:
    Timer(bool is_lazy = false) : is_lazy(is_lazy) {
        start = chrono::system_clock::now();
    }

    int get_ms() {
        if (!is_lazy || (call_cnt & LAZY_MASK) == 0) {
            auto end = chrono::system_clock::now();
            prev_time = chrono::duration_cast<chrono::milliseconds>(end - start)
                            .count();
        }
        call_cnt++;
        return prev_time;
    }
};

int N, M;
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < N && 0 <= w && w < N);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * N + w; }
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

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
    Pos operator*(const int x) {
        Pos rtn;
        rtn.h = h * x;
        rtn.w = w * x;
        return rtn;
    }
};
Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
string itod = "RULD-";

struct Attend {
    int direction;
    bool rollable;

    Attend() {};
    Attend(int d, bool roll) {
        direction = d;
        rollable = roll;
    }
};

struct Hand {
    int type;
    int direction;

    Hand() {};
    Hand(int t, int d) {
        type = t;
        direction = d;
    }
};

struct Cave {
    vector<string> board;
    Pos hole;
    Pos player;
    vector<Pos> gems;
    // vector<Pos> rocks;
    vector<vector<Attend>> attend;
    vector<Hand> ans;
    int remain;

    void init(int NN, vector<string> &C) {
        remain = 2 * N;
        board = C;
        rep(i, N) {
            rep(j, N) {
                if (C[i][j] == 'a') {
                    gems.emplace_back(i, j);
                } else if (C[i][j] == 'A') {
                    hole = {i, j};
                    player = {i, j};
                } else if (C[i][j] == '@') {
                    // rocks.emplace_back(i, j);
                }
            }
        }
    }

    void calc_attend() {
        // cerr << "Cal" << endl;
        attend.clear();
        attend.resize(N, vector<Attend>(N, {4, false}));
        vector<vector<int>> dist(N, vector<int>(N, imax));
        dist[hole.h][hole.w] = 0;
        queue<Pos> pos_q;
        queue<int> dis_q;
        pos_q.push(hole);
        dis_q.push(0);

        while (!pos_q.empty()) {
            Pos pos = pos_q.front();
            int dis = dis_q.front();
            pos_q.pop();
            dis_q.pop();
            // pos.print();
            // cout << dis << endl;
            if (dist[pos.h][pos.w] < dis) {
                continue;
            }
            rep(i, 4) {
                int lp = 1;
                Pos npos = pos + d4[i] * lp;
                // cout << "npos ";
                // npos.print();
                if (!npos.is_oob() && dist[npos.h][npos.w] > dis + 1 &&
                    board[pos.h][pos.w] != '@' && board[pos.h][pos.w] != 'a') {
                    dist[npos.h][npos.w] = dis + 1;
                    pos_q.push(npos);
                    dis_q.push(dis + 1);
                    attend[npos.h][npos.w] = Attend((i + 2) % 4, false);
                }
                lp = 2;
                npos = pos + d4[i] * lp;
                bool touched = false;
                // 転がりを止めるストッパーが必要
                if (!(pos == hole)) {
                    Pos rpos = pos + d4[(i + 2) % 4];
                    if (rpos.is_oob() || (board[rpos.h][rpos.w] != '@' &&
                                          board[rpos.h][rpos.w] != 'a')) {
                        continue;
                    }
                }
                while (!npos.is_oob() && !touched) {
                    touched = board[npos.h][npos.w] == '@' ||
                              board[npos.h][npos.w] == 'a';
                    if (dist[npos.h][npos.w] > dis + 1) {
                        dist[npos.h][npos.w] = dis + 1;
                        pos_q.push(npos);
                        dis_q.push(dis + 1);
                        attend[npos.h][npos.w] = Attend((i + 2) % 4, true);
                    }
                    lp++;
                    npos = pos + d4[i] * lp;
                }
            }
        }
        // PVV(dist);
    }
    void move_player(int dir) {
        Pos npos = player + d4[dir];
        assert(!npos.is_oob());
        player = npos;
        ans.emplace_back(1, dir);
    }
    void move_player_to(Pos pos) {
        while (!(player == pos)) {
            if (player.h < pos.h) {
                move_player(3);
            } else if (player.h > pos.h) {
                move_player(1);
            } else if (player.w < pos.w) {
                move_player(0);
            } else if (player.w > pos.w) {
                move_player(2);
            }
        }
    }
    void carry_object(Pos pos, int dir) {
        Pos npos = pos + d4[dir];
        player = npos;
        if (npos == hole) {
            remain--;
            board[pos.h][pos.w] = '.';
            return;
        }
        assert(board[npos.h][npos.w] != '@' && board[npos.h][npos.w] != 'a');
        board[npos.h][npos.w] = board[pos.h][pos.w];
        board[pos.h][pos.w] = '.';
        ans.emplace_back(2, dir);
    }
    void roll_object(Pos pos, int dir) {
        int lp = 1;
        Pos npos = pos + d4[dir] * lp;
        if (npos == hole) {
            remain--;
            board[pos.h][pos.w] = '.';
            return;
        }
        while (!npos.is_oob() || board[npos.h][npos.w] == '@' ||
               board[npos.h][npos.w] == 'a') {
            lp++;
            npos = pos + d4[dir] * lp;
        }
        assert(lp > 1);
        Pos cpos = pos + d4[dir] * (lp - 1);
        board[cpos.h][cpos.w] = board[pos.h][pos.w];
        board[pos.h][pos.w] = '.';
        ans.emplace_back(3, dir);
    }
    void move_object(Pos pos) {
        move_player_to(pos);
        int dir = attend[pos.h][pos.w].direction;
        bool roll = attend[pos.h][pos.w].rollable;
        int type = roll ? 3 : 2;
        if (type == 3) {
            roll_object(pos, dir);
        } else {
            carry_object(pos, dir);
        }
    }
    void progress() {
        calc_attend();
        rep(i, gems.size()) {
            cerr << i << endl;
            if (i == 4) {
                print_ans();
                exit(0);
            }
            move_object(gems[i]);
        }
    }

    void print_ans() {
        rep(i, ans.size()) {
            cout << ans[i].type << " " << itod[ans[i].direction] << endl;
        }
    }
    void print_attend() {
        rep(i, N) {
            rep(j, N) { cout << itod[attend[i][j].direction]; }
            cout << endl;
        }
        cout << "-----" << endl;
        rep(i, N) {
            rep(j, N) {
                if (attend[i][j].rollable) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }
    void PVV(vector<vector<int>> &v) {
        rep(i, N) {
            rep(j, N) { cout << v[i][j] << " "; }
            cout << endl;
        }
    }
};

int main() {
    cin >> N >> M;
    vector<string> S(N);
    rep(i, N) cin >> S[i];

    Cave cave;
    cave.init(N, S);
    cave.progress();

    return 0;
}
