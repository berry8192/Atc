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
double TIME_LIMIT = 1950.0;
// double TIME_LIMIT=190.0;
double start_temp = 100.0;
double end_temp = 10.0;
int DEPTH_LIMIT = 10;

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

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 20250119;
mt19937 mt(seed);

int N, M, H;
vector<int> A;

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
    int n, m, h, w;
    vector<vector<Edge>> g;
    vector<Edge> edges;
    vector<vector<ll>> dist;
    vector<Edge> euler_e;
    vector<int> euler_used;

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
    }
    void board_init(int hh, int ww, int &sh, int &sw, int &gh, int &gw) {
        // void board_init(int h, int w) {
        h = hh;
        w = ww;
        g.resize(h * w);

        vector<string> s(h);
        rep(i, h) { cin >> s[i]; }

        // for (int i = 0; i < h; i++) {
        //     for (int j = 0; j < w; j++) {
        //         if (s[i][j] == 'S') {
        //             sh = i;
        //             sw = j;
        //         }
        //         if (s[i][j] == 'G') {
        //             gh = i;
        //             gw = j;
        //         }
        //     }
        // }
        for (int i = 0; i < h - 1; i++) {
            for (int j = 0; j < w; j++) {
                if (s[i][j] != '#' && s[i + 1][j] != '#') {
                    int wei = 1;
                    g[i * w + j].push_back({i * w + j, (i + 1) * w + j, wei});
                    g[(i + 1) * w + j].push_back(
                        {(i + 1) * w + j, i * w + j, wei});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w - 1; j++) {
                if (s[i][j] != '#' && s[i][j + 1] != '#') {
                    int wei = 1;
                    g[i * w + j].push_back({i * w + j, i * w + j + 1, wei});
                    g[i * w + j + 1].push_back({i * w + j + 1, i * w + j, wei});
                    // edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
                    // edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
                }
            }
        }
    }

    vector<int> bfs(int x) {
        vector<int> rtn(n, imax);
        rtn[x] = 0;
        queue<int> que;
        que.push(x);
        while (!que.empty()) {
            int y = que.front();
            int d = rtn[y];
            que.pop();
            for (int i = 0; i < g[y].size(); i++) {
                int to_x = g[y][i].to;
                if (d + g[y][i].cost < rtn[to_x]) {
                    rtn[to_x] = d + g[y][i].cost;
                    que.push(to_x);
                }
            }
        }
        return rtn;
    }
    // ダイクストラ法
    void djikstra(int startIndex) {
        dist.clear();
        dist.resize(n);
        dist[startIndex][startIndex] = 0;
        priority_queue<Edge, vector<Edge>, greater<Edge>> q;
        q.emplace(0, 0, startIndex);

        while (!q.empty()) {
            const long long distance = q.top().cost;
            const int from = q.top().from;
            q.pop();

            // 最短距離でなければ処理しない
            if (dist[startIndex][from] < distance) {
                continue;
            }

            // 現在の頂点からの各辺について
            for (const auto &edge : g[from]) {
                // to までの新しい距離
                const long long d = (dist[startIndex][from] + edge.cost);

                // d が現在の記録より小さければ更新
                if (d < dist[startIndex][edge.to]) {
                    dist[startIndex][edge.to] = d;
                    q.emplace(d, 0, edge.to);
                }
            }
        }
    }
    // ワーシャルフロイド法
    void worshalfroid() {}
    // 閉路検出
    bool has_cycle() { return false; }
    // 連結成分に分解
    void decomp(vector<Graph> vg) {}
    void euler_tour(int x) {
        if (euler_used[x])
            return;
        euler_used[x] = 1;
        rep(i, g[x].size()) {
            if (euler_used[g[x][i].to])
                continue;
            euler_e.push_back({g[x][i].to, x, g[x][i].cost});
            euler_tour(g[x][i].to);
            euler_e.push_back({x, g[x][i].to, g[x][i].cost});
        }
    }
    ll calc_diameter() {
        djikstra(0);
        ll ma = 0;
        int mai;
        rep(i, n) {
            ma = max(ma, dist[0][i]);
            mai = i;
        }
        djikstra(mai);
        rep(i, n) { ma = max(ma, dist[0][i]); }
        return ma;
    }
};

// 構造体
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h <= 1000 && 0 <= w && w <= 1000);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    // int index() { return h * WIDTH + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};

vector<Pos> XY;
vector<pair<int, int>> beautiful;

void calc_beautiful() {
    rep(i, A.size()) {
        beautiful[i].first = A[i] + (mt() * 100 + 50);
        beautiful[i].second = i;
    }
    sort(all(beautiful));
}

