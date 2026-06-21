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
int seed = 1;
mt19937 mt(seed);

int N;
int HEIGHT, WIDTH;

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
        return !(0 <= h && h < HEIGHT && 0 <= w && w < WIDTH);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * WIDTH + w; }
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

struct Grid {};

Pos itop(int idx) { return {idx / WIDTH, idx % WIDTH}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

int M, K;          // M: 扉の最大枚数(=50), K: スイッチの種類数(=10)
vector<string> c;  // 盤面

void inpt() {
    cin >> N >> M >> K;
    HEIGHT = WIDTH = N;
    c.resize(N);
    rep(i, N) cin >> c[i];
}

// 1本の扉
struct Door {
    int d, i, j, g;  // 向き, 座標, 型
};
// 1つのスイッチ
struct Switch {
    int p, q, s;  // 座標, 種類
};

int main() {
    start = chrono::system_clock::now();
    inpt();

    Pos goal(N - 1, N - 1);

    // ゴールから空きマスのみを通る距離をBFSで計算
    vector<vector<int>> dist(N, vector<int>(N, -1));
    {
        queue<Pos> que;
        dist[goal.h][goal.w] = 0;
        que.push(goal);
        while (!que.empty()) {
            Pos p = que.front();
            que.pop();
            for (Pos dp : d4) {
                Pos np = p + dp;
                if (np.is_oob())
                    continue;
                if (c[np.h][np.w] == '#')
                    continue;
                if (dist[np.h][np.w] != -1)
                    continue;
                dist[np.h][np.w] = dist[p.h][p.w] + 1;
                que.push(np);
            }
        }
    }

    // 通行可能なエッジを列挙(両端が空きマス)。ゴールに近い順に並べる
    // d=0: (i,j)-(i+1,j),  d=1: (i,j)-(i,j+1)
    struct Edge {
        int d, i, j, key;
    };
    vector<Edge> edges;
    rep(i, N) rep(j, N) {
        if (c[i][j] != '.')
            continue;
        // 下方向 d=0
        if (i + 1 < N && c[i + 1][j] == '.') {
            int a = dist[i][j], b = dist[i + 1][j];
            if (a != -1 && b != -1)
                edges.push_back({0, i, j, min(a, b)});
        }
        // 右方向 d=1
        if (j + 1 < N && c[i][j + 1] == '.') {
            int a = dist[i][j], b = dist[i][j + 1];
            if (a != -1 && b != -1)
                edges.push_back({1, i, j, min(a, b)});
        }
    }
    sort(all(edges),
         [](const Edge &x, const Edge &y) { return x.key < y.key; });

    // ゴールに近いエッジ K 本に、初期状態で閉じている扉(型 2k+1)を設置
    vector<Door> doors;
    rep(k, K) {
        if (k >= (int)edges.size())
            break;
        Edge &e = edges[k];
        doors.push_back({e.d, e.i, e.j, 2 * k + 1});
    }

    // スイッチ k を盤面の端の空きマスに適当に配置
    // 端マスを (0,0)・ゴールを除いて集め、先頭から K 個使う
    vector<Pos> border;
    rep(i, N) rep(j, N) {
        bool is_border = (i == 0 || i == N - 1 || j == 0 || j == N - 1);
        if (!is_border)
            continue;
        if (c[i][j] != '.')
            continue;
        if ((i == 0 && j == 0) || (i == N - 1 && j == N - 1))
            continue;
        border.emplace_back(i, j);
    }
    vector<Switch> switches;
    rep(k, K) {
        if (k >= (int)border.size())
            break;
        switches.push_back({border[k].h, border[k].w, k});
    }

    // 出力
    cout << doors.size() << "\n";
    for (auto &dr : doors)
        cout << dr.d SP << dr.i SP << dr.j SP << dr.g << "\n";
    cout << switches.size() << "\n";
    for (auto &sw : switches)
        cout << sw.p SP << sw.q SP << sw.s << "\n";

    return 0;
}
