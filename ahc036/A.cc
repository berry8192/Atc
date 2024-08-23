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
// auto seed=(unsigned)time(NULL);
int seed = 1;
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
    // vector<Edge> edges;

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
            // edges.push_back({uu, vv, ww}); // edges
            if (!directed) {
                g[vv].push_back({vv, uu, ww});
                // edges.push_back({vv, uu, ww}); // edges
            }
        }
    }

    vector<int> shortest_path(int start, int goal) {
        vector<int> dist(n, -1); // 距離を管理する配列、初期値は -1（未訪問）
        vector<int> prev(n, -1); // 経路を復元するための前の頂点を記録する配列
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (v == goal)
                break; // ゴールに到達したら探索終了

            for (auto &edge : g[v]) {
                int to = edge.to;
                if (dist[to] == -1) { // 未訪問の頂点のみ探索
                    dist[to] = dist[v] + 1;
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
};

int N, M, T, La, Lb;
Graph graph;
vector<int> t;

struct Grid {};

int calc_visit_uniq() {
    set<int> visit;
    rep(i, T) { visit.insert(t[i]); }
    return visit.size();
}

void inpt() {
    cin >> N >> M >> T >> La >> Lb;
    graph.init(N, M);
    t.resize(T);
    rep(i, T) cin >> t[i];

    // outputFile << calc_visit_uniq() << endl;
    // exit(0);
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
    PV(a);

    rep(i, grand_path.size()) {
        if (a_last - i >= Lb) {
            cout << "s" SP << Lb SP << i / Lb * Lb SP << 0 << endl;
            rep(k, Lb) cout << "m " << grand_path[i + k] << endl;
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
            cout << "s" SP << 1 SP << idx SP << 0 << endl;
            cout << "m " << grand_path[i] << endl;
        }
    }
}

int main() {
    inpt();
    simple_bfs_path();

    return 0;
}
