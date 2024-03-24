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
        // N以上で最小の平方数にする
        int division = ceil(sqrt(N)) * ceil(sqrt(N));
        rows.resize(division);
        rep(i, division) { rows[i] = Row(W / division, (i + 1) * division); }
        rep(i, N) {
            rows[i % division].columns.push_back(
                Column(i, W / division, (i + 1) * division));
        } // 左上から正方形で敷き詰めていく
    }
    void tmp() {}

    void print_ans() {
        // cout << "print_ans: " << day << endl;
        vector<string> s(N);
    }
};

struct Hall {
    vector<Day> days;
    int cost;

    void init() {
        cost = 1;
        days.resize(D);
        rep(i, D) { days[i] = Day(i, a[i]); }
    }

    void tmp() {
        // rep(i, D) { days[i].tmp(); }
        days[0].init_day();
        days[0].tmp();
    }

    void print_ans() {
        rep(i, D) { days[i].print_ans(); }
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
    Hall hall;
    hall.init();
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
