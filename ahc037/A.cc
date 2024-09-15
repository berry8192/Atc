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

struct Line {
    Pos from;
    Pos to;

    Line() {};
    Line(Pos from_pos, Pos to_pos) {
        from = from_pos;
        to = to_pos;
    }

    void output_line() {
        cout << from.h << " " << from.w << " " << to.h << " " << to.w << endl;
    }
};

struct Graph {
    vector<Line> lines;
    vector<Line> sorted_lines;

    Graph() {};

    void greed_mini_cost() {
        cout << 1000 << endl;
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
            lines.push_back({AB[min_cost_index], AB[i]});
        }
        sort_lines();
        print_lines();
    }
    void sort_lines() {
        set<Pos> connected;
        connected.insert({0, 0});
        vector<int> conn_lines(lines.size());

        while (1) {
            int connect_count = 0;
            rep(i, lines.size()) {
                if (conn_lines[i])
                    continue;
                if (connected.find(lines[i].from) != connected.end()) {
                    sorted_lines.push_back(lines[i]);
                    connected.insert(lines[i].to);
                    conn_lines[i] = 1;
                    connect_count++;
                }
            }
            if (connect_count == 0)
                break;
        }
    }

    void print_lines() {
        rep(i, sorted_lines.size()) { sorted_lines[i].output_line(); }
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
