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

// ---- ベイズ推定 (グリッドベース) ----
const int GS = 7;
const int TOTAL = GS * GS * GS * GS * GS; // 16807
double w_vals[GS], e_vals[GS];

struct CellInfo {
    int x, y;
    double v;
    int cat; // 0=未占領, 1=自分<U, 2=自分=U, 3=敵L1, 4=敵L2+
};

struct Estimator {
    vector<double> wt;
    double est_wa, est_wb, est_wc, est_wd, est_eps;

    void init() {
        wt.assign(TOTAL, 1.0 / TOTAL);
        est_wa = est_wb = est_wc = est_wd = 0.65;
        est_eps = 0.3;
    }

    void update(pair<int, int> target, vector<CellInfo>& cells) {
        int B = cells.size();
        if (B <= 1) return;

        rep(idx, TOTAL) {
            int tmp = idx;
            int ei = tmp % GS; tmp /= GS;
            int di = tmp % GS; tmp /= GS;
            int ci = tmp % GS; tmp /= GS;
            int bi = tmp % GS; tmp /= GS;
            int ai = tmp;

            double wa = w_vals[ai], wb = w_vals[bi], wc = w_vals[ci], wd = w_vals[di];
            double eps = e_vals[ei];

            double best_eval = -1e18;
            int tie_count = 0;
            bool target_is_best = false;

            for (auto& c : cells) {
                double ev;
                switch (c.cat) {
                    case 0: ev = c.v * wa; break;
                    case 1: ev = c.v * wb; break;
                    case 2: ev = 0; break;
                    case 3: ev = c.v * wc; break;
                    default: ev = c.v * wd; break;
                }
                if (ev > best_eval + 1e-9) {
                    best_eval = ev;
                    tie_count = 1;
                    target_is_best = (c.x == target.first && c.y == target.second);
                } else if (ev > best_eval - 1e-9) {
                    tie_count++;
                    if (c.x == target.first && c.y == target.second)
                        target_is_best = true;
                }
            }

            double lik = target_is_best
                             ? (1.0 - eps) / tie_count + eps / B
                             : eps / B;
            wt[idx] *= lik;
        }

        double sum = 0;
        for (double w : wt) sum += w;
        if (sum > 1e-300) {
            for (double& w : wt) w /= sum;
        } else {
            fill(all(wt), 1.0 / TOTAL);
        }

        est_wa = est_wb = est_wc = est_wd = est_eps = 0;
        rep(idx, TOTAL) {
            int tmp = idx;
            int ei = tmp % GS; tmp /= GS;
            int di = tmp % GS; tmp /= GS;
            int ci = tmp % GS; tmp /= GS;
            int bi = tmp % GS; tmp /= GS;
            int ai = tmp;
            est_wa += wt[idx] * w_vals[ai];
            est_wb += wt[idx] * w_vals[bi];
            est_wc += wt[idx] * w_vals[ci];
            est_wd += wt[idx] * w_vals[di];
            est_eps += wt[idx] * e_vals[ei];
        }
    }

    pair<int, int> predict(vector<CellInfo>& cells) {
        if (cells.empty()) return {-1, -1};
        double best_eval = -1e18;
        pair<int, int> best = {cells[0].x, cells[0].y};
        for (auto& c : cells) {
            double ev;
            switch (c.cat) {
                case 0: ev = c.v * est_wa; break;
                case 1: ev = c.v * est_wb; break;
                case 2: ev = 0; break;
                case 3: ev = c.v * est_wc; break;
                default: ev = c.v * est_wd; break;
            }
            if (ev > best_eval) {
                best_eval = ev;
                best = {c.x, c.y};
            }
        }
        return best;
    }
};

vector<Estimator> est;

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

vector<pair<int, int>> turn_targets;

void read_turn_result() {
    turn_targets.resize(M);
    rep(p, M) cin >> turn_targets[p].first >> turn_targets[p].second;
    rep(p, M) cin >> piece_pos[p].first >> piece_pos[p].second;
    rep(i, N) rep(j, N) cin >> owner[i][j];
    rep(i, N) rep(j, N) cin >> level[i][j];
}

// ---- ボードロジック ----
vector<ll> calc_scores() {
    vector<ll> scores(M, 0);
    rep(i, N) rep(j, N) {
        if (owner[i][j] >= 0) {
            scores[owner[i][j]] += (ll)V[i][j] * level[i][j];
        }
    }
    return scores;
}

int get_top_rival(const vector<ll>& scores) {
    int top = 1;
    for (int p = 2; p < M; p++) {
        if (scores[p] > scores[top]) top = p;
    }
    return top;
}

