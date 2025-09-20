#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <vector>

using namespace std;

// 迷路のサイズ
int N;
// ゴールの座標
int ti, tj;
// 現在の迷路の状態
vector<string> current_maze;
// 冒険者が確認済みのマス
vector<vector<bool>> confirmed;

// 4方向の移動 (上, 下, 左, 右)
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 2点間の最短経路長を計算する
int calculate_path_length(int start_r, int start_c, int end_r, int end_c,
                          const vector<string> &maze) {
    vector<vector<int>> dist(N, vector<int>(N, -1));
    queue<pair<int, int>> q;

    if (maze[start_r][start_c] == 'T' || maze[start_r][start_c] == 't')
        return -1;

    dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int r = curr.first;
        int c = curr.second;

        if (r == end_r && c == end_c) {
            return dist[r][c];
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < N && dist[nr][nc] == -1 &&
                maze[nr][nc] != 'T' && maze[nr][nc] != 't') {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1; // 到達不能
}

// 新しい渦巻きアルゴリズム
vector<pair<int, int>> create_strategic_treants(int pi, int pj, int open_dir,
                                                int rotation_dir) {
    vector<pair<int, int>> treants_to_place;

    // 現在の迷路状態をバックアップ
    vector<string> original_maze = current_maze;

    // 花の周りの3方向を最初に塞ぐ
    for (int i = 0; i < 4; ++i) {
        if (i == open_dir)
            continue;
        int nr = ti + dr[i];
        int nc = tj + dc[i];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            original_maze[nr][nc] == '.') {
            current_maze[nr][nc] = 't';
            treants_to_place.push_back({nr, nc});
        }
    }

    // 経路探索の現在地と過去の現在地
    int current_r = ti + dr[open_dir];
    int current_c = tj + dc[open_dir];
    int prev_r = ti;
    int prev_c = tj;

    // 経路確保のための仮チェック
    if (current_r < 0 || current_r >= N || current_c < 0 || current_c >= N ||
        current_maze[current_r][current_c] != '.') {
        current_maze = original_maze;
        return {};
    }

    // 経路構築のループ
    for (int i = 0; i < N * N; ++i) {
        int next_r = -1, next_c = -1;
        double min_dist_sq = 1e18;

        // 次の現在地を決定（花に最も近い空きマス）
        // ユークリッド距離の2乗で比較
        for (int j = 0; j < 4; ++j) {
            int nr = current_r + dr[j];
            int nc = current_c + dc[j];

            if (nr == prev_r && nc == prev_c)
                continue; // 戻る経路は考慮しない

            if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                current_maze[nr][nc] == '.') {
                double dist_sq = pow(nr - ti, 2) + pow(nc - tj, 2);
                if (dist_sq < min_dist_sq) {
                    min_dist_sq = dist_sq;
                    next_r = nr;
                    next_c = nc;
                }
            }
        }

        if (next_r == -1)
            break; // 次に進むマスがない

        // 現在地から見た4近傍のうち、前と次の現在地以外のマスにトレントを配置
        for (int j = 0; j < 4; ++j) {
            int tr = current_r + dr[j];
            int tc = current_c + dc[j];
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                current_maze[tr][tc] == '.' && (tr != prev_r || tc != prev_c) &&
                (tr != next_r || tc != next_c)) {

                current_maze[tr][tc] = 't';
                if (calculate_path_length(pi, pj, ti, tj, current_maze) != -1) {
                    treants_to_place.push_back({tr, tc});
                } else {
                    current_maze[tr][tc] = '.'; // 経路が途絶えるので元に戻す
                }
            }
        }

        // 現在地を更新
        prev_r = current_r;
        prev_c = current_c;
        current_r = next_r;
        current_c = next_c;
    }

    current_maze = original_maze;
    return treants_to_place;
}

// 最初のターンの処理
void solve_first_turn(int pi, int pj, int /* n */,
                      const vector<pair<int, int>> &newly_confirmed) {
    for (const auto &p : newly_confirmed) {
        confirmed[p.first][p.second] = true;
    }

    vector<string> original_maze = current_maze;
    vector<pair<int, int>> best_treants;
    int max_path_length = -1;

    // 8通りの戦略をシミュレート (4方向 x 2回転方向)
    for (int open_dir = 0; open_dir < 4; ++open_dir) {
        // rotation_dirはここでは使わないが、将来的な拡張のために残しておく
        for (int rotation_dir = 0; rotation_dir < 2; ++rotation_dir) {
            current_maze = original_maze;
            vector<pair<int, int>> treants =
                create_strategic_treants(pi, pj, open_dir, rotation_dir);

            // 評価のため、トレントを仮に配置した迷路を構築
            vector<string> temp_maze = original_maze;
            for (const auto &p : treants)
                temp_maze[p.first][p.second] = 't';

            int current_path_length =
                calculate_path_length(pi, pj, ti, tj, temp_maze);

            if (current_path_length > max_path_length) {
                max_path_length = current_path_length;
                best_treants = treants;
            }
        }
    }

    // 出力
    cout << best_treants.size();
    for (const auto &p : best_treants) {
        cout << " " << p.first << " " << p.second;
        current_maze[p.first][p.second] = 'T'; // 確定
    }
    cout << endl;
}

// 最初のターン以外の処理（何もしない）
void solve_other_turns(int /* pi */, int /* pj */, int /* n */,
                       const vector<pair<int, int>> &newly_confirmed) {
    for (const auto &p : newly_confirmed) {
        confirmed[p.first][p.second] = true;
    }
    cout << 0 << endl;
}

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));
    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    bool first_turn = true;
    long long turn_limit = 10LL * N * N;
    long long current_turn = 0;

    while (true) {
        int pi, pj, n;
        cin >> pi >> pj >> n;

        if (pi == ti && pj == tj) {
            break;
        }

        vector<pair<int, int>> newly_confirmed(n);
        for (int k = 0; k < n; ++k) {
            cin >> newly_confirmed[k].first >> newly_confirmed[k].second;
        }

        if (first_turn) {
            solve_first_turn(pi, pj, n, newly_confirmed);
            first_turn = false;
        } else {
            solve_other_turns(pi, pj, n, newly_confirmed);
        }

        current_turn++;
        if (current_turn > turn_limit) {
            return 0;
        }
    }

    return 0;
}
