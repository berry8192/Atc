#include <atcoder/all>
#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] << " ";
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

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 2900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
auto seed = (unsigned)time(NULL);
// int seed = 1;
mt19937 mt(seed);

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

struct Edge {
    int from;
    int to;
    ll cost;

    Edge() {};
    Edge(int ifrom, int ito, ll icost) {
        from = ifrom;
        to = ito;
        cost = icost;
    }

    bool operator<(const Edge &in) const {
        return cost != in.cost ? cost < in.cost
               : to != in.to   ? to < in.to
                               : from < in.from;
    };
    bool operator>(const Edge &in) const {
        return cost != in.cost ? cost > in.cost
               : to != in.to   ? to > in.to
                               : from > in.from;
    };
};
struct Graph {
    int n, m;
    vector<vector<Edge>> g;
    vector<vector<int>> dist;
    vector<Edge> edges;

    Graph() {};

    void init(int nn, int mm, bool weight = false, bool directed = false) {
        n = nn;
        m = mm;
        // n頂点、m辺、重み有無、有向無向
        int uu, vv, ww;
        g.resize(nn);

        for (int i = 0; i < mm; i++) {
            cin >> uu >> vv;
            if (weight)
                cin >> ww;
            else
                ww = 1;

            g[uu].push_back({uu, vv, ww});
            edges.push_back({uu, vv, ww}); // edges
            if (!directed) {
                g[vv].push_back({vv, uu, ww});
                edges.push_back({vv, uu, ww}); // edges
            }
        }
        calculate_all_pairs_shortest_paths();
    }

    vector<int> shortest_path(int start, int goal) {
        vector<int> dists(n, -1); // 距離を管理する配列、初期値は -1（未訪問）
        vector<int> prev(n, -1); // 経路を復元するための前の頂点を記録する配列
        queue<int> q;

        dists[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (v == goal)
                break; // ゴールに到達したら探索終了

            for (auto &edge : g[v]) {
                int to = edge.to;
                if (dists[to] == -1) { // 未訪問の頂点のみ探索
                    dists[to] = dists[v] + 1;
                    prev[to] = v; // 前の頂点を記録
                    q.push(to);
                }
            }
        }

        // 経路を復元
        vector<int> path;
        for (int v = goal; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        if (path[0] == start)
            return path; // 経路が見つかった場合
        return {}; // 経路が見つからなかった場合（スタートからゴールに到達不可）
    }
    // 全頂点対の最短距離を計算し、distに保存する関数
    void calculate_all_pairs_shortest_paths() {
        dist.resize(n, vector<int>(n, imax));

        // 自己ループの距離を0に設定
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }

        // グラフのエッジから距離を初期化
        for (int i = 0; i < n; ++i) {
            for (const auto &edge : g[i]) {
                dist[edge.from][edge.to] = edge.cost;
            }
        }

        // フロイド・ワーシャル法による全頂点対最短経路計算
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] < imax && dist[k][j] < imax) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }

    // 現在の頂点から移動可能な頂点を辿って目的の頂点に最も近い距離を求める関数
    int closest_reachable_distance(int current, int target,
                                   const multiset<int> &possible_moves,
                                   vector<int> &path) {

        int cut = 1;
        rep(i, g[current].size()) {
            if (possible_moves.find(g[current][i].to) != possible_moves.end()) {
                cut = 0;
                break;
            }
        }
        if (cut)
            return imax;
        vector<bool> visited(n, false); // 訪問済みチェック用
        vector<int> parent(n, -1); // 各頂点の親（前の頂点）を記録
        queue<int> q;
        visited[current] = true;
        q.push(current);

        int min_distance = imax;
        int min_distance_id = -1;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << "v: " << v << endl;

            // 隣接する頂点を探索
            for (const auto &edge : g[v]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;

                    if (possible_moves.find(edge.to) != possible_moves.end()) {
                        // cout << "edge.to: " << edge.to << endl;
                        int distance = dist[edge.to][target];
                        if (distance + 1 < min_distance) {
                            // cout << v << endl;
                            // cout << "par " << edge.to SP << v << endl;
                            parent[edge.to] = v; // 親として記録
                            min_distance = distance;
                            min_distance_id = edge.to;
                        }
                        q.push(edge.to);
                    }
                }
                // cout << "edge.to: " << edge.to << endl;
            }
        }

        // 経路を復元（始点は含めずにpathに追加）
        if (min_distance_id != -1) {
            int v = min_distance_id;
            cout << v << endl;
            while (v != current) {
                if (v > 0)
                    cout << v << endl;
                path.push_back(v);
                v = parent[v];
            }
            reverse(path.begin(), path.end());
        }

        return min_distance;
    }
};

