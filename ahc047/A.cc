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

int N, M, L;
vector<string> S;
vector<int> P;

struct Model {
    vector<char> C;
    vector<vector<int>> A;
    Model() {
        C.assign(M, 'a');
        A.assign(M, vector<int>(M, 0));
        for (int i = 0; i < M; i++) {
            A[i][0] = 100;
        }
    }
    void print_ans() {
        for (int i = 0; i < M; i++) {
            cout << C[i];
            for (int j = 0; j < M; j++) {
                cout << " " << A[i][j];
            }
            cout << endl;
        }
    }
    double
    compute_word_probability(const std::vector<char> &word, int L,
                             const std::vector<char> &C,
                             const std::vector<std::vector<int>> &A) const {
        int M = C.size();
        int n = 0;
        std::map<std::pair<int, int>, int> states;
        for (int j = 0; j < M; ++j) {
            states[{0, j}] = n++;
            for (int i = 0; i + 1 < word.size(); ++i) {
                if (word[i] == C[j]) {
                    states[{i + 1, j}] = n++;
                }
            }
        }
        std::vector<double> X(n * n, 0.0);
        for (const auto &kv : states) {
            int len = kv.first.first, u = kv.first.second, j = kv.second;
            for (int v = 0; v < M; ++v) {
                std::vector<char> next(word.begin(), word.begin() + len);
                next.push_back(C[v]);
                int s = 0;
                while (s < next.size() &&
                       std::vector<char>(next.begin() + s, next.end()) !=
                           std::vector<char>(word.begin(),
                                             word.begin() + next.size() - s)) {
                    ++s;
                }
                if (next.size() - s != word.size()) {
                    int i2 = states[{int(next.size() - s), v}];
                    X[i2 * n + j] += A[u][v] / 100.0;
                }
            }
        }
        // 行列累乗
        int power = L - 1;
        std::vector<double> Y(n * n, 0.0);
        for (int i = 0; i < n; ++i)
            Y[i * n + i] = 1.0;
        auto mul = [&](const std::vector<double> &a,
                       const std::vector<double> &b) {
            std::vector<double> c(n * n, 0.0);
            for (int i = 0; i < n; ++i)
                for (int k = 0; k < n; ++k)
                    for (int j = 0; j < n; ++j)
                        c[i * n + j] += a[i * n + k] * b[k * n + j];
            return c;
        };
        std::vector<double> Xpow = X;
        while (power > 0) {
            if (power & 1)
                Y = mul(Y, Xpow);
            Xpow = mul(Xpow, Xpow);
            power >>= 1;
        }
        int init;
        if (C[0] == word[0]) {
            init = states[{1, 0}];
        } else {
            init = states[{0, 0}];
        }
        double ret = 1.0;
        for (int i = 0; i < n; ++i)
            ret -= Y[i * n + init];
        if (ret < 0.0)
            ret = 0.0;
        if (ret > 1.0)
            ret = 1.0;
        return ret;
    }
    // 得点計算
    long long compute_score(const vector<string> &S, const vector<int> &P,
                            int N, int M, int L, string &err) const {
        for (int i = 0; i < M; ++i) {
            int sum = 0;
            for (int j = 0; j < M; ++j)
                sum += A[i][j];
            if (sum != 100) {
                err = "Sum of A[" + to_string(i) + "] is not 100 (" +
                      to_string(sum) + ")";
                return 0;
            }
        }
        double total_score = 0.0;
        for (int i = 0; i < N; ++i) {
            vector<char> word(S[i].begin(), S[i].end());
            double prob = compute_word_probability(word, L, C, A);
            total_score += prob * P[i];
        }
        err = "";
        return static_cast<long long>(round(total_score));
    }
};

void inpt() {
    cin >> N >> M >> L;
    S.resize(N);
    P.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> P[i];
    }
}

int main() {
    inpt();
    Model model;
    string err;
    long long score = model.compute_score(S, P, N, M, L, err);
    cerr << "Initial score: " << score << endl;
    model.print_ans();
    return 0;
}
