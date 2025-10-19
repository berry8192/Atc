#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// Xorshiftによる乱数生成器
struct XorShift {
    unsigned int x, y, z, w;
    XorShift(unsigned int seed)
        : x(123456789), y(362436069), z(521288629), w(seed) {}
    unsigned int next() {
        unsigned int t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    int next_int(int min_val, int max_val) {
        return min_val + (next() % (max_val - min_val));
    }
    // [0, 1)の範囲でdouble型の乱数を生成
    double next_double() { return (double)next() / 0xFFFFFFFF; }
    // [min_val, max_val)の範囲でdouble型の乱数を生成
    double next_double(double min_val, double max_val) {
        return min_val + (max_val - min_val) * next_double();
    }
};

// 1回の攻撃の可能性を表す構造体（概念的なグラフの「辺」に相当）
struct Edge {
    double power; // この攻撃の評価値（ランダム性を含む）
    int weapon;   // 武器のインデックス
    int chest;    // 攻撃対象の宝箱のインデックス
};

bool compareEdges(const Edge &a, const Edge &b) { return a.power > b.power; }

int main() {
    // --- 入力 ---
    int N;
    cin >> N;
    vector<long long> initial_H(N);
    for (int i = 0; i < N; ++i)
        cin >> initial_H[i];
    vector<int> C(N);
    for (int i = 0; i < N; ++i)
        cin >> C[i];
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    XorShift rng(20251019);

    auto start_time = chrono::high_resolution_clock::now();
    vector<pair<int, int>> best_attacks;
    // vector<vector<int>> weapon_use_limit(N, vector<int>(N));
    // for (int i = 0; i < N; ++i) {
    //     for (int j = 0; j < N; ++j) {
    //         if (rng.next_int(0, 10) == 0) {
    //             weapon_use_limit[i][j] = 0;
    //         } else {
    //             weapon_use_limit[i][j] = C[i];
    //         }
    //     }
    // }

    // --- 制限時間いっぱいまで最適解の探索を繰り返す ---
    int loop = 0;
    while (true) {
        loop++;
        auto current_time = chrono::high_resolution_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current_time -
                                                        start_time)
                .count() > 1920) {
            break;
        }

        // --- フェーズ1: 攻撃計画の策定 ---
        // int WEAK_WEAPON_THRESHOLD = loop % 8 + 3;
        int WEAK_WEAPON_THRESHOLD = 4;
        vector<Edge> edges;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j || A[i][j] < WEAK_WEAPON_THRESHOLD) {
                    continue; // 武器は自分が入っている宝箱を開けられない、かつ弱すぎる武器は無視
                }
                // if (weapon_use_limit[i][j] == 0) {
                //     continue;
                // }
                double randomized_power = A[i][j] * rng.next_double(0.8, 1.2);
                for (int k = 0; k < C[i]; ++k) {
                    edges.push_back({randomized_power, i, j});
                }
            }
        }
        sort(edges.begin(), edges.end(), compareEdges);

        vector<vector<pair<int, int>>> attack_plan(N);
        vector<vector<bool>> R(N, vector<bool>(N, false));
        for (int i = 0; i < N; ++i) {
            R[i][i] = true; // 自分自身へは常に到達可能（推移閉包の更新に必要）
        }
        vector<long long> planned_damage(N, 0);
        vector<int> weapon_uses(N, 0);

        for (const auto &edge : edges) {
            int w = edge.weapon;
            int b = edge.chest;
            vector<bool> visited(N, false);
            if (planned_damage[b] < initial_H[b] && weapon_uses[w] < C[w] &&
                !R[b][w]) { // 辺(w, b)を追加すると b -> ... -> w -> b
                            // の閉路ができるか？

                attack_plan[b].push_back(
                    {w, A[w][b]}); // 計画には元の攻撃力を保存
                planned_damage[b] += A[w][b];
                weapon_uses[w]++;
                // adj[w].push_back(b); // <-- 削除

                // 到達可能性行列 R を O(N^2) で更新
                // 「xがwに到達可能」かつ「bがyに到達可能」ならば、
                // 辺(w, b)が追加されたことで「xがyに到達可能」になる
                for (int x = 0; x < N; ++x) {
                    if (R[x][w]) { // x が w に到達可能なら
                        for (int y = 0; y < N; ++y) {
                            if (R[b][y]) {      // b が y に到達可能なら
                                R[x][y] = true; // x は y に到達可能になる
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            if (planned_damage[i] < initial_H[i]) {
                long long needed = initial_H[i] - planned_damage[i];
                for (int j = 0; j < needed; ++j) {
                    attack_plan[i].push_back({-1, 1});
                }
            }
        }

        // --- フェーズ2: 計画の実行シミュレーション ---
        vector<long long> H = initial_H;
        vector<bool> is_chest_open(N, false);
        int open_chests_count = 0;
        vector<pair<int, int>> current_attacks;
        vector<vector<bool>> is_attack_done(N);
        for (int i = 0; i < N; ++i)
            is_attack_done[i].resize(attack_plan[i].size(), false);

        while (open_chests_count < N) {
            bool attack_found = false;
            for (int b = 0; b < N; ++b) {
                if (is_chest_open[b])
                    continue;
                for (int i = 0; i < attack_plan[b].size(); ++i) {
                    if (is_attack_done[b][i])
                        continue;
                    int w = attack_plan[b][i].first;
                    if (w == -1 || is_chest_open[w]) {
                        current_attacks.push_back({w, b});
                        H[b] -= attack_plan[b][i].second;
                        is_attack_done[b][i] = true;
                        attack_found = true;
                        if (H[b] <= 0) {
                            is_chest_open[b] = true;
                            open_chests_count++;
                        }
                        goto next_turn;
                    }
                }
            }
            if (!attack_found) {
                for (int b = 0; b < N; ++b) {
                    if (!is_chest_open[b]) {
                        current_attacks.push_back({-1, b});
                        H[b]--;
                        if (H[b] <= 0) {
                            is_chest_open[b] = true;
                            open_chests_count++;
                        }
                        break;
                    }
                }
            }
        next_turn:;
        }

        // --- 最良解の更新 ---
        if (best_attacks.empty() ||
            current_attacks.size() < best_attacks.size()) {
            best_attacks = current_attacks;
        }
    }

    // --- 出力 ---
    for (const auto &attack : best_attacks) {
        cout << attack.first << " " << attack.second << endl;
    }
    cerr << "loop, score: " << loop << " " << best_attacks.size() << endl;

    return 0;
}
