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

// std::ofstream outputFile("log.csv", std::ios::app);

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cerr << pvv[i] << ", ";
    // rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
    cerr << pvv[pvv.size() - 1] << endl;
}

template <class T> void PVV(T pvv) {
    rep(i, pvv.size()) {
        // outputFile<< "i: " << i <<endl;
        rep(j, pvv[i].size() - 1) { cerr << pvv[i][j] << ", "; }
        if (pvv[i].size())
            cerr << pvv[i][pvv[i].size() - 1] << endl;
    }
}
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

int get_max_element_index(const vector<double> &vec, bool match_first = true) {
    double ma = -9223372036854775807;
    int mai;
    if (match_first) {
        rep(i, vec.size()) {
            if (ma < vec[i]) {
                ma = vec[i];
                mai = i;
            }
        }
    } else {
        rep(i, vec.size()) {
            if (ma <= vec[i]) {
                ma = vec[i];
                mai = i;
            }
        }
    }
    return mai;
}
vector<int> get_max_element_indices(const vector<double> &vec, int length) {
    assert(length <= vec.size());
    vector<pair<double, int>> p;
    rep(i, vec.size()) {
        p.emplace_back(-vec[i], i); // 今回は降順なのでマイナスにする
    }
    sort(all(p));
    vector<int> ans;
    rep(i, length) { ans.push_back(p[i].second); }
    return ans;
}
void normalize_vector_by_matrix(vector<vector<double>> &mat,
                                vector<double> &norm) {
    assert(mat.size() == norm.size());
    int mat_width = mat[0].size();
    int mat_sum = 0, norm_sum = 0;
    rep(i, norm.size()) { norm_sum += norm[i]; }
    rep(j, mat_width) {
        rep(i, mat.size()) { mat_sum += mat[i][j]; }
        rep(i, mat.size()) { mat[i][j] = mat_sum * norm[i] / norm_sum; }
    }
}
vector<double> normalize_vector_by_int(int obj_sum, vector<double> &norm) {
    vector<double> rtn(norm.size());
    double norm_sum = 0;
    rep(i, norm.size()) { norm_sum += norm[i]; }
    rep(i, norm.size()) { rtn[i] = norm[i] * obj_sum / norm_sum; }
    return rtn;
}
double vectors_value_range(vector<double> &vec) {
    double mi = 9223372036854775807;
    double ma = -9223372036854775807;
    rep(i, vec.size()) {
        mi = min(mi, vec[i]);
        ma = max(ma, vec[i]);
    }
    return ma - mi;
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
    char dir;

    Row() {
        dir = 'r'; // 右方向にのびる
    }
    Row(char i_dir) { dir = i_dir; }
    Row(int i_height, int i_bottom_pos, char i_dir = 'r') {
        height = i_height;
        bottom_pos = i_bottom_pos;
        dir = i_dir;
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
                // cerr << "! " << lp SP << rows[rows.size() -
                // 1].bottom_pos
                //      << endl;
            }
            // cerr << lp SP << rows[rows.size() - 1].bottom_pos <<
            // endl;
        }
    }
    void make_row_by_indices(vector<int> &indices, Row &row) {
        int area_sum = 0;
        rep(i, indices.size()) { area_sum += a_day[indices[i]]; }
        int max_height = 0;
        vector<int> new_widths(indices);
        rep(i, indices.size()) {
            // 切り捨てで幅を計算する
            new_widths[i] = max(1, W * a_day[indices[i]] / area_sum);
            max_height =
                max(max_height,
                    (a_day[indices[i]] + new_widths[i] - 1) / new_widths[i]);
        }
        row.height = max_height;
        row.columns.clear();
        rep(i, new_widths.size()) {
            row.columns.push_back(Column(indices[i], new_widths[i], -1));
        }
    }
    void optimize(vector<double> &row_height_aves) {
        vector<double> aim_heights = normalize_vector_by_int(
            rows[rows.size() - 1].bottom_pos, row_height_aves);
        // PV(aim_heights);
        // print_rows();
        int l = 0, r;
        rep(i, aim_heights.size() - 1) {
            r = N - aim_heights.size() + i + 1;
            vector<Row> made_rows(N); // ここをケチるとなぜかバグる
            double best_distance = imax;
            vector<int> indices;
            rep3(j, r + 1, l) {
                indices.push_back(j);
                make_row_by_indices(indices, made_rows[j - l]);
                double distance = abs(made_rows[j - l].height - aim_heights[i]);
                if (distance < best_distance && j != N - 1) {
                    best_distance = distance;
                } else {
                    rows[i] = made_rows[max(0, j - l - 1)];
                    l = j;
                    break;
                }
            }
        }
        vector<int> indices;
        rep3(i, N, l) { indices.push_back(i); }
        Row row;
        make_row_by_indices(indices, row);
        rows[aim_heights.size() - 1] = row;

        // print_rows();
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
    // 便宜上幅から計算する名前にしているが、高さでもOK
    int calc_loss_from_width_and_indices(int width, vector<int> &indices,
                                         Row &row, double order_weight,
                                         bool create = false) {
        assert(row.columns.size() == 0);
        int area_sum = 0;
        int max_height = 0;
        rep(i, indices.size()) { area_sum += a_day[indices[i]]; }
        vector<int> new_widths(indices.size());
        rep(i, indices.size()) {
            // 切り捨てで幅を計算する
            new_widths[i] = max(1, width * a_day[indices[i]] / area_sum);
            max_height =
                max(max_height,
                    (a_day[indices[i]] + new_widths[i] - 1) / new_widths[i]);
            // if (max_height > W) {
            //     cerr << "Max height" << endl;
            // }
        }
        if (create) {
            // vector<int> right_poses = ruiseki(new_widths);
            row.columns.resize(
                indices.size()); // 関数の頭でサイズが0であることを確認済み
            rep(i, indices.size()) {
                row.columns[i].idx = indices[i];
                row.columns[i].width = new_widths[i];
                // row.columns[i].right_pos = right_poses[i + 1];
            }
            row.height = max_height;
        }
        return max_height * width - area_sum +
               order_weight * area_sum / indices.size();
    }
    bool init_day_ul(double order_weight) {
        rows.clear();
        int remain_height = W;
        int remain_width = W;
        set<int> unused_indices;
        rep(i, N) { unused_indices.insert(i); }
        while (!unused_indices.empty()) {
            if (remain_height == 0 || remain_width == 0) {
                return false;
            }
            int smallest_loss = imax;
            vector<int> smallest_loss_vec;
            char smallett_loss_dir;
            int cnt = 0;
            // まずは1つずつしか使わない作戦 50
            for (auto idx : unused_indices) {
                vector<int> vec = {idx}; // 後々複数個になるかも
                int tmp;

                Row rowr('r');
                tmp = calc_loss_from_width_and_indices(remain_width, vec, rowr,
                                                       order_weight, false);
                // cerr << tmp << endl;
                if (tmp < smallest_loss) {
                    smallest_loss = tmp;
                    smallest_loss_vec = vec;
                    smallett_loss_dir = 'r';
                }

                Row rowd('d');
                tmp = calc_loss_from_width_and_indices(remain_height, vec, rowd,
                                                       order_weight, false);
                // cerr << tmp << endl;
                if (tmp < smallest_loss) {
                    smallest_loss = tmp;
                    smallest_loss_vec = vec;
                    smallett_loss_dir = 'd';
                }
            }
            // 2つずつ使う作戦 1225
            for (auto idx : unused_indices) {
                for (auto idx2 : unused_indices) {
                    if (!(idx > idx2)) {
                        break;
                    }
                    vector<int> vec = {idx, idx2};
                    int tmp;

                    Row rowr('r');
                    tmp = calc_loss_from_width_and_indices(
                        remain_width, vec, rowr, order_weight, false);
                    // cerr << tmp << endl;
                    if (tmp < smallest_loss) {
                        smallest_loss = tmp;
                        smallest_loss_vec = vec;
                        smallett_loss_dir = 'r';
                    }

                    Row rowd('d');
                    tmp = calc_loss_from_width_and_indices(
                        remain_height, vec, rowd, order_weight, false);
                    // cerr << tmp << endl;
                    if (tmp < smallest_loss) {
                        smallest_loss = tmp;
                        smallest_loss_vec = vec;
                        smallett_loss_dir = 'd';
                    }
                }
            }
            // 3つずつ使う作戦 4060
            if (N <= 30) {
                for (auto idx : unused_indices) {
                    for (auto idx2 : unused_indices) {
                        if (!(idx > idx2)) {
                            break;
                        }
                        for (auto idx3 : unused_indices) {
                            if (!(idx2 > idx3)) {
                                break;
                            }
                            vector<int> vec = {idx, idx2, idx3};
                            int tmp;

                            Row rowr('r');
                            tmp = calc_loss_from_width_and_indices(
                                remain_width, vec, rowr, order_weight, false);
                            // cerr << tmp << endl;
                            if (tmp < smallest_loss) {
                                smallest_loss = tmp;
                                smallest_loss_vec = vec;
                                smallett_loss_dir = 'r';
                            }

                            Row rowd('d');
                            tmp = calc_loss_from_width_and_indices(
                                remain_height, vec, rowd, order_weight, false);
                            // cerr << tmp << endl;
                            if (tmp < smallest_loss) {
                                smallest_loss = tmp;
                                smallest_loss_vec = vec;
                                smallett_loss_dir = 'd';
                            }
                        }
                    }
                }
            }
            // 4つずつ使う作戦 4845
            if (N <= 20) {
                for (auto idx : unused_indices) {
                    for (auto idx2 : unused_indices) {
                        if (!(idx > idx2)) {
                            break;
                        }
                        for (auto idx3 : unused_indices) {
                            if (!(idx2 > idx3)) {
                                break;
                            }
                            for (auto idx4 : unused_indices) {
                                if (!(idx3 > idx4)) {
                                    break;
                                }
                                vector<int> vec = {idx, idx2, idx3, idx4};
                                int tmp;

                                Row rowr('r');
                                tmp = calc_loss_from_width_and_indices(
                                    remain_width, vec, rowr, order_weight,
                                    false);
                                // cerr << tmp << endl;
                                if (tmp < smallest_loss) {
                                    smallest_loss = tmp;
                                    smallest_loss_vec = vec;
                                    smallett_loss_dir = 'r';
                                }

                                Row rowd('d');
                                tmp = calc_loss_from_width_and_indices(
                                    remain_height, vec, rowd, order_weight,
                                    false);
                                // cerr << tmp << endl;
                                if (tmp < smallest_loss) {
                                    smallest_loss = tmp;
                                    smallest_loss_vec = vec;
                                    smallett_loss_dir = 'd';
                                }
                            }
                        }
                    }
                }
            }
            // 5つずつ使う作戦 4368
            if (N <= 16) {
                for (auto idx : unused_indices) {
                    for (auto idx2 : unused_indices) {
                        if (!(idx > idx2)) {
                            break;
                        }
                        for (auto idx3 : unused_indices) {
                            if (!(idx2 > idx3)) {
                                break;
                            }
                            for (auto idx4 : unused_indices) {
                                if (!(idx3 > idx4)) {
                                    break;
                                }
                                for (auto idx5 : unused_indices) {
                                    if (!idx4 > idx5) {
                                        break;
                                    }
                                    vector<int> vec = {idx, idx2, idx3, idx4,
                                                       idx5};
                                    int tmp;

                                    Row rowr('r');
                                    tmp = calc_loss_from_width_and_indices(
                                        remain_width, vec, rowr, order_weight,
                                        false);
                                    // cerr << tmp << endl;
                                    if (tmp < smallest_loss) {
                                        smallest_loss = tmp;
                                        smallest_loss_vec = vec;
                                        smallett_loss_dir = 'r';
                                    }

                                    Row rowd('d');
                                    tmp = calc_loss_from_width_and_indices(
                                        remain_height, vec, rowd, order_weight,
                                        false);
                                    // cerr << tmp << endl;
                                    if (tmp < smallest_loss) {
                                        smallest_loss = tmp;
                                        smallest_loss_vec = vec;
                                        smallett_loss_dir = 'd';
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Row row(smallett_loss_dir);
            // cerr << row.dir << endl;
            if (smallett_loss_dir == 'r') {
                calc_loss_from_width_and_indices(
                    remain_width, smallest_loss_vec, row, order_weight, true);
                if (unused_indices.size() == smallest_loss_vec.size() &&
                    row.height < remain_height) {
                    // 最後の1つはすべてを埋める
                    row.height = remain_height;
                }
                remain_height -= row.height;
                if (remain_height < 0) {
                    return false;
                }
            } else {
                calc_loss_from_width_and_indices(
                    remain_height, smallest_loss_vec, row, order_weight, true);
                if (unused_indices.size() == smallest_loss_vec.size() &&
                    row.height < remain_width) {
                    // 最後の1つはすべてを埋める
                    row.height = remain_width;
                }
                remain_width -= row.height;
                if (remain_width < 0) {
                    return false;
                }
            }
            rows.push_back(row);
            rep(i, smallest_loss_vec.size()) {
                unused_indices.erase(smallest_loss_vec[i]);
            }
        }
        return true;
    }
    bool init_day_ul_fixed_order() {
        rows.clear();
        int remain_height = W;
        int remain_width = W;
        rep(i, N) {
            // repr(i, N) {
            int smallest_loss = imax;
            char smallett_loss_dir;
            vector<int> vec = {i}; // 後々複数個になるかも
            int tmp;

            Row rowr('r');
            tmp = calc_loss_from_width_and_indices(remain_width, vec, rowr, 0,
                                                   false);
            if (tmp < smallest_loss) {
                smallest_loss = tmp;
                smallett_loss_dir = 'r';
            }

            Row rowd('d');
            tmp = calc_loss_from_width_and_indices(remain_height, vec, rowd, 0,
                                                   false);
            if (tmp < smallest_loss) {
                smallest_loss = tmp;
                smallett_loss_dir = 'd';
            }
            Row row(smallett_loss_dir);
            // cerr << row.dir << endl;
            if (smallett_loss_dir == 'r') {
                calc_loss_from_width_and_indices(remain_width, vec, row, 0,
                                                 true);
                remain_height -= row.height;
                if (remain_height < 0) {
                    return false;
                }
            } else {
                calc_loss_from_width_and_indices(remain_height, vec, row, 0,
                                                 true);
                remain_width -= row.height;
                if (remain_width < 0) {
                    return false;
                }
            }
            rows.push_back(row);
        }

        return true;
    }
    void make_row_by_pack(char rows_dir, int use_height, int remain_width,
                          set<int> &remain_area_idx, int idx_dist_lim,
                          int fixed_head, bool last_one) {
        Row row(use_height, -1, rows_dir);
        vector<int> used_idx;
        vector<int> use_width(N);
        for (auto itr = remain_area_idx.rbegin(); itr != remain_area_idx.rend();
             itr++) {
            int idx = *itr;
            use_width[idx] = (a_day[idx] + use_height - 1) / use_height;
            if (use_width[idx] <= remain_width) {
                if (!used_idx.empty() && used_idx[0] - idx > idx_dist_lim) {
                    break;
                }
                remain_width -= use_width[idx];
                used_idx.push_back(idx);
                if (rows.size() < fixed_head) {
                    break;
                }
                // if (used_idx.size() == 3) {
                //     break;
                // }
                if (last_one && remain_area_idx.size() == used_idx.size() + 1) {
                    break;
                }
            }
        }
        rep(i, used_idx.size()) {
            row.columns.push_back(
                Column(used_idx[i], use_width[used_idx[i]], -1));
            remain_area_idx.erase(used_idx[i]);
        }
        rows.push_back(row);
    }
    void adjust_row_size(int row_size) {}
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
                    if (rows[i].loss > largeest_loss && rows[i].height > 1) {
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
    void get_partitions_ul(int &partition_length, int &area_loss,
                           map<int, set<pair<int, int>>> &right_partitions,
                           map<int, set<pair<int, int>>> &down_partitions) {
        map<int, set<pair<int, int>>> rps;
        map<int, set<pair<int, int>>> dps;
        int up = 0, left = 0;
        rep(i, rows.size()) {
            if (rows[i].dir == 'r') {
                int u = up;
                int d = u + rows[i].height;
                int l = left;
                rep(j, rows[i].columns.size()) {
                    int r = l + rows[i].columns[j].width;
                    if (j == rows[i].columns.size() - 1) {
                        r = W;
                    }
                    if (u != 0) {
                        rps[u].insert(make_pair(l, r));
                        partition_length += r - l;
                    }
                    if (l != 0) {
                        dps[l].insert(make_pair(u, d));
                        partition_length += d - u;
                    }
                    area_loss += 100 * (max(0, a_day[rows[i].columns[j].idx] -
                                                   (d - u) * (r - l)));
                    l = r;
                }
                up = d;
            } else {
                int l = left;
                int r = l + rows[i].height;
                int u = up;
                rep(j, rows[i].columns.size()) {
                    int d = u + rows[i].columns[j].width;
                    if (j == rows[i].columns.size() - 1) {
                        d = W;
                    }
                    if (u != 0) {
                        rps[u].insert(make_pair(l, r));
                        partition_length += r - l;
                    }
                    if (l != 0) {
                        dps[l].insert(make_pair(u, d));
                        partition_length += d - u;
                    }
                    area_loss += 100 * (max(0, a_day[rows[i].columns[j].idx] -
                                                   (d - u) * (r - l)));
                    u = d;
                }
                left = r;
            }
        }
        for (auto rp : rps) {
            bool idx_over_1 = false;
            pair<int, int> pa;
            int le = 0;
            rp.second.insert(make_pair(W + 1, -1));
            for (auto itv : rp.second) {
                if (idx_over_1) {
                    if (pa.second != itv.first) {
                        right_partitions[rp.first].insert(
                            make_pair(le, pa.second));
                        le = itv.first;
                    }
                } else {
                    le = itv.first;
                }
                pa = itv;
                idx_over_1 = true;
            }
        }
        for (auto dp : dps) {
            bool idx_over_1 = false;
            pair<int, int> pa;
            int le = 0;
            dp.second.insert(make_pair(W + 1, -1));
            for (auto itv : dp.second) {
                if (idx_over_1) {
                    if (pa.second != itv.first) {
                        down_partitions[dp.first].insert(
                            make_pair(le, pa.second));
                        le = itv.first;
                    }
                } else {
                    le = itv.first;
                }
                pa = itv;
                idx_over_1 = true;
            }
        }
    }

    void print_ans() {
        // cout << "print_ans: " << day << endl;
        vector<int> su(N);
        vector<int> sl(N);
        vector<int> sd(N);
        vector<int> sr(N);
        int u = 0, l, d, r;
        rep(i, rows.size()) {
            // d = rows[i].bottom_pos;
            d = min(int(W - (rows.size() - i - 1)),
                    rows[i].bottom_pos); // TODO: minなしにしたい
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
    void print_ans_by_ul() {
        vector<int> su(N);
        vector<int> sl(N);
        vector<int> sd(N);
        vector<int> sr(N);
        int up = 0, left = 0;
        rep(i, rows.size()) {
            if (rows[i].dir == 'r') {
                int u = up;
                int d = u + rows[i].height;
                int l = left;
                rep(j, rows[i].columns.size()) {
                    int r = l + rows[i].columns[j].width;
                    if (j == rows[i].columns.size() - 1) {
                        r = W;
                    }
                    su[rows[i].columns[j].idx] = u;
                    sl[rows[i].columns[j].idx] = l;
                    sd[rows[i].columns[j].idx] = d;
                    sr[rows[i].columns[j].idx] = r;
                    l = r;
                }
                up = d;
            } else {
                int l = left;
                int r = l + rows[i].height;
                int u = up;
                rep(j, rows[i].columns.size()) {
                    int d = u + rows[i].columns[j].width;
                    if (j == rows[i].columns.size() - 1) {
                        d = W;
                    }
                    su[rows[i].columns[j].idx] = u;
                    sl[rows[i].columns[j].idx] = l;
                    sd[rows[i].columns[j].idx] = d;
                    sr[rows[i].columns[j].idx] = r;
                    u = d;
                }
                left = r;
            }
        }
        rep(i, N) {
            cout << su[i] << " " << sl[i] << " " << sd[i] << " " << sr[i]
                 << endl;
        }
        // cerr << (W - left) * (W - up) SP << W - left SP << W - up <<
        // endl;
    }
    void print_rows() {
        rep(i, rows.size()) {
            cerr << "rows: " << i << "  height: " << rows[i].height
                 << " bottom_pos: " << rows[i].bottom_pos << endl;
            cerr << "  widths: ";
            rep(j, rows[i].columns.size()) {
                cerr << rows[i].columns[j].idx << " ";
            }
            cerr << endl;
        }
    }
};

struct Hall {
    ll hall_loss;
    vector<Day> days;

    void init() {
        hall_loss = lmax;
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
    void execute_largest_size() {
        vector<int> a_day = calc_days_max();
        Day day(-1, a_day);
        day.interval_dp();
        rep(i, D) { days[i] = day; }
    }
    void execute_annealing(int division) {
        rep(i, D) {
            days[i].init_day_fixed_division(division);
            days[i].adjsut_rows();
        }
        // cout << days[0].rows[days[0].rows.size() - 1].bottom_pos <<
        // endl; 各日のrowsの数はすべて同じ（変えない）前提で動く
        int row_length = days[0].rows.size();
        vector<double> row_height_aves(row_length);
        vector<vector<double>> row_height_distance_from_aves(row_length,
                                                             vector<double>(D));
        vector<double> row_height_variances(row_length);
        rep(lp, 100) {
            rep(i, row_length) {
                row_height_aves[i] = calc_rows_ave(i);
                row_height_variances[i] = calc_rows_variance_and_days_distance(
                    i, row_height_aves[i], row_height_distance_from_aves[i]);
                // cerr << "row: " << i SP << row_height_aves[i] SP
                //      << row_height_variances[i] << endl;
            }
            // 一番分散がデカいrowをどうにかする、遷移対象は同じdayに対して行う必要がある
            // PVV(row_height_distance_from_aves);
            // print_annealing();
            // PV(row_height_aves);

            rep(i, D) {
                days[i].optimize(row_height_aves);
                days[i].adjsut_rows();
            }

            // cerr << target_row_indices[0] SP << target_row_indices[1]
            // << endl;
        }
        arrange_height();
        rep(i, D) { days[i].adjsut_rows(false); }
        touch_right_and_bottom_all_days();
        // print_annealing();
    }
    bool execute_ul() {
        rep(i, D) {
            bool created = false;
            repr(j, 10) {
                days[i] = Day(i, a[i]);
                if (days[i].init_day_ul(-0.01 * j)) {
                    // cerr << -0.01 * j << endl;
                    created = true;
                    break;
                }
            }
            if (created == false) {
                return false;
            }
        }
        return true;
    }
    bool execute_ul_fixed() {
        rep(i, D) {
            if (!days[i].init_day_ul_fixed_order()) {
                return false;
            }
        }
        return true;
    }
    void slide_idx() {
        int max_row_size = 0;
        rep(i, D) {
            max_row_size = max(max_row_size, int(days[i].rows.size()));
        }
        rep(i, D) { days[i].adjust_row_size(max_row_size); }
    }
    bool execute_pack(int idx_dist_lim, int additional_length, int fixed_head,
                      bool last_one) {
        vector<set<int>> days_remain_area_idx(D);
        rep(i, D) {
            rep(j, N) { days_remain_area_idx[i].insert(j); }
        }
        int remain_height = W, remain_width = W;
        char rows_dir = 'r';
        bool remain_area = true;
        while (remain_area) {
            if (remain_height == 0 || remain_width == 0) {
                return false;
            }
            remain_area = false;
            int remain_max = -1;
            rep(i, D) {
                if (days_remain_area_idx[i].empty()) {
                    continue;
                }
                remain_area = true;
                int max_idx = *days_remain_area_idx[i].rbegin();
                remain_max = max(remain_max, a[i][max_idx]);
            }
            int use_height;
            if (rows_dir == 'r') {
                use_height = (remain_max + remain_width - 1) / remain_width;
            } else {
                use_height = (remain_max + remain_height - 1) / remain_height;
            }
            use_height += additional_length;
            rep(i, D) {
                if (days_remain_area_idx[i].empty()) {
                    continue;
                }
                if (rows_dir == 'r') {
                    days[i].make_row_by_pack(rows_dir, use_height, remain_width,
                                             days_remain_area_idx[i],
                                             idx_dist_lim, fixed_head,
                                             last_one);
                    if (days_remain_area_idx[i].empty() &&
                        days[i].rows[days[i].rows.size() - 1].height <
                            remain_height) {
                        // 最後の1つはすべてを埋める
                        days[i].rows[days[i].rows.size() - 1].height =
                            remain_height;
                    }
                } else {
                    days[i].make_row_by_pack(
                        rows_dir, use_height, remain_height,
                        days_remain_area_idx[i], idx_dist_lim, fixed_head,
                        last_one);
                    if (days_remain_area_idx[i].empty() &&
                        days[i].rows[days[i].rows.size() - 1].height <
                            remain_width) {
                        // 最後の1つはすべてを埋める
                        days[i].rows[days[i].rows.size() - 1].height =
                            remain_width;
                    }
                }
            }
            if (rows_dir == 'r') {
                remain_height -= use_height;
                if (remain_height < 0) {
                    return false;
                }
                rows_dir = 'd';
            } else {
                remain_width -= use_height;
                if (remain_width < 0) {
                    return false;
                }
                rows_dir = 'r';
            }
        }
        slide_idx();
        return true;
    }
    void make_perfect_ul() {
        vector<int> a_day = calc_days_max();
        Day day(-1, a_day);

        repr(i, 10) {
            if (day.init_day_ul(-0.01 * i)) {
                rep(i, D) { days[i] = day; }
                print_ans_by_ul();
                exit(0);
            }
        }
        init();
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
    int no_need_to_move_partition(map<int, set<pair<int, int>>> &partitions,
                                  map<int, set<pair<int, int>>> &partitions2) {
        int duplicate_sum = 0;
        for (auto partition : partitions) {
            int pos = partition.first;
            if (partitions2[pos].empty()) {
                continue;
            }
            for (auto itv : partition.second) {
                for (auto itv2 : partitions2[pos]) {
                    duplicate_sum += max(0, min(itv.second, itv2.second) -
                                                max(itv.first, itv2.first));
                }
            }
        }
        return duplicate_sum;
    }
    void calc_accurate_loss_ul() {
        // 面積不足はないものとする
        // 上、左から何マス目からスタートして何マス目まで存在している
        map<int, set<pair<int, int>>> right_partitions, down_partitions;
        map<int, set<pair<int, int>>> right_partitions2, down_partitions2;
        vector<int> partition_length(D);
        vector<int> area_loss(D);
        vector<int> partition_duplicate(D - 1); // i日目とi+1日目の間
        rep(i, D) {
            if (i % 2 == 0) {
                right_partitions.clear();
                down_partitions.clear();
                days[i].get_partitions_ul(partition_length[i], area_loss[i],
                                          right_partitions, down_partitions);
            } else {
                right_partitions2.clear();
                down_partitions2.clear();
                days[i].get_partitions_ul(partition_length[i], area_loss[i],
                                          right_partitions2, down_partitions2);
            }
            // 初日は設置コストが発生しない
            if (i >= 1) {
                partition_duplicate[i - 1] += no_need_to_move_partition(
                    right_partitions, right_partitions2);
                partition_duplicate[i - 1] += no_need_to_move_partition(
                    down_partitions, down_partitions2);
            }
        }
        int partition_loss_sum = 1;
        partition_loss_sum += area_loss[0];
        rep3(i, D, 1) {
            // 前日を撤去
            partition_loss_sum += partition_length[i - 1];
            // 当日を配置
            partition_loss_sum += partition_length[i];
            // 動かさなくてよかった部分は保持
            partition_loss_sum -= 2 * partition_duplicate[i - 1];
            // 面積不足ペナルティ
            partition_loss_sum += area_loss[i];
        }
        hall_loss = partition_loss_sum;
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
    int calc_max_height_sum() {
        int max_sum = 0;
        // すべての日でrowsの長さが同じであることを前提としている
        rep(i, days[0].rows.size()) {
            int ma = 0;
            rep(j, D) { ma = max(ma, days[j].rows[i].height); }
            max_sum += ma;
        }
        return max_sum;
    }
    double calc_rows_ave(int idx) {
        double row_height_sum = 0;
        rep(i, D) { row_height_sum += days[i].rows[idx].height; }
        return row_height_sum / D;
    }
    double calc_rows_variance_and_days_distance(int idx, double row_height_sum,
                                                vector<double> &days_distance) {
        double row_height_variance = 0;
        int tmp;
        rep(i, D) {
            tmp = (days[i].rows[idx].height - row_height_sum);
            days_distance[i] = tmp;
            row_height_variance += tmp * tmp;
        }
        return row_height_variance / D;
    }
    // 単純に上から各列の最大値まで下げる
    void arrange_height() {
        int row_size = days[0].rows.size();
        int sum_height = 0;
        rep(i, row_size) {
            int max_height = 0;
            for (int j = 0; j < D; j++) {
                max_height = max(max_height, days[j].rows[i].height);
            }
            for (int j = 0; j < D; j++) {
                days[j].rows[i].height = max_height;
            }
            sum_height += max_height;
            // cerr << max_height << endl;
        }
        // cout << sum_height << endl;
        // exit(0);
    }
    void print_ans() {
        rep(i, D) { days[i].print_ans(); }
    }
    void print_ans_by_ul() {
        rep(i, D) { days[i].print_ans_by_ul(); }
    }
    void
    print_annealing(/*vector<double> row_height_aves = {},
                    vector<vector<double>> row_height_distance_from_aves = {{}},
                    vector<double> row_height_variances = {}*/) {
        int row_size = days[0].rows.size();
        cerr << "row_heights" << endl;
        rep(i, row_size) {
            rep(j, D) { cerr << days[j].rows[i].height SP; }
            cerr << endl;
        }
        // cerr << "row_height_aves" << endl;
        // PV(row_height_aves);
        // cerr << "row_height_distance_from_aves" << endl;
        // PVV(row_height_distance_from_aves);
        // cerr << "row_height_variances" << endl;
        // PV(row_height_variances);
    }
    void touch_right_and_bottom_all_days() {
        rep(i, D) { days[i].touch_right_and_bottom(); }
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

    Hall perfect_ul;
    perfect_ul.init();
    // perfect_ul.make_perfect_ul();

    Hall best;
    best.hall_loss = lmax;

    // cerr << "execute_ul" << endl;
    rep(lp, 0) {
        Hall hall;
        hall.init();
        hall.execute_ul();
        hall.calc_accurate_loss_ul();
        // cerr << hall.hall_loss << endl;
        if (hall.hall_loss < best.hall_loss) {
            best = hall;
        }
    }

    // cerr << "execute_ul_fixed: " << i << endl;
    rep(lp, 0) {
        vector<int> days_max = calc_days_max();
        repr(i, N) {
            // N-1 -> 0, i個統一する
            Hall hall;
            hall.init();
            rep(j, D) {
                // j日目を操作
                rep(k, i + 1) {
                    // N-1からi個
                    hall.days[j].a_day[k] = days_max[k];
                    // hall.days[j].a_day[N - 1 - k] = days_max[N - 1 - k];
                }
            }
            if (hall.execute_ul_fixed()) {
                hall.calc_accurate_loss_ul();
                // cerr << hall.hall_loss << endl;
                if (hall.hall_loss < best.hall_loss) {
                    best = hall;
                }
            }
        }
    }

    // cerr << "execute_annealing" << endl;
    rep(lp, 0) {
        rep3(i, N, 1) {
            Hall hall;
            hall.init();
            hall.execute_annealing(i);
            hall.calc_accurate_loss_ul();
            // cerr << hall.hall_loss << endl;
            if (hall.hall_loss < best.hall_loss) {
                best = hall;
            }
        }
    }

    // cerr << "execute_interval_dp" << endl;
    rep(lp, 0) {
        Hall hall;
        hall.init();
        hall.execute_interval_dp();
        hall.calc_max_height_sum();
        // cerr << best.calc_max_height_sum() << endl;
        hall.calc_accurate_loss_ul();
        // cerr << hall.hall_loss << endl;
        if (hall.hall_loss < best.hall_loss) {
            best = hall;
        }
    }

    // cerr << "execute_fixed_division" << endl;
    rep(lp, 0) {
        rep(i, N) {
            Hall hall;
            hall.init();
            if (hall.execute_fixed_division(i + 1)) {
                hall.calc_accurate_loss_ul();
                // cerr << hall.hall_loss << endl;
                if (hall.hall_loss < best.hall_loss) {
                    best = hall;
                }
            }
        }
    }

    // cerr << "execute_pack_ul" << endl;
    rep(lp, 1) {
        rep(i, N) {
            // idx_dist_lim
            // rep(j, 10) {
            // additional_length
            rep(k, 4) {
                // fixed_head
                rep(l, 2) {
                    // last_one
                    Hall hall;
                    hall.init();
                    // if (hall.execute_pack(i, j * 10)) {
                    if (hall.execute_pack(i, 0, k, (l == 0))) {
                        hall.calc_accurate_loss_ul();
                        if (hall.hall_loss <= best.hall_loss) {
                            cerr << hall.hall_loss SP << i SP << k SP << l
                                 << endl;
                            best = hall;
                        }
                    }
                }
            }
            // }
        }
        Hall hall;
        hall.init();
        // if (hall.execute_pack(i, j * 10)) {
        if (hall.execute_pack(N, 0, 0, true)) {
            hall.calc_accurate_loss_ul();
            // cerr << hall.hall_loss << endl;
            if (hall.hall_loss < best.hall_loss) {
                best = hall;
            }
        }
    }

    // 今のところ効果なし
    // int loop = 0;
    // while (timer.progress() < 0.0) {
    //     loop++;
    //     Hall hall;
    //     hall.init();
    //     hall.execute_shuffle_interval_dp();
    //     hall.calc_accurate_loss_ul();
    //     if (hall.hall_loss < best.hall_loss) {
    //         best = hall;
    //         cerr << loop SP << timer.progress() SP << best.hall_loss <<
    //         endl;
    //     }
    // }
    // cerr << loop SP << timer.progress() << endl;
    // cerr << best.hall_loss << endl;
    best.print_ans_by_ul();

    return 0;
}
