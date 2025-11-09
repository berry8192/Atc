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
        if (ny == y + 1) dir = 0; // R
        else if (nx == x - 1) dir = 1; // U
        else if (ny == y - 1) dir = 2; // L
        else if (nx == x + 1) dir = 3; // D

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

        if (dirs.empty()) continue;

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
        for (int d : dirs) cerr << " " << d;
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
        for (int d : dirs) cerr << " " << d;
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

    // 目的地間の経路を連結
    vector<pair<int, int>> full_path;
    for (int i = 0; i + 1 < K; i++) {
        auto path = bfs_path(grid, N, goals[i], goals[i + 1]);
        if (i > 0)
            path.erase(path.begin()); // 重複防止
        for (auto &p : path)
            full_path.push_back(p);
    }

    // 経路をセグメントに分解
    vector<Segment> segments = decompose_path(full_path);

    // 盤面の色を設定 & 遷移規則を生成
    vector<vector<int>> board(N, vector<int>(N, 0)); // デフォルトは色0
    pair<map<pair<int, int>, tuple<int, int, char>>, int> result = generate_rules(full_path, N, board);
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
