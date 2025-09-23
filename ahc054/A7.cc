#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

// グローバル変数
int N, ti, tj;
vector<string> current_maze;
vector<vector<bool>> confirmed;
vector<pair<int, int>> placed_treants;

// 4方向の移動
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

// 花からの道の最大長さ
const int MAX_FLOWER_PATH_LENGTH = 8;

// 道を管理する構造体
struct Path {
    int id;                       // 道のID
    vector<pair<int, int>> cells; // 道のマスリスト
    int last_dir;                 // 最後に進んだ方向
    bool active;                  // この道がアクティブか
    int extension_count;          // 分岐後の延長回数
    bool is_initial;              // 初期の道かどうか
    bool from_flower;             // 花から出発した道か

    Path(int path_id, int sr, int sc, bool initial = false,
         bool flower_origin = false)
        : id(path_id), last_dir(-1), active(true), extension_count(0),
          is_initial(initial), from_flower(flower_origin) {
        cells.push_back({sr, sc});
    }

    pair<int, int> head() const {
        if (cells.empty())
            return {-1, -1};
        return cells.back();
    }

    void add_cell(int r, int c, int dir) {
        cells.push_back({r, c});
        last_dir = dir;
        extension_count++;
    }

    void deactivate() { active = false; }

    bool can_branch() const {
        // 花からの道は分岐しない
        if (from_flower)
            return false;
        // 冒険者からの道も使わないので常にfalse
        return false;
    }
};

// 迷路を生成する構造体
struct MazeGenerator {
    vector<string> maze;          // 現在の迷路
    vector<Path> paths;           // 道のリスト
    vector<vector<int>> path_map; // 各マスがどの道に属するか (-1: 未使用)
    vector<vector<bool>> from_flower_map;  // 各マスが花からの道か
    vector<pair<int, int>> reserved_cells; // 冒険者の道として予約されたマス
    int N, ti, tj;
    int next_path_id;

    MazeGenerator(int n, int flower_i, int flower_j,
                  const vector<string> &initial_maze)
        : N(n), ti(flower_i), tj(flower_j), maze(initial_maze),
          next_path_id(1) {
        path_map.assign(N, vector<int>(N, -1));
        from_flower_map.assign(N, vector<bool>(N, false));
    }

