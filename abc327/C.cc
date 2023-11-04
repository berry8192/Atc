#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    vector<vector<int>> A(9, vector<int>(9));

    // マス目Aの入力を受け取る
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> A[i][j];
        }
    }

    // 各行、各列、各3x3のブロックに対してセットを使ってユニークな要素の数を数える
    for (int i = 0; i < 9; i++) {
        set<int> rowSet, colSet;
        for (int j = 0; j < 9; j++) {
            rowSet.insert(A[i][j]);
            colSet.insert(A[j][i]);
        }
        if (rowSet.size() != 9 || colSet.size() != 9) {
            cout << "No" << endl;
            return 0;
        }
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            set<int> blockSet;
            for (int x = i; x < i + 3; x++) {
                for (int y = j; y < j + 3; y++) {
                    blockSet.insert(A[x][y]);
                }
            }
            if (blockSet.size() != 9) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    // すべての条件を満たす場合、Yesを出力
    cout << "Yes" << endl;

    return 0;
}
