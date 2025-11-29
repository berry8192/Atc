#include <bits/stdc++.h>
using namespace std;

struct Cell {
    bool wall_up, wall_down, wall_left, wall_right;
};

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
const char dirc[4] = {'R', 'U', 'L', 'D'};

// BFSで(start→goal)の最短経路を返す
vector<pair<int, int>> bfs_path(const vector<vector<Cell>> &grid, int N,
                                pair<int, int> start, pair<int, int> goal) {
    vector<vector<pair<int, int>>> prev(N, vector<pair<int, int>>(N, {-1, -1}));
    queue<pair<int, int>> q;
    q.push(start);
    prev[start.first][start.second] = start;

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        if (make_pair(x, y) == goal)
            break;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (d == 0 && grid[x][y].wall_right)
                continue;
            if (d == 1 && grid[x][y].wall_up)
                continue;
            if (d == 2 && grid[x][y].wall_left)
                continue;
            if (d == 3 && grid[x][y].wall_down)
                continue;
            if (prev[nx][ny].first != -1)
                continue;
            prev[nx][ny] = {x, y};
            q.push({nx, ny});
        }
    }

    // 経路復元
    vector<pair<int, int>> path;
    pair<int, int> cur = goal;
    while (cur != start) {
        path.push_back(cur);
        cur = prev[cur.first][cur.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

// 経路を方向と歩数に分解
struct Segment {
    int dir;   // 0:R, 1:U, 2:L, 3:D
    int steps; // 歩数
    pair<int, int> start_pos;
};

vector<Segment> decompose_path(const vector<pair<int, int>> &path) {
    vector<Segment> segments;
    if (path.size() <= 1)
        return segments;

    int cur_dir = -1;
    int steps = 0;
    pair<int, int> seg_start = path[0];

    for (int i = 0; i + 1 < path.size(); i++) {
        int x1 = path[i].first;
        int y1 = path[i].second;
        int x2 = path[i + 1].first;
        int y2 = path[i + 1].second;

        int dir = -1;
        if (y2 == y1 + 1)
            dir = 0; // R
        else if (x2 == x1 - 1)
            dir = 1; // U
        else if (y2 == y1 - 1)
            dir = 2; // L
        else if (x2 == x1 + 1)
            dir = 3; // D

        if (cur_dir == -1) {
            cur_dir = dir;
            steps = 1;
            seg_start = path[i];
        } else if (cur_dir == dir) {
            steps++;
        } else {
            segments.push_back({cur_dir, steps, seg_start});
            cur_dir = dir;
            steps = 1;
            seg_start = path[i];
        }
    }

    if (cur_dir != -1) {
        segments.push_back({cur_dir, steps, seg_start});
    }

    return segments;
}

// 遷移規則を生成する関数（状態数1の新アプローチ）
// 戻り値: (rules, 使用した色数)
pair<map<pair<int, int>, tuple<int, int, char>>, int>
generate_rules(const vector<pair<int, int>> &path, int N,
               vector<vector<int>> &board) {

    map<pair<int, int>, tuple<int, int, char>> rules;

    // 各マスの訪問時の移動方向リストを作成
    map<pair<int, int>, vector<int>> cell_dirs;
    for (int i = 0; i + 1 < path.size(); i++) {
        int x = path[i].first;
        int y = path[i].second;
        int nx = path[i + 1].first;
        int ny = path[i + 1].second;

        int dir = -1;
        if (ny == y + 1)
            dir = 0; // R
        else if (nx == x - 1)
            dir = 1; // U
        else if (ny == y - 1)
            dir = 2; // L
        else if (nx == x + 1)
            dir = 3; // D

        cell_dirs[{x, y}].push_back(dir);
    }

    // 必要なすべての方向リスト（接尾辞含む）を収集
    set<vector<int>> all_dir_lists;
    for (map<pair<int, int>, vector<int>>::iterator it = cell_dirs.begin();
         it != cell_dirs.end(); ++it) {
        const vector<int> &dirs = it->second;
        // すべての接尾辞を追加
        for (int i = 0; i < dirs.size(); i++) {
            vector<int> suffix(dirs.begin() + i, dirs.end());
            all_dir_lists.insert(suffix);
        }
    }

    // 方向リストに対してカラーを割り当てる
    map<vector<int>, int> dirlist_to_color;
    int next_color = 4; // 0-3は単一方向用

    // 単一方向のカラー設定
    for (int dir = 0; dir < 4; dir++) {
        dirlist_to_color[{dir}] = dir;
    }

    // すべての方向リストに対してカラーを事前割り当て
    for (const auto &dirs : all_dir_lists) {
        if (dirlist_to_color.find(dirs) == dirlist_to_color.end()) {
            dirlist_to_color[dirs] = next_color++;
        }
    }

    // 各方向リストに対する遷移規則を作成
    for (map<vector<int>, int>::iterator it = dirlist_to_color.begin();
         it != dirlist_to_color.end(); ++it) {
        const vector<int> &dirs = it->first;
        int color = it->second;

        if (dirs.empty())
            continue;

        int move_dir = dirs[0]; // 最初の方向に移動

        // 残りの方向リスト
        vector<int> remaining_dirs(dirs.begin() + 1, dirs.end());

        int next_color_val;
        if (remaining_dirs.empty()) {
            // 最後の訪問
            // カラー0~3の場合は(c+1)%4、それ以外はデフォルトカラー0
            if (color < 4) {
                next_color_val = (color + 1) % 4;
            } else {
                next_color_val = 0;
            }
        } else {
            // 残りの方向リストに対応するカラーを取得（事前に割り当て済み）
            next_color_val = dirlist_to_color[remaining_dirs];
        }

        rules[{color, 0}] = {next_color_val, 0, dirc[move_dir]};

        cerr << "Rule: (" << color << ", 0) -> (" << next_color_val << ", 0, "
             << dirc[move_dir] << ") [dirs:";
        for (int d : dirs)
            cerr << " " << d;
        cerr << "]" << endl;
    }

    // 各マスに初期カラーを設定
    cerr << "\n=== Board Color Assignment ===" << endl;
    for (map<pair<int, int>, vector<int>>::iterator it = cell_dirs.begin();
         it != cell_dirs.end(); ++it) {
        const pair<int, int> &pos = it->first;
        const vector<int> &dirs = it->second;
        board[pos.first][pos.second] = dirlist_to_color[dirs];
        cerr << "Cell (" << pos.first << "," << pos.second << ") = color "
             << dirlist_to_color[dirs] << " [dirs:";
        for (int d : dirs)
            cerr << " " << d;
        cerr << "]" << endl;
    }

    cerr << "\nTotal colors used: " << next_color << endl;
    cerr << "Total rules: " << rules.size() << endl << endl;

    return {rules, next_color};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K, T;
    cin >> N >> K >> T;

    vector<string> v(N), h(N - 1);
    for (int i = 0; i < N; i++)
        cin >> v[i];
    for (int i = 0; i < N - 1; i++)
        cin >> h[i];

    vector<pair<int, int>> goals(K);
    for (int i = 0; i < K; i++)
        cin >> goals[i].first >> goals[i].second;

    // 壁情報の構築
    vector<vector<Cell>> grid(N, vector<Cell>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j].wall_left = (j == 0) || (v[i][j - 1] == '1');
            grid[i][j].wall_right = (j == N - 1) || (v[i][j] == '1');
            grid[i][j].wall_up = (i == 0) || (h[i - 1][j] == '1');
            grid[i][j].wall_down = (i == N - 1) || (h[i][j] == '1');
        }
    }

    // 各区間の経路を個別に管理
    vector<vector<pair<int, int>>> segment_paths(K - 1);
    for (int i = 0; i + 1 < K; i++) {
        segment_paths[i] = bfs_path(grid, N, goals[i], goals[i + 1]);
    }

    // 訪問済みマスを避けるダイクストラ法
    auto dijkstra_avoid = [&](pair<int, int> start, pair<int, int> goal,
                              const map<pair<int, int>, int> &visit_penalty)
        -> vector<pair<int, int>> {
        vector<vector<int>> dist(N, vector<int>(N, 1e9));
        vector<vector<pair<int, int>>> prev(
            N, vector<pair<int, int>>(N, {-1, -1}));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
                       greater<>>
            pq;

        dist[start.first][start.second] = 0;
        pq.push({0, start.first, start.second});

        while (!pq.empty()) {
            int d = get<0>(pq.top());
            int x = get<1>(pq.top());
            int y = get<2>(pq.top());
            pq.pop();

            if (d > dist[x][y])
                continue;
            if (make_pair(x, y) == goal)
                break;

            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                    continue;
                if (dir == 0 && grid[x][y].wall_right)
                    continue;
                if (dir == 1 && grid[x][y].wall_up)
                    continue;
                if (dir == 2 && grid[x][y].wall_left)
                    continue;
                if (dir == 3 && grid[x][y].wall_down)
                    continue;

                int cost = 1;
                auto it = visit_penalty.find({nx, ny});
                if (it != visit_penalty.end()) {
                    cost += it->second * 100; // 訪問済みマスに大きなペナルティ
                }

                if (dist[nx][ny] > dist[x][y] + cost) {
                    dist[nx][ny] = dist[x][y] + cost;
                    prev[nx][ny] = {x, y};
                    pq.push({dist[nx][ny], nx, ny});
                }
            }
        }

        // 経路復元
        vector<pair<int, int>> path;
        pair<int, int> cur = goal;
        while (cur != start &&
               prev[cur.first][cur.second] != make_pair(-1, -1)) {
            path.push_back(cur);
            cur = prev[cur.first][cur.second];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        if (path.size() == 1 && start != goal)
            return {}; // 経路が見つからない
        return path;
    };

    // 焼きなましで各区間を最適化
    cerr << "Optimizing segment paths..." << endl;
    auto start_time = chrono::system_clock::now();
    double time_limit = 1.8;
    int iterations = 0;
    int improvements = 0;

    while (true) {
        auto current_time = chrono::system_clock::now();
        double elapsed =
            chrono::duration<double>(current_time - start_time).count();
        if (elapsed > time_limit)
            break;

        // 全経路を結合してマスの訪問回数を計算
        vector<pair<int, int>> full_path;
        for (int i = 0; i < K - 1; i++) {
            for (int j = 0; j < segment_paths[i].size(); j++) {
                if (i > 0 && j == 0)
                    continue; // 重複を避ける
                full_path.push_back(segment_paths[i][j]);
            }
        }

        // 経路長チェック
        if (full_path.size() - 1 > T) {
            // Tを超えている場合は最短経路に戻す
            for (int i = 0; i < K - 1; i++) {
                segment_paths[i] = bfs_path(grid, N, goals[i], goals[i + 1]);
            }
            continue;
        }

        // 現在のスコアを計算（マス訪問回数の2乗和）
        map<pair<int, int>, int> visit_count;
        for (const auto &pos : full_path) {
            visit_count[pos]++;
        }
        int current_score = 0;
        for (const auto &p : visit_count) {
            current_score += p.second * p.second;
        }

        // ランダムに区間を選択
        int seg_idx = rand() % (K - 1);

        // この区間以外のマスの訪問回数を計算
        map<pair<int, int>, int> other_visit_count;
        for (int i = 0; i < K - 1; i++) {
            if (i == seg_idx)
                continue;
            for (const auto &pos : segment_paths[i]) {
                other_visit_count[pos]++;
            }
        }

        // 新しい経路を探索（訪問済みマスを避ける）
        auto new_seg_path = dijkstra_avoid(goals[seg_idx], goals[seg_idx + 1],
                                           other_visit_count);
        if (new_seg_path.empty())
            continue;

        // 新しい経路でスコアを再計算
        vector<vector<pair<int, int>>> new_segment_paths = segment_paths;
        new_segment_paths[seg_idx] = new_seg_path;

        vector<pair<int, int>> new_full_path;
        for (int i = 0; i < K - 1; i++) {
            for (int j = 0; j < new_segment_paths[i].size(); j++) {
                if (i > 0 && j == 0)
                    continue;
                new_full_path.push_back(new_segment_paths[i][j]);
            }
        }

        if (new_full_path.size() - 1 > T)
            continue; // T制約チェック

        map<pair<int, int>, int> new_visit_count;
        for (const auto &pos : new_full_path) {
            new_visit_count[pos]++;
        }
        int new_score = 0;
        for (const auto &p : new_visit_count) {
            new_score += p.second * p.second;
        }

        // 温度による採用判定
        double temp = 100.0 * (1.0 - elapsed / time_limit);
        double prob = exp((current_score - new_score) / temp);

        if (new_score < current_score || (double)rand() / RAND_MAX < prob) {
            segment_paths[seg_idx] = new_seg_path;
            if (new_score < current_score)
                improvements++;
        }

        iterations++;
        if (iterations % 1000 == 0) {
            cerr << "Iter: " << iterations << ", Score: " << current_score
                 << ", Improvements: " << improvements
                 << ", PathLen: " << full_path.size() - 1 << "/" << T << endl;
        }
    }

    // 最終経路を結合
    vector<pair<int, int>> full_path;
    for (int i = 0; i < K - 1; i++) {
        for (int j = 0; j < segment_paths[i].size(); j++) {
            if (i > 0 && j == 0)
                continue;
            full_path.push_back(segment_paths[i][j]);
        }
    }

    cerr << "Final path length: " << full_path.size() - 1 << "/" << T << endl;
    cerr << "Total iterations: " << iterations
         << ", Improvements: " << improvements << endl;

    // 経路をセグメントに分解
    vector<Segment> segments = decompose_path(full_path);

    // 盤面の色を設定 & 遷移規則を生成
    vector<vector<int>> board(N, vector<int>(N, 0)); // デフォルトは色0
    pair<map<pair<int, int>, tuple<int, int, char>>, int> result =
        generate_rules(full_path, N, board);
    map<pair<int, int>, tuple<int, int, char>> rules = result.first;
    int C = result.second;

    // 状態数は1（状態0のみ）
    int Q = 1;
    int M = min((int)rules.size(), T);

    // 出力
    cout << C << " " << Q << " " << M << "\n";

    // 初期盤面
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << (j + 1 == N ? '\n' : ' ');
        }
    }

    // 遷移規則
    int count = 0;
    for (auto &rule : rules) {
        if (count >= M)
            break;
        int c = rule.first.first;
        int q = rule.first.second;
        int new_c = get<0>(rule.second);
        int new_q = get<1>(rule.second);
        char move = get<2>(rule.second);
        cout << c << " " << q << " " << new_c << " " << new_q << " " << move
             << "\n";
        count++;
    }

    return 0;
}
