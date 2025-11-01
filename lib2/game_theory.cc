// Game Theory ゲーム理論 Nim Grundy数 必勝判定

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
using namespace std;

// ========== ライブラリ部分 ==========

// Nimゲーム
class Nim {
private:
    vector<int> piles;

public:
    Nim(const vector<int>& initial_piles) : piles(initial_piles) {}

    // Nim和（XOR和）を計算
    int nim_sum() const {
        int result = 0;
        for (int pile : piles) {
            result ^= pile;
        }
        return result;
    }

    // 現在の状態が必勝かどうか判定
    bool is_winning() const {
        return nim_sum() != 0;
    }

    // 必勝手を見つける（あれば）
    pair<int, int> find_winning_move() const {
        if (!is_winning()) return {-1, -1};  // 必勝手がない

        int nim_val = nim_sum();
        for (int i = 0; i < (int)piles.size(); i++) {
            int target = piles[i] ^ nim_val;
            if (target < piles[i]) {
                return {i, piles[i] - target};  // 山i から target個取る
            }
        }
        return {-1, -1};
    }

    // 石を取る
    void take_stones(int pile_index, int stones) {
        if (pile_index >= 0 && pile_index < (int)piles.size()) {
            piles[pile_index] = max(0, piles[pile_index] - stones);
        }
    }

    // 現在の状態を表示
    void print_state() const {
        cout << "山の状態: ";
        for (int pile : piles) cout << pile << " ";
        cout << "(Nim和: " << nim_sum() << ")";
    }

    // ゲーム終了判定
    bool is_game_over() const {
        for (int pile : piles) {
            if (pile > 0) return false;
        }
        return true;
    }
};

// Grundy数を計算するクラス
class GrundyCalculator {
private:
    map<int, int> memo;

public:
    // 状態からGrundy数を計算（メモ化あり）
    int grundy(int state, const vector<int>& moves) {
        if (memo.find(state) != memo.end()) {
            return memo[state];
        }

        set<int> reachable;
        for (int move : moves) {
            if (state >= move) {
                reachable.insert(grundy(state - move, moves));
            }
        }

        // mex（minimum excludant）を計算
        int mex = 0;
        while (reachable.count(mex)) {
            mex++;
        }

        return memo[state] = mex;
    }

    // 複数の独立したゲームのGrundy数（XOR）
    int combined_grundy(const vector<int>& states, const vector<int>& moves) {
        int result = 0;
        for (int state : states) {
            result ^= grundy(state, moves);
        }
        return result;
    }

    void clear_memo() {
        memo.clear();
    }
};

// 石取りゲーム（一度に1個、2個、または3個取れる）
class StoneGame {
private:
    int stones;
    GrundyCalculator gc;

public:
    StoneGame(int n) : stones(n) {}

    int grundy_value() {
        vector<int> moves = {1, 2, 3};
        return gc.grundy(stones, moves);
    }

    bool is_winning() {
        return grundy_value() != 0;
    }
};

// 一般的な石取りゲーム
class GeneralStoneGame {
private:
    vector<int> allowed_moves;
    GrundyCalculator gc;

public:
    GeneralStoneGame(const vector<int>& moves) : allowed_moves(moves) {}

    int grundy_value(int stones) {
        return gc.grundy(stones, allowed_moves);
    }

    bool is_winning(int stones) {
        return grundy_value(stones) != 0;
    }

    // 複数山での必勝判定
    bool is_winning_multi(const vector<int>& piles) {
        return gc.combined_grundy(piles, allowed_moves) != 0;
    }
};

// 階段Nim
class StairNim {
private:
    vector<int> stairs;

public:
    StairNim(const vector<int>& initial_stairs) : stairs(initial_stairs) {}

    // 階段Nimでは奇数番目の階段のXORを取る
    bool is_winning() {
        int xor_sum = 0;
        for (int i = 1; i < (int)stairs.size(); i += 2) {  // 奇数番目（1-indexed）
            xor_sum ^= stairs[i];
        }
        return xor_sum != 0;
    }

    void print_state() const {
        cout << "階段の状態: ";
        for (int i = 0; i < (int)stairs.size(); i++) {
            cout << "階段" << i << ":" << stairs[i] << " ";
        }
    }
};

// 2人零和ゲームのミニマックス法（簡単な例）
class TicTacToe {
private:
    vector<vector<char>> board;

    bool is_winner(char player) {
        // 行・列・対角線をチェック
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                return true;
            }
        }
        return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
               (board[0][2] == player && board[1][1] == player && board[2][0] == player);
    }

    bool is_full() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') return false;
            }
        }
        return true;
    }

    int minimax(bool is_maximizing) {
        if (is_winner('X')) return 1;
        if (is_winner('O')) return -1;
        if (is_full()) return 0;

        if (is_maximizing) {
            int best_score = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        int score = minimax(false);
                        board[i][j] = ' ';
                        best_score = max(best_score, score);
                    }
                }
            }
            return best_score;
        } else {
            int best_score = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        int score = minimax(true);
                        board[i][j] = ' ';
                        best_score = min(best_score, score);
                    }
                }
            }
            return best_score;
        }
    }

