#include <algorithm>
#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int N, M;
const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};
const char dir_char[4] = {'U', 'D', 'L', 'R'};

int start_i, start_j;
vector<pair<int, int>> goals(39);

int seed = 1;
mt19937 mt(seed);

const double TIME_LIMIT = 1900.0;

struct Timer {
    chrono::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::system_clock::time_point current = chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};

int best_turn = 10000;

struct Link {
    vector<vector<bool>> block;
    int ci, cj;
    vector<string> actions;
    vector<bool> reached_goal;
    set<pair<int, int>> placed_blocks; // 設置したブロック
    set<pair<int, int>> used_blocks;   // 実際に使われたブロック
    set<pair<int, int>> banned_blocks; // 次の周回で設置禁止にするブロック

    Link(int si, int sj)
        : ci(si), cj(sj), block(N, vector<bool>(N, false)),
          reached_goal(M, false) {}

    bool is_in(int i, int j) const {
        return 0 <= i && i < N && 0 <= j && j < N;
    }

    bool has_nearby_block(int i, int j) {
        for (int dx = -3; dx <= 3; ++dx) {
            for (int dy = -3; dy <= 3; ++dy) {
                if (abs(dx) + abs(dy) > 3)
                    continue;
                int ni = i + dx, nj = j + dy;
                if (is_in(ni, nj) && block[ni][nj])
                    return true;
            }
        }
        return false;
    }

    bool maybe_toggle_block(int exclude_dir, int goal_id) {
        if (mt() % (5 + goal_id) == 0) {
            vector<int> dirs = {0, 1, 2, 3};
            shuffle(dirs.begin(), dirs.end(), mt);
            for (int d : dirs) {
                if (d == exclude_dir)
                    continue;
                int ni = ci + di[d], nj = cj + dj[d];
                if (is_in(ni, nj)) {
                    if (banned_blocks.count({ni, nj}))
                        continue; // 禁止リストにあったら設置しない

                    bool is_goal = false;
                    for (const auto &g : goals) {
                        if (g.first == ni && g.second == nj) {
                            is_goal = true;
                            break;
                        }
                    }
                    if (is_goal)
                        continue;

                    if (has_nearby_block(ni, nj))
                        continue;

                    block[ni][nj] = !block[ni][nj];
                    actions.push_back("A "s + dir_char[d]);

                    placed_blocks.insert({ni, nj}); // 設置したことを記録

                    return true;
                }
            }
        }
        return false;
    }

    vector<pair<char, int>> bfs(int si, int sj, int ti, int tj) {
        queue<pair<int, int>> q;
        vector<vector<pair<int, int>>> prev(
            N, vector<pair<int, int>>(N, {-1, -1}));
        vector<vector<char>> how(N, vector<char>(N));
        q.emplace(si, sj);
        prev[si][sj] = {si, sj};

        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            for (int d = 0; d < 4; ++d) {
                int ni = i + di[d], nj = j + dj[d];
                if (is_in(ni, nj) && !block[ni][nj] &&
                    prev[ni][nj].first == -1) {
                    prev[ni][nj] = {i, j};
                    how[ni][nj] = d;
                    q.emplace(ni, nj);
                }

                ni = i, nj = j;
                while (is_in(ni + di[d], nj + dj[d]) &&
                       !block[ni + di[d]][nj + dj[d]]) {
                    ni += di[d];
                    nj += dj[d];
                }
                if ((ni != i || nj != j) && prev[ni][nj].first == -1) {
                    prev[ni][nj] = {i, j};
                    how[ni][nj] = d + 4;
                    q.emplace(ni, nj);
                }
            }
        }

        // ゴールがブロックされていても、1マス手前から解除できるようにする
        if (prev[ti][tj].first == -1) {
            for (int d = 0; d < 4; ++d) {
                int ni = ti + di[d], nj = tj + dj[d];
                if (is_in(ni, nj) && prev[ni][nj].first != -1) {
                    // ゴールの隣のマスからブロックを壊して到達可能
                    prev[ti][tj] = {ni, nj};
                    how[ti][tj] =
                        d; // 移動方向として記録（MでもSでもないが特別処理で対応）
                    break;
                }
            }
        }

        if (prev[ti][tj].first == -1)
            return {};

        vector<pair<char, int>> path;
        int x = ti, y = tj;
        while (!(x == si && y == sj)) {
            int px, py;
            tie(px, py) = prev[x][y];
            int move_type = how[x][y];
            if (move_type >= 4)
                path.emplace_back('S', move_type - 4);
            else
                path.emplace_back('M', move_type);
            x = px, y = py;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    bool move_with_bfs(int goal_id) {
        // 目的地がブロックされていたら壊す
        int ti = goals[goal_id].first;
        int tj = goals[goal_id].second;

        while (!(ci == ti && cj == tj)) {
            auto path = bfs(ci, cj, ti, tj);
            if (path.empty())
                return false; // 行けない

            for (auto [type, d] : path) {
                bool updated = maybe_toggle_block(d, goal_id);

                if (type == 'M') {
                    int ni = ci + di[d], nj = cj + dj[d];
                    if (!is_in(ni, nj) || block[ni][nj])
                        return false;
                    ci = ni;
                    cj = nj;
                    actions.push_back("M "s + dir_char[d]);
                } else { // 'S' のとき
                    int ni = ci, nj = cj;
                    bool moved = false;
                    while (is_in(ni + di[d], nj + dj[d]) &&
                           !block[ni + di[d]][nj + dj[d]]) {
                        ni += di[d];
                        nj += dj[d];
                        moved = true;
                    }
                    if (!moved)
                        return false;

                    // ここで、止まった位置の隣にブロックがあるはず
                    int stop_i = ni + di[d];
                    int stop_j = nj + dj[d];
                    if (is_in(stop_i, stop_j)) {
                        if (block[stop_i][stop_j]) {
                            used_blocks.insert(
                                {stop_i, stop_j}); // 使ったブロックとして記録
                        }
                    }

                    ci = ni;
                    cj = nj;
                    actions.push_back("S "s + dir_char[d]);
                }

                updated |= maybe_toggle_block(d, goal_id);
                if (updated)
                    break; // ブロック設置でBFSやり直し
            }
        }

        reached_goal[goal_id] = true;
        return true;
    }

    void solve() {
        for (int i = 0; i < M - 1; ++i) {
            if (actions.size() >= best_turn) {
                break;
            }
            if (!move_with_bfs(i)) {
                break;
            }
        }
        // solveが終わったら、使われなかったブロックを禁止リストに追加
        for (auto &p : placed_blocks) {
            if (used_blocks.count(p) == 0) {
                banned_blocks.insert(p);
            }
        }
    }

    int score() const {
        int unreached =
            M - 1 - count(reached_goal.begin(), reached_goal.end(), true);
        return 40 + 2 * N * M - actions.size() - unreached * 10000;
    }

    void output_actions() const {
        for (const auto &act : actions) {
            cout << act << '\n';
        }
    }
};

int main() {
    cin >> N >> M;
    cin >> start_i >> start_j;
    for (int i = 0; i < M - 1; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }

    Link initial(start_i, start_j);

    Timer timer;
    Link best = initial;
    best.solve();

    int lp = 0;
    while (timer.progress() < 1.0) {
        lp++;
        Link current = initial;
        current.solve();
        if (current.score() > best.score()) {
            cerr << "lp: " << lp << " score: " << current.score() << '\n';
            best = current;
            best_turn = best.actions.size();
        }
    }

    best.output_actions();
    return 0;
}
