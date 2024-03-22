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
int a[50][50];

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

struct Point {
    int h;
    int w;

    Point(){};
    Point(int hh, int ww) {
        h = hh;
        w = ww;
        assert(h >= 0 && w >= 0);
        assert(h <= HEIGHT && w <= WIDTH); // 今回は等号でもOK
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h <= HEIGHT && 0 <= w && w <= WIDTH);
    }
    int manhattan(Point pos) { return abs(h - pos.h) + abs(w - pos.w); }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPointを作る
    vector<Point> around_pos(const vector<Point> &dir) {
        vector<Point> rtn;
        Point new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Point &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Point &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Point operator+(const Point pos) {
        Point rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Point operator-(const Point pos) {
        Point rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};

struct Rectangle {
    Point lu;
    Point rd;
    int h;
    int w;

    Rectangle(){};
    Rectangle(Point ilu, Point ird) {
        lu = ilu;
        rd = ird;
        h = rd.h - lu.h + 1;
        w = rd.w - lu.w + 1;
    }
    Rectangle(Point ilu, int ih, int iw) {
        lu = ilu;
        rd = {ilu.h + ih - 1, ilu.w + iw - 1};
        h = rd.h - ilu.h + 1;
        w = rd.w - ilu.w + 1;
    }

    bool is_overlap(Rectangle rec) {
        // 長方形が重なっていたらtrueを返す
        if (rec.rd.h <= lu.h || rd.h <= rec.lu.h || rec.rd.w <= lu.w ||
            rd.w <= rec.lu.w)
            return false;
        else
            return true;
    }

    void print() {
        cout << lu.h << " " << lu.w << " " << rd.h << " " << rd.w << endl;
    }
};

struct Grid {
    vector<vector<Rectangle>> ans; // 各日の置き方を保存する

    bool fill_all_one_day(int day) {
        vector<Rectangle> rects; // 置かれている長方形
        set<Point> lu_points;    // 左上角の場所
        lu_points.insert({0, 0});

        int i = day;
        double time_bonus = 1.0 - 5.0 * max(timer.progress() - 0.90, 0.0);
        // デカいものから置いていく
        repr(j, N) {
            int sz = lu_points.size();
            int area = max(1.0, ceil(a[i][j] * time_bonus));
            Rectangle rec;
            bool rec_ok = false;
            int loop = sqrt(area) * 10;
            rep(lp, loop) {
                int idx = rand(0, sz - 1);
                auto itr = lu_points.begin();
                rep(k, idx) itr++;
                Point lu_point = *itr;
                int maxh = min(W - lu_point.h, area);
                int maxw = min(W - lu_point.w, area);
                if (maxh <= 0 || maxw <= 0) {
                    continue;
                }
                int minh = (area + maxw - 1) / maxw;

                if (maxh < minh) {
                    continue;
                }
                int height = rand(minh, maxh);
                int width = (area + height - 1) / height;

                assert(lu_point.h + height <= W); // 引っ掛からないはず
                assert(lu_point.w + width <= W);  // 引っ掛からないはず
                Point rd_point = {lu_point.h + height, lu_point.w + width};
                rec = Rectangle(lu_point, rd_point);
                bool overlapped = false;
                rep(k, rects.size()) {
                    if (rec.is_overlap(rects[k])) {
                        overlapped = true;
                        break;
                    }
                }
                if (!overlapped) {
                    rec_ok = true;
                    rects.push_back(rec);
                    lu_points.erase(itr);
                    lu_points.insert({lu_point.h + height, lu_point.w});
                    lu_points.insert({lu_point.h, lu_point.w + width});
                    break;
                }
            }
            if (!rec_ok) {
                return false;
            }
        }
        reverse(all(rects));
        ans[day] = rects;
        return true;
    }
    void fill_all() {
        ans.resize(D);
        set<int> rest_days;
        rep(i, D) rest_days.insert(i);
        // cout << timer.progress() << endl;
        rep(lp, 500) {
            vector<int> clear_days;
            for (auto day : rest_days) {
                if (fill_all_one_day(day)) {
                    clear_days.push_back(day);
                }
            }
            rep(i, clear_days.size()) { rest_days.erase(clear_days[i]); }
            if (rest_days.empty()) {
                print_ans();
                exit(0);
            }
        }
    }

    void print_ans() {
        rep(i, ans.size()) {
            rep(j, ans[i].size()) { ans[i][j].print(); }
        }
    }
};

void inpt() {
    cin >> W >> D >> N;
    HEIGHT = W;
    WIDTH = W;
    rep(i, D) {
        rep(j, N) { cin >> a[i][j]; }
    }
}

void median_ans() {
    // i番目に大きいブースを要求する団体の中央値で仕切りを固定してしまう
    vector<vector<int>> tmp(N, vector<int>(D));
    vector<int> med(N);
    rep(i, N) {
        rep(j, D) { tmp[i][j] = a[j][i]; }
        sort(tmp[i].begin(), tmp[i].end());
        // PV(tmp[i]);
    }
    int su = 0;
    rep(i, N) {
        med[i] = tmp[i][D / 2];
        su += med[i];
    }
    rep(i, N) { med[i] = floor(1.0 * W * med[i] / su); }
    // PV(med);
    vector<int> ans = ruiseki(med);
    ans[N] = W;
    rep(i, N) {
        if (ans[i] >= ans[i + 1]) {
            ans[i + 1]++;
        }
    }
    // PV(ans);
    rep(i, D) {
        rep(j, N) { cout << 0 SP << ans[j] SP << W SP << ans[j + 1] << endl; }
    }
    exit(0);
}

int main() {
    inpt();

    int loop = 0;
    while (1) {
        if (timer.progress() > 1.0)
            break;
        loop++;
        Grid grid;
        grid.fill_all();
        // cout << loop SP << timer.progress() << endl;
    }

    return 0;
}