    // 指定したマスが使用可能かチェック
    bool can_use_cell(int r, int c, int path_id, bool path_from_flower) {
        if (r < 0 || r >= N || c < 0 || c >= N)
            return false;
        if (maze[r][c] != '.')
            return false;
        if (path_map[r][c] != -1)
            return false; // 既に使用されている

        // 花から距離3の4方向は道にしない
        if ((r == ti + 3 && c == tj) || (r == ti && c == tj + 3) ||
            (r == ti - 3 && c == tj) || (r == ti && c == tj - 3)) {
            return false;
        }

        // 4近傍をチェック
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                // 異なる道のマスと隣接している場合のチェック
                if (path_map[nr][nc] != -1 && path_map[nr][nc] != path_id) {
                    // 花からの道と冒険者からの道は隣接OK
                    if (from_flower_map[nr][nc] != path_from_flower) {
                        // 異なる出発点の道同士はOK
                        continue;
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // 最も近い他の道の先頭までの距離を計算
    int get_min_distance_to_other_heads(int r, int c, int exclude_id) {
        int min_dist = N * N;
        for (const auto &path : paths) {
            if (path.id != exclude_id && path.active) {
                auto [hr, hc] = path.head();
                int dist = abs(r - hr) + abs(c - hc);
                min_dist = min(min_dist, dist);
            }
        }
        return min_dist;
    }

    // 花からのみ道を生成（枝分かれなし、最大長さ8、方向転換可）
    void generate_flower_only_paths(int flower_r, int flower_c) {
        // 花から各方向に道を開始
        for (int initial_dir = 0; initial_dir < 4; initial_dir++) {
            int curr_r = flower_r;
            int curr_c = flower_c;
            Path flower_path(next_path_id++, flower_r, flower_c, false, true);
            int last_dir = initial_dir;

            // 最大長さ8まで道を伸ばす（方向転換可能）
            for (int len = 0; len < MAX_FLOWER_PATH_LENGTH; len++) {
                // 利用可能な方向を探す
                vector<int> available_dirs;
                for (int d = 0; d < 4; d++) {
                    int nr = curr_r + dr[d];
                    int nc = curr_c + dc[d];

                    // 使用可能かチェック
                    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                        maze[nr][nc] == '.' && path_map[nr][nc] == -1) {

                        // 花から距離3の4方向 (3,0), (0,3), (-3,0), (0,-3)
                        // はスキップ
                        if ((nr == ti + 3 && nc == tj) ||
                            (nr == ti && nc == tj + 3) ||
                            (nr == ti - 3 && nc == tj) ||
                            (nr == ti && nc == tj - 3)) {
                            continue;
                        }

                        available_dirs.push_back(d);
                    }
                }

                if (available_dirs.empty()) {
                    break; // 進める方向がない
                }

                // 方向を選択（前回と異なる方向を優先）
                int chosen_dir = available_dirs[0];
                for (int d : available_dirs) {
                    if (d != last_dir) {
                        chosen_dir = d;
                        break;
                    }
                }

                int nr = curr_r + dr[chosen_dir];
                int nc = curr_c + dc[chosen_dir];

                flower_path.add_cell(nr, nc, chosen_dir);
                path_map[nr][nc] = flower_path.id;
                from_flower_map[nr][nc] = true;
                reserved_cells.push_back({nr, nc});

                curr_r = nr;
                curr_c = nc;
                last_dir = chosen_dir;
            }

            if (flower_path.cells.size() > 1) {
                paths.push_back(flower_path);
            }
        }

        cerr << "Created " << paths.size() << " paths from flower at ("
             << flower_r << ", " << flower_c << ")" << endl;

        // トレントを配置
        place_treants();
    }

    // BFSで到達可能性をチェック
    bool check_reachability(int start_r, int start_c,
                            const vector<string> &test_maze) {
        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<pair<int, int>> q;
        q.push({start_r, start_c});
        visited[start_r][start_c] = true;

        bool flower_reachable = false;
        int reachable_count = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            reachable_count++;

            if (r == ti && c == tj) {
                flower_reachable = true;
            }

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
                    !visited[nr][nc] && test_maze[nr][nc] == '.') {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        // 全ての空きマスが到達可能かチェック
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (test_maze[i][j] == '.' && !visited[i][j]) {
                    return false;
                }
            }
        }

        return flower_reachable;
    }

