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

int N, L;
vector<int> T;

struct Touban {
    vector<int> a;
    vector<int> b;
    int score = -1;

    Touban() {
        a.resize(N);
        b.resize(N);
    }

    void random() {
        rep(i, N) {
            // a[i] = mt() % N;
            // b[i] = mt() % N;
            a[i] = (i + 1) % N;
            b[i] = (i + 1) % N;
        }
    }

    int calc_score() {
        int sco = 1000000;
        vector<int> cleaned(N);
        int cur = 0;
        bool skipped = false;
        rep(i, L) {
            bool is_odd = cleaned[cur] & 1;
            cleaned[cur]++;
            cur = is_odd ? b[cur] : a[cur];
        }
        rep(i, N) { sco -= abs(T[i] - cleaned[i]); }
        return sco;
    }

    void print_ans() { rep(i, N) cout << a[i] SP << b[i] << endl; }
};

void inpt() {
    cin >> N >> L;
    T.resize(N);
    rep(i, N) cin >> T[i];
}

int main() {
    start = chrono::system_clock::now();
    inpt();
    Touban best;
    best.random();
    cerr << best.calc_score() << endl;
    best.print_ans();

    return 0;
}
