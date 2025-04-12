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

int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry;

int main() {
    cin >> N >> M >> Q >> L >> W;
    G.resize(M);
    rep(i, M) cin >> G[i];
    lx.resize(N);
    rx.resize(N);
    ly.resize(N);
    ry.resize(N);
    rep(i, N) { cin >> lx[i] >> rx[i] >> ly[i] >> ry[i]; }
    vector<vector<int>> best_ans(M);
    int index = 0;
    rep(i, M) {
        best_ans[i].resize(G[i]);
        rep(j, G[i]) {
            best_ans[i][j] = index;
            index++;
        }
    }
    int best_score = 1000000000;

    int loop = 0;
    while (timer.progress() < 1) {
        loop++;
        int group_num1 = mt() % M;
        int group_num2 = mt() % M;
        int index1 = mt() % G[group_num1];
        int index2 = mt() % G[group_num2];
        swap(best_ans[group_num1][index1], best_ans[group_num2][index2]);
        int sco = 0;
        rep(i, M) {
            int gy = 0, gx = 0;
            rep(j, G[i]) {
                int id = best_ans[i][j];
                gx += (rx[id] + lx[id]) / 2;
                gy += (ry[id] + ly[id]) / 2;
            }
            gx /= G[i];
            gy /= G[i];
            double dist = 0;
            rep(j, G[i]) {
                int id = best_ans[i][j];
                dist += sqrt(pow((rx[id] + lx[id]) / 2 - gx, 2) +
                             pow((ry[id] + ly[id]) / 2 - gy, 2));
            }
            dist /= G[i];
            sco += dist;
        }
        if (sco < best_score) {
            best_score = sco;
            // cerr << loop SP << best_score << endl;
        } else {
            swap(best_ans[group_num1][index1], best_ans[group_num2][index2]);
        }
    }
    cout << "!" << endl;
    rep(i, M) {
        rep(j, G[i]) { cout << best_ans[i][j] SP; }
        cout << endl;
        rep(j, G[i] - 1) {
            cout << best_ans[i][j] SP << best_ans[i][j + 1] << endl;
        }
        cout << endl;
    }

    return 0;
}
