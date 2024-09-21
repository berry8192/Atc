#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

// 直線を表す構造体
struct Line {
    ll slope, intercept; // y = slope * x + intercept

    Line(ll slope, ll intercept) : slope(slope), intercept(intercept) {}

    // 交点を計算するための関数
    ll value_at(ll x) const { return slope * x + intercept; }
};

// Convex Hull Trick (単調減少のxに対して最大のyを求める)
class ConvexHullTrick {
  public:
    vector<Line> hull;

    // 傾きが単調に減少するなら、新しい直線が不要になるかどうかを判断
    bool bad(const Line &l1, const Line &l2, const Line &l3) {
        return (l3.intercept - l1.intercept) * (l1.slope - l2.slope) <
               (l2.intercept - l1.intercept) * (l1.slope - l3.slope);
    }

    // 直線を追加する
    void add_line(ll slope, ll intercept) {
        Line new_line(slope, intercept);
        while (hull.size() >= 2 &&
               bad(hull[hull.size() - 2], hull[hull.size() - 1], new_line)) {
            hull.pop_back();
        }
        hull.push_back(new_line);
    }

    // xに対して最大のyを求める（二分探索）
    ll query(ll x) {
        int low = 0, high = hull.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (hull[mid].value_at(x) >= hull[mid + 1].value_at(x)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return hull[low].value_at(x);
    }
};

// 格子点を数える関数
ll count_lattice_points(vector<pair<ll, ll>> &lines) {
    ConvexHullTrick cht;

    // 傾きが減少順になるようにソート (xx/yyの順で処理)
    sort(lines.begin(), lines.end(),
         [](const pair<ll, ll> &a, const pair<ll, ll> &b) {
             return a.first * b.second < b.first * a.second;
         });

    // 各直線をCHTに追加
    for (auto &p : lines) {
        ll xx = p.first, yy = p.second;
        if (xx != 0) {
            cht.add_line(-yy, yy);
        }
    }

    ll count = 0;

    // 各格子点に対して直線の条件を確認
    for (ll x = 0; x <= lines[0].first; ++x) {
        ll max_y = cht.query(x);
        count += max_y + 1; // 各xに対してyが0からmax_yまでの格子点を数える
    }

    return count;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<ll, ll>> lines(n);

    // 直線のx軸、y軸との交点を入力
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        lines[i].first = c / a;
        lines[i].second = c / b;
    }

    ll result = count_lattice_points(lines);
    cout << result << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
