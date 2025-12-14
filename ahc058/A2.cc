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

        // 簡易計算: A * (500^level)
        double base_value = A[id];
        rep(i, level) { base_value *= 500.0; }

        return base_value / cost;
    }

    // 何ターン待てば購入できるか計算
    int turns_until_affordable(int level, int id) const {
        long long cost = C[level][id] * (P[level][id] + 1);
        if (apples >= cost)
            return 0;

        long long production = 0;
        rep(j, N) { production += A[j] * B[0][j] * P[0][j]; }

        if (production == 0)
            return 1000000; // 生産量0なら永遠に買えない

        long long shortage = cost - apples;
        int turns = (shortage + production - 1) / production; // 切り上げ
        return turns;
    }

    // 可能な行動を将来利得順に列挙（待機近傍を含む）
    vector<pair<int, int>> get_actions_by_value(int remaining_turns) const {
        vector<pair<double, pair<int, int>>> value_actions;

        // 待機
        value_actions.push_back({0.0, {-1, -1}});

        rep(level, L) {
            rep(id, N) {
                long long cost = C[level][id] * (P[level][id] + 1);
                if (apples >= cost) {
                    // 即座に購入可能
                    double value =
                        calculate_future_value(level, id, remaining_turns);
                    value_actions.push_back({value, {level, id}});
                } else {
                    // 将来購入可能か確認
                    int wait_turns = turns_until_affordable(level, id);
                    if (wait_turns > 0 && wait_turns <= 100 &&
                        wait_turns < remaining_turns) {
                        // 待機してから購入する価値を計算
                        // wait_turns後に購入し、残りremaining_turns -
                        // wait_turnsターンで稼ぐ
                        int future_remaining = remaining_turns - wait_turns;
                        if (future_remaining > 0) {
                            // 待機コストを考慮（生産機会損失）
                            double future_value = calculate_future_value(
                                level, id, future_remaining);
                            // 待機分を割り引く
                            double discounted_value =
                                future_value; // 待機のペナルティなし

                            // 特殊な行動ID: (level, -id-2)
                            // で「idのlevelを買うために待機」を表現
                            // 負の値で待機ターン数をエンコード: -(id * 1000 +
                            // wait_turns + 10)
                            int encoded = -(id * 1000 + wait_turns + 10);
                            value_actions.push_back(
                                {discounted_value, {level, encoded}});
                        }
                    }
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

    int beam_width = 100;

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

            // 上位30個に増やす（待機近傍を含むため）
            if (actions.size() > 30) {
                actions.resize(30);
            }

            for (auto action : actions) {
                int level = action.first;
                int id = action.second;

                // 待機行動のデコード
                bool is_wait_action = (id < -1);
                int actual_id = id;
                int wait_turns = 1;

                if (is_wait_action) {
                    int encoded = -id;
                    encoded -= 10;
                    wait_turns = encoded % 1000;
                    actual_id = encoded / 1000;
                }

                // wait_turnsターン待機してから購入
                State new_state = parent;

                if (is_wait_action) {
                    // wait_turnsターン分の生産を実行
                    rep(w, wait_turns) {
                        new_state.produce();
                        if (w == wait_turns - 1) {
                            // 最後のターンで購入
                            if (new_state.apples >=
                                C[level][actual_id] *
                                    (new_state.P[level][actual_id] + 1)) {
                                new_state.upgrade(level, actual_id);
                            }
                        }
                    }
                    // 行動記録は最初の待機として記録
                    tree.push_back(
                        Node(parent_tree_idx, {-1, -1})); // 待機の記録
                } else {
                    // 通常の行動
                    if (level != -1) {
                        new_state.upgrade(level, actual_id);
                    }
                    new_state.produce();
                    tree.push_back(Node(parent_tree_idx, action));
                }

                // 評価関数：現在の生産量 + 将来利得の加重平均
                new_state.score = new_state.evaluate();

                // 将来の期待値も加味
                double future_potential = 0.0;
                rep(lv, L) {
                    rep(id2, N) {
                        if (new_state.P[lv][id2] > 0) {
                            future_potential +=
                                new_state.calculate_future_value(
                                    lv, id2,
                                    remaining_turns -
                                        (is_wait_action ? wait_turns : 1)) *
                                0.01;
                        }
                    }
                }
                new_state.score += future_potential;

                int new_tree_idx = tree.size() - 1;

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
