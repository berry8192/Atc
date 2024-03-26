#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] << ", ";
    // rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
    cout << pvv[pvv.size() - 1] << endl;
}

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

// 累積和
vector<int> ruiseki(vector<int> vv) {
    vector<int> xx;
    xx.resize(vv.size() + 1);
    xx[0] = 0;
    for (int i = 0; i < (int)vv.size(); i++) {
        xx[i + 1] = xx[i] + vv[i];
        // xx[i+1]=xx[i+1]%mod;
    }
    return xx;
}

int imax = 2147483647;
long long lmax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 2900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

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
    long long len = (b - a + 1);
    return randxor() % len + a;
}

int W, D, N;
int HEIGHT, WIDTH;
vector<vector<int>> a;

// Wで割った余りが0になるように切り上げる
int W_ceil(int x) { return (x + W - 1) / W * W; }

// 構造体
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

vector<int> shuffle_v(int length) {
    // cout << "shuffle_v" << endl;
    vector<int> rtn(length);
    rep(i, length) rtn[i] = i;
    // ダステンフェルドのアルゴリズムを使っている、はず
    rep(i, length - 1) {
        int j = rand(i, length - 1);
        swap(rtn[i], rtn[j]);
    }
    return rtn;
}

struct Column {
    int idx;       // 何個目の利用要望か
    int width;     // 幅
    int right_pos; // 右端の位置

    Column() {}
    Column(int iidx, int iwidth, int iright_pos) {
        idx = iidx;
        width = iwidth;
        right_pos = iright_pos;
    }
};
struct Row {
    vector<Column> columns;
    int height;     // 高さ
    int bottom_pos; // 下端
    int loss;

    Row() {}
    Row(int iheight, int ibottom_pos) {
        height = iheight;
        bottom_pos = ibottom_pos;
    }

    // ロスのない最小の高さにする、bottomは計算しない
    void adjust_row(vector<int> &a_day) {
        // cerr << "adjust_row" << endl;
        assert(columns.size() > 0);
        int area_sum = 0;
        rep(i, columns.size()) {
            area_sum += a_day[columns[i].idx];
        } // TODO: ここは高速化できる
        int max_height = 0;
        vector<int> new_widths(columns.size());
        rep(i, columns.size()) {
            // 切り捨てで幅を計算する
            new_widths[i] = max(1, W * a_day[columns[i].idx] / area_sum);
            max_height = max(
                max_height,
                (a_day[columns[i].idx] + new_widths[i] - 1) /
                    new_widths[i]); // TODO:
                                    // 愚直に一番高さを取るものに合わせている
        }
        vector<int> right_poses = ruiseki(new_widths);
        rep(i, columns.size()) {
            columns[i].width = new_widths[i];
            columns[i].right_pos = right_poses[i + 1];
        }
        height = max_height;
    }
    void touch_right() {
        int diff = W - columns[columns.size() - 1].width;
        columns[columns.size() - 1].width += diff;
        columns[columns.size() - 1].right_pos = W;
    }
    void calc_loss(vector<int> &a_day) {
        int need_area_sum = 0;
        rep(i, columns.size()) { need_area_sum += a_day[columns[i].idx]; }
        loss = height * W - need_area_sum;
    }
};
struct Day {
    int day;
    vector<Row> rows;
    vector<int> a_day;

    Day() {}
    Day(int iday, vector<int> &ia_day) {
        day = iday;
        a_day = ia_day;
    }

