#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// DFSによる閉路検出のためのパス探索
// 依存関係グラフ`adj`において、`start`から`end`へのパスが存在するかを調べる。
// これは、`b`から`w`へのパスが既に存在する場合に辺`w -> b`を追加すると、
// 閉路(例: b -> ... -> w -> b)が形成されるのを防ぐために使用される。
bool hasPath(int start, int end, int N, const vector<vector<int>> &adj,
             vector<bool> &visited) {
    if (start == end)
        return true;
    visited[start] = true;
    for (int neighbor : adj[start]) {
        if (!visited[neighbor]) {
            if (hasPath(neighbor, end, N, adj, visited)) {
                return true;
            }
        }
    }
    return false;
}

// 1回の攻撃の可能性を表す構造体（概念的なグラフの「辺」に相当）
struct Edge {
    int power;  // この攻撃の攻撃力
    int weapon; // 武器のインデックス
    int chest;  // 攻撃対象の宝箱のインデックス
};

bool compareEdges(const Edge &a, const Edge &b) { return a.power > b.power; }

int main() {
    // Input
    int N;
    cin >> N;
    vector<long long> H(N);
    for (int i = 0; i < N; ++i)
        cin >> H[i];
    vector<int> C(N);
    for (int i = 0; i < N; ++i)
        cin >> C[i];
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    // --- フェーズ1: 攻撃計画の策定 ---
    // このフェーズでは、実際には攻撃を行わず、最適な攻撃計画を構築する。
    // 戦略はクラスカル法（最小全域木問題の解法）から着想を得ている。
    // 全ての可能な攻撃を「辺」とみなし、論理的な矛盾（依存関係の閉路）を生まない範囲で
    // 最も攻撃力の高いものから貪欲に選択していく。

    // 1. 武器の耐久値を考慮し、全ての可能な単一攻撃（辺）のリストを作成する。
    // 各武器`i`は`C[i]`回攻撃できるため、それぞれの攻撃対象に対して`C[i]`本の辺を生成する。
    vector<Edge> edges;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < C[i]; ++k) {
                edges.push_back({A[i][j], i, j});
            }
        }
    }
    // 2. 全ての可能な攻撃を、攻撃力の降順でソートする。
    // これにより、最も効果的な攻撃から貪欲に検討できるようになる。
    sort(edges.begin(), edges.end(), compareEdges);

    // 3.
    // 依存関係の閉路を作らないように、最も攻撃力の高い攻撃から順に計画に採用していく。
    vector<vector<int>> adj(
        N); // 依存関係グラフ: adj[w]には、武器wに依存する宝箱bが格納される。
    vector<vector<pair<int, int>>> attack_plan(
        N); // attack_plan[b]には、宝箱bに対する攻撃計画が格納される。
    vector<long long> planned_damage(
        N, 0); // 各宝箱に対して計画された合計ダメージを追跡する。
    vector<int> weapon_uses(
        N, 0); // 武器の計画使用回数を追跡し、耐久値`C[w]`を超えないようにする。

    for (const auto &edge : edges) {
        int w = edge.weapon;
        int b = edge.chest;
        int power = edge.power;

        if (w == b)
            continue; // 武器は自分が入っている宝箱を開けることはできない。これは論理的な制約。

        // 閉路のチェック:
        // 依存グラフにおいて`b`から`w`へのパスが既に存在する場合、 辺`w ->
        // b`を追加すると閉路が形成されてしまう。このパスの有無をDFSで確認する。
        vector<bool> visited(N, false);
        if (planned_damage[b] < H[b] && weapon_uses[w] < C[w] &&
            !hasPath(b, w, N, adj, visited)) {
            // もし攻撃が有効（宝箱にまだダメージが必要、武器に耐久値が残っている、閉路を形成しない）
            // であれば、この攻撃を計画に採用する。
            attack_plan[b].push_back({w, power});
            planned_damage[b] += power;
            weapon_uses[w]++;
            adj[w].push_back(b); // 新しい依存関係`w -> b`をグラフに追加する。
        }
    }

    // 4.
    // 全ての武器による攻撃を計画した後、残りの必要なダメージを素手の攻撃で補う。
    // 素手の攻撃には依存関係がない。
    for (int i = 0; i < N; ++i) {
        if (planned_damage[i] < H[i]) {
            long long needed = H[i] - planned_damage[i];
            for (int j = 0; j < needed; ++j) {
                attack_plan[i].push_back({-1, 1});
            }
        }
    }

    // --- フェーズ2: 計画の実行 ---
    // このフェーズでは、生成された`attack_plan`に基づき、ターンごとのシミュレーションを行い、
    // 最終的な攻撃手順を生成する。
    vector<bool> is_chest_open(N, false);
    int open_chests_count = 0;
    vector<pair<int, int>> result_attacks; // 最終的に出力する攻撃手順
    vector<vector<bool>> is_attack_done(
        N); // 計画された攻撃が実行済みかどうかを追跡する
    for (int i = 0; i < N; ++i)
        is_attack_done[i].resize(attack_plan[i].size(), false);

    // 全ての宝箱が開くまでループ。ループ1回が1ターン（1回の攻撃）に相当する。
    while (open_chests_count < N) {
        bool attack_found = false;
        // 各ターンで、全ての宝箱とその攻撃計画を走査し、現在実行可能な攻撃を探す。
        for (int b = 0; b < N; ++b) {
            if (is_chest_open[b])
                continue;
            for (int i = 0; i < attack_plan[b].size(); ++i) {
                if (is_attack_done[b][i])
                    continue;

                int w = attack_plan[b][i].first;
                // 攻撃が実行可能である条件は、
                // 1. 素手での攻撃(w == -1)である
                // 2. 必要な武器`w`が利用可能（宝箱`w`が開いている）である
                if (w == -1 || is_chest_open[w]) {
                    // 攻撃を実行する
                    result_attacks.push_back({w, b});
                    H[b] -= attack_plan[b][i].second;
                    is_attack_done[b][i] = true;
                    attack_found = true;

                    // 攻撃の結果、宝箱が開いた場合、状態を更新する。
                    // これにより、次のターン以降で新しい武器が利用可能になることがある。
                    if (H[b] <= 0) {
                        is_chest_open[b] = true;
                        open_chests_count++;
                    }
                    // 1ターンに1回攻撃したら、次のターンのためにループを抜ける。
                    goto next_turn;
                }
            }
        }

        // デッドロックからの回復処理（現在の計画ロジックでは起こらないはずだが、安全策として）。
        // 計画内で実行可能な攻撃が見つからなかった場合、計画の欠陥かデッドロックを意味する。
        // フォールバックとして、未開封の宝箱を素手で攻撃する。
        if (!attack_found) {
            for (int b = 0; b < N; ++b) {
                if (!is_chest_open[b]) {
                    result_attacks.push_back({-1, b});
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

    for (const auto &attack : result_attacks) {
        cout << attack.first << " " << attack.second << endl;
    }

    return 0;
}
