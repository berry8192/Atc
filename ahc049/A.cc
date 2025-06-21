#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

int N;
vector<vector<int>> w, d;

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
    string direct_path(Pos goal) {
        // cerr << "Generating direct path from " << h << "," << w << " to "
        //      << goal.h << "," << goal.w << endl;
        assert(!is_oob());
        assert(!goal.is_oob());
        string path = "";
        int sh = h, sw = w;
        int gh = goal.h, gw = goal.w;
        while (sh < gh) {
            path += 'D';
            ++sh;
        }
        while (sh > gh) {
            path += 'U';
            --sh;
        }
        while (sw < gw) {
            path += 'R';
            ++sw;
        }
        while (sw > gw) {
            path += 'L';
            --sw;
        }
        // cerr << "Direct path generated: " << path << endl;
        return path;
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
};

struct Box {
    Pos pos;
    int w, d;

    Box(int ph, int pw, int ww, int dd) {
        pos = Pos(ph, pw);
        w = ww;
        d = dd;
    }

    bool operator<(const Box &in) const { return w > in.w; };
};

vector<Box> box_order;

struct BoxGroup {
    vector<Box> boxes;

    string get_path() const {
        // cerr << "Generating path for group..." << endl;
        Pos cpos = {0, 0};
        string res = "";
        rep(i, boxes.size()) {
            res += cpos.direct_path(boxes[i].pos);
            res += '1'; // pick up
            cpos = boxes[i].pos;
        }
        // (0,0)へ
        res += cpos.direct_path({0, 0});
        // cerr << "Path generated: " << res << endl;
        return res;
    }

    bool can_deliver() const {
        // cerr << "Checking if can deliver..." << endl;
        int weight_sum = 0;
        Pos cpos = {0, 0};
        repr(i, boxes.size()) {
            int dist = cpos.manhattan(boxes[i].pos);
            if (weight_sum * dist >= boxes[i].d) {
                return false;
            }
            weight_sum += boxes[i].w;
            cpos = boxes[i].pos;
        }
        return true;
    }
};

struct Grid {
    int groups_size;
    vector<BoxGroup> groups;
    int total_moves = 0;

    void init() {
        groups_size = 399;
        groups.resize(groups_size);
    }
    void make_groups() {
        // cerr << "Making groups..." << endl;
        vector<int> total_weights(groups_size);
        rep(i, box_order.size()) {
            int idx = i % groups_size;
            groups[idx].boxes.push_back(box_order[i]);
        }
    }

    void output_answer() {
        // cerr << "Outputting answer..." << endl;
        for (const auto &g : groups) {
            if (g.can_deliver()) {
                string path = g.get_path();
                total_moves += count_if(path.begin(), path.end(), [](char c) {
                    return c == 'U' || c == 'D' || c == 'L' || c == 'R';
                });
                rep(i, path.size()) { cout << path[i] << endl; }
            }
        }
    }
    void debug() {
        cerr << "Total moves: " << total_moves << endl;
        cerr << "Number of groups: " << groups.size() << endl;
        for (const auto &g : groups) {
            cerr << "Group size: " << g.boxes.size() << endl;
            for (const auto &box : g.boxes) {
                cerr << "Box at (" << box.pos.h << ", " << box.pos.w
                     << ") with weight " << box.w << " and taikyu " << box.d
                     << endl;
            }
        }
    }
};

void read_input() {
    cin >> N;
    w.resize(N, vector<int>(N));
    d.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> w[i][j];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> d[i][j];
    rep(i, N) {
        rep(j, N) {
            if (i == 0 && j == 0)
                continue;
            box_order.push_back(Box{i, j, w[i][j], d[i][j]});
        }
    }
    sort(all(box_order));
}

int main() {
    read_input();

    Grid grid;
    grid.init();
    grid.make_groups();
    grid.output_answer();
    grid.debug();

    return 0;
}