#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> grid;
vector<pair<int, int>> card_pos[200];

// カード回収順序から総移動距離を計算
int calc_score(const vector<int> &order) {
    int h = 0, w = 0;
    int total_dist = 0;

    for (int card_num : order) {
        // 1枚目への移動
        int h1 = card_pos[card_num][0].first;
        int w1 = card_pos[card_num][0].second;
        total_dist += abs(h - h1) + abs(w - w1) + 1; // +1 for Z
        h = h1;
        w = w1;

        // 2枚目への移動
        int h2 = card_pos[card_num][1].first;
        int w2 = card_pos[card_num][1].second;
        total_dist += abs(h - h2) + abs(w - w2) + 1; // +1 for Z
        h = h2;
        w = w2;
    }

    return total_dist;
}

// 順序から実際の移動列を生成
string generate_moves(const vector<int> &order) {
    string ans;
    int cur_h = 0, cur_w = 0;

    for (int card_num : order) {
        // 1枚目への移動
        int h1 = card_pos[card_num][0].first;
        int w1 = card_pos[card_num][0].second;

        while (cur_h < h1) {
            ans += 'D';
            cur_h++;
        }
        while (cur_h > h1) {
            ans += 'U';
            cur_h--;
        }
        while (cur_w < w1) {
            ans += 'R';
            cur_w++;
        }
        while (cur_w > w1) {
            ans += 'L';
            cur_w--;
        }
        ans += 'Z';
        cur_h = h1;
        cur_w = w1;

        // 2枚目への移動
        int h2 = card_pos[card_num][1].first;
        int w2 = card_pos[card_num][1].second;

        while (cur_h < h2) {
            ans += 'D';
            cur_h++;
        }
        while (cur_h > h2) {
            ans += 'U';
            cur_h--;
        }
        while (cur_w < w2) {
            ans += 'R';
            cur_w++;
        }
        while (cur_w > w2) {
            ans += 'L';
            cur_w--;
        }
        ans += 'Z';
        cur_h = h2;
        cur_w = w2;
    }

    return ans;
}

int main() {
    cin >> N;
    grid.resize(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            card_pos[grid[i][j]].push_back({i, j});
        }
    }

    int num_cards = N * N / 2;

    // 初期解: 0, 1, 2, ..., num_cards-1 の順
    vector<int> current_order(num_cards);
    for (int i = 0; i < num_cards; i++) {
        current_order[i] = i;
    }

    int best_score = calc_score(current_order);
    vector<int> best_order = current_order;

    auto start_time = chrono::steady_clock::now();
    const double TIME_LIMIT = 1.9; // 秒

    mt19937 rng(42);

    while (true) {
        auto current_time = chrono::steady_clock::now();
        double elapsed =
            chrono::duration<double>(current_time - start_time).count();
        if (elapsed > TIME_LIMIT)
            break;

        vector<int> new_order = current_order;

        // 近傍操作をランダムに選択
        if (rng() % 2 == 0) {
            // スワップ操作
            int i = rng() % num_cards;
            int j = rng() % num_cards;
            swap(new_order[i], new_order[j]);
        } else {
            // 挿入操作
            int from = rng() % num_cards;
            int to = rng() % num_cards;
            int card = new_order[from];
            new_order.erase(new_order.begin() + from);
            new_order.insert(new_order.begin() + to, card);
        }

        int new_score = calc_score(new_order);

        // 改善した場合のみ受け入れ
        if (new_score < best_score) {
            current_order = new_order;
            best_score = new_score;
            best_order = new_order;
        }
    }

    // 最良解を出力
    string ans = generate_moves(best_order);
    for (char c : ans) {
        cout << c << endl;
    }

    return 0;
}