    void init_day() {
        // cout << "init_day" << endl;
        // N以上で最小の平方数にする
        int division = ceil(sqrt(N));
        // 空のrowsを作らないために必要最小限にする
        int rows_size = (N + division - 1) / division;
        rows.resize(rows_size);
        rep(i, rows_size) {
            int height = W / division;
            rows[i] = Row(height, (i + 1) * height);
        }
        rep(i, N) {
            int width = W / division;
            rows[i / division].columns.push_back(
                {i, width, (i % division + 1) * width});
        } // 左上から正方形で敷き詰めていく
    }
    void init_day_fixed_division(int division) {
        // cout << "init_day_fixed_division" << endl;
        // 空のrowsを作らないために必要最小限にする
        rows.clear();
        int rows_size = (N + division - 1) / division;
        // cerr << rows_size << endl;
        rows.resize(rows_size);
        rep(i, rows_size) {
            int height = W / division;
            rows[i] = Row(height, (i + 1) * height);
        }
        // vector<int> perm = shuffle_v(N);
        rep(i, N) {
            // int row_idx;
            // if (i < rows_size) {
            //     row_idx = i;
            // } else {
            //     row_idx = rand(0, rows_size - 1);
            // }
            int width = W / division;

            // rows[row_idx].columns.push_back(
            //     {perm[i], width, (i % division + 1) * width});
            rows[i / division].columns.push_back(
                {i, width, (i % division + 1) * width});
        } // 左上から正方形で敷き詰めていく
    }     // なるべく低い高さになるようにする
    void init_day_from_bitset_with_shuffle(bitset<50> bs,
                                           vector<pair<int, int>> &perm) {
        // cerr << "init_day_from_bitset" << endl;
        rows.clear();
        int idx;
        rep(i, N) {
            if (bs[i]) {
                rows.push_back(Row());
                idx = rows.size() - 1;
            }
            rows[idx].columns.push_back({perm[i].second, -1, -1});
        }
        adjsut_rows();
    }
    void init_day_from_bitset(bitset<50> bs) {
        // cerr << "init_day_from_bitset" << endl;
        rows.clear();
        int idx;
        rep(i, N) {
            if (bs[i]) {
                rows.push_back(Row());
                idx = rows.size() - 1;
            }
            rows[idx].columns.push_back({i, -1, -1});
        }
        adjsut_rows();
    }
    void gen_shuffle_a_day(vector<pair<int, int>> &perm,
                           vector<int> &shuffled_a_day) {
        rep(i, N) { perm[i] = {i, i}; }
        int lp = rand(1, int(sqrt(N)));
        rep(i, lp) {
            int idx1 = rand(0, N - 1);
            int idx2 = min(N - 1, idx1 + rand(1, int(sqrt(N))));
            swap(perm[idx1].first, perm[idx2].first);
            swap(shuffled_a_day[idx1], shuffled_a_day[idx2]);
        }
    }
    void shuffle_interval_dp() {
        // cerr << "interval_dp" << endl;
        vector<pair<int, int>> perm(N);
        vector<int> shuffled_a_day = a_day;
        gen_shuffle_a_day(perm, shuffled_a_day);

        vector<int> w_day = ruiseki(shuffled_a_day);
        // 区間の最小高さ
        vector<vector<int>> min_height(N, vector<int>(N));
        // 仕切りの左を1として記録する
        vector<vector<bitset<50>>> partition(N, vector<bitset<50>>(N));
        for (int i = 1; i <= N; i++) {
            // i個からなる区間
            for (int j = 0; j + i - 1 < N; j++) {
                // jからスタート
                int su = w_day[i + j] - w_day[j];
                int mi = 0;
                for (int k = 0; k < i; k++) {
                    int tmp_width = max(1, shuffled_a_day[j + k] * W / su);
                    mi = max(mi, (shuffled_a_day[j + k] + tmp_width - 1) /
                                     tmp_width);
                }
                bitset<50> par;
                par.set(j); // 最初は[j~j+i]が1番とする
                // 内包する2区間の結合を取る場合も計算する
                for (int k = 0; k < i - 1; k++) {
                    int tmp =
                        min_height[j][j + k] + min_height[j + k + 1][j + i - 1];
                    if (tmp < mi) {
                        mi = tmp;
                        par = (partition[j][j + k] |
                               partition[j + k + 1][j + i - 1]);
                    }
                }
                min_height[j][j + i - 1] = mi;
                partition[j][j + i - 1] = par;
            }
        }
        // cerr << min_height[0][N - 1] << endl;
        // cerr << partition[0][N - 1] << endl;
        sort(all(perm));
        init_day_from_bitset_with_shuffle(partition[0][N - 1], perm);
    }
    void interval_dp() {
        // cerr << "interval_dp" << endl;
        vector<int> w_day = ruiseki(a_day);
        // 区間の最小高さ
        vector<vector<int>> min_height(N, vector<int>(N));
        // 仕切りの左を1として記録する
        vector<vector<bitset<50>>> partition(N, vector<bitset<50>>(N));
        for (int i = 1; i <= N; i++) {
            // i個からなる区間
            for (int j = 0; j + i - 1 < N; j++) {
                // jからスタート
                int su = w_day[i + j] - w_day[j];
                int mi = 0;
                for (int k = 0; k < i; k++) {
                    int tmp_width = max(1, a_day[j + k] * W / su);
                    mi = max(mi, (a_day[j + k] + tmp_width - 1) / tmp_width);
                }
                bitset<50> par;
                par.set(j); // 最初は[j~j+i]が1番とする
                // 内包する2区間の結合を取る場合も計算する
                for (int k = 0; k < i - 1; k++) {
                    int tmp =
                        min_height[j][j + k] + min_height[j + k + 1][j + i - 1];
                    if (tmp < mi) {
                        mi = tmp;
                        par = (partition[j][j + k] |
                               partition[j + k + 1][j + i - 1]);
                    }
                }
                min_height[j][j + i - 1] = mi;
                partition[j][j + i - 1] = par;
            }
        }
        // cerr << min_height[0][N - 1] << endl;
        // cerr << partition[0][N - 1] << endl;
        init_day_from_bitset(partition[0][N - 1]);
    }
    void low_height() {
        // cout << "low_height" << endl;
        // cerr << "base: " << rows[rows.size() - 1].bottom_pos << endl;
        assert(rows.size() >= 0); // 先にinit_dayしてから来てね
        assert(rows.size() >= 1); // 移動の余地がない
        assert(rows.size() < N);  // 移動の余地がない
        vector<Row> current_rows = rows;

        rep(i, current_rows.size()) { current_rows[i].calc_loss(a_day); }
        rep(lp, 100) {
            // 1番無駄があるrowから2番目に無駄があるrowに移したい、無理そうな時はよしなに
            ll loss_size[2] = {-imax, -imax}, loss_idx[2];
            rep(i, current_rows.size()) {
                if (loss_size[0] < current_rows[i].loss) {
                    loss_size[1] = loss_size[0];
                    loss_idx[1] = loss_idx[0];
                    loss_size[0] = current_rows[i].loss;
                    loss_idx[0] = i;
                } else if (loss_size[1] < current_rows[i].loss) {
                    loss_size[1] = current_rows[i].loss;
                    loss_idx[1] = i;
                }
            }
            // 移動するrowのidxを設定
            int move_from, move_to;
            int idx;
            if (lp % 10) {
                do {
                    idx = rand(0, int(current_rows.size() - 1));
                    // cerr << idx << endl;
                } while (current_rows[idx].columns.size() < 2);
                move_from = idx;
                move_to = (idx + rand(1, int(current_rows.size() - 1))) %
                          current_rows.size();
                // cerr << move_from SP << move_to << endl;
            } else {
                if (current_rows[loss_idx[0]].columns.size() >= 2) {
                    move_from = loss_idx[0];
                    move_to = loss_idx[1];
                } else if (current_rows[loss_idx[1]].columns.size() >= 2) {
                    move_from = loss_idx[1];
                    move_to = loss_idx[0];
                } else {
                    do {
                        idx = rand(0, int(current_rows.size() - 1));
                    } while (current_rows[idx].columns.size() < 2);
                    move_from = idx;
                    move_to = loss_idx[0];
                }
            }
            // 移動実行
            int column_size = current_rows[move_from].columns.size();
            int swap_column_idx = rand(0, column_size - 2);
            // ランダムに移動元となる最後尾に持ってくる
            swap(current_rows[move_from].columns[swap_column_idx],
                 current_rows[move_from].columns[column_size - 1]);
            current_rows[move_to].columns.push_back(
                current_rows[move_from].columns[column_size - 1]);
            current_rows[move_from].columns.pop_back();

            // 移動後にadjust_rowをする
            current_rows[move_from].adjust_row(a_day);
            current_rows[move_to].adjust_row(a_day);
            adjsut_rows(false);

            if (current_rows[current_rows.size() - 1].bottom_pos <
                current_rows[current_rows.size() - 1].bottom_pos) {
                rows = current_rows;
                // cerr << "! " << lp SP << rows[rows.size() - 1].bottom_pos
                //      << endl;
            }
            // cerr << lp SP << rows[rows.size() - 1].bottom_pos << endl;
        }
    }
    bool adjsut_rows(bool exec_adjust_row = true) {
        // cerr << "adjsut_rows" << endl;
        int height_sum = 0;
        rep(i, rows.size()) {
            if (exec_adjust_row) {
                rows[i].adjust_row(a_day); // この中でrows[i].heightが書き換わる
            }
            height_sum += rows[i].height;
            rows[i].bottom_pos = height_sum;
        }
        // cout << day SP << height_sum << endl;
        return (height_sum <= W);
    }
    bool W_limit_init_day(int division) {
        rep(lp, 1) {
            init_day_fixed_division(division);
            if (adjsut_rows())
                return true;
        }
        return false;
    }
    void touch_bottom() {
        int margin = W - rows[rows.size() - 1].bottom_pos;
        if (margin > 0) {
            rows[rows.size() - 1].height += margin;
            rows[rows.size() - 1].bottom_pos = W;
        } else {
            margin = abs(margin);
            rep(lp, margin) {
                int largeest_loss = -imax;
                int best_idx;
                rep(i, rows.size()) {
                    rows[i].calc_loss(a_day);
                    if (rows[i].loss > largeest_loss) {
                        largeest_loss = rows[i].loss;
                        best_idx = i;
                    }
                }
                while (rows[best_idx].height == 1) {
                    best_idx = (best_idx + 1) % rows.size();
                }
                rows[best_idx].height--;
            }
            int height_sum = 0;
            rep(i, rows.size()) {
                height_sum += rows[i].height;
                rows[i].bottom_pos = height_sum;
            }
            assert(rows[rows.size() - 1].bottom_pos == W);
        }
    }
    void touch_right_and_bottom() {
        touch_bottom();
        rep(i, rows.size()) { rows[i].touch_right(); }
    }
    ll calc_area_shortage_loss() {
        ll loss = 0;
        rep(i, rows.size()) {
            ll height = rows[i].height;
            rep(j, rows[i].columns.size()) {
                ll tmp = 100LL * (a_day[rows[i].columns[j].idx] -
                                  height * rows[i].columns[j].width);
                loss += max(0LL, tmp);
            }
        }
        return loss;
    }

