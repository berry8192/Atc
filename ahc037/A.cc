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
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int N;
vector<int> A, B;

// 構造体
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    bool is_right_up_by(Pos pos) { return h >= pos.h && w >= pos.w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }

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
vector<Pos> AB;

// struct Line {
//     Pos from;
//     Pos to;

//     Line() {};
//     Line(Pos from_pos, Pos to_pos) {
//         from = from_pos;
//         to = to_pos;
//     }

//     void output_line() {
//         cout << from.h << " " << from.w << " " << to.h << " " << to.w <<
//         endl;
//     }
// };

struct Edge {
    int from;
    int to;

    Edge() {};
    Edge(int from_index, int to_index) {
        from = from_index;
        to = to_index;
    }

    void output_edge() {
        cout << AB[from].h << " " << AB[from].w << " " << AB[to].h << " "
             << AB[to].w << endl;
    }
    double calc_dir() const {
        double dx = AB[to].h - AB[from].h;
        double dy = AB[to].w - AB[from].w;
        return atan2(dy, dx);
    }

    bool operator<(const Edge &in) const { return calc_dir() < in.calc_dir(); };
};

struct Graph {
    // vector<Line> lines;
    // vector<Line> sorted_lines;
    vector<vector<Edge>> edges;
    vector<Edge> sorted_edges;
    vector<Edge> jointed_edges;

    Graph() { edges.resize(5 * N); };

    void greed_mini_cost() {
        rep(i, N) {
            int min_cost = AB[i].manhattan({0, 0});
            int min_cost_index = N;

            rep(j, N) {
                if (i == j)
                    continue;
                if (!AB[i].is_right_up_by(AB[j]))
                    continue;
                int cost = AB[i].manhattan(AB[j]);
                if (cost < min_cost) {
                    min_cost = cost;
                    min_cost_index = j;
                }
            }
            // lines.push_back({AB[min_cost_index], AB[i]});
            edges[min_cost_index].push_back({min_cost_index, i});
        }
        // sort_lines();
        // print_lines();
        dir_sort_edges();
        reduce_edges();
        sort_edges(N); // 0,0 からスタート
        joint_edges();
        print_edges();
    }
    void dir_sort_edges() {
        rep(i, edges.size()) { sort(all(edges[i])); }
    }
    void reduce_edges() {
        rep(i, N + 1) {
            // もともと存在していた辺に対してのみ実行する
            while (edges[i].size() >= 2) {
                int pos1 = edges[i][edges[i].size() - 1].to;
                int pos2 = edges[i][edges[i].size() - 2].to;
                Pos mid_pos = {min(AB[pos1].h, AB[pos2].h),
                               min(AB[pos1].w, AB[pos2].w)};
                AB.push_back(mid_pos);
                int added_index = AB.size() - 1;

                // iで削除と追加
                edges[i].pop_back();
                edges[i].pop_back();
                edges[i].push_back({i, added_index});

                // added_indexで追加
                edges[added_index].push_back({added_index, pos1});
                edges[added_index].push_back({added_index, pos2});
            }
        }
    }
    void joint_edges() {
        rep(i, sorted_edges.size()) {
            if (AB[sorted_edges[i].from].h == AB[sorted_edges[i].to].h ||
                AB[sorted_edges[i].from].w == AB[sorted_edges[i].to].w) {
                jointed_edges.push_back(sorted_edges[i]);
                continue;
            }

            Pos joint_point = {AB[sorted_edges[i].from].h,
                               AB[sorted_edges[i].to].w};
            AB.push_back(joint_point);
            int added_index = AB.size() - 1;
            jointed_edges.push_back({sorted_edges[i].from, added_index});
            jointed_edges.push_back({added_index, sorted_edges[i].to});

            Pos joint_point2 = {AB[sorted_edges[i].to].h,
                                AB[sorted_edges[i].from].w};
            AB.push_back(joint_point2);
            int added_index2 = AB.size() - 1;
            jointed_edges.push_back({sorted_edges[i].from, added_index2});
            jointed_edges.push_back({added_index2, sorted_edges[i].to});
        }
    }
    // void sort_lines() {
    //     set<Pos> connected;
    //     connected.insert({0, 0});
    //     vector<int> conn_lines(lines.size());

    //     while (1) {
    //         int connect_count = 0;
    //         rep(i, lines.size()) {
    //             if (conn_lines[i])
    //                 continue;
    //             if (connected.find(lines[i].from) != connected.end()) {
    //                 sorted_lines.push_back(lines[i]);
    //                 connected.insert(lines[i].to);
    //                 conn_lines[i] = 1;
    //                 connect_count++;
    //             }
    //         }
    //         if (connect_count == 0)
    //             break;
    //     }
    // }
    void sort_edges(int pos_index) {
        rep(i, edges[pos_index].size()) {
            sorted_edges.push_back(edges[pos_index][i]);
            sort_edges(edges[pos_index][i].to);
        }
    }

    // void print_lines() {
    //     rep(i, sorted_lines.size()) { sorted_lines[i].output_line(); }
    // }
    void print_edges() {
        // cout << sorted_edges.size() << endl;
        // rep(i, sorted_edges.size()) { sorted_edges[i].output_edge(); }
        cout << jointed_edges.size() << endl;
        rep(i, jointed_edges.size()) { jointed_edges[i].output_edge(); }
    }
};

void all_zero() {
    cout << 1000 << endl;
    rep(i, N) { cout << 0 SP << 0 SP << A[i] SP << B[i] << endl; }
}

void inpt() {
    cin >> N;
    A.resize(N + 1);
    B.resize(N + 1);
    AB.resize(N + 1);
    rep(i, N) {
        cin >> A[i] >> B[i];
        AB[i] = Pos(A[i], B[i]);
    }
    A[N] = 0;
    B[N] = 0;
    AB[N] = Pos(0, 0);
}

int main() {
    start = chrono::system_clock::now();

    inpt();

    Graph graph;
    graph.greed_mini_cost();

    return 0;
}
