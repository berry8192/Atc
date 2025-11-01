// Geometry 幾何ライブラリ 点・線分・円・多角形 計算幾何

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

// ========== ライブラリ部分 ==========

const double EPS = 1e-9;
const double PI = acos(-1.0);

// 誤差つき比較
bool equals(double a, double b) { return abs(a - b) < EPS; }
bool less_than(double a, double b) { return a < b - EPS; }
bool less_equal(double a, double b) { return a < b + EPS; }

// 点クラス
struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double t) const { return Point(x * t, y * t); }
    Point operator/(double t) const { return Point(x / t, y / t); }

    bool operator==(const Point& p) const { return equals(x, p.x) && equals(y, p.y); }
    bool operator<(const Point& p) const {
        return less_than(x, p.x) || (equals(x, p.x) && less_than(y, p.y));
    }

    double norm() const { return x * x + y * y; }
    double abs() const { return sqrt(norm()); }
    Point unit() const { return *this / abs(); }
    Point rotate(double theta) const {
        return Point(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
    }

    void print() const { cout << "(" << x << ", " << y << ")"; }
};

// 内積・外積
double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }

// 距離
double distance(const Point& a, const Point& b) { return (a - b).abs(); }

// 線分クラス
struct Segment {
    Point p1, p2;

    Segment(Point p1, Point p2) : p1(p1), p2(p2) {}

    Point vector() const { return p2 - p1; }
    double length() const { return vector().abs(); }
};

// 直線クラス
struct Line {
    Point p1, p2;

    Line(Point p1, Point p2) : p1(p1), p2(p2) {}

    Point vector() const { return p2 - p1; }
};

// 円クラス
struct Circle {
    Point center;
    double radius;

    Circle(Point c, double r) : center(c), radius(r) {}
};

// 多角形クラス
struct Polygon {
    vector<Point> points;

    Polygon(const vector<Point>& pts) : points(pts) {}

    int size() const { return points.size(); }
    Point& operator[](int i) { return points[i]; }
    const Point& operator[](int i) const { return points[i]; }
};

// CCW（Counter Clock Wise）判定
int ccw(const Point& a, const Point& b, const Point& c) {
    Point ba = a - b, bc = c - b;
    double cross_product = cross(ba, bc);
    if (cross_product > EPS) return 1;      // 反時計回り
    if (cross_product < -EPS) return -1;    // 時計回り
    return 0;                               // 直線上
}

// 点と線分の関係
double point_to_segment_distance(const Point& p, const Segment& seg) {
    Point v = seg.vector();
    Point w = p - seg.p1;

    double t = dot(w, v) / v.norm();
    t = max(0.0, min(1.0, t));

    Point closest = seg.p1 + v * t;
    return distance(p, closest);
}

// 線分の交差判定
bool segments_intersect(const Segment& s1, const Segment& s2) {
    int ccw1 = ccw(s1.p1, s1.p2, s2.p1);
    int ccw2 = ccw(s1.p1, s1.p2, s2.p2);
    int ccw3 = ccw(s2.p1, s2.p2, s1.p1);
    int ccw4 = ccw(s2.p1, s2.p2, s1.p2);

    return ccw1 * ccw2 <= 0 && ccw3 * ccw4 <= 0;
}

// 直線の交点
Point line_intersection(const Line& l1, const Line& l2) {
    Point v1 = l1.vector(), v2 = l2.vector();
    double cross_v = cross(v1, v2);

    if (equals(cross_v, 0)) {
        // 平行線の場合
        return Point(1e9, 1e9);  // 無限遠点を表す
    }

    Point w = l2.p1 - l1.p1;
    double t = cross(w, v2) / cross_v;
    return l1.p1 + v1 * t;
}

// 点の多角形内外判定
bool point_in_polygon(const Point& p, const Polygon& poly) {
    int n = poly.size();
    bool inside = false;

    for (int i = 0; i < n; i++) {
        Point a = poly[i];
        Point b = poly[(i + 1) % n];

        if (a.y > b.y) swap(a, b);

        if (a.y <= p.y && p.y < b.y) {
            double cross_product = cross(b - a, p - a);
            if (cross_product > 0) inside = !inside;
        }
    }

    return inside;
}

// 多角形の面積
double polygon_area(const Polygon& poly) {
    int n = poly.size();
    double area = 0;

    for (int i = 0; i < n; i++) {
        area += cross(poly[i], poly[(i + 1) % n]);
    }

    return abs(area) / 2.0;
}

