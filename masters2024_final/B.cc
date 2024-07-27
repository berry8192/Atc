#include <bits/stdc++.h>
// #include <atcoder/all>
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
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

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

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N, M;
double eps, del;

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

struct Pos {
    int x;
    int y;

    Pos(){};
    Pos(int xx, int yy) {
        x = xx;
        y = yy;
    }

    // bool is_oob() {
    //     // assert(0<=h);
    //     // assert(h<n);
    //     // assert(0<=w);
    //     // assert(w<=h);
    //     return !(0 <= h && h < n && 0 <= w && w < n);
    // }
    int dist(Pos pos) {
        return int(sqrt((1LL * x - pos.x) * (x - pos.x) +
                        (1LL * y - pos.y) * (y - pos.y)));
    }
    // 長さlenと角度ang(ラジアン)からPosを計算
    void calc_pos_from_length_and_angle(int len, double ang, Pos &pos) {
        pos.x = len * cos(ang);
        pos.y = len * sin(ang);
        // cerr << pos.x SP << pos.y << endl;
    }
    // aim_posまでの距離と角度を計算する
    void calc_length_and_angle_from_poses(int &len, double &ang,
                                          const Pos &aim_pos) {
        int dx = aim_pos.x - x;
        int dy = aim_pos.y - y;
        len = dist(aim_pos);
        ang = atan2(dy, dx);
    }
    int pos_abs() { return int(sqrt((1LL * x) * (x) + (1LL * y) * (y))); }
    void print() { cerr << "(" << x << ", " << y << ")" << endl; }

    bool operator<(const Pos &in) const {
        return x != in.x ? x < in.x : y < in.y;
    };
    bool operator==(const Pos &cpos) const {
        return (x == cpos.x && y == cpos.y);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.x = x + pos.x;
        rtn.y = y + pos.y;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.x = x - pos.x;
        rtn.y = y - pos.y;
        return rtn;
    }
};
Pos S;
vector<Pos> P;

struct Wall {
    Pos l;
    Pos r;

    Wall() {}
    Wall(Pos _l, Pos _r) {
        l = _l;
        r = _r;
    }
};
vector<Wall> W;

void turn_end(bool &c, int &h, vector<int> &q) {
    int cc;
    cin >> cc;
    c = cc;
    cin >> h;
    if (h == 0)
        return;
    rep(i, h) cin >> q[i];
}

void acceleration(Pos pos) { cout << "A " << pos.x SP << pos.y << endl; }

int search(Pos pos) {
    cout << "S " << pos.x SP << pos.y << endl;
    int tmp;
    cin >> tmp;
    return tmp;
}

vector<int> make_rooting() {
    vector<int> idx(N);
    iota(idx.begin(), idx.end(), 0);

    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1));
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            long long temp = P[i].dist(P[j]);

            dist[i][j] = temp;
            dist[j][i] = temp;
        }
    }

    long long best_score = 1LL << 60;

    vector<int> best;

    do {
        long long sum = S.dist(P[idx[0]]);
        for (int i = 0; i < N - 1; i++) {
            sum += dist[idx[i]][idx[i + 1]];
        }
        if (chmin(best_score, sum))
            best = idx;
    } while (next_permutation(idx.begin(), idx.end()));
    return best;
}
/**
   @brief 線分と点の距離を計算する。
   @param line 線分
   @param point 点
   @return ユークリッド距離
 */
double k_calc_dist(Pos p, Pos l, Pos r) {
    double x0 = p.x, y0 = p.y;
    double x1 = l.x, y1 = l.y;
    double x2 = r.x, y2 = r.y;

    double a = x2 - x1;
    double b = y2 - y1;
    double a2 = a * a;
    double b2 = b * b;
    double r2 = a2 + b2;
    double tt = -(a * (x1 - x0) + b * (y1 - y0));

    if (tt < 0)
        return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    else if (tt > r2)
        return sqrt((x2 - x0) * (x2 - x0) + (y2 - y0) * (y2 - y0));

    double f1 = a * (y1 - y0) - b * (x1 - x0);
    return sqrt((f1 * f1) / r2);
}

bool cross_check(double ax, double ay, double bx, double by, double cx,
                 double cy, double dx, double dy) {
    double ta = (cx - dx) * (ay - cy) + (cy - dy) * (cx - ax);
    double tb = (cx - dx) * (by - cy) + (cy - dy) * (cx - bx);
    double tc = (ax - bx) * (cy - ay) + (ay - by) * (ax - cx);
    double td = (ax - bx) * (dy - ay) + (ay - by) * (ax - dx);

    return tc * td < 0 && ta * tb < 0;
}