    void print_ans() {
        // cout << "print_ans: " << day << endl;
        vector<int> su(N);
        vector<int> sl(N);
        vector<int> sd(N);
        vector<int> sr(N);
        int u = 0, l, d, r;
        rep(i, rows.size()) {
            d = min(W, rows[i].bottom_pos); // TODO: minなしにしたい
            // TODO: bottom_pos側をWに合わせる
            if (i == rows.size() - 1) {
                // d = W;
            }
            l = 0;
            rep(j, rows[i].columns.size()) {
                r = rows[i].columns[j].right_pos;
                // TODO: right_pos側をWに合わせる
                if (j == rows[i].columns.size() - 1) {
                    // r = W;
                }
                su[rows[i].columns[j].idx] = u;
                sl[rows[i].columns[j].idx] = l;
                sd[rows[i].columns[j].idx] = d;
                sr[rows[i].columns[j].idx] = r;
                l = r;
            }
            u = d;
        }
        rep(i, N) {
            cout << su[i] << " " << sl[i] << " " << sd[i] << " " << sr[i]
                 << endl;
        }
    }
};

struct Hall {
    ll hall_loss;
    vector<Day> days;

    void init() {
        days.resize(D);
        rep(i, D) { days[i] = Day(i, a[i]); }
    }

    void execute() {
        rep(i, D) {
            // cerr << "day: " << i << endl;
            days[i].init_day_fixed_division(ceil(sqrt(N)));
            days[i].adjsut_rows();
            days[i].touch_right_and_bottom();
        }
    }
    bool execute_fixed_division(int division) {
        rep(i, D) {
            if (days[i].W_limit_init_day(division) == false)
                return false;
            days[i].touch_right_and_bottom();
        }
        return true;
    }
    void execute_low_height() {
        rep(i, D) {
            // cerr << "day: " << i << endl;
            Day today(i, a[i]);
            ll best_cost = lmax;
            rep3(j, N - 1, 1) {
                // cerr << " division: " << j << endl;
                today.init_day_fixed_division(j);
                // cerr << " rows :" << today.rows.size() << endl;
                if (today.rows.size() <= 1 || N <= today.rows.size()) {
                    continue;
                }
                today.low_height();
                today.adjsut_rows();
                today.touch_right_and_bottom();
                ll tmp = today.calc_area_shortage_loss();
                if (tmp < best_cost) {
                    best_cost = tmp;
                    days[i] = today;
                }
            }
        }
    }
    void execute_interval_dp() {
        rep(i, D) {
            days[i].interval_dp();
            days[i].touch_right_and_bottom();
        }
        calc_loss();
    }
    void execute_shuffle_interval_dp() {
        rep(i, D) {
            days[i].shuffle_interval_dp();
            days[i].touch_right_and_bottom();
        }
        calc_loss();
    }
    // 厳密な計算ではないが、横線の数が違う場合は適当にコストを増やす
    // 右端と下端はWになっているものとしている
    ll calc_partition_loss(int day) {
        assert(day != 0);
        ll loss = 0;
        if (days[day - 1].rows.size() != days[day].rows.size()) {
            ll rtn =
                W * (days[day - 1].rows.size() - 1 + days[day].rows.size() - 1);
            rep(i, days[day - 1].rows.size()) {
                rtn += days[day - 1].rows[i].height *
                       (days[day - 1].rows[i].columns.size() - 1);
            }
            rep(i, days[day].rows.size()) {
                rtn += days[day].rows[i].height *
                       (days[day].rows[i].columns.size() - 1);
            }
            return rtn;
        }
        rep(j, days[day].rows.size()) {
            bool same_height_line = days[day].rows[j].bottom_pos ==
                                    days[day - 1].rows[j].bottom_pos;
            // 偶然一致したheightでもコスト0として扱う
            // 一番下の線はWになっているものとする
            if (!same_height_line && j != days[day].rows.size() - 1) {
                loss += 2 * W; // 横線を消す分と書く分で2Wかかる
            }

            // 縦線のコスト計算
            bool same_height =
                same_height_line &&
                (days[day].rows[j].height == days[day - 1].rows[j].height);
            set<int> v_lines;
            // 一番右の線はWになっているものとする
            rep(k, days[day - 1].rows[j].columns.size() - 1) {
                if (same_height) {
                    v_lines.insert(days[day - 1].rows[j].columns[k].right_pos);
                }
                // 前の日の仕切りを回収する場合
                loss += days[day - 1].rows[j].height;
            }
            rep(k, days[day].rows[j].columns.size() - 1) {
                if (same_height &&
                    (v_lines.find(days[day].rows[j].columns[k].right_pos) !=
                     v_lines.end())) {
                    // 前日は回収せず当日は置かない
                    loss -= days[day - 1].rows[j].height;
                } else {
                    // 当日に仕切りを置く場合
                    loss += days[day].rows[j].height;
                }
            }
        }
        return loss;
    }
    ll calc_day_loss(int day) {
        ll loss = 0;
        loss += days[day].calc_area_shortage_loss();
        if (day != 0) {
            loss += calc_partition_loss(day);
        }
        return loss;
    }
    void calc_loss() {
        // cerr << "calc_loss" << endl;
        ll loss = 1;
        rep(i, D) {
            loss += calc_day_loss(i);
            // cerr << "day: " << i SP << loss << endl;
        }
        hall_loss = loss;
    }

