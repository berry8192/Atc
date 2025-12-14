#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

long long llimax = 9223372036854775807;
chrono::system_clock::time_point start_time;
double TIME_LIMIT = 1900.0;

int N, L, T, K;
vector<int> A;
vector<vector<long long>> C;

struct State {
    vector<vector<long long>> B;    // 機械の個数
    vector<vector<long long>> P;    // 機械のパワー
    long long apples;               // りんごの数
    vector<pair<int, int>> history; // 行動履歴
    double score;

    State() {
        B.resize(L, vector<long long>(N, 1));
        P.resize(L, vector<long long>(N, 0));
        apples = K;
        score = 0.0;
    }

    State(const State &other) = default;

    // 評価関数：1ターンあたりのりんご生産量
    double evaluate() {
        long long production = 0;
        rep(j, N) { production += A[j] * B[0][j] * P[0][j]; }
        return (double)production;
    }

    // 機械を強化
    bool upgrade(int level, int id) {
        long long cost = C[level][id] * (P[level][id] + 1);
        if (apples >= cost) {
            apples -= cost;
            P[level][id]++;
            return true;
        }
        return false;
    }

    // 生産処理
    void produce() {
        rep(i, L) {
            rep(j, N) {
                if (i == 0) {
                    apples += A[j] * B[i][j] * P[i][j];
                } else {
                    B[i - 1][j] += B[i][j] * P[i][j];
                }
            }
        }
    }

    // 次の状態を生成
    State next_state(int level, int id) const {
        State new_state = *this;
        if (level == -1) {
            // 何もしない
            new_state.history.push_back({-1, -1});
        } else {
            bool success = new_state.upgrade(level, id);
            if (success) {
                new_state.history.push_back({level, id});
            } else {
                new_state.history.push_back({-1, -1});
            }
        }
        new_state.produce();
        new_state.score = new_state.evaluate();
        return new_state;
    }

    // 可能な行動を列挙
    vector<pair<int, int>> get_actions() const {
        vector<pair<int, int>> actions;
        actions.push_back({-1, -1}); // 待機
        rep(level, L) {
            rep(id, N) {
                long long cost = C[level][id] * (P[level][id] + 1);
                if (apples >= cost) {
                    actions.push_back({level, id});
                }
            }
        }
        return actions;
    }

    bool operator<(const State &other) const { return score < other.score; }
    bool operator>(const State &other) const { return score > other.score; }
};

void inpt() {
    cin >> N >> L >> T >> K;
    A.resize(N);
    rep(i, N) cin >> A[i];
    C.resize(L, vector<long long>(N));
    rep(i, L) {
        rep(j, N) { cin >> C[i][j]; }
    }
}

int main() {
    start_time = chrono::system_clock::now();
    inpt();

    int beam_width = 10;
    vector<State> current_beam;
    current_beam.push_back(State());

    rep(turn, T) {
        vector<State> next_beam;

        for (const State &st : current_beam) {
            vector<pair<int, int>> actions = st.get_actions();
            for (auto action : actions) {
                int level = action.first;
                int id = action.second;
                State new_state = st.next_state(level, id);
                next_beam.push_back(new_state);
            }
        }

        // スコアでソート（降順）
        sort(all(next_beam), greater<State>());

        // beam_width個に絞る
        if (next_beam.size() > beam_width) {
            next_beam.resize(beam_width);
        }

        current_beam = next_beam;
    }

    // 最良の状態を出力
    if (!current_beam.empty()) {
        State best = current_beam[0];
        long long final_score = round(1e5 * log2((double)best.apples));
        cerr << "Score: " << final_score << endl;

        for (auto action : best.history) {
            int level = action.first;
            int id = action.second;
            if (level == -1) {
                cout << -1 << endl;
            } else {
                cout << level SP << id << endl;
            }
        }
    }

    return 0;
}