pair<double, double> k_get_pos(int i) {
    if (i < N) {
        return make_pair(1.0 * P[i].x, 1.0 * P[i].y);
    } else if (i < N + 2 * M) {
        int x = (i - N) / 2, y = (i - N) & 1;
        if (y) {
            return make_pair(1.0 * W[x].r.x, 1.0 * W[x].r.y);
        } else {
            return make_pair(1.0 * W[x].l.x, 1.0 * W[x].l.y);
        }
    } else {
        return make_pair(1.0 * S.x, 1.0 * S.y);
    }
}

Pos k_get_pos_id(int i) {
    if (i < N) {
        return P[i];
    } else if (i < N + 2 * M) {
        int x = (i - N) / 2, y = (i - N) & 1;
        if (y) {
            return W[x].r;
        } else {
            return W[x].l;
        }
    } else {
        return S;
    }
}

vector<Pos> k_make_root() {
    int K = N + 2 * M + 1;
    double inf = 10000000000.0;
    vector<vector<double>> w(K, vector<double>(K, inf));
    for (int i = 0; i < K; i++)
        w[i][i] = 0.0;

    // 付近に壁があるか
    vector<int> near_wall(K, 0);
    for (int i = 0; i < M; i++) {
        bool flag = false;
        for (int j = 0; j < M; j++) {
            if (i == j)
                continue;
            {
                Pos p = W[i].l;
                Pos l = W[j].l, r = W[j].r;
                if (k_calc_dist(p, l, r) < 100) {
                    near_wall[2 * i + N] = 1;
                }
            }
            {
                Pos p = W[i].r;
                Pos l = W[j].l, r = W[j].r;
                if (k_calc_dist(p, l, r) < 100) {
                    near_wall[2 * i + 1 + N] = 1;
                }
            }
        }
        int haji = 100000;
        vector<pair<Pos, Pos>> ps = {
            make_pair(Pos(-haji, -haji), Pos(-haji, haji)),
            make_pair(Pos(-haji, haji), Pos(haji, haji)),
            make_pair(Pos(haji, haji), Pos(haji, -haji)),
            make_pair(Pos(haji, -haji), Pos(-haji, -haji)),
        };
        for (auto &[l, r] : ps) {
            {
                Pos p = W[i].l;
                if (k_calc_dist(p, l, r) < 100) {
                    near_wall[2 * i + N] = 1;
                }
            }
            {
                Pos p = W[i].r;
                if (k_calc_dist(p, l, r) < 100) {
                    near_wall[2 * i + 1 + N] = 1;
                }
            }
        }
    }
    // iからjへ交差せずにまっすぐ進めるか
    for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
            auto [ax, ay] = k_get_pos(i);
            auto [bx, by] = k_get_pos(j);

            // 線分の長さを両端から少し縮める
            double gx = bx - ax, gy = by - ay, g = sqrt(gx * gx + gy * gy);
            double e = 0.01;
            gx /= g;
            gy /= g;
            ax += gx * e;
            ay += gy * e;
            bx -= gx * e;
            by -= gy * e;

            bool flag = true;
            for (int k = 0; k < M; k++) {
                double cx = W[k].l.x, cy = W[k].l.y;
                double dx = W[k].r.x, dy = W[k].r.y;

                if (cross_check(ax, ay, bx, by, cx, cy, dx, dy)) {
                    flag = false;
                    break;
                }
            }

            if (flag and near_wall[i] + near_wall[j] == 0)
                w[i][j] = w[j][i] = g;
        }
    }

    vector<vector<double>> ww(w);
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++)
            for (int k = 0; k < K; k++) {
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
            }

    int Z = N + 1;
    vector<vector<double>> dist(Z, vector<double>(Z, inf));
    for (int i = 0; i < Z; i++)
        for (int j = 0; j < Z; j++) {
            int k = j, l = i;
            if (l == N)
                l = N + 2 * M;
            if (k == N)
                k = N + 2 * M;

            dist[i][j] = w[l][k];
        }

    vector<vector<double>> dp(1 << Z, vector<double>(Z, inf));
    dp[1 << (Z - 1)][N] = 0;
    for (int s = 0; s < (1 << Z); s++)
        for (int v = 0; v < Z; v++) {
            if (dp[s][v] > inf - 100)
                continue;
            for (int to = 0; to < Z; to++) {
                if ((s >> to) & 1)
                    continue;
                chmin(dp[s | (1 << to)][to], dp[s][v] + dist[v][to]);
            }
        }

    double mn = inf;
    int id = -1, state = (1 << Z) - 1;
    for (int i = 0; i < Z; i++)
        if (chmin(mn, dp[(1 << Z) - 1][i]))
            id = i;

    vector<int> path1{id};
    while (path1.size() < Z) {
        for (int to = 0; to < Z; to++) {
            if (((state >> to) & 1) == 0)
                continue;
            int prev = state ^ (1 << id);
            if (abs(dp[state][id] - dp[prev][to] - dist[to][id]) < 1) {
                id = to;
                state = prev;
                path1.push_back(id);
                break;
            }
        }
    }
    path1.pop_back();
    reverse(path1.begin(), path1.end());

    vector<Pos> pathpath[Z][Z];
    for (int i = 0; i < Z; i++) {
        int X = i;
        if (i == N)
            X = K - 1;
        vector<double> mindist(K, inf);
        queue<pair<int, double>> q;

        auto push = [&](int v, double cost) {
            if (chmin(mindist[v], cost))
                q.emplace(v, cost);
        };

        push(X, 0.0);
        while (!q.empty()) {
            auto [v, cost] = q.front();
            q.pop();
            for (int to = 0; to < K; to++) {
                if (to == v)
                    continue;
                push(to, cost + ww[v][to]);
            }
        }

        vector<int> where(K, -1);
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                if (j == k)
                    continue;
                if (abs(mindist[j] - mindist[k] - ww[k][j]) < 1) {
                    where[j] = k;
                    break;
                }
            }
        }

        for (int to = 0; to < Z; to++) {
            if (i == to)
                continue;
            int now = to == N ? K - 1 : to;
            vector<Pos> tmp{k_get_pos_id(now)};
            while (where[now] != -1) {
                Pos p = k_get_pos_id(where[now]);
                tmp.push_back(p);
                now = where[now];
            }
            reverse(tmp.begin(), tmp.end());
            pathpath[i][to] = tmp;
        }
    }
    int now = Z - 1;
    vector<Pos> path2;
    for (int to : path1) {
        vector<Pos> tmp = pathpath[now][to];
        path2.insert(path2.end(), tmp.begin() + 1, tmp.end());
        now = to;
    }

    return path2;
}

