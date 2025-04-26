#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <tuple> // tieを使うため
#include <vector>
using namespace std;

int N, M;
const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};
const char dir_char[4] = {'U', 'D', 'L', 'R'};

int start_i, start_j;
vector<pair<int, int>> goals(40);

struct Link {
    vector<vector<bool>> block;
    int ci, cj;
    vector<string> actions;
    mt19937 mt;
    uniform_int_distribution<> chance;

    Link(int si, int sj)
        : ci(si), cj(sj), block(N, vector<bool>(N, false)), chance(0, 99) {
        random_device seed_gen;
        mt.seed(seed_gen());
    }

    bool is_in(int i, int j) const {
        return 0 <= i && i < N && 0 <= j && j < N;
    }

    bool maybe_toggle_block(int exclude_dir) {
        if (chance(mt) < 5) {
            vector<int> dirs = {0, 1, 2, 3};
            shuffle(dirs.begin(), dirs.end(), mt);
            for (int d : dirs) {
                if (d == exclude_dir)
                    continue;
                int ni = ci + di[d], nj = cj + dj[d];
                if (is_in(ni, nj)) {
                    block[ni][nj] = !block[ni][nj];
                    actions.push_back("A "s + dir_char[d]);
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
                    how[ni][nj] = d + 4; // 4以上なら滑走
                    q.emplace(ni, nj);
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

    void move_with_bfs(int ti, int tj) {
        while (!(ci == ti && cj == tj)) {
            auto path = bfs(ci, cj, ti, tj);
            if (path.empty())
                return; // もう行けない

            for (auto [type, d] : path) {
                bool updated = maybe_toggle_block(d);

                if (type == 'M') {
                    int ni = ci + di[d], nj = cj + dj[d];
                    if (!is_in(ni, nj) || block[ni][nj])
                        break;
                    ci = ni;
                    cj = nj;
                    actions.push_back("M "s + dir_char[d]);
                } else {
                    int ni = ci, nj = cj;
                    bool moved = false;
                    while (is_in(ni + di[d], nj + dj[d]) &&
                           !block[ni + di[d]][nj + dj[d]]) {
                        ni += di[d];
                        nj += dj[d];
                        moved = true;
                    }
                    if (!moved)
                        break;
                    ci = ni;
                    cj = nj;
                    actions.push_back("S "s + dir_char[d]);
                }

                updated |= maybe_toggle_block(d);
                if (updated)
                    break; // ブロック設置ならBFSからやり直す
            }
        }
    }

    void solve() {
        for (const auto &g : goals) {
            move_with_bfs(g.first, g.second);
        }
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
    for (int i = 0; i < M; ++i) {
        cin >> goals[i].first >> goals[i].second;
    }

    Link link(start_i, start_j);
    link.solve();
    link.output_actions();

    return 0;
}
