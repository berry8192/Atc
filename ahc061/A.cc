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

// セル情報（ボード状態をキャプチャ）
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

        // 正規化
        double sum = 0;
        for (double w : wt) sum += w;
        if (sum > 1e-300) {
            for (double& w : wt) w /= sum;
        } else {
            fill(all(wt), 1.0 / TOTAL);
        }

        // 推定値更新
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

    // 推定パラメータでAIの次手を予測
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

// 任意プレイヤーの到達可能領土
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

// 任意プレイヤーの移動可能マス
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

// AIプレイヤーの移動可能マスのセル情報を作成（ボード状態をキャプチャ）
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

// ---- 距離計算 ----
// プレイヤーの到達可能領土からの拡張距離（空きマスのみ通過）
vector<vector<int>> calc_expand_dist(int player) {
    vector<vector<int>> dist(N, vector<int>(N, 999));
    queue<pair<int, int>> q;
    auto reach = get_reachable(player);
    for (auto& [rx, ry] : reach) {
        dist[rx][ry] = 0;
        q.push({rx, ry});
    }
    while (!q.empty()) {
        auto [cx, cy] = q.front(); q.pop();
        rep(d, 4) {
            int nx = cx + dx[d], ny = cy + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (dist[cx][cy] + 1 >= dist[nx][ny]) continue;
            if (owner[nx][ny] == -1) {
                dist[nx][ny] = dist[cx][cy] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist;
}

// ---- 自分の評価関数 ----
double evaluate_cell(int x, int y, int top_rival) {
    if (x == piece_pos[0].first && y == piece_pos[0].second) return 0.0;
    double v = V[x][y];
    if (owner[x][y] == -1) return v;
    if (owner[x][y] == 0) return (level[x][y] < U) ? v : 0.0;
    if (owner[x][y] == top_rival) return (level[x][y] == 1) ? v * 1.8 : v * 1.0;
    return 0.0;
}

int main() {
    read_initial_input();

    // グリッド値の初期化
    rep(i, GS) {
        w_vals[i] = 0.3 + 0.7 * i / (GS - 1);
        e_vals[i] = 0.1 + 0.4 * i / (GS - 1);
    }
    est.resize(M);
    for (int p = 1; p < M; p++) est[p].init();

    rep(turn, T) {
        // AI移動可能マスのセル情報を記録（現在のボード状態で）
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

        // 各敵の拡張距離を計算
        vector<vector<vector<int>>> enemy_dist(M);
        for (int p = 1; p < M; p++) {
            enemy_dist[p] = calc_expand_dist(p);
        }

        // 空きマスのポテンシャル（敵が遠いほど高い）
        vector<vector<double>> potential(N, vector<double>(N, 0));
        rep(i, N) rep(j, N) {
            if (owner[i][j] == -1) {
                int min_ed = 999;
                for (int p = 1; p < M; p++)
                    min_ed = min(min_ed, enemy_dist[p][i][j]);
                potential[i][j] = V[i][j] * (1.0 + 0.15 * min(min_ed, 6));
            }
        }

        // 自分の手を決定
        auto scores = calc_scores();
        int top_rival = get_top_rival(scores);
        auto movable = get_movable(0);

        pair<int, int> best_move = piece_pos[0];
        double best_score = -1e18;
        for (auto& [x, y] : movable) {
            double score = evaluate_cell(x, y, top_rival);

            // 空きマスに敵距離ボーナス（敵が来ないほど安全に取れる）
            if (owner[x][y] == -1) {
                int min_ed = 999;
                for (int p = 1; p < M; p++)
                    min_ed = min(min_ed, enemy_dist[p][x][y]);
                score *= (1.0 + 0.15 * min(min_ed, 6));
            }

            // 方向ボーナス: この方向に進むと将来どれだけ良い空きマスがあるか
            double future = 0;
            rep(i, N) rep(j, N) {
                if (potential[i][j] > 0) {
                    int md = abs(x - i) + abs(y - j);
                    if (md > 0) future += potential[i][j] / (md + 1);
                }
            }
            score += future * 0.05;

            // AIが向かう先で自分の領土でない → 衝突リスク
            if (predicted.count({x, y}) && owner[x][y] != 0) {
                score *= 0.3;
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

        // ベイズ更新（観測されたAIの行動で）
        for (int p = 1; p < M; p++) {
            est[p].update(turn_targets[p], ai_cells[p]);
        }
    }
    return 0;
}