struct Field {
    vector<Pos> p_order;
    vector<bool> visited;
    int rest_hand = 5000;

    void init() {}

    void calc_p_order() {
        p_order = k_make_root();
        visited.resize(p_order.size(), false);
    }
    int calc_acceleration_kaisuu(int dist) {
        // return ceil(sqrt(dist) / 10);
        rep3(lp, 1000, 1) {
            // cerr << lp * lp * 500 + lp * 5000 << endl;
            if (lp * lp * 500 + lp * 5000 > dist) {
                return lp;
            }
        }
    }
    void visit_pos(Pos &drone_pos, Pos &drone_speed, const Pos &aim_pos) {
        int rest_dist;
        double aim_angle;
        double first_aim_angle;
        drone_pos.calc_length_and_angle_from_poses(rest_dist, aim_angle,
                                                   aim_pos);
        first_aim_angle = aim_angle;
        // 加速フェーズ
        int acceleration_kaisuu = calc_acceleration_kaisuu(rest_dist);
        // cerr << rest_dist SP << acceleration_kaisuu << endl;
        // exit(0);
        int acceleration_exec_kaisuu = acceleration_kaisuu;
        rep(lp, acceleration_kaisuu) {
            if (rest_hand <= 0) {
                exit(0);
            }
            rest_hand--;
            Pos add_speed;
            drone_pos.calc_pos_from_length_and_angle(min(499, rest_dist / 12),
                                                     aim_angle, add_speed);
            acceleration(add_speed);

            bool c;
            int h;
            vector<int> q(N);
            turn_end(c, h, q);
            drone_speed = drone_speed + add_speed;
            if (c) {
                drone_speed = {0, 0};
            } else {
                drone_pos = drone_pos + drone_speed;
                if (h > 0) {
                    rep(i, N) {
                        visited[q[i]] = true;
                        if (P[q[i]] == aim_pos) {
                            acceleration_exec_kaisuu = lp;
                            // lp = 10000;
                        }
                    }
                }
            }
        }

        if (acceleration_exec_kaisuu == acceleration_kaisuu) {
            // 巡行フェーズ
            int going_kaisuu = 10;
            vector<int> search_result_x, search_result_y, speed_suitei_x,
                speed_suitei_y;
            rep(i, going_kaisuu) {
                if (rest_hand <= 0) {
                    exit(0);
                }
                rest_hand--;
                if (i % 2 == 0) {
                    // 奇数回目はxについて計測
                    if (drone_pos.x >= 0) {
                        // 近い方の壁に向かって計測
                        search_result_x.push_back(100000 - search({1, 0}));
                    } else {
                        search_result_x.push_back(search({-1, 0}) - 100000);
                    }
                } else {
                    if (drone_pos.y >= 0) {
                        search_result_y.push_back(100000 - search({0, 1}));
                    } else {
                        search_result_y.push_back(search({0, -1}) - 100000);
                    }
                }
                bool c;
                int h;
                vector<int> q(N);
                turn_end(c, h, q);
                // drone_speed = drone_speed + add_speed; //
                // 巡行しているので不要
                if (c) {
                    drone_speed = {0, 0};
                } else {
                    drone_pos = drone_pos + drone_speed;
                    if (h > 0) {
                        rep(j, N) {
                            visited[q[j]] = true;
                            if (P[q[j]] == aim_pos) {
                                // i = 10000;
                            }
                        }
                    }
                }
            }
            // int average_speed_x = 0;
            // rep(i, search_result_x.size() - 1) {
            //     int tmp = (search_result_x[i + 1] - search_result_x[i]) / 2;
            //     speed_suitei_x.push_back(tmp);
            //     average_speed_x += tmp;
            // }
            // int average_speed_y = 0;
            // rep(i, search_result_y.size()) {
            //     int tmp = (search_result_y[i + 1] - search_result_y[i]) / 2;
            //     speed_suitei_y.push_back(tmp);
            //     average_speed_y += tmp;
            // }
            // average_speed_x = (average_speed_x / (going_kaisuu / 2 - 1));
            // average_speed_y = (average_speed_y / (going_kaisuu / 2 - 1));

            // drone_pos = {search_result_x[search_result_x.size() - 1] +
            //                  2 * average_speed_x,
            //              search_result_y[search_result_y.size() - 1] +
            //                  average_speed_y};
            // drone_speed = {average_speed_x, average_speed_y};
        }

        // 減速フェーズ
        drone_pos.calc_length_and_angle_from_poses(rest_dist, aim_angle,
                                                   aim_pos);
        // double current_angle = atan2(drone_speed.y, drone_speed.x);
        // double angle_diff = current_angle - aim_angle;
        // int hosei_vec_length = drone_speed.pos_abs() * sin(angle_diff);
        // double hosei_angle = angle_diff - (3.141592 / 2);
        rep(lp, acceleration_kaisuu) {
            if (lp == acceleration_exec_kaisuu)
                break;
            if (rest_hand <= 0) {
                exit(0);
            }
            rest_hand--;
            Pos add_speed;
            drone_pos.calc_pos_from_length_and_angle(
                min(499, rest_dist), first_aim_angle + 3.141592, add_speed);
            add_speed = {add_speed.x, add_speed.y};
            acceleration(add_speed);

            bool c;
            int h;
            vector<int> q(N);
            turn_end(c, h, q);
            drone_speed = drone_speed + add_speed;
            if (c) {
                drone_speed = {0, 0};
            } else {
                drone_pos = drone_pos + drone_speed;
                if (h > 0) {
                    rep(i, N) {
                        visited[q[i]] = true;
                        if (P[q[i]] == aim_pos) {
                            // return true;
                        }
                    }
                }
            }
        }
        drone_speed.print();
    }
    void simple_acceleration() {
        Pos drone_pos = S;
        Pos drone_speed = {0, 0};

        rep(i, p_order.size()) {
            visit_pos(drone_pos, drone_speed, p_order[i]);
        }
        rep(i, rest_hand) { cout << "A 0 0" << endl; }
    }
};

void inpt() {
    cin >> N >> M >> eps >> del;
    P.resize(N);
    W.resize(M);
    cin >> S.x >> S.y;

    int tmpx, tmpy;
    rep(i, N) {
        cin >> tmpx >> tmpy;
        P[i] = {tmpx, tmpy};
        // P[i].print();
    }
    rep(i, M) {
        cin >> tmpx >> tmpy;
        W[i].l = {tmpx, tmpy};
        cin >> tmpx >> tmpy;
        W[i].r = {tmpx, tmpy};
    }
}

int main() {
    inpt();
    Field best;
    best.init();
    best.calc_p_order();
    best.simple_acceleration();

    return 0;
}