public:
    TicTacToe() : board(3, vector<char>(3, ' ')) {}

    pair<int, int> best_move() {
        int best_score = -1000;
        pair<int, int> best_pos = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(false);
                    board[i][j] = ' ';

                    if (score > best_score) {
                        best_score = score;
                        best_pos = {i, j};
                    }
                }
            }
        }

        return best_pos;
    }

    void make_move(int x, int y, char player) {
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
            board[x][y] = player;
        }
    }

    void print_board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "-----" << endl;
        }
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: Nimゲーム
    cout << "例1: Nimゲーム" << endl;
    vector<int> nim_piles = {3, 4, 5};
    Nim nim_game(nim_piles);

    nim_game.print_state();
    cout << " -> " << (nim_game.is_winning() ? "先手必勝" : "後手必勝") << endl;

    auto [pile_idx, stones] = nim_game.find_winning_move();
    if (pile_idx != -1) {
        cout << "必勝手: 山" << pile_idx << "から" << stones << "個取る" << endl;
        nim_game.take_stones(pile_idx, stones);
        nim_game.print_state();
        cout << " -> " << (nim_game.is_winning() ? "先手必勝" : "後手必勝") << endl;
    }
    cout << endl;

    // 例2: Grundy数の計算
    cout << "例2: Grundy数の計算" << endl;
    cout << "石取りゲーム（1,2,3個ずつ取れる）:" << endl;

    for (int stones = 0; stones <= 10; stones++) {
        StoneGame sg(stones);
        cout << "石" << stones << "個: Grundy=" << sg.grundy_value()
             << " (" << (sg.is_winning() ? "必勝" : "必敗") << ")" << endl;
    }
    cout << endl;

    // 例3: 一般的な石取りゲーム
    cout << "例3: 一般的な石取りゲーム（1,3,4個取れる）" << endl;
    vector<int> moves = {1, 3, 4};
    GeneralStoneGame gsg(moves);

    for (int stones = 0; stones <= 15; stones++) {
        cout << "石" << stones << "個: Grundy=" << gsg.grundy_value(stones)
             << " (" << (gsg.is_winning(stones) ? "必勝" : "必敗") << ")" << endl;
    }
    cout << endl;

    // 例4: 複数山での石取りゲーム
    cout << "例4: 複数山での石取りゲーム" << endl;
    vector<int> multi_piles = {2, 3, 4};
    cout << "山の状態: ";
    for (int pile : multi_piles) cout << pile << " ";
    cout << "-> " << (gsg.is_winning_multi(multi_piles) ? "先手必勝" : "後手必勝") << endl;
    cout << endl;

    // 例5: 階段Nim
    cout << "例5: 階段Nim" << endl;
    vector<int> stair_stones = {0, 2, 1, 3, 2};  // 階段0,1,2,3,4に石が0,2,1,3,2個
    StairNim stair_nim(stair_stones);

    stair_nim.print_state();
    cout << " -> " << (stair_nim.is_winning() ? "先手必勝" : "後手必勝") << endl;
    cout << endl;

    // 例6: 様々なNimの亜種
    cout << "例6: 様々なNimゲームでの必勝判定" << endl;

    vector<vector<int>> test_cases = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 1, 1},
        {7, 8, 9},
        {2, 4, 6, 8}
    };

    for (const auto& piles : test_cases) {
        Nim test_nim(piles);
        test_nim.print_state();
        cout << " -> " << (test_nim.is_winning() ? "先手必勝" : "後手必勝") << endl;
    }
    cout << endl;

    // 例7: Grundy数の組み合わせ
    cout << "例7: 独立したゲームの組み合わせ" << endl;
    cout << "ゲーム1: 石5個（1,2,3個取れる）" << endl;
    cout << "ゲーム2: 石7個（1,2,3個取れる）" << endl;

    StoneGame game1(5), game2(7);
    int combined = game1.grundy_value() ^ game2.grundy_value();

    cout << "ゲーム1のGrundy数: " << game1.grundy_value() << endl;
    cout << "ゲーム2のGrundy数: " << game2.grundy_value() << endl;
    cout << "組み合わせ: " << combined << " (" << (combined != 0 ? "先手必勝" : "後手必勝") << ")" << endl;
    cout << endl;

    // 例8: ミニマックス法（三目並べの最適手）
    cout << "例8: ミニマックス法（三目並べ）" << endl;
    TicTacToe ttt;

    cout << "初期盤面:" << endl;
    ttt.print_board();

    auto [best_x, best_y] = ttt.best_move();
    cout << "最適手: (" << best_x << ", " << best_y << ")" << endl;

    ttt.make_move(best_x, best_y, 'X');
    cout << "手を打った後:" << endl;
    ttt.print_board();

    return 0;
}