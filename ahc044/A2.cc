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
template <class T> void PV(T pvv) {
    if (!pvv.size())
        return;
    rep(i, pvv.size() - 1) cout << pvv[i] << ", ";
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
vector<pair<int, int>> pair_T;

struct Touban {
    vector<int> a;
    vector<int> b;
    vector<int> cleaned;
    vector<pair<int, int>> p_cleaned;
    vector<pair<int, int>> p_T = pair_T;
    int score = -1;

    Touban() {
        a.resize(N);
        b.resize(N);
    }

    void random() {
        rep(i, N) {
            a[i] = mt() % N;
            b[i] = mt() % N;
        }
    }
    void k_random() {
        vector<int> tmp;
        int zero;
        if (T[0] <= 10000 / 3) {
            zero = 1;
        } else if (T[0] <= 2 * 10000 / 3) {
            zero = 2;
        } else {
            zero = 3;
        }
        rep(i, zero) { tmp.push_back(0); }
        rep3(i, N / 3, 1) { tmp.push_back(i); }
        rep3(i, 2 * N / 3 + 1, N / 3) { rep(j, 2) tmp.push_back(i); }
        rep3(i, N, 2 * N / 3 + 1) { rep(j, 3) tmp.push_back(i); }
        // cerr << tmp.size() << endl;
        // rep(i, tmp.size()) { cout << tmp[i] << endl; }
        // exit(0);
        shuffle(all(tmp), mt);
        rep(i, N) {
            a[i] = tmp[i];
            b[i] = tmp[i + N];
        }
    }
    void calc_cleaned() {
        // cerr << "calc_cleaned" << endl;
        cleaned.clear();
        cleaned.resize(N);
        int cur = 0;
        bool skipped = false;
        rep(i, L) {
            bool is_odd = cleaned[cur] & 1;
            cleaned[cur]++;
            cur = is_odd ? b[cur] : a[cur];
        }
        rep(i, N) { p_cleaned.push_back({cleaned[i], i}); }
        sort(all(p_cleaned));
    }
    void rough_calc_cleaned(int div) {
        // cerr << "calc_cleaned" << endl;
        cleaned.clear();
        cleaned.resize(N);
        int cur = 0;
        rep(i, L / div) {
            bool is_odd = cleaned[cur] & 1;
            cleaned[cur] += div;
            cur = is_odd ? b[cur] : a[cur];
        }
        rep(i, N) { p_cleaned.push_back({cleaned[i], i}); }
        sort(all(p_cleaned));
    }
    void match_all_clean() {
        for (int i = N - 1; i >= 1; i--) {
            match_clean(i);
        }
    }
    int detect_idx(vector<pair<int, int>> pairs, int val) {
        rep(i, pairs.size()) {
            if (pairs[i].second == val)
                return i;
        }
        assert(false);
        return -1;
    }
    void swap_idx(int t_idx, int c_idx) {
        // cerr << "swap_idx" SP << t_idx SP << c_idx << endl;
        swap(a[t_idx], a[c_idx]);
        swap(b[t_idx], b[c_idx]);
        rep(i, N) {
            int temp_a = a[i];
            int temp_b = b[i];
            int temp_p_T = p_T[i].second;
            int temp_p_cleaned = p_cleaned[i].second;

            if (temp_a == t_idx) {
                a[i] = c_idx;
            } else if (temp_a == c_idx) {
                a[i] = t_idx;
            }
            if (temp_b == t_idx) {
                b[i] = c_idx;
            } else if (temp_b == c_idx) {
                b[i] = t_idx;
            }
            // if (temp_p_T == t_idx) {
            //     p_T[i].second = c_idx;
            // } else if (temp_p_T == c_idx) {
            //     p_T[i].second = t_idx;
            // }
            if (temp_p_cleaned == t_idx) {
                p_cleaned[i].second = c_idx;
            } else if (temp_p_cleaned == c_idx) {
                p_cleaned[i].second = t_idx;
            }
        }
    }
    void match_clean(int idx) {
        // cerr << "match_clean" SP << idx << endl;
        int t_idx = detect_idx(p_T, idx);
        int cleaned_idx = p_cleaned[t_idx].second;
        // cout << T[idx] SP << cleaned[cleaned_idx] << endl;
        // cout << idx SP << cleaned_idx << endl;
        if (cleaned_idx != 0) {
            swap_idx(idx, cleaned_idx);
        }
    }

    void calc_score() {
        int sco = 1000000;
        vector<int> cleaned(N);
        int cur = 0;
        rep(i, L) {
            bool is_odd = cleaned[cur] & 1;
            cleaned[cur]++;
            cur = is_odd ? b[cur] : a[cur];
        }
        rep(i, N) { sco -= abs(T[i] - cleaned[i]); }
        score = sco;
    }
    void rough_calc_score(int div) {
        int sco = 1000000;
        vector<int> cleaned(N);
        int cur = 0;
        rep(i, L / div) {
            bool is_odd = cleaned[cur] & 1;
            cleaned[cur] += div;
            cur = is_odd ? b[cur] : a[cur];
        }
        rep(i, N) { sco -= abs(T[i] - cleaned[i]); }
        score = sco;
    }

    void print_ans() { rep(i, N) cout << a[i] SP << b[i] << endl; }
};

void inpt() {
    cin >> N >> L;
    T.resize(N);
    rep(i, N) {
        cin >> T[i];
        pair_T.push_back({T[i], i});
    }
    sort(all(pair_T));
}

int main() {
    start = chrono::system_clock::now();
    inpt();
    Touban best;
    best.k_random();
    best.calc_cleaned();
    best.match_all_clean();
    best.calc_score();

    int loop = 0;
    while (timer.progress() < 1) {
        loop++;
        Touban touban;
        touban.k_random();
        touban.rough_calc_cleaned(101);
        // touban.calc_cleaned();
        touban.match_all_clean();
        touban.rough_calc_score(101);
        // touban.calc_score();
        // cerr << loop SP << touban.score << endl;
        if (touban.score > best.score) {
            touban.calc_score();
            if (touban.score > best.score) {
                best = touban;
                cerr << loop SP << best.score << endl;
            }
        }
    }
    best.print_ans();

    return 0;
}
