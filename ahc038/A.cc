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

int N, M, V;
vector<string> s, t;
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
string dc = "RULD";

void inpt() {
    cin >> N >> M >> V;
    HEIGHT = N;
    WIDTH = N;
    s.resize(N);
    t.resize(N);
    rep(i, N) { cin >> s[i]; }
    rep(i, N) { cin >> t[i]; }
}

void zero_tree() {
    cout << 1 << endl;

    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1' && t[i][j] == '1') {
                s[i][j] = '0';
                t[i][j] = '0';
            }
        }
    }
    Pos pos;
    rep(i, N) {
        rep(j, N) {
            if (s[i][j] == '1') {
                pos = {i, j};
                i = N;
                break;
            }
        }
    }
    cout << pos.h SP << pos.w << endl;
    s[pos.h][pos.w] = '0';
    cout << ".P" << endl;
    bool hold = true;
    while (1) {
        // if (hold) {
        //     cout << "hold" << endl;
        // } else {
        //     cout << "not hold" << endl;
        // }
        int min_dist = imax;
        Pos min_dist_pos;
        rep(i, N) {
            rep(j, N) {
                if (hold) {
                    if (t[i][j] == '1') {
                        int tmp = pos.manhattan({i, j});
                        if (tmp < min_dist) {
                            min_dist = tmp;
                            min_dist_pos = {i, j};
                        }
                    }
                } else {
                    if (s[i][j] == '1') {
                        int tmp = pos.manhattan({i, j});
                        if (tmp < min_dist) {
                            min_dist = tmp;
                            min_dist_pos = {i, j};
                        }
                    }
                }
            }
        }
        // cout << "min_dist_pos: "; //
        // min_dist_pos.print(); //

        if (hold) {
            t[min_dist_pos.h][min_dist_pos.w] = '0';
        } else {
            s[min_dist_pos.h][min_dist_pos.w] = '0';
        }

        if (min_dist == imax) {
            exit(0);
        }
        while (!(pos == min_dist_pos)) {
            int min_dir_dist = imax;
            int min_dir_dist_index;
            Pos npos;
            rep(i, 4) {
                npos = pos + d4[i];
                int tmp = npos.manhattan(min_dist_pos);
                // cout << tmp << endl; //
                if (tmp < min_dir_dist) {
                    min_dir_dist = tmp;
                    min_dir_dist_index = i;
                }
            }
            pos = pos + d4[min_dir_dist_index];
            // cout << "pos: "; //
            // pos.print(); //
            cout << dc[min_dir_dist_index];
            if (pos == min_dist_pos) {
                cout << 'P' << endl;
            } else {
                cout << '.' << endl;
            }
        }
        hold = !hold;
    }
}

int main() {
    start = chrono::system_clock::now();
    inpt();
    zero_tree();

    Grid best;

    int loop = 0;
    while (1) {
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start)
                .count() > TIME_LIMIT) {
            // break;
        }
        loop++;

        Grid grid;

        // if (best.score < grid.score) {
        // best = space;
        // cout<< "loop: " << loop <<endl;
        // best.print_ans();
        // cout<< "score: " << space.score SP << space.score*25 <<endl;
        // }
    }
    // cout<< space.score SP << space.score*25 <<endl;
    // best.print_ans();

    return 0;
}
