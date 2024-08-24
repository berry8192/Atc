// #include <atcoder/all>
#include <bits/stdc++.h>

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
        // calculate_all_pairs_shortest_paths();
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

            // 隣接する頂点を探索
            for (const auto &edge : g[v]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;

                    if (possible_moves.find(edge.to) != possible_moves.end()) {
                        int distance = dist[edge.to][target];
                        if (distance < min_distance) {
                            parent[edge.to] = v; // 親として記録
                            min_distance = distance;
                            min_distance_id = edge.to;
                        }

                        q.push(edge.to);
                    }
                }
            }
        }

        // 経路を復元（始点は含めずにpathに追加）
        if (min_distance_id != -1) {
            int v = min_distance_id;
            while (v != current) {
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

void calc_reduce_t() {}

vector<int> simple_bfs_visit_path() {
    vector<int> visit(N);

    int pos = 0;
    rep(i, T) {
        vector<int> path = graph.shortest_path(pos, t[i]);
        rep3(j, path.size(), 1) { visit[path[j]]++; }
        pos = t[i];
    }
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
    PV(simple_bfs_visit_path());
    return 0;
    City city;
    city.init();

    return 0;
}
