#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
vector<string> board;

void moveRow(int i, char dir) {
    if (dir == 'L') {
        cout << "L " << i << endl;
    } else {
        cout << "R " << i << endl;
    }
}

void moveCol(int j, char dir) {
    if (dir == 'U') {
        cout << "U " << j << endl;
    } else {
        cout << "D " << j << endl;
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 'x') {
                if (i == 0 || board[i - 1][j] != 'o') {
                    for (int k = 0; k <= i; k++)
                        moveCol(j, 'U');
                    for (int k = 0; k <= i; k++)
                        moveCol(j, 'D');
                } else if (i == N - 1 || board[i + 1][j] != 'o') {
                    for (int k = 0; k <= (N - 1 - i); k++)
                        moveCol(j, 'D');
                    for (int k = 0; k <= (N - 1 - i); k++)
                        moveCol(j, 'U');
                } else if (j == 0 || board[i][j - 1] != 'o') {
                    for (int k = 0; k <= j; k++)
                        moveRow(i, 'L');
                    for (int k = 0; k <= j; k++)
                        moveRow(i, 'R');
                } else if (j == N - 1 || board[i][j + 1] != 'o') {
                    for (int k = 0; k <= (N - 1 - j); k++)
                        moveRow(i, 'R');
                    for (int k = 0; k <= (N - 1 - j); k++)
                        moveRow(i, 'L');
                }
            }
        }
    }
}

int main() {
    cin >> N;
    board.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> board[i];
    }
    solve();
    return 0;
}