int N, M, T, La, Lb;
Graph graph;
vector<int> t, rev_t;
vector<int> x, y;
vector<int> reduce_t;

struct City {
    vector<int> A;

    void init() {
        A.resize(La);
        rep(i, La) A[i] = i % N;
    }
    void out_s(int l, int Pa, int Pb) {
        assert(1 <= l);
        assert(l <= Lb);
        assert(0 <= Pa);
        assert(Pa <= La - l);
        assert(0 <= Pb);
        assert(Pb <= Lb - l);
        cout << "s " << l SP << Pa SP << Pb << endl;
    }
    void out_m(int v) {
        assert(0 <= v);
        assert(v < N);
        cout << "m " << v << endl;
    }
    bool exec_path(int from, int to, bool dryrun, int &score) {
        cout << "# " << from << " " << to << endl;
        set<int> passed;
        int pos = from;
        while (pos != to) {
            int min_dist = imax;
            int min_dist_La_id = -1;
            vector<int> best_path;
            multiset<int> possible_v;
            for (int i = 0; i + Lb < La; i += Lb) {
                possible_v.clear();
                rep3(j, i + Lb, i) { possible_v.insert(A[j]); }
                vector<int> path;
                int dist =
                    graph.closest_reachable_distance(pos, to, possible_v, path);
                if (dist < min_dist) {
                    int flg = 1;
                    rep(j, path.size()) {
                        if (passed.find(path[j]) != passed.end()) {
                            flg = 0;
                            break;
                        }
                    }
                    if (flg) {
                        min_dist = dist;
                        min_dist_La_id = i;
                        best_path = path;
                    }
                }
            }
            if (min_dist_La_id == -1) {
                return false;
            }
            if (dryrun) {
                cout << "# ";
            }
            out_s(Lb, min_dist_La_id, 0);
            score++;

            rep(i, best_path.size()) {
                if (dryrun) {
                    cout << "# ";
                }
                out_m(best_path[i]);
                pos = best_path[i];
                passed.insert(pos);
            }
        }
        return true;
    }
    int exec(bool dryrun = true) {
        if (!dryrun) {
            rep(i, La) cout << A[i] SP;
            cout << endl;
        }
        int pos = 0;
        int score = 0;
        rep(i, T) {
            cout << "# exec " << i << endl;
            if (!exec_path(pos, t[i], dryrun, score)) {
                return imax;
            }
            pos = t[i];
        }
        return score;
    }
    void annering() {
        int best_score = imax;
        rep(lp, 0) {
            cerr << "# anneal start " << lp << endl;
            int idx1 = rand() % La;
            int idx2 = rand() % La;

            swap(A[idx1], A[idx2]);

            int score = exec();
            if (score < best_score) {
                best_score = score;
                cerr << "# anneal " << lp << " " << score << endl;
            } else {
                swap(A[idx1], A[idx2]);
                cerr << "# anneal rejected " << lp << " " << score << endl;
            }
        }
        exec(false);
    }
};

int calc_v_dist(int v_index, int ix, int iy) {
    int dx = ix - x[v_index];
    int dy = iy - y[v_index];
    return sqrt(dx * dx + dy * dy);
}

int calc_nearest_v(int ix, int iy) {
    int nearest = imax;
    int nearest_id;
    rep(i, N) {
        int dx = ix - x[i];
        int dy = iy - y[i];
        int d = dx * dx + dy * dy;
        if (d < nearest) {
            nearest = d;
            nearest_id = i;
        }
    }
    return nearest_id;
}

void print_v(vector<int> v) {
    rep(i, La) {
        if (i < N)
            cout << i SP;
        else
            cout << 0 SP;
    }
    cout << endl;

    rep3(i, v.size(), 1) {
        cout << "s " << 1 SP << v[i] SP << 0 << endl;
        cout << "m " << v[i] << endl;
    }
}

int calc_visit_uniq() {
    set<int> visit;
    rep(i, T) { visit.insert(t[i]); }
    return visit.size();
}

