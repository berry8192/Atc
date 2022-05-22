#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 1<<29;        // 十分大きい値にする

// 入力
string S, T;

// DP テーブル
int dp[1010][1010];

int main() {
  cin >> S >> T;

  memset(dp, 0, sizeof(dp));    // 初期化
  for (int i = 0; i < S.size(); ++i) {
    for (int j = 0; j < T.size(); ++j) {
      if (S[i] == T[j]) dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + 1);
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i+1][j]);
      dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j+1]);
    }
  }

  cout << dp[S.size()][T.size()] << endl;
}