Graph graph;
struct Grid {
    vector<set<int>> g;
    vector<int> parent;
    int current_score;

    void init() {
        g.resize(N);
        parent.resize(N, imax);
        current_score = -1;
    }

    void donyoku() {
        queue<int> que, dep;
        // vector<int> perm(N);
        // rep(i, N) { perm[i] = i; }
        // shuffle(all(perm), mt);
        calc_beautiful();

        rep(i, N) {
            // int idx = perm[i];
            int idx = beautiful[i].second;
            if (parent[idx] != imax) {
                continue;
            }
            parent[idx] = -1;
            que.push(idx);
            dep.push(0);
            while (!que.empty()) {
                int from = que.front();
                int d = dep.front();
                // cout << from SP << d << endl;
                que.pop();
                dep.pop();
                rep(j, graph.g[from].size()) {
                    int to = graph.g[from][j].to;
                    // cout << to SP << A[to] << endl;
                    if (parent[to] != imax || d >= 10) {
                        continue;
                    }
                    if ((A[to] - 50) / 10 > d - 2) {
                        continue;
                    }

                    g[from].insert(to);
                    parent[to] = from;
                    que.push(to);
                    dep.push(d + 1);
                }
            }
        }
        current_score = score();
    }
    void destroy_single() {
        rep(i, N) {
            if (parent[i] == -1 && g[i].empty()) {
                parent[i] = imax;
            }
        }
    }
    void destroy_root(int idx) {
        vector<int> destroy_list;
        for (auto s : g[idx]) {
            destroy_list.push_back(s);
        }
        g[idx].clear();
        rep(i, destroy_list.size()) {
            parent[destroy_list[i]] = imax;
            destroy_root(destroy_list[i]);
        }
    }
    void annering() {
        int loop = 0;
        while (timer.progress() < 1.0) {
            loop++;
            // int type = mt() % 100;

            // if (type <= 50) {
            // rootを減らす
            vector<set<int>> copy_g = g;
            vector<int> copy_parent = parent;
            int idx;
            do {
                idx = mt() % N;
            } while (parent[idx] != -1);
            parent[idx] = imax;
            int before_score = current_score;
            // int des = mt() % 3 + 1;
            // rep(i, des) { destroy_root(idx); }
            destroy_root(idx);
            if (mt() % 2 == 0) {
                destroy_single();
            }
            donyoku();
            // cout << current_score << endl;
            // if (loop % 10 == 0) {
            //     print_ans();
            // }
            double temp =
                start_temp + (end_temp - start_temp) * timer.progress();
            double prob = exp((current_score - before_score) / temp);
            // cout << current_score - before_score SP << prob << endl;
            if (prob < (mt() % imax) / (double)imax) {
                current_score = before_score;
                g = copy_g;
                parent = copy_parent;
            }
            // } else {
            //     // 木を回転させる
            // }
        }
    }
    void score_dfs(int idx, int dep, int &sco) {
        sco += A[idx] * (dep + 1);
        for (auto v : g[idx]) {
            score_dfs(v, dep + 1, sco);
        }
    }
    int score() {
        int sco = 1;
        rep(i, N) {
            if (parent[i] == -1) {
                sco += A[i] * 1;
                for (auto v : g[i]) {
                    score_dfs(v, 1, sco);
                }
            }
        }
        return sco;
    }

    void print_ans() {
        rep(i, N) { cout << parent[i] SP; }
        cout << endl;
    }
};

void inpt() {
    cin >> N >> M >> H;
    A.resize(N);
    rep(i, N) { cin >> A[i]; }
    beautiful.resize(N);
    graph.init(N, M);
    rep(i, N) {
        int x, y;
        cin >> x >> y;
        XY.push_back(Pos(x, y));
    }
}

void gutyoku() {
    rep(i, N) { cout << -1 << endl; }
    exit(0);
}

void rantaku() {
    int best_score = -1;
    Grid best_grid;

    while (timer.progress() < 1.0) {
        Grid grid;
        grid.init();
        grid.donyoku();
        int score = grid.score();
        if (best_score < score) {
            best_score = score;
            best_grid = grid;
        }
    }
    best_grid.print_ans();
    exit(0);
}

int main() {
    inpt();
    rantaku();
    Grid grid;
    grid.init();
    grid.donyoku();
    // cout << grid.score() << endl;
    grid.annering();
    grid.print_ans();
    return 0;

    int loop = 0;
    while (1) {
        loop++;
    }
    // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
