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

    int beam_width = 50; // メモリ削減のため幅を減らす

    vector<State> current_beam;
    current_beam.push_back(State());

    vector<Node> tree; // 行動の木構造のみ保持
    tree.push_back(Node(-1, {-1, -1}));

    vector<int> current_tree_indices = {0};

    rep(turn, T) {
        vector<State> next_beam;
        vector<int> next_tree_indices;
        vector<pair<double, int>> score_pairs; // {score, index}

        int base_tree_size = tree.size();

        rep(beam_idx, current_beam.size()) {
            const State &parent = current_beam[beam_idx];
            int parent_tree_idx = current_tree_indices[beam_idx];

            vector<pair<int, int>> actions = parent.get_actions();

            // 行動数が多すぎる場合は間引く
            if (actions.size() > 15) {
                vector<pair<long long, pair<int, int>>> cost_actions;
                for (auto action : actions) {
                    int level = action.first;
                    int id = action.second;
                    if (level != -1) {
                        long long cost =
                            C[level][id] * (parent.P[level][id] + 1);
                        cost_actions.push_back({cost, action});
                    }
                }
                sort(all(cost_actions));
                actions.clear();
                actions.push_back({-1, -1});
                rep(i, min(14, (int)cost_actions.size())) {
                    actions.push_back(cost_actions[i].second);
                }
            }

            for (auto action : actions) {
                State new_state = parent;

                int level = action.first;
                int id = action.second;

                if (level != -1) {
                    new_state.upgrade(level, id);
                }
                new_state.produce();
                new_state.score = new_state.evaluate();

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
            cerr << "Turn: " << turn << " / " << T << endl;
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
