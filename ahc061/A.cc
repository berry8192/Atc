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
    vector<pair<int, int>> targets(M);
    rep(p, M) cin >> targets[p].first >> targets[p].second;
    rep(p, M) cin >> piece_pos[p].first >> piece_pos[p].second;
    rep(i, N) rep(j, N) cin >> owner[i][j];
    rep(i, N) rep(j, N) cin >> level[i][j];
}

// 最もスコアが高いAIプレイヤーを特定
int get_top_rival() {
    vector<ll> scores(M, 0);
    rep(i, N) rep(j, N) {
        if (owner[i][j] >= 1) {
            scores[owner[i][j]] += (ll)V[i][j] * level[i][j];
        }
    }
    int top = 1;
    for (int p = 2; p < M; p++) {
        if (scores[p] > scores[top]) top = p;
    }
    return top;
}

// 到達可能領土（BFS）
set<pair<int, int>> get_reachable_territory() {
    set<pair<int, int>> reachable;
    queue<pair<int, int>> q;
    auto [sx, sy] = piece_pos[0];
    q.push({sx, sy});
    reachable.insert({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        rep(d, 4) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (reachable.count({nx, ny})) continue;
            if (owner[nx][ny] != 0) continue;
            reachable.insert({nx, ny});
            q.push({nx, ny});
        }
    }
    return reachable;
}

// 移動可能マスを取得
vector<pair<int, int>> get_movable_cells() {
    auto reachable = get_reachable_territory();
    set<pair<int, int>> movable(all(reachable));

    for (auto [x, y] : reachable) {
        rep(d, 4) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            bool has_other = false;
            for (int p = 1; p < M; p++) {
                if (piece_pos[p].first == nx && piece_pos[p].second == ny) {
                    has_other = true;
                    break;
                }
            }
            if (!has_other) movable.insert({nx, ny});
        }
    }
    return vector<pair<int, int>>(all(movable));
}

// 中心への近さ（中心4マス=3, 端=2）
double center_weight(int i, int j) {
    int ci = min(i, N - 1 - i);
    int cj = min(j, N - 1 - j);
    return 2.0 + min(ci, cj) / 4.0;
}

// マスの評価値
double evaluate_cell(int x, int y, int top_rival) {
    // 現在位置にとどまるのは無意味
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];
    double D = center_weight(x, y);
    if (owner[x][y] == -1) {
        return v * D * 0.3;
    } else if (owner[x][y] == 0) {
        return (level[x][y] < U) ? v * D * 0.25 : 0.0;
    } else if (owner[x][y] == top_rival) {
        return (level[x][y] == 1) ? v * D * 0.25 : v * D * 0.2;
    } else {
        return 0.0;
    }
}

int main() {
    read_initial_input();

    rep(turn, T) {
        int top_rival = get_top_rival();
        auto movable = get_movable_cells();

        pair<int, int> best_move = piece_pos[0];
        double best_score = -1;
        for (auto [x, y] : movable) {
            double score = evaluate_cell(x, y, top_rival);
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