    // トレントを配置すべきかチェック（2近傍以上がブロックされている場合は配置しない）
    bool should_place_treant(int r, int c, const vector<string> &test_maze) {
        int blocked_count = 0;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N ||
                test_maze[nr][nc] == 'T') {
                blocked_count++;
            }
        }
        return blocked_count < 2;
    }

    // トレントを配置
    void place_treants() {
        vector<pair<int, int>> treant_positions;
        set<pair<int, int>> used_positions;
        vector<string> test_maze = maze;

        // 各道の最後のマスと進行方向を記録
        set<pair<int, int>> path_end_forward_positions;
        for (const auto &path : paths) {
            if (path.cells.size() > 1) {
                auto [last_r, last_c] = path.cells.back();
                // 最後の進行方向の先のマスを記録
                if (path.last_dir >= 0 && path.last_dir < 4) {
                    int forward_r = last_r + dr[path.last_dir];
                    int forward_c = last_c + dc[path.last_dir];
                    if (forward_r >= 0 && forward_r < N && forward_c >= 0 &&
                        forward_c < N) {
                        path_end_forward_positions.insert(
                            {forward_r, forward_c});
                    }
                }
            }
        }

        // 花の周りの特定位置にトレントを配置
        // (1,1), (1,-1), (-1,1), (-1,-1) の位置
        vector<pair<int, int>> diagonal_offsets = {
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        for (const auto &[dr, dc] : diagonal_offsets) {
            int tr = ti + dr;
            int tc = tj + dc;
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                test_maze[tr][tc] == '.' && path_map[tr][tc] == -1 &&
                path_end_forward_positions.find({tr, tc}) ==
                    path_end_forward_positions.end()) {
                test_maze[tr][tc] = 'T';
                if (check_reachability(0, N / 2, test_maze)) {
                    treant_positions.push_back({tr, tc});
                    used_positions.insert({tr, tc});
                } else {
                    test_maze[tr][tc] = '.';
                }
            }
        }

        // (3,0), (0,3), (-3,0), (0,-3) の位置に必ずトレントを配置
        vector<pair<int, int>> cardinal_3_offsets = {
            {3, 0}, {0, 3}, {-3, 0}, {0, -3}};
        for (const auto &[dr, dc] : cardinal_3_offsets) {
            int tr = ti + dr;
            int tc = tj + dc;
            if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                test_maze[tr][tc] == '.' && path_map[tr][tc] == -1 &&
                used_positions.find({tr, tc}) == used_positions.end() &&
                path_end_forward_positions.find({tr, tc}) ==
                    path_end_forward_positions.end()) {
                test_maze[tr][tc] = 'T';
                if (check_reachability(0, N / 2, test_maze)) {
                    treant_positions.push_back({tr, tc});
                    used_positions.insert({tr, tc});
                } else {
                    test_maze[tr][tc] = '.';
                }
            }
        }

        // 各予約済みマスの4近傍にトレントを配置
        for (const auto &[r, c] : reserved_cells) {
            for (int i = 0; i < 4; i++) {
                int tr = r + dr[i];
                int tc = c + dc[i];

                // 配置可能な位置かチェック
                if (tr >= 0 && tr < N && tc >= 0 && tc < N &&
                    test_maze[tr][tc] == '.' &&
                    path_map[tr][tc] == -1 &&  // どの道にも属していない
                    !(tr == ti && tc == tj) && // 花の位置ではない
                    used_positions.find({tr, tc}) == used_positions.end() &&
                    path_end_forward_positions.find({tr, tc}) ==
                        path_end_forward_positions
                            .end() && // 道の最終進行方向ではない
                    should_place_treant(tr, tc, test_maze)) {

                    // 仮配置して到達可能性をチェック
                    test_maze[tr][tc] = 'T';
                    if (check_reachability(0, N / 2, test_maze)) {
                        treant_positions.push_back({tr, tc});
                        used_positions.insert({tr, tc});
                    } else {
                        test_maze[tr][tc] = '.'; // 配置を取り消し
                    }
                }
            }
        }

        // トレントリストを更新
        for (const auto &pos : treant_positions) {
            placed_treants.push_back(pos);
        }
    }

    // トレントのリストを取得
    vector<pair<int, int>> get_treants() const { return placed_treants; }
};

// 動的ブロック用のフラグ
vector<vector<bool>> block_placed;

