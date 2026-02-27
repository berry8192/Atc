#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};

int N, M, T, U;
vector<vector<int>> V;
vector<pair<int, int>> piece_pos;
vector<vector<int>> owner;
vector<vector<int>> level;

// ---- I/O ----
void read_initial_input() {
    cin >> N >> M >> T >> U;
    V.assign(N, vector<int>(N));
    rep(i, N) rep(j, N) cin >> V[i][j];
    piece_pos.resize(M);
    rep(p, M) cin >> piece_pos[p].first >> piece_pos[p].second;
    owner.assign(N, vector<int>(N, -1));
    level.assign(N, vector<int>(N, 0));
    rep(p, M) {
        owner[piece_pos[p].first][piece_pos[p].second] = p;
        level[piece_pos[p].first][piece_pos[p].second] = 1;
    }
}

void read_turn_result() {
    // targets (全プレイヤー)
    rep(p, M) { int a, b; cin >> a >> b; }
    // positions
    rep(p, M) cin >> piece_pos[p].first >> piece_pos[p].second;
    rep(i, N) rep(j, N) cin >> owner[i][j];
    rep(i, N) rep(j, N) cin >> level[i][j];
}

// ---- ボードロジック ----
set<pair<int, int>> get_reachable(int player) {
    set<pair<int, int>> reachable;
    queue<pair<int, int>> q;
    auto [sx, sy] = piece_pos[player];
    q.push({sx, sy});
    reachable.insert({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        rep(d, 4) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (reachable.count({nx, ny})) continue;
            if (owner[nx][ny] != player) continue;
            reachable.insert({nx, ny});
            q.push({nx, ny});
        }
    }
    return reachable;
}

vector<pair<int, int>> get_movable(int player) {
    auto reachable = get_reachable(player);
    set<pair<int, int>> movable(all(reachable));
    for (auto& [x, y] : reachable) {
        rep(d, 4) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            bool blocked = false;
            rep(p, M) {
                if (p == player) continue;
                if (piece_pos[p].first == nx && piece_pos[p].second == ny) {
                    blocked = true;
                    break;
                }
            }
            if (!blocked) movable.insert({nx, ny});
        }
    }
    return vector<pair<int, int>>(all(movable));
}

// ---- 敵マスまでの最短マンハッタン距離 ----
vector<vector<int>> calc_enemy_manhattan() {
    vector<vector<int>> dist(N, vector<int>(N, 999));
    rep(ei, N) rep(ej, N) {
        if (owner[ei][ej] >= 1) {
            rep(x, N) rep(y, N) {
                dist[x][y] = min(dist[x][y], abs(x - ei) + abs(y - ej));
            }
        }
    }
    return dist;
}

// ---- 評価関数 ----
double evaluate_cell(int x, int y, int turn, int ed) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) {
        // 現在地に留まる = レベルアップ
        if (owner[x][y] == 0 && level[x][y] < U && U > 1) {
            double v = V[x][y];
            if (turn >= 40 && ed <= 1) return v * 2.5; // 中盤以降: 敵隣接の防御
            if (turn >= 40 && ed == 2) return v * 1.5;  // 壁強化
            return v * 0.3; // 序盤はレベルアップ後回し
        }
        return 0.0;
    }

    double v = V[x][y];

    if (owner[x][y] == -1) {
        // 空きマス
        if (turn < 40) return v * 1.3; // 序盤: 広く取る
        // 中盤以降: 壁候補を優先
        if (ed == 2) return v * 2.0;
        if (ed == 1) return v * 1.2;
        return v * 1.5;
    }
    if (owner[x][y] == 0) {
        // 自領土に移動 → レベルアップ
        if (level[x][y] >= U || U == 1) return 0.0;
        if (turn >= 40 && ed <= 1) return v * 2.5; // 防御
        if (turn >= 40 && ed == 2) return v * 1.5;  // 壁強化
        return v * 0.3;
    }
    // 敵マス: L=1のみ攻撃
    if (level[x][y] == 1) return v * 1.0;
    return 0.0;
}

int main() {
    read_initial_input();

    rep(turn, T) {
        auto enemy_md = calc_enemy_manhattan();
        auto movable = get_movable(0);

        pair<int, int> best_move = piece_pos[0];
        double best_score = -1;
        for (auto& [x, y] : movable) {
            double score = evaluate_cell(x, y, turn, enemy_md[x][y]);
            if (score > best_score) {
                best_score = score;
                best_move = {x, y};
            }
        }

        cout << best_move.first SP << best_move.second << endl;
        cout.flush();

        read_turn_result();
    }
    return 0;
}
