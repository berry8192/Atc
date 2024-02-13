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

int N, M, eps;

int ask(const vector<Pos> &poses) {
    cout << "q" SP << poses.size() SP;
    rep(i, poses.size()) { cout << poses[i].h SP << poses[i].w SP; }
    cout << endl;

    int rtn;
    cin >> rtn;
    return rtn;
}

// 構造体
struct Pos {
    int h;
    int w;

    Pos(){};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < N && 0 <= w && w < N);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * N + w; }
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

struct Probability {
    int val;
    double prob;

    Probability(){};
    Probability(int ival, double iprob) {
        val = ival;
        prob = iprob;
    }
};

struct Poly {
    int d;
    vector<Pos> poses;

    Poly(){};
};

struct Grid {
    vector<Pos> estimates;
    vector<vector<Probability>> probability;

    void init() {
        probability.resize(N);
        rep(i, N) probability[i].resize(N);
    }

    void itv_serach() {
        for (int i = 1; i < N - 1; i += 2) {
            for (int j = 1; j < N - 1; j += 2) {
                probability[i][j] = {ask({i, j}), 1.0};
            }
        }
    }

    void ans() {
        cout << "a" SP << estimates.size() SP;
        rep(i, estimates.size()) {
            cout << estimates[i].h SP << estimates[i].w SP;
        }
        cout << endl;

        int rtn;
        cin >> rtn;
        if (rtn == 1)
            exit(0);
    }
};

Pos itop(int idx) { return {idx / N, idx % N}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

void inpt() {
    cin >> N >> M >> eps;
    int d, ii, jj;
    rep(i, M) {
        Poly poly;
        cin >> d;
        poly.d = d;
        rep(j, d) {
            cin >> ii >> jj;
            poly.poses.push_back({ii, jj});
        }
    }
}

int main() {
    start = chrono::system_clock::now();

    Grid best;
    best.init();
    best.itv_serach();
    return 0;

    int loop = 0;
    while (1) {
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start)
                .count() > TIME_LIMIT) {
            // break;
        }
        loop++;
    }

    return 0;
}
