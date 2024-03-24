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
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 2700.0;
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

    Row() {}
    Row(int iheight, int ibottom_pos) {
        height = iheight;
        bottom_pos = ibottom_pos;
    }

    // ロスのない最小の高さにする
    void adjust_row(vector<int> &a_day) {
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
    void adjsut_rows() {
        // cout << "adjsut_rows" << endl;
        int height_sum = 0;
        rep(i, rows.size()) {
            rows[i].adjust_row(a_day); // この中でrows[i].heightが書き換わる
            height_sum += rows[i].height;
            rows[i].bottom_pos = height_sum;
        }
    }
    void touch_bottom() {
        int diff = W - rows[rows.size() - 1].bottom_pos;
        rows[rows.size() - 1].height += diff;
        rows[rows.size() - 1].bottom_pos = W;
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
                d = W;
            }
            l = 0;
            rep(j, rows[i].columns.size()) {
                r = rows[i].columns[j].right_pos;
                // TODO: right_pos側をWに合わせる
                if (j == rows[i].columns.size() - 1) {
                    r = W;
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
    vector<Day> days;

    void init() {
        days.resize(D);
        rep(i, D) { days[i] = Day(i, a[i]); }
    }

    void execute() {
        rep(i, D) {
            days[i].init_day();
            days[i].adjsut_rows();
            days[i].touch_right_and_bottom();
        }
    }
    // 厳密な計算ではないが、横線の数が違う場合は適当にコストを増やす
    // 右端と下端はWになっているものとしている
    ll calc_partition_loss(int day) {
        assert(day != 0);
        ll loss = 0;
        if (days[day - 1].rows.size() != days[day].rows.size()) {
            return 1000000000000000;
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
    ll calc_loss() {
        ll loss = 1;
        rep(i, D) {
            loss += calc_day_loss(i);
            cerr << "day: " << i SP << loss << endl;
        }
        return loss;
    }

    void print_ans() {
        rep(i, D) { days[i].print_ans(); }
    }

    void output_false_ans_exit() {
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

    Hall hall;
    hall.init();
    hall.execute();
    // hall.output_false_ans_exit();
    cerr << hall.calc_loss() << endl;
    hall.print_ans();
    return 0;

    int loop = 0;
    while (1) {
        if (timer.progress() > 1.0)
            break;
        loop++;
        // cout << loop SP << timer.progress() << endl;
    }

    return 0;
}