// BFSで冒険者の位置から花に到達可能か確認
bool check_flower_reachable(int start_r, int start_c,
                            const vector<string> &test_maze) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<pair<int, int>> q;
    q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == ti && c == tj) {
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < N && !visited[nr][nc] &&
                test_maze[nr][nc] == '.') {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

// 冒険者が特定位置に近づいたときのブロック処理
vector<pair<int, int>> check_dynamic_blocks(int pi, int pj) {
    vector<pair<int, int>> blocks_to_add;

    // (2,0), (0,2), (-2,0), (0,-2) の4近傍に冒険者がいるかチェック
    vector<pair<int, int>> trigger_offsets = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
    vector<pair<int, int>> block_offsets = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<pair<int, int>> treant_check_offsets = {
        {3, 0}, {0, 3}, {-3, 0}, {0, -3}};

    // 現在ブロックされていない方向の数をカウント
    int unblocked_count = 0;
    for (int i = 0; i < 4; i++) {
        int block_r = ti + block_offsets[i].first;
        int block_c = tj + block_offsets[i].second;
        if (block_r >= 0 && block_r < N && block_c >= 0 && block_c < N &&
            !block_placed[block_r][block_c] &&
            current_maze[block_r][block_c] == '.') {
            unblocked_count++;
        }
    }

    for (int i = 0; i < 4; i++) {
        int trigger_r = ti + trigger_offsets[i].first;
        int trigger_c = tj + trigger_offsets[i].second;

        // トリガー条件をチェック:
        // 1. 冒険者がトリガー位置(2,0)等にいる
        // 2. 冒険者がトリガー位置の4近傍にいる
        bool should_block = false;

        // 冒険者がトリガー位置そのものにいるか
        if (trigger_r == pi && trigger_c == pj) {
            should_block = true;
        }

        // トリガー位置の4近傍に冒険者がいるか
        if (!should_block) {
            for (int d = 0; d < 4; d++) {
                int check_r = trigger_r + dr[d];
                int check_c = trigger_c + dc[d];
                if (check_r == pi && check_c == pj) {
                    should_block = true;
                    break;
                }
            }
        }

        if (should_block) {
            // 対応するブロック位置
            int block_r = ti + block_offsets[i].first;
            int block_c = tj + block_offsets[i].second;

            // ブロック条件をチェック
            // 1. まだブロックしていない
            // 2. 設置位置が冒険者に発見されていない
            // 3. 距離3の位置にトレントがある
            if (!block_placed[block_r][block_c] && block_r >= 0 &&
                block_r < N && block_c >= 0 && block_c < N &&
                current_maze[block_r][block_c] == '.' &&
                !confirmed[block_r][block_c]) {

                // 距離3の位置にトレントがあるかチェック
                int treant_r = ti + treant_check_offsets[i].first;
                int treant_c = tj + treant_check_offsets[i].second;
                if (treant_r < 0 || treant_r >= N || treant_c < 0 ||
                    treant_c >= N || current_maze[treant_r][treant_c] != 'T') {
                    // トレントがない場合はブロックできない
                    continue;
                }

                // 実際にトレントを設置した場合の到達可能性を確認
                vector<string> test_maze = current_maze;
                test_maze[block_r][block_c] = 'T';

                // 冒険者の現在位置から花に到達可能か確認
                if (!check_flower_reachable(pi, pj, test_maze)) {
                    // 到達不可能になる場合はブロックしない
                    cerr << "Blocking (" << block_r << ", " << block_c
                         << ") would make flower unreachable, skipping" << endl;
                    continue;
                }

                blocks_to_add.push_back({block_r, block_c});
                block_placed[block_r][block_c] = true;
                unblocked_count--;
            }
        }
    }

    return blocks_to_add;
}

int main() {
    cin >> N >> ti >> tj;
    current_maze.resize(N);
    confirmed.assign(N, vector<bool>(N, false));
    block_placed.assign(N, vector<bool>(N, false));

    for (int i = 0; i < N; ++i) {
        cin >> current_maze[i];
    }

    // 初期状態
    int pi, pj;
    int n;

    int lp = 0;
    while (true) {
        lp++;
        cin >> pi >> pj >> n;

        if (pi == ti && pj == tj) {
            return 0;
        }

        vector<pair<int, int>> newly_confirmed(n);
        for (int k = 0; k < n; ++k) {
            cin >> newly_confirmed[k].first >> newly_confirmed[k].second;
        }

        for (const auto &p : newly_confirmed) {
            confirmed[p.first][p.second] = true;
        }

        // 初回のみ道とトレントを配置
        if (placed_treants.empty()) {
            MazeGenerator generator(N, ti, tj, current_maze);
            generator.generate_flower_only_paths(ti, tj); // 花からのみ道を生成
            vector<pair<int, int>> treants = generator.get_treants();

            // トレント配置の出力（正しいフォーマット）
            cout << treants.size();
            for (const auto &p : treants) {
                cout << " " << p.first << " " << p.second;
                current_maze[p.first][p.second] = 'T';
                placed_treants.push_back(p);
            }
            cout << endl << flush;
        } else {
            // 動的ブロックのチェック
            vector<pair<int, int>> dynamic_blocks =
                check_dynamic_blocks(pi, pj);

            cout << dynamic_blocks.size();
            for (const auto &p : dynamic_blocks) {
                cout << " " << p.first << " " << p.second;
                current_maze[p.first][p.second] = 'T';
                placed_treants.push_back(p);
            }
            cout << endl << flush;
        }
    }

    return 0;
}