void printSortedMap(const std::map<std::string, int> &myMap) {
    // mapの内容をペアのベクトルにコピー
    std::vector<std::pair<std::string, int>> vec(myMap.begin(), myMap.end());

    // ペアのベクトルをintの降順にソート
    std::sort(vec.begin(), vec.end(),
              [](const std::pair<std::string, int> &a,
                 const std::pair<std::string, int> &b) {
                  return b.second < a.second; // 降順ソート
              });

    // ソートされた結果を出力
    for (const auto &pair : vec) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void print_vs(vector<int> vs) {
    rep(i, La) { cout << i % N SP; }
    cout << endl;
    rep(i, vs.size()) cout << "s 1 " << vs[i] << " 0" << endl;
}

int calc_center_v(vector<int> &visit) {
    double max_centerity = 0.0;
    int max_centrrity_v = -1;

    rep(i, visit.size()) {
        double centerity = 1.0 * visit[i] / (calc_v_dist(i, 500, 500) + 10);
        // cout << i SP << centerity << endl;
        if (max_centerity < centerity) {
            max_centerity = centerity;
            max_centrrity_v = i;
        }
    }
    return max_centrrity_v;
}

vector<int> simple_bfs_visit_path() {
    vector<int> visit(N);

    int pos = 0;
    rep(i, T) {
        vector<int> path = graph.shortest_path(pos, t[i]);
        rep3(j, path.size(), 1) { visit[path[j]]++; }
        pos = t[i];
    }
    // map<string, int> used_edge;
    // int pos = 0;
    // rep(i, T) {
    //     vector<int> path = graph.shortest_path(pos, t[i]);
    //     rep3(j, path.size(), 1) {
    //         used_edge[to_string(min(pos, path[j])) + "-" +
    //                   to_string(max(pos, path[j]))]++;
    //         visit[path[j]]++;
    //         pos = path[j];
    //     }
    // }
    // printSortedMap(used_edge);

    // visitの最大値のindexを求める
    // int max_visit = 0;
    // int max_visit_index = -1;
    // rep(i, visit.size()) {
    //     if (max_visit < visit[i]) {
    //         max_visit = visit[i];
    //         max_visit_index = i;
    //     }
    // }
    // print_vs({max_visit_index});
    // cout << max_visit_index SP << x[max_visit_index] SP << y[max_visit_index]
    //      << endl;
    print_vs({calc_center_v(visit)});
    exit(0);

    return visit;
}

void simple_bfs_path() {
    set<int> visit;
    vector<int> a;

    int pos = 0;
    int a_last = N;
    vector<int> grand_path;
    rep(i, T) {
        vector<int> path = graph.shortest_path(pos, t[i]);
        rep3(j, path.size(), 1) { grand_path.push_back(path[j]); }
        rep(j, grand_path.size()) { visit.insert(grand_path[j]); }
        pos = t[i];
    }
    pos = 0;
    rep(i, T) {
        // cout << "# " << pos SP << t[i] << endl;
        vector<int> path = graph.shortest_path(pos, t[i]);
        rep3(j, path.size(), 1) {
            // if (visit.find(path[j]) != visit.end()) {
            //     cout << "# match" << endl;
            // }
            // cout << "# " << path[j] SP << La SP << int(a.size()) SP
            // << visit.size() << endl;
            if (La - int(a.size()) <= visit.size()) {
                a_last = min(a_last, int(a.size()));
                if (visit.find(path[j]) != visit.end()) {
                    a.push_back(path[j]);
                    visit.erase(path[j]);
                }
            } else {
                a.push_back(path[j]);
                visit.erase(path[j]);
            }
        }
        pos = t[i];
    }
    while (a.size() < La)
        a.push_back(0);
    // PV(a);

    vector<int> vis(N);
    rep(i, grand_path.size()) {
        if (a_last - i >= Lb) {
            // cout << "s" SP << Lb SP << i / Lb * Lb SP << 0 << endl;
            // rep(k, Lb) cout << "m " << grand_path[i + k] << endl;
            rep(k, Lb) vis[grand_path[i + k]]++;
            i += Lb - 1;
        } else {
            // aの中でpath[j]となっている値のindexを線形探索で取ってくる
            int idx = -1;
            rep(k, a.size()) {
                if (a[k] == grand_path[i]) {
                    idx = k;
                    break;
                }
            }
            // cout << "s" SP << 1 SP << idx SP << 0 << endl;
            // cout << "m " << grand_path[i] << endl;
            vis[grand_path[i]]++;
        }
    }
    // rep(i, N) { outputFile << x[i] << ", " << y[i] << ", " << vis[i] << endl;
    // }
}

struct Country {
    vector<int> A;
    int center_v;
    vector<int> visit;
    vector<int> target;
    vector<vector<int>> radial_paths, circle_paths;
    dsu d;
    set<int> jointed;
    map<int, int> next_to_jointed;

    void calc_target() {
        target.resize(N);
        rep(i, T) { target[t[i]]++; }
        d = dsu(N + 1);
    }
    void calc_visit_path() {
        visit.resize(N);

        int pos = 0;
        rep(i, T) {
            vector<int> path = graph.shortest_path(pos, t[i]);
            rep3(j, path.size(), 1) { visit[path[j]]++; }
            pos = t[i];
        }
        center_v = calc_center_v(visit);
    }
    int calc_nearest_v_only_target(int ix, int iy) {
        int nearest = imax;
        int nearest_id;
        rep(i, N) {
            if (target[i] == 0) {
                continue;
            }
            int dx = ix - x[i];
            int dy = iy - y[i];
            int d = dx * dx + dy * dy;
            if (d < nearest) {
                nearest = d;
                nearest_id = i;
            }
        }
        return nearest_id;
    }
    void make_radial_path() {
        // 8方向のweb
        int WEB_SIZE = 8;
        radial_paths.resize(WEB_SIZE / 2);
        vector<int> X_ENDS = {0, 1000, 500, 500, 1000, 0, 1000, 0};
        vector<int> Y_ENDS = {0, 1000, 0, 1000, 0, 1000, 500, 500};

        // vector<int> tmp;
        // vector<int> tmp2;
        rep(i, WEB_SIZE) {
            int end_v = calc_nearest_v_only_target(X_ENDS[i], Y_ENDS[i]);
            // tmp.push_back(end_v);
            if (i % 2 == 0) {
                vector<int> path = graph.shortest_path(end_v, center_v);
                rep(j, path.size() - 1) {
                    radial_paths[i / 2].push_back(path[j]);
                    d.merge(N, path[j]);
                    // tmp2.push_back(path[j]);
                    A.push_back(path[j]);
                    jointed.insert(path[j]);
                }
            } else {
                vector<int> path = graph.shortest_path(center_v, end_v);
                rep(j, path.size()) {
                    radial_paths[i / 2].push_back(path[j]);
                    d.merge(N, path[j]);
                    // tmp2.push_back(path[j]);
                    A.push_back(path[j]);
                    jointed.insert(path[j]);
                }
            }
            // if (i % 2) {
            //     cout << "radial: " << i SP << radial_paths[i / 2].size()
            //          << endl;
            // }
        }
        // print_vs(tmp2);
    }
    void make_circle_path() {
        // 2つの同心円
        int CIRCLE_SIZE = 3;
        int PATH_DIVISION = 6; // 半径150あたりの分割数
        circle_paths.resize(CIRCLE_SIZE);
        vector<double> radius = {150, 300, 450};

        rep(i, CIRCLE_SIZE) {
            vector<int> check_points;
            rep(j, PATH_DIVISION * radius[i] / 150) {
                double theta =
                    2.0 * M_PI * j / (PATH_DIVISION * radius[i] / 150);
                int dx = radius[i] * cos(theta);
                int dy = radius[i] * sin(theta);
                int nx = 500 + dx;
                int ny = 500 + dy;
                int nearest = calc_nearest_v_only_target(nx, ny);
                check_points.push_back(nearest);
            }
            rep(j, check_points.size()) {
                vector<int> path = graph.shortest_path(
                    check_points[j],
                    check_points[(j + 1) % check_points.size()]);
                rep(k, path.size() - 1) {
                    circle_paths[i].push_back(path[k]);
                    d.merge(N, path[k]);
                    A.push_back(path[k]);
                    jointed.insert(path[k]);
                }
            }
            // cout << "circle: " << i SP << circle_paths[i].size() << endl;
        }
        // print_vs(circle_paths[0]);
    }
    void calc_next_to_jointed() {
        for (auto ver : jointed) {
            rep(i, graph.g[ver].size()) {
                int to = graph.g[ver][i].to;
                if (jointed.find(to) != jointed.end())
                    continue;
                next_to_jointed[to] = ver;
            }
        }
    }
    void make_gap_inner_path() {
        rep(i, N) {
            if (target[i] && !d.same(N, i)) {
                // cout << i << endl;
                rep(j, graph.g[i].size()) {
                    if (d.size(i) >= Lb) {
                        break;
                    }
                    int to = graph.g[i][j].to;
                    if (target[to] && !d.same(N, i) &&
                        d.size(i) + d.size(to) <= Lb) {
                        d.merge(i, to);
                    }
                }
            }
        }
    }
    void make_gap_outer_path() {
        vector<vector<int>> tmp = d.groups();
        rep(i, tmp.size()) {
            if (target[i] && !d.same(N, i)) {
                int joint = 0;
                rep(j, tmp[i].size()) {
                    if (next_to_jointed.find(tmp[i][j]) !=
                        next_to_jointed.end()) {
                        joint = 1;
                    }
                }
                if (joint) {
                    rep(j, tmp[i].size()) { jointed.insert(tmp[i][j]); }
                    rep(j, tmp[i].size()) {
                        rep(k, graph.g[tmp[i][j]].size()) {
                            int to = graph.g[tmp[i][j]][k].to;
                            if (jointed.find(to) != jointed.end())
                                continue;
                            next_to_jointed[to] = tmp[i][j];
                        }
                        A.push_back(tmp[i][j]);
                    }
                } else {
                    // rep(j, tmp[i].size()) {

                    //     if (tmp[i].size() >= Lb) {
                    //         break;
                    //     }
                    // }
                }
            }
        }
    }
    void fill_A() {
        vector<int> rev_A(N);
        rep(i, A.size()) { rev_A[A[i]]++; }
        rep(i, 10) {
            rep(j, N) {
                if (target[j] == 0)
                    continue;
                if (A.size() >= La) {
                    break;
                }
                if (rev_A[j] == i) {
                    A.push_back(j);
                    rev_A[j]++;
                }
            }
        }
        PV(rev_A);
    }
    void exec(bool dry_run = true) {
        vector<string> ans;
        int pos = 0;
        rep(i, T) { move_to(pos, t[i], ans); }
        if (dry_run) {
            rep(i, La) cout << A[i] SP;
            cout << endl;
            rep(i, ans.size()) { cout << ans[i] << endl; }
        }
    }
    string to_str_s(int l, int Pa, int Pb) {
        cout << "l,Pa,Pb: " << l SP << Pa SP << Pb << endl;
        assert(1 <= l);
        assert(l <= Lb);
        assert(0 <= Pa);
        assert(Pa <= La - l);
        assert(0 <= Pb);
        assert(Pb <= Lb - l);
        return "s " + to_string(l) + " " + to_string(Pa) + " " + to_string(Pb);
    }
    string to_str_m(int v) {
        cout << "v: " << v << endl;
        assert(0 <= v);
        assert(v < N);
        return "m " + to_string(v);
    }
    void move_to(int from, int to, vector<string> &ans) {
        cout << "move " << from << " " << to << endl;
        set<int> passed;
        int pos = from;
        while (pos != to) {
            int min_dist = imax;
            int min_dist_La_id = -1;
            vector<int> best_path;
            multiset<int> possible_v;
            for (int i = 0; i + Lb < La; i++) {
                possible_v.clear();
                rep3(j, i + Lb, i) { possible_v.insert(A[j]); }
                vector<int> path;
                int dist =
                    graph.closest_reachable_distance(pos, to, possible_v, path);
                // cout << "i: " << i << " dist: " << dist << endl;
                if (dist < min_dist) {
                    int flg = 1;
                    rep(j, path.size()) {
                        if (passed.find(path[j]) != passed.end()) {
                            flg = 0;
                            break;
                        }
                    }
                    if (flg) {
                        min_dist = dist;
                        min_dist_La_id = i;
                        best_path = path;
                    }
                }
            }
            ans.push_back(to_str_s(Lb, min_dist_La_id, 0));

            rep(i, best_path.size()) {
                ans.push_back(to_str_m(best_path[i]));
                passed.insert(pos);
                pos = best_path[i];
            }
        }
    }
};

void inpt() {
    cin >> N >> M >> T >> La >> Lb;
    graph.init(N, M);
    t.resize(T);
    rev_t.resize(N);
    rep(i, T) {
        cin >> t[i];
        rev_t[t[i]]++;
    }
    x.resize(N);
    y.resize(N);
    rep(i, N) cin >> x[i] >> y[i];

    // outputFile << calc_visit_uniq() << endl;
    // exit(0);
}

int main() {
    inpt();

    Country country;
    country.calc_target();
    country.calc_visit_path();
    country.make_radial_path();
    country.make_circle_path();
    country.calc_next_to_jointed();
    country.make_gap_inner_path();
    country.make_gap_outer_path();
    country.fill_A();
    country.exec(false);

    return 0;
}
