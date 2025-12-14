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
    vector<vector<long long>> B; // 機械の個数
    vector<vector<long long>> P; // 機械のパワー
    long long apples;            // りんごの数
    double score;

    State() {
        B.resize(L, vector<long long>(N, 1));
        P.resize(L, vector<long long>(N, 0));
        apples = K;
        score = 0.0;
    }

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

    // 正確な将来利得計算（積分ベース）
    double calculate_future_value(int level, int id,
                                  int remaining_turns) const {
        long long cost = C[level][id] * (P[level][id] + 1);
        if (apples < cost)
            return -1e18;

        double t = remaining_turns;

        // 現在のパワーから1増えた場合の増加分を計算
        if (level == 0) {
            // Level 0: パワー1増加で毎ターン A[id] * B[0][id] 個増える
            // 総生産 = A[id] * B[0][id] * t
            return A[id] * B[0][id] * t / cost;
        } else if (level == 1) {
            // Level 1: パワー1増加で毎ターンB[1][id]個のLevel 0機械が増える
            // k番目のターンに増えたLevel 0機械は残り(t-k)ターン稼働
            // 総生産 = A[id] * B[1][id] * Σ(t-k) for k=1..t
            //        = A[id] * B[1][id] * (t-1)*t/2
            return A[id] * B[1][id] * (t - 1) * t / 2.0 / cost;
        } else if (level == 2) {
            // Level 2: パワー1増加で毎ターンB[2][id]個のLevel 1機械が増える
            // k番目のターンに増えたLevel 1機械は残り(t-k)ターンで
            // A[id] * B[1][id] * (t-k)*(t-k-1)/2 個のりんごを生産
            // 総生産 = A[id] * B[2][id] * Σ((t-k)*(t-k-1)/2) for k=1..t
            //        = A[id] * B[2][id] * t*(t-1)*(t-2)/6
            return A[id] * B[2][id] * t * (t - 1) * (t - 2) / 6.0 / cost;
        } else {
            // Level 3: パワー1増加で毎ターンB[3][id]個のLevel 2機械が増える
            // k番目のターンに増えたLevel 2機械は残り(t-k)ターンで
            // A[id] * B[2][id] * (t-k)*(t-k-1)*(t-k-2)/6 個のりんごを生産
            // 総生産 = A[id] * B[3][id] * Σ((t-k)*(t-k-1)*(t-k-2)/6) for k=1..t
            //        = A[id] * B[3][id] * t*(t-1)*(t-2)*(t-3)/24
            if (t >= 3) {
                return A[id] * B[3][id] * t * (t - 1) * (t - 2) * (t - 3) /
                       24.0 / cost;
            } else {
                return 0.0;
            }
        }
    }

    // 可能な行動を将来利得順に列挙
    vector<pair<int, int>> get_actions_by_value(int remaining_turns) const {
        vector<pair<double, pair<int, int>>> value_actions;

        // 待機
        value_actions.push_back({0.0, {-1, -1}});

        rep(level, L) {
            rep(id, N) {
                long long cost = C[level][id] * (P[level][id] + 1);
                if (apples >= cost) {
                    double value =
                        calculate_future_value(level, id, remaining_turns);
                    value_actions.push_back({value, {level, id}});
                }
            }
        }

        // 将来利得の大きい順にソート
        sort(all(value_actions), greater<pair<double, pair<int, int>>>());

        vector<pair<int, int>> actions;
        for (auto [value, action] : value_actions) {
            actions.push_back(action);
        }
        return actions;
    }

    bool operator>(const State &other) const { return score > other.score; }
};

// 木構造用の軽量ノード
struct Node {
    int parent_idx;
    pair<int, int> action;

    Node(int p, pair<int, int> a) : parent_idx(p), action(a) {}
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

    int beam_width = 100; // 幅を増やす

    vector<State> current_beam;
    current_beam.push_back(State());

    vector<Node> tree;
    tree.push_back(Node(-1, {-1, -1}));

    vector<int> current_tree_indices = {0};

    rep(turn, T) {
        int remaining_turns = T - turn;

        vector<State> next_beam;
        vector<int> next_tree_indices;
        vector<pair<double, int>> score_pairs;

        int base_tree_size = tree.size();

        rep(beam_idx, current_beam.size()) {
            const State &parent = current_beam[beam_idx];
            int parent_tree_idx = current_tree_indices[beam_idx];

            // 将来利得順に行動を取得
            vector<pair<int, int>> actions =
                parent.get_actions_by_value(remaining_turns);

            // 上位20個に増やす（より多くの選択肢を試す）
            if (actions.size() > 20) {
                actions.resize(20);
            }

            for (auto action : actions) {
                State new_state = parent;

                int level = action.first;
                int id = action.second;

                if (level != -1) {
                    new_state.upgrade(level, id);
                }
                new_state.produce();

                // 評価関数：現在の生産量 + 将来利得の加重平均
                new_state.score = new_state.evaluate();

                // 将来の期待値も加味
                double future_potential = 0.0;
                rep(lv, L) {
                    rep(id2, N) {
                        if (new_state.P[lv][id2] > 0) {
                            future_potential +=
                                new_state.calculate_future_value(
                                    lv, id2, remaining_turns - 1) *
                                0.01;
                        }
                    }
                }
                new_state.score += future_potential;

                int new_tree_idx = tree.size();
                tree.push_back(Node(parent_tree_idx, action));

                score_pairs.push_back({new_state.score, next_beam.size()});
                next_beam.push_back(new_state);
                next_tree_indices.push_back(new_tree_idx);
            }
        }

        // スコアでソート（降順）
        sort(all(score_pairs), greater<pair<double, int>>());

        // beam_width個に絞る
        vector<State> selected_beam;
        vector<int> selected_tree_indices;

        rep(i, min(beam_width, (int)score_pairs.size())) {
            int idx = score_pairs[i].second;
            selected_beam.push_back(next_beam[idx]);
            selected_tree_indices.push_back(next_tree_indices[idx]);
        }

        current_beam = move(selected_beam);
        current_tree_indices = move(selected_tree_indices);

        // 進捗表示
        if (turn % 100 == 0) {
            cerr << "Turn: " << turn << " / " << T
                 << ", Beam size: " << current_beam.size() << endl;
        }
    }

    // 最良の状態から行動列を復元
    if (!current_beam.empty()) {
        State best = current_beam[0];
        int best_tree_idx = current_tree_indices[0];

        long long final_score = round(1e5 * log2((double)best.apples));
        cerr << "Score: " << final_score << endl;

        // 行動列を復元
        vector<pair<int, int>> actions;
        int idx = best_tree_idx;
        while (idx != -1 && idx < tree.size()) {
            if (tree[idx].action.first != -1 || tree[idx].action.second != -1) {
                actions.push_back(tree[idx].action);
            }
            idx = tree[idx].parent_idx;
        }
        reverse(all(actions));

        // 出力
        for (auto action : actions) {
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