set<pair<int, int>> get_reachable(int player) {
    set<pair<int, int>> reachable;
    queue<pair<int, int>> q;
    auto [sx, sy] = piece_pos[player];
    q.push({sx, sy});
    reachable.insert({sx, sy});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
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

vector<CellInfo> make_cell_infos(int player, vector<pair<int, int>>& movable) {
    vector<CellInfo> cells;
    for (auto& [x, y] : movable) {
        int cat;
        if (owner[x][y] == -1)
            cat = 0;
        else if (owner[x][y] == player)
            cat = (level[x][y] < U) ? 1 : 2;
        else
            cat = (level[x][y] == 1) ? 3 : 4;
        cells.push_back({x, y, (double)V[x][y], cat});
    }
    return cells;
}

// ==== 戦略システム ====

enum Strategy { STALKER, WALL, EXPAND_RAID, LEVELUP };

struct BoardStats {
    int empty_count;
    vector<vector<int>> enemy_piece_dist;
    vector<vector<int>> enemy_terr_dist;
    double wall_completeness;

    void compute() {
        // 空きマス数
        empty_count = 0;
        rep(i, N) rep(j, N) if (owner[i][j] == -1) empty_count++;

        // 敵コマからのBFS距離
        enemy_piece_dist.assign(N, vector<int>(N, 999));
        {
            queue<pair<int,int>> q;
            for (int p = 1; p < M; p++) {
                auto [ex, ey] = piece_pos[p];
                if (enemy_piece_dist[ex][ey] > 0) {
                    enemy_piece_dist[ex][ey] = 0;
                    q.push({ex, ey});
                }
            }
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                rep(d, 4) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    if (enemy_piece_dist[nx][ny] <= enemy_piece_dist[x][y] + 1) continue;
                    enemy_piece_dist[nx][ny] = enemy_piece_dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // 敵領土からのBFS距離
        enemy_terr_dist.assign(N, vector<int>(N, 999));
        {
            queue<pair<int,int>> q;
            rep(i, N) rep(j, N) {
                if (owner[i][j] > 0) {
                    enemy_terr_dist[i][j] = 0;
                    q.push({i, j});
                }
            }
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                rep(d, 4) {
                    int nx = x + dx[d], ny = y + dy[d];
                    if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                    if (enemy_terr_dist[nx][ny] <= enemy_terr_dist[x][y] + 1) continue;
                    enemy_terr_dist[nx][ny] = enemy_terr_dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        // 壁完成度: 前線セル(敵領土に隣接する自セル)のうちL>=2の割合
        int front_total = 0, front_leveled = 0;
        rep(i, N) rep(j, N) {
            if (owner[i][j] != 0) continue;
            bool is_front = false;
            rep(d, 4) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
                if (owner[ni][nj] > 0) { is_front = true; break; }
            }
            if (is_front) {
                front_total++;
                if (level[i][j] >= 2) front_leveled++;
            }
        }
        wall_completeness = front_total > 0 ? (double)front_leveled / front_total : 0.0;
    }
};

// ---- 戦略別評価関数 ----

// EXPAND_RAID: M>=3, U=1 → A.ccと同一
double eval_expand_raid(int x, int y, int turn, int top_rival, const BoardStats& bs) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];
    if (owner[x][y] == -1) return v;
    if (owner[x][y] == 0) return (level[x][y] < U) ? v : 0.0;
    if (owner[x][y] == top_rival) return (level[x][y] == 1) ? v * 1.8 : v * 1.0;
    return 0.0;
}

// STALKER: M=2, U=1
// 敵マス奪取(v*2.0) > 空きマス(v*0.8) + 敵コマへの接近ボーナス
double eval_stalker(int x, int y, int turn, int top_rival, const BoardStats& bs) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];

    // 敵コマ(player 1)への近さボーナス
    int dist = abs(x - piece_pos[1].first) + abs(y - piece_pos[1].second);
    double prox = max(0.0, (10.0 - dist) * 2.0);

    if (owner[x][y] > 0) {
        // 敵マス: 奪取で自分+v, 敵-v → 比率改善2倍
        return v * 2.0 + prox;
    }
    if (owner[x][y] == -1) {
        return v * 0.8 + prox * 0.3;
    }
    return 0.0; // 自マス, U=1 maxed
}

