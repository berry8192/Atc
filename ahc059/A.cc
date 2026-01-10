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

    // 初期解: 貪欲法で生成
    vector<int> current_order;
    vector<bool> used(num_cards, false);

    // (0,0)にあるカードから始める
    int start_card = grid[0][0];
    current_order.push_back(start_card);
    used[start_card] = true;

    // 最後の位置（2枚目のカードの位置）
    int cur_h = card_pos[start_card][1].first;
    int cur_w = card_pos[start_card][1].second;

    // 残りのカードを貪欲に選択
    for (int cnt = 1; cnt < num_cards; cnt++) {
        int best_card = -1;
        int best_dist = INT_MAX;

        // 未使用のカードの中で最も近いものを探す
        for (int card = 0; card < num_cards; card++) {
            if (used[card])
                continue;

            // このカードの1枚目への距離
            int h1 = card_pos[card][0].first;
            int w1 = card_pos[card][0].second;
            int dist = abs(cur_h - h1) + abs(cur_w - w1);

            if (dist < best_dist) {
                best_dist = dist;
                best_card = card;
            }
        }

        current_order.push_back(best_card);
        used[best_card] = true;

        // 次の位置を更新（2枚目のカードの位置）
        cur_h = card_pos[best_card][1].first;
        cur_w = card_pos[best_card][1].second;
    }

    int best_score = calc_score(current_order);
    vector<int> best_order = current_order;

    // 初期解のデバッグ出力
    cerr << "Initial best_order (score=" << best_score << "): ";
    for (int card : best_order) {
        cerr << card << " ";
    }
    cerr << endl;

    auto start_time = chrono::steady_clock::now();
    const double TIME_LIMIT = 1.9; // 秒

    mt19937 rng(42);

    int loop = 0;
    while (true) {
        loop++;
        auto current_time = chrono::steady_clock::now();
        double elapsed =
            chrono::duration<double>(current_time - start_time).count();
        if (elapsed > TIME_LIMIT)
            break;

        vector<int> new_order = current_order;

        // 近傍操作をランダムに選択
        int op = rng() % 3;
        int swap_card = -1;

        if (op == 0) {
            // スワップ操作
            int i = rng() % num_cards;
            int j = rng() % num_cards;
            swap(new_order[i], new_order[j]);
        } else if (op == 1) {
            // 挿入操作
            int from = rng() % num_cards;
            int to = rng() % num_cards;
            int card = new_order[from];
            new_order.erase(new_order.begin() + from);
            new_order.insert(new_order.begin() + to, card);
        } else {
            // カードの1枚目と2枚目を入れ替える操作
            swap_card = rng() % num_cards;
            swap(card_pos[swap_card][0], card_pos[swap_card][1]);
        }

        int new_score = calc_score(new_order);

        // 改善した場合のみ受け入れ
        if (new_score < best_score) {
            current_order = new_order;
            best_score = new_score;
            best_order = new_order;
        } else {
            // 受け入れなかった場合、カードの入れ替えを元に戻す
            if (op == 2 && swap_card != -1) {
                swap(card_pos[swap_card][0], card_pos[swap_card][1]);
            }
        }
    }

    cerr << loop << endl;
    // 最良解を出力
    string ans = generate_moves(best_order);
    for (char c : ans) {
        cout << c << endl;
    }

    return 0;
}
