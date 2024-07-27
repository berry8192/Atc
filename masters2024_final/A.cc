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

struct Field {
    vector<Pos> p_order;
    vector<bool> visited;
    int rest_hand = 5000;

    void init() {}

    void calc_p_order() {
        vector<int> order_idx = make_rooting();
        p_order.resize(N);
        rep(i, N) { p_order[i] = P[order_idx[i]]; }

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
    bool visit_pos(Pos &drone_pos, Pos &drone_speed, const Pos &aim_pos) {
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
                            lp = 10000;
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
                                i = 10000;
                            }
                        }
                    }
                }
            }
            int average_speed_x = 0;
            rep(i, search_result_x.size() - 1) {
                int tmp = (search_result_x[i + 1] - search_result_x[i]) / 2;
                speed_suitei_x.push_back(tmp);
                average_speed_x += tmp;
            }
            int average_speed_y = 0;
            rep(i, search_result_y.size()) {
                int tmp = (search_result_y[i + 1] - search_result_y[i]) / 2;
                speed_suitei_y.push_back(tmp);
                average_speed_y += tmp;
            }
            if (acceleration_exec_kaisuu == acceleration_kaisuu) {
                average_speed_x = (average_speed_x / (going_kaisuu / 2 - 1));
                average_speed_y = (average_speed_y / (going_kaisuu / 2 - 1));

                drone_pos = {search_result_x[search_result_x.size() - 1] +
                                 2 * average_speed_x,
                             search_result_y[search_result_y.size() - 1] +
                                 average_speed_y};
                drone_speed = {average_speed_x, average_speed_y};
            }
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
                return true;
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
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    void simple_acceleration() {
        Pos drone_pos = S;
        Pos drone_speed = {0, 0};

        rep(i, p_order.size()) {
            while (1) {
                bool tmp = visit_pos(drone_pos, drone_speed, p_order[i]);
                if (tmp) {
                    cerr << i << endl;
                    drone_pos.print();
                    drone_speed.print();
                    break;
                }
            }
        }
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