    void print_ans() {
        rep(i, D) { days[i].print_ans(); }
    }

    void output_false_and_exit() {
        int cnt = 0;

        rep(i, D) {
            if (days[i].rows[days[i].rows.size() - 1].bottom_pos > W) {
                cnt++;
            }
        }

        std::ofstream outputFile("log.csv", std::ios::app);
        outputFile << cnt << endl;
        outputFile.close();
        exit(0);
    }
};

int calc_sum_by_days_max() {
    int su = 0;
    for (int i = 0; i < N; i++) {
        int ma = 0;
        for (int j = 0; j < D; j++) {
            ma = max(ma, a[j][i]);
        }
        su += ma;
    }
    return su;
}

vector<int> calc_days_max() {
    vector<int> rtn(N);
    for (int i = 0; i < N; i++) {
        int ma = 0;
        for (int j = 0; j < D; j++) {
            ma = max(ma, a[j][i]);
        }
        rtn[i] = ma;
    }
    return rtn;
}

vector<int> calc_sum_by_day() {
    // int maxa = 0;
    vector<int> tmp(D);
    for (int i = 0; i < D; i++) {
        int su = 0;
        for (int j = 0; j < N; j++) {
            su += a[i][j];
            // maxa = max(maxa, a[i][j]);
        }
        tmp[i] = su;
    }
    return tmp;
}