// WALL: M=2, U>=2
// expandフェーズ: 敵方向に拡張
// wall_buildフェーズ: 敵境界の自マスをレベルアップ
// exploitフェーズ: 内側レベルアップ + 弱い敵マス攻撃
double eval_wall(int x, int y, int turn, int top_rival, const BoardStats& bs) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];
    int etd = bs.enemy_terr_dist[x][y];

    if (bs.empty_count >= 30) {
        // Expandフェーズ: 敵方向に拡張
        if (owner[x][y] == -1) {
            double toward_bonus = max(0.0, 8.0 - (double)etd) * 2.0;
            return v + toward_bonus;
        }
        if (owner[x][y] == 0) return (level[x][y] < U) ? v * 0.5 : 0.0;
        return (level[x][y] == 1) ? v * 1.5 : 0.0;
    } else if (bs.wall_completeness < 0.7) {
        // Wall buildフェーズ: 境界セルをレベルアップ
        if (owner[x][y] == 0 && level[x][y] < U) {
            if (etd <= 2) return v * 3.0;  // 境界: 高優先
            return v * 1.0;                 // 内側
        }
        if (owner[x][y] == -1) return v * 0.5;
        if (owner[x][y] > 0 && level[x][y] == 1) return v * 0.3;
        return 0.0;
    } else {
        // Exploitフェーズ: 内側レベルアップ + 弱い敵セル攻撃
        if (owner[x][y] == 0 && level[x][y] < U) return v * 2.0;
        if (owner[x][y] > 0 && level[x][y] == 1) return v * 1.0;
        if (owner[x][y] == -1) return v * 0.3;
        return 0.0;
    }
}

// LEVELUP: M>=3, U>=2 → A.ccと同一
double eval_levelup(int x, int y, int turn, int top_rival, const BoardStats& bs) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];
    if (owner[x][y] == -1) return v;
    if (owner[x][y] == 0) return (level[x][y] < U) ? v : 0.0;
    if (owner[x][y] == top_rival) return (level[x][y] == 1) ? v * 1.8 : v * 1.0;
    return 0.0;
}

// ---- メイン ----

int main() {
    read_initial_input();

    // ベイズ推定グリッド初期化
    rep(i, GS) {
        w_vals[i] = 0.3 + 0.7 * i / (GS - 1);
        e_vals[i] = 0.1 + 0.4 * i / (GS - 1);
    }
    est.resize(M);
    for (int p = 1; p < M; p++) est[p].init();

    // 戦略選択
    Strategy strat;
    if (M == 2 && U == 1) strat = STALKER;
    else if (M == 2) strat = WALL;
    else if (U == 1) strat = EXPAND_RAID;
    else strat = LEVELUP;

    // 戦略別衝突ペナルティ
    double collision_penalty;
    switch (strat) {
        case STALKER: collision_penalty = 0.2; break;
        case WALL: collision_penalty = 0.1; break;
        default: collision_penalty = 0.3; break;
    }

    rep(turn, T) {
        // AI移動可能マスのセル情報（現在のボード状態で記録）
        vector<vector<CellInfo>> ai_cells(M);
        for (int p = 1; p < M; p++) {
            auto mov = get_movable(p);
            ai_cells[p] = make_cell_infos(p, mov);
        }

        // AI次手予測 → 衝突回避用
        set<pair<int, int>> predicted;
        for (int p = 1; p < M; p++) {
            auto pred = est[p].predict(ai_cells[p]);
            predicted.insert(pred);
        }

        // ボード統計計算
        BoardStats bs;
        bs.compute();

        // 自分の手を決定
        auto scores = calc_scores();
        int top_rival = get_top_rival(scores);
        auto movable = get_movable(0);

        pair<int, int> best_move = piece_pos[0];
        double best_score = -1;
        for (auto& [x, y] : movable) {
            double score;
            switch (strat) {
                case EXPAND_RAID: score = eval_expand_raid(x, y, turn, top_rival, bs); break;
                case STALKER: score = eval_stalker(x, y, turn, top_rival, bs); break;
                case WALL: score = eval_wall(x, y, turn, top_rival, bs); break;
                case LEVELUP: score = eval_levelup(x, y, turn, top_rival, bs); break;
            }
            // AI予測先で自分の領土でない → 衝突リスク
            if (predicted.count({x, y}) && owner[x][y] != 0) {
                score *= collision_penalty;
            }
            if (score > best_score) {
                best_score = score;
                best_move = {x, y};
            }
        }

        cout << best_move.first SP << best_move.second << endl;
        cout.flush();

        // ターン結果読み込み
        read_turn_result();

        // ベイズ更新
        for (int p = 1; p < M; p++) {
            est[p].update(turn_targets[p], ai_cells[p]);
        }
    }
    return 0;
}
