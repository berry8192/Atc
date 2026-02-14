#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

// 定数
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

// グローバル変数
int N, M, T, U;
vector<vector<int>> V;  // 価値マップ
vector<pair<int, int>> start_pos;  // 初期位置
vector<pair<int, int>> piece_pos;  // 駒の位置
vector<vector<int>> owner;  // 所有者 (-1: なし, 0~M-1: プレイヤー)
vector<vector<int>> level;  // レベル
int current_turn = 0;

// 入力読み込み
void read_initial_input() {
    cin >> N >> M >> T >> U;

    V.assign(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> V[i][j];

    start_pos.resize(M);
    rep(p, M) {
        cin >> start_pos[p].first >> start_pos[p].second;
    }

    // 初期化
    piece_pos = start_pos;
    owner.assign(N, vector<int>(N, -1));
    level.assign(N, vector<int>(N, 0));

    rep(p, M) {
        int x = start_pos[p].first;
        int y = start_pos[p].second;
        owner[x][y] = p;
        level[x][y] = 1;
    }
}

// ターン結果の読み込み
void read_turn_result() {
    // 各プレイヤーの移動先
    vector<pair<int, int>> targets(M);
    rep(p, M) {
        cin >> targets[p].first >> targets[p].second;
    }

    // 各プレイヤーの駒の最終位置
    rep(p, M) {
        cin >> piece_pos[p].first >> piece_pos[p].second;
    }

    // 盤面の所有者
    rep(i, N) rep(j, N) cin >> owner[i][j];

    // 盤面のレベル
    rep(i, N) rep(j, N) cin >> level[i][j];
}

// 到達可能領土を取得（BFS）
set<pair<int, int>> get_reachable_territory() {
    set<pair<int, int>> reachable;
    queue<pair<int, int>> q;

    int sx = piece_pos[0].first;
    int sy = piece_pos[0].second;

    q.push({sx, sy});
    reachable.insert({sx, sy});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        rep(d, 4) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (reachable.count({nx, ny})) continue;
            if (owner[nx][ny] != 0) continue;  // 自分の領土でない

            reachable.insert({nx, ny});
            q.push({nx, ny});
        }
    }

    return reachable;
}

// 移動可能マスを取得
vector<pair<int, int>> get_movable_cells() {
    auto reachable = get_reachable_territory();
    set<pair<int, int>> movable_set;

    // 到達可能領土を追加
    for (auto pos : reachable) {
        movable_set.insert(pos);
    }

    // 到達可能領土の隣接マスを追加
    for (auto [x, y] : reachable) {
        rep(d, 4) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

            // 他のプレイヤーの駒がいる場所は除外
            bool has_other_piece = false;
            rep(p, M) {
                if (p == 0) continue;
                if (piece_pos[p].first == nx && piece_pos[p].second == ny) {
                    has_other_piece = true;
                    break;
                }
            }

            if (!has_other_piece) {
                movable_set.insert({nx, ny});
            }
        }
    }

    return vector<pair<int, int>>(all(movable_set));
}

// マスの評価値を計算
double evaluate_cell(int x, int y) {
    double value = V[x][y];
    int remaining_turns = T - current_turn;

    // フェーズ判定
    double early_phase = max(0.0, 1.0 - current_turn / 30.0);  // 序盤(0-30ターン)
    double late_phase = max(0.0, (current_turn - 70.0) / 30.0);  // 終盤(70-100ターン)
    double mid_phase = 1.0 - early_phase - late_phase;  // 中盤

    if (owner[x][y] == -1) {
        // 未占領: 新規領土の価値
        // 序盤は積極的に、終盤は控えめに
        double base_score = value * 1.0;
        double phase_bonus = early_phase * 0.5 - late_phase * 0.3;
        return base_score * (1.0 + phase_bonus);

    } else if (owner[x][y] == 0) {
        // 自分の領土: レベルアップの価値
        if (level[x][y] < U) {
            // レベルアップによるスコア増加: value * 残りターン数
            // ただし、レベルが低いほど価値が高い（上限まで何度も上げられる）
            int level_up_potential = U - level[x][y];
            double potential_gain = value * min(remaining_turns, level_up_potential);

            // 終盤はレベルアップをより重視
            double phase_bonus = late_phase * 0.5;
            return potential_gain * (1.0 + phase_bonus);
        } else {
            return 0.0;  // レベル上限に達している
        }

    } else {
        // 他プレイヤーの領土: 攻撃の価値
        if (level[x][y] == 1) {
            // レベル1は1ターンで奪取可能
            double gain = value * min(remaining_turns, U);
            double phase_bonus = mid_phase * 0.3;
            return gain * (0.9 + phase_bonus);
        } else if (level[x][y] == 2) {
            // レベル2は2ターンで奪取可能だが、コストが高い
            if (remaining_turns >= 3) {
                double gain = value * min(remaining_turns - 1, U);
                return gain * 0.5;
            }
            return value * 0.2;
        } else {
            // レベル3以上は基本的に避ける
            return value * 0.1 / level[x][y];
        }
    }
}

// 最良の手を選択
pair<int, int> select_best_move() {
    auto movable = get_movable_cells();

    if (movable.empty()) {
        // 移動不可能な場合は現在位置を返す
        return piece_pos[0];
    }

    double best_score = -1;
    pair<int, int> best_move = movable[0];

    for (auto [x, y] : movable) {
        double score = evaluate_cell(x, y);

        if (score > best_score) {
            best_score = score;
            best_move = {x, y};
        }
    }

    return best_move;
}

int main() {
    // 初期入力
    read_initial_input();

    // 各ターンの処理
    rep(turn, T) {
        current_turn = turn;

        // 最良の手を選択
        auto [x, y] = select_best_move();

        // 出力（flush必須）
        cout << x SP << y << endl;
        cout.flush();

        // ターン結果の読み込み
        read_turn_result();
    }

    return 0;
}
