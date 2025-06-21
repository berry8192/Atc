#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

int imax = 2147483647;
ll lmax = 9223372036854775807;

double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 1000.0;
double end_temp = 10.0;

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

auto seed = (unsigned)time(NULL);
mt19937 mt(seed);

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
    bool is_north_west_than(Pos pos) { return h < pos.h && w < pos.w; }
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
    int damage;

    Box(int ph, int pw, int ww, int dd) {
        pos = Pos(ph, pw);
        w = ww;
        d = dd;
        damage = (pos.h + pos.w) * w;
    }

    bool operator<(const Box &in) const {
        return (pos.h + pos.w) * w > (in.pos.h + in.pos.w) * in.w;
    };
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
        assert(!boxes.empty());

        rep(i, boxes.size() - 1) {
            int weight_sum = 0;
            Pos cpos = boxes[i].pos;
            int taikyu = boxes[i].d;
            // cout << "taikyu: " << taikyu << endl;
            rep3(j, boxes.size(), i + 1) {
                int dist = cpos.manhattan(boxes[j].pos);
                int damage = dist * weight_sum;

                taikyu -= damage;
                // cout << i SP << j SP << "dist: " << dist SP
                //      << "weight_sum: " << weight_sum SP
                //      << "damage: " << damage SP << "taikyu: " << taikyu <<
                //      endl;
                if (taikyu <= 0) {
                    return false;
                }
                weight_sum += boxes[j].w;
                cpos = boxes[j].pos;
            }
            int dist = cpos.manhattan({0, 0});
            int damage = dist * weight_sum;
            taikyu -= damage;
            if (taikyu <= 0) {
                return false;
            }
        }
        return true;
    }
};

struct Grid {
    int groups_size;
    vector<BoxGroup> groups;
    string ans;
    ll hands;

    void init() { groups_size = 100; }
    void make_groups_fixed_size() {
        // cerr << "Making groups..." << endl;
        groups.resize(groups_size);
        rep(i, box_order.size()) {
            int idx = i % groups_size;
            groups[idx].boxes.push_back(box_order[i]);
        }
    }
    void make_groups(double slide_p = 0.3, double allow_p = 0.3) {
        int used_count = 0;
        vector<int> used_idx(box_order.size());

        int left_min_idx = 0;
        while (used_count < box_order.size()) {
            // cout << "Used count: " << used_count << endl;
            BoxGroup group;
            int first_box_idx;
            while (used_idx[left_min_idx]) {
                left_min_idx++;
            }
            first_box_idx = left_min_idx;
            left_min_idx++;
            group.boxes.push_back(box_order[first_box_idx]);
            used_idx[first_box_idx] = 1;
            used_count++;

            vector<int> taikyus = {box_order[first_box_idx].d};
            int search_idx = first_box_idx + 1;
            while (search_idx < 399) {
                Box current_box = group.boxes.back();
                search_idx = 400 - (400 - search_idx) * slide_p + 1;
                rep3(i, box_order.size(), search_idx) {
                    // int miss = abs(abs(box_order[i].pos.h -
                    // current_box.pos.h) -
                    //                abs(box_order[i].pos.w -
                    //                current_box.pos.w));
                    // if (mt() % (miss + 1) < 2) {
                    //     continue; // Skip some boxes randomly
                    // }
                    if (!used_idx[i] &&
                        box_order[i].pos.is_north_west_than(current_box.pos)) {
                        int flg = 1;
                        rep(j, taikyus.size()) {
                            if (box_order[i].damage > taikyus[j] * allow_p) {
                                flg = 0;
                                break;
                            }
                        }
                        if (flg) {
                            rep(j, taikyus.size()) {
                                taikyus[j] -= box_order[i].damage;
                            }
                            used_idx[i] = 1;
                            used_count++;
                            group.boxes.push_back(box_order[i]);
                            taikyus.push_back(box_order[i].d);
                            search_idx = i + 1;
                            break;
                        }
                    }
                }
            }
            groups.push_back(group);
        }
    }

    void gen_answer() {
        hands = 0;
        ans = "";
        // cerr << "Outputting answer..." << endl;
        for (const auto &g : groups) {
            if (g.can_deliver()) {
                string path = g.get_path();
                int total_moves =
                    count_if(path.begin(), path.end(), [](char c) {
                        return c == 'U' || c == 'D' || c == 'L' || c == 'R';
                    });
                ans += path;
                hands += total_moves;
                // rep(i, path.size()) { cout << path[i] << endl; }
            } else {
                hands += imax;
            }
        }
    }

    void print_ans() {
        rep(i, ans.size()) { cout << ans[i] << endl; }
    }
    void debug() {
        // cerr << "Total moves: " << total_moves << endl;
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

    ll best_hands = lmax;
    Grid best;

    int lp = 0;
    while (timer.progress() < 1.0) {
        lp++;

        double slide_p = 0.01 * (mt() % 20) + 0.8;
        double allow_p = 0.01 * (mt() % 50) + 0.5;
        Grid grid;
        grid.init();
        grid.make_groups(slide_p, allow_p);
        grid.gen_answer();

        ll new_hands = grid.hands;
        if (new_hands < best_hands) {
            cerr << "loop: " << lp SP << new_hands SP << slide_p SP << allow_p
                 << endl;
            best_hands = new_hands;
            best = grid;
        } else {
            // cerr << "No improvement in loop: " << lp SP << new_hands
            //      << endl;
        }
    }

    // while (timer.progress() < 1.0) {
    //     lp++;
    //     int type = mt() % 1;

    //     if (type == 0) {
    //         int from_group_idx = mt() % grid.groups.size();
    //         int to_group_idx = mt() % grid.groups.size();
    //         if (from_group_idx == to_group_idx) {
    //             continue; // Skip if the same group
    //         }
    //         int min_box_count = min(grid.groups[from_group_idx].boxes.size(),
    //                                 grid.groups[to_group_idx].boxes.size());
    //         int box_idx = mt() % min_box_count;

    //         swap(grid.groups[from_group_idx].boxes[box_idx],
    //              grid.groups[to_group_idx].boxes[box_idx]);
    //         grid.gen_answer();
    //         ll new_hands = grid.hands;

    //         if (new_hands < best_hands) {
    //             cerr << "loop: " << lp SP << new_hands << endl;
    //             best_hands = new_hands;
    //         } else {
    //             // Undo the swap if it didn't improve the score
    //             swap(grid.groups[from_group_idx].boxes[box_idx],
    //                  grid.groups[to_group_idx].boxes[box_idx]);
    //         }
    //     }
    // }

    best.print_ans();

    return 0;
}