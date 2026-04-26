#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int N, M, C;
vector<vector<int>> board;
vector<int> target;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
char dc[4] = {'U', 'R', 'D', 'L'};

bool inside(int x, int y) { return 0 <= x && x < N && 0 <= y && y < N; }

struct Snake {
    deque<pii> body;
    deque<int> color;
};

vector<int> bfs(pii start, function<bool(int, int)> is_goal,
                function<bool(int, int)> can_pass, const Snake &snake,
                bool use_occ = true, bool allow_u_turn = false) {
    queue<pii> q;
    map<pii, pii> prev;
    map<pii, int> pdir;

    set<pii> occ;
    if (use_occ) {
        occ = set<pii>(snake.body.begin(), snake.body.end());
        if (!snake.body.empty())
            occ.erase(snake.body.back());
    }
    q.push(start);
    prev[start] = {-1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (is_goal(x, y)) {
            vector<int> path;
            pii cur = {x, y};
            while (prev[cur] != make_pair(-1, -1)) {
                path.push_back(pdir[cur]);
                cur = prev[cur];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (!inside(nx, ny))
                continue;
            if (prev.count({nx, ny}))
                continue;
            if (occ.count({nx, ny}) && !is_goal(nx, ny))
                continue;
            // Strict U-turn check: body[1] is always forbidden as target.
            // This is a game rule and cannot be overridden by allow_u_turn.
            if (snake.body.size() >= 2 && make_pair(nx, ny) == snake.body[1])
                continue;
            if (!can_pass(nx, ny) && !is_goal(nx, ny))
                continue;

            prev[{nx, ny}] = {x, y};
            pdir[{nx, ny}] = d;
            q.push({nx, ny});
        }
    }
    return {};
}

int longest_matched_prefix(const Snake &s) {
    int len = min((int)s.color.size(), M);
    int p = 0;
    while (p < len && s.color[p] == target[p])
        p++;
    return p;
}

void move_snake(Snake &s, int dir, pii &head, int &progress,
                bool update_progress = true) {
    int nx = head.first + dx[dir];
    int ny = head.second + dy[dir];
    head = {nx, ny};

    s.body.push_front(head);
    int eaten_color = board[nx][ny];
    if (eaten_color != 0) {
        board[nx][ny] = 0;
        s.color.push_back(eaten_color);
    } else {
        s.body.pop_back();
    }
    if (update_progress) {
        progress = longest_matched_prefix(s);
    }
}

void bite(Snake &s, pii &head, vector<pii> &saved, vector<int> &saved_color,
          vector<char> &ans, int &progress, int bite_count) {
    if (s.body.size() <= 5)
        return;

    int preserve = longest_matched_prefix(s);
    int bite_idx = max(2, preserve + (bite_count % 5));

    pii target_pos = s.body[bite_idx];
    auto path = bfs(
        head, [&](int x, int y) { return make_pair(x, y) == target_pos; },
        [&](int x, int y) { return board[x][y] == 0; }, s, false, true);
    if (path.empty())
        return;

    auto original_head = head;
    auto original_body = s.body;
    int original_ans_size = ans.size();

    for (int d : path) {
        ans.push_back(dc[d]);
        move_snake(s, d, head, progress, false);

        for (int i = 1; i < (int)s.body.size(); i++) {
            if (s.body[i] == head) {
                int bite_pos = i;
                for (int j = bite_pos + 1; j < (int)s.body.size(); j++) {
                    saved.push_back(s.body[j]);
                    saved_color.push_back(s.color[j]);
                    board[s.body[j].first][s.body[j].second] = s.color[j];
                }
                while ((int)s.body.size() > bite_pos + 1) {
                    s.body.pop_back();
                    s.color.pop_back();
                }
                return;
            }
        }
    }

    // if no bite, revert
    s.body = original_body;
    head = original_head;
    ans.resize(original_ans_size);
}

void restore(Snake &s, pii &head, vector<pii> saved, vector<int> saved_color,
             int &progress, vector<char> &ans) {
    while (!saved.empty() && progress < M && (int)ans.size() < 100000) {
        int next_color = target[progress];
        bool found = false;
        for (int idx = 0; idx < (int)saved.size(); idx++) {
            if (saved_color[idx] != next_color)
                continue;
            auto path = bfs(
                head,
                [&](int x, int y) { return make_pair(x, y) == saved[idx]; },
                [&](int x, int y) {
                    return board[x][y] == 0 || make_pair(x, y) == saved[idx];
                },
                s, false, false);
            if (path.empty())
                continue;
            for (int d : path) {
                ans.push_back(dc[d]);
                move_snake(s, d, head, progress, false);
            }
            saved.erase(saved.begin() + idx);
            saved_color.erase(saved_color.begin() + idx);
            found = true;
            progress = longest_matched_prefix(s);
            break;
        }
        if (!found)
            break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> C;
    target.resize(M);
    for (int i = 0; i < M; i++)
        cin >> target[i];

    board.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }

    Snake snake;
    pii head = {4, 0};
    for (int i = 4; i >= 0; i--) {
        snake.body.emplace_back(i, 0);
        snake.color.push_back(1);
    }

    vector<char> ans;
    int progress = 5;

    int prev_progress = -1;
    int stuck_count = 0;
    bool did_fallback = false;
    int last_bite_progress = -1;
    int bite_count = 0;
    while (progress < M && (int)ans.size() < 100000) {

        auto path = bfs(
            head,
            [&](int x, int y) {
                return board[x][y] != 0 && board[x][y] == target[progress];
            },
            [&](int x, int y) { return board[x][y] == 0; }, snake, true, false);

        did_fallback = false;
        if (path.empty()) {
            path = bfs(
                head, [&](int x, int y) { return board[x][y] != 0; },
                [&](int x, int y) { return board[x][y] == 0; }, snake, true,
                false);
            did_fallback = true;
            if (path.empty()) {
                if (stuck_count > 10)
                    break;
                stuck_count++;
                continue;
            } else {
                stuck_count = 0;
            }
        } else {
            stuck_count = 0;
        }

        for (int d : path) {
            ans.push_back(dc[d]);
            move_snake(snake, d, head, progress);
        }

        // Bite only when we had to fallback and progress > 5 and advanced
        if (did_fallback && snake.body.size() > 5 && progress > 5 &&
            progress > last_bite_progress) {
            vector<pii> saved;
            vector<int> saved_color;
            bite(snake, head, saved, saved_color, ans, progress, 0);
            if (!saved.empty()) {
                progress = longest_matched_prefix(snake);
                restore(snake, head, saved, saved_color, progress, ans);
                progress = longest_matched_prefix(snake);
            }
            last_bite_progress = progress;
        }

        if (progress == prev_progress && stuck_count > 5) {
            // Progress stuck, break
            break;
        }
        prev_progress = progress;
    }

    int k = snake.color.size();
    int E = 0;
    for (int p = 0; p < k; p++) {
        if (snake.color[p] != target[p])
            E++;
    }

    for (char c : ans) {
        cout << c << '\n';
    }
    return 0;
}
