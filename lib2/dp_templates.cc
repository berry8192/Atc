// DP Templates 動的計画法 ナップサック LIS LCS 区間DP

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ========== ライブラリ部分 ==========

// ナップサック問題（0-1ナップサック）
long long knapsack_01(const vector<int>& weights, const vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            dp[i][w] = dp[i-1][w];  // 選ばない場合
            if (w >= weights[i-1]) {
                dp[i][w] = max(dp[i][w], dp[i-1][w - weights[i-1]] + values[i-1]);
            }
        }
    }

    return dp[n][capacity];
}

// 無限ナップサック問題
long long knapsack_unlimited(const vector<int>& weights, const vector<int>& values, int capacity) {
    vector<long long> dp(capacity + 1, 0);

    for (int w = 1; w <= capacity; w++) {
        for (int i = 0; i < (int)weights.size(); i++) {
            if (w >= weights[i]) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }

    return dp[capacity];
}

// 最長増加部分列（LIS）
int longest_increasing_subsequence(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    vector<int> lis;

    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lis.begin(), lis.end(), arr[i]);
        if (it == lis.end()) {
            lis.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
    }

    return lis.size();
}

// 最長共通部分列（LCS）
int longest_common_subsequence(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    return dp[m][n];
}

// 編集距離（レーベンシュタイン距離）
int edit_distance(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // 初期化
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }

    return dp[m][n];
}

// 区間DP（行列の連鎖積）
long long matrix_chain_multiplication(const vector<int>& dims) {
    int n = dims.size() - 1;
    if (n <= 1) return 0;

    vector<vector<long long>> dp(n, vector<long long>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k+1][j] +
                               (long long)dims[i] * dims[k+1] * dims[j+1];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n-1];
}

// コインの問題（最小枚数）
int coin_change_min(const vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i >= coin && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// コインの問題（組み合わせ数）
long long coin_change_ways(const vector<int>& coins, int amount) {
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;

    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }

    return dp[amount];
}

// 最大部分配列和（Kadane's algorithm）
long long max_subarray_sum(const vector<int>& arr) {
    long long max_so_far = arr[0];
    long long max_ending_here = arr[0];

    for (int i = 1; i < (int)arr.size(); i++) {
        max_ending_here = max((long long)arr[i], max_ending_here + arr[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }

    return max_so_far;
}

// 部分集合和問題
bool subset_sum(const vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    return dp[target];
}

// 分割数（整数nをk個以下の正整数の和で表す方法の数）
long long partition_count(int n, int k) {
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k && j <= i; j++) {
            dp[i][j] = dp[i-1][j-1] + dp[i-j][j];
        }
    }

    long long result = 0;
    for (int j = 1; j <= k; j++) {
        result += dp[n][j];
    }
    return result;
}

// 階段上り（n段の階段を1歩または2歩で上る方法の数）
long long climbing_stairs(int n) {
    if (n <= 2) return n;

    vector<long long> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];
}

// ========== サンプルコード ==========

int main() {
    // 例1: ナップサック問題
    cout << "例1: ナップサック問題" << endl;
    vector<int> weights = {2, 1, 3, 2};
    vector<int> values = {12, 10, 20, 15};
    int capacity = 5;

    cout << "アイテム: ";
    for (int i = 0; i < (int)weights.size(); i++) {
        cout << "(重さ" << weights[i] << ", 価値" << values[i] << ") ";
    }
    cout << endl;
    cout << "容量: " << capacity << endl;
    cout << "0-1ナップサック: " << knapsack_01(weights, values, capacity) << endl;
    cout << "無限ナップサック: " << knapsack_unlimited(weights, values, capacity) << endl;
    cout << endl;

    // 例2: 最長増加部分列
    cout << "例2: 最長増加部分列（LIS）" << endl;
    vector<int> lis_arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};

    cout << "配列: ";
    for (int x : lis_arr) cout << x << " ";
    cout << endl;
    cout << "LISの長さ: " << longest_increasing_subsequence(lis_arr) << endl;
    cout << endl;

    // 例3: 最長共通部分列
    cout << "例3: 最長共通部分列（LCS）" << endl;
    string s1 = "ABCDGH";
    string s2 = "AEDFHR";

    cout << "文字列1: " << s1 << endl;
    cout << "文字列2: " << s2 << endl;
    cout << "LCSの長さ: " << longest_common_subsequence(s1, s2) << endl;
    cout << endl;

    // 例4: 編集距離
    cout << "例4: 編集距離" << endl;
    string edit_s1 = "kitten";
    string edit_s2 = "sitting";

    cout << "文字列1: " << edit_s1 << endl;
    cout << "文字列2: " << edit_s2 << endl;
    cout << "編集距離: " << edit_distance(edit_s1, edit_s2) << endl;
    cout << endl;

    // 例5: 行列の連鎖積
    cout << "例5: 行列の連鎖積" << endl;
    vector<int> dimensions = {1, 2, 3, 4, 5};  // 4つの行列: 1x2, 2x3, 3x4, 4x5

    cout << "行列の次元: ";
    for (int i = 0; i < (int)dimensions.size() - 1; i++) {
        cout << dimensions[i] << "x" << dimensions[i+1] << " ";
    }
    cout << endl;
    cout << "最小乗算回数: " << matrix_chain_multiplication(dimensions) << endl;
    cout << endl;

    // 例6: コインの問題
    cout << "例6: コインの問題" << endl;
    vector<int> coins = {1, 3, 4};
    int amount = 6;

    cout << "コインの種類: ";
    for (int coin : coins) cout << coin << " ";
    cout << endl;
    cout << "金額: " << amount << endl;
    cout << "最小枚数: " << coin_change_min(coins, amount) << endl;
    cout << "組み合わせ数: " << coin_change_ways(coins, amount) << endl;
    cout << endl;

    // 例7: 最大部分配列和
    cout << "例7: 最大部分配列和" << endl;
    vector<int> subarray = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    cout << "配列: ";
    for (int x : subarray) cout << x << " ";
    cout << endl;
    cout << "最大部分配列和: " << max_subarray_sum(subarray) << endl;
    cout << endl;

    // 例8: 部分集合和問題
    cout << "例8: 部分集合和問題" << endl;
    vector<int> subset_nums = {3, 34, 4, 12, 5, 2};
    int target = 9;

    cout << "集合: ";
    for (int x : subset_nums) cout << x << " ";
    cout << endl;
    cout << "目標和: " << target << endl;
    cout << "可能: " << (subset_sum(subset_nums, target) ? "Yes" : "No") << endl;
    cout << endl;

    // 例9: 階段上り
    cout << "例9: 階段上り" << endl;
    vector<int> stairs = {1, 2, 3, 4, 5, 10};

    for (int n : stairs) {
        cout << n << "段の階段: " << climbing_stairs(n) << "通り" << endl;
    }
    cout << endl;

    // 例10: 分割数
    cout << "例10: 分割数" << endl;
    vector<pair<int, int>> partition_cases = {{5, 3}, {6, 4}, {10, 5}};

    for (auto [n, k] : partition_cases) {
        cout << n << "を" << k << "個以下の正整数で分割: " << partition_count(n, k) << "通り" << endl;
    }

    return 0;
}