// 凸包（Graham Scan）
Polygon convex_hull(vector<Point> points) {
    int n = points.size();
    if (n <= 1) return Polygon(points);

    sort(points.begin(), points.end());

    // 下半分
    vector<Point> hull;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && ccw(hull[hull.size()-2], hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // 上半分
    int lower_size = hull.size();
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_size && ccw(hull[hull.size()-2], hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    hull.pop_back();  // 最初の点の重複を削除
    return Polygon(hull);
}

// 円と点の関係
int point_circle_relation(const Point& p, const Circle& c) {
    double d = distance(p, c.center);
    if (d < c.radius - EPS) return 1;      // 内部
    if (d > c.radius + EPS) return -1;     // 外部
    return 0;                              // 円周上
}

// 円と直線の交点
vector<Point> circle_line_intersection(const Circle& c, const Line& l) {
    vector<Point> result;
    Point v = l.vector().unit();
    Point w = l.p1 - c.center;

    double a = 1.0;
    double b = 2.0 * dot(v, w);
    double det = b * b - 4.0 * a * (w.norm() - c.radius * c.radius);

    if (det < -EPS) return result;  // 交点なし

    if (det < EPS) {
        // 接触
        double t = -b / (2.0 * a);
        result.push_back(l.p1 + v * t);
    } else {
        // 2点で交差
        double sqrt_det = sqrt(det);
        double t1 = (-b - sqrt_det) / (2.0 * a);
        double t2 = (-b + sqrt_det) / (2.0 * a);
        result.push_back(l.p1 + v * t1);
        result.push_back(l.p1 + v * t2);
    }

    return result;
}

// ========== サンプルコード ==========

int main() {
    cout << fixed << setprecision(6);

    // 例1: 基本的な点の操作
    cout << "例1: 基本的な点の操作" << endl;
    Point p1(3, 4);
    Point p2(1, 2);

    cout << "p1 = "; p1.print(); cout << endl;
    cout << "p2 = "; p2.print(); cout << endl;
    cout << "p1 + p2 = "; (p1 + p2).print(); cout << endl;
    cout << "p1 - p2 = "; (p1 - p2).print(); cout << endl;
    cout << "距離 = " << distance(p1, p2) << endl;
    cout << "内積 = " << dot(p1, p2) << endl;
    cout << "外積 = " << cross(p1, p2) << endl;
    cout << endl;

    // 例2: 線分の交差判定
    cout << "例2: 線分の交差判定" << endl;
    Segment seg1(Point(0, 0), Point(2, 2));
    Segment seg2(Point(0, 2), Point(2, 0));
    Segment seg3(Point(3, 0), Point(4, 1));

    cout << "線分1: (0,0)-(2,2)" << endl;
    cout << "線分2: (0,2)-(2,0)" << endl;
    cout << "線分3: (3,0)-(4,1)" << endl;
    cout << "線分1と線分2の交差: " << (segments_intersect(seg1, seg2) ? "Yes" : "No") << endl;
    cout << "線分1と線分3の交差: " << (segments_intersect(seg1, seg3) ? "Yes" : "No") << endl;
    cout << endl;

    // 例3: 直線の交点
    cout << "例3: 直線の交点" << endl;
    Line line1(Point(0, 0), Point(1, 1));
    Line line2(Point(0, 1), Point(1, 0));

    Point intersection = line_intersection(line1, line2);
    cout << "直線1: (0,0)を通り方向(1,1)" << endl;
    cout << "直線2: (0,1)を通り方向(1,-1)" << endl;
    cout << "交点: "; intersection.print(); cout << endl;
    cout << endl;

    // 例4: 多角形と点の内外判定
    cout << "例4: 多角形と点の内外判定" << endl;
    vector<Point> square_points = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    Polygon square(square_points);

    vector<Point> test_points = {Point(1, 1), Point(3, 3), Point(0, 0), Point(1, 0)};

    cout << "正方形: (0,0), (2,0), (2,2), (0,2)" << endl;
    for (const Point& p : test_points) {
        bool inside = point_in_polygon(p, square);
        cout << "点"; p.print(); cout << ": " << (inside ? "内部" : "外部") << endl;
    }
    cout << endl;

    // 例5: 多角形の面積
    cout << "例5: 多角形の面積" << endl;
    cout << "正方形の面積: " << polygon_area(square) << endl;

    vector<Point> triangle_points = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Polygon triangle(triangle_points);
    cout << "三角形の面積: " << polygon_area(triangle) << endl;
    cout << endl;

    // 例6: 凸包
    cout << "例6: 凸包" << endl;
    vector<Point> random_points = {
        Point(0, 0), Point(1, 1), Point(0, 2), Point(-1, 1),
        Point(0.5, 0.5), Point(1, 0), Point(0, 1)
    };

    cout << "点集合: ";
    for (const Point& p : random_points) {
        p.print(); cout << " ";
    }
    cout << endl;

    Polygon hull = convex_hull(random_points);
    cout << "凸包: ";
    for (int i = 0; i < hull.size(); i++) {
        hull[i].print(); cout << " ";
    }
    cout << endl;
    cout << "凸包の面積: " << polygon_area(hull) << endl;
    cout << endl;

    // 例7: 円と点の関係
    cout << "例7: 円と点の関係" << endl;
    Circle circle(Point(0, 0), 2);
    vector<Point> circle_test_points = {Point(0, 0), Point(1, 1), Point(2, 0), Point(3, 0)};

    cout << "円: 中心(0,0), 半径2" << endl;
    for (const Point& p : circle_test_points) {
        int relation = point_circle_relation(p, circle);
        cout << "点"; p.print(); cout << ": ";
        if (relation == 1) cout << "内部";
        else if (relation == 0) cout << "円周上";
        else cout << "外部";
        cout << endl;
    }
    cout << endl;

    // 例8: 円と直線の交点
    cout << "例8: 円と直線の交点" << endl;
    Line test_line(Point(-3, 0), Point(3, 0));  // x軸
    auto intersections = circle_line_intersection(circle, test_line);

    cout << "円: 中心(0,0), 半径2" << endl;
    cout << "直線: x軸" << endl;
    cout << "交点数: " << intersections.size() << endl;
    for (const Point& p : intersections) {
        cout << "交点: "; p.print(); cout << endl;
    }

    return 0;
}