// Wで切り上げた数字の総和がWに満たないときはscore1が取れる
void simple_h_line() {
    vector<int> cdm = calc_days_max();
    vector<int> ceiled;
    rep(i, cdm.size()) { ceiled.push_back((cdm[i] + W - 1) / W); }
    vector<int> tmp = ruiseki(ceiled);
    if (tmp[N] <= W) {
        rep(lp, D) {
            rep(i, N) {
                cout << tmp[i] SP << 0 SP << tmp[i + 1] SP << W << endl;
            }
        }
        exit(0);
    }
}

void inpt() {
    cin >> W >> D >> N;
    a.resize(D);
    rep(i, D) { a[i].resize(N); }
    rep(i, D) {
        rep(j, N) { cin >> a[i][j]; }
    }
}

int main() {
    inpt();
    simple_h_line(); // TODO: いずれ使わなくてもよくなる

    Hall best;
    best.init();
    best.execute_interval_dp();
    // cerr << best.hall_loss << endl;
    rep(i, N) {
        Hall hall;
        hall.init();
        if (hall.execute_fixed_division(i + 1) == false) {
            continue;
        }
        hall.calc_loss();
        if (hall.hall_loss < best.hall_loss) {
            best = hall;
            // cerr << loop SP << timer.progress() SP << hall.hall_loss << endl;
        }
    }

    int loop = 0;
    while (1) {
        loop++;
        if (timer.progress() > 1.0) {
            break;
        }
        Hall hall;
        hall.init();
        hall.execute_shuffle_interval_dp();
        if (hall.hall_loss < best.hall_loss) {
            best = hall;
            // cerr << loop SP << timer.progress() SP << hall.hall_loss << endl;
        }
        // cerr << loop SP << timer.progress() SP << hall.hall_loss << endl;
    }
    // cerr << loop SP << timer.progress() << endl;
    // cerr << best.hall_loss << endl;
    best.print_ans();

    return 0;
}
