// 環状配列のDP ring DP circular distance 円環上の最適化
// ABC376 F - Hands on Ring 用

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ========== ライブラリ本体 ==========

// 環状配列上での操作を最適化
struct RingDP {
    int n;  // 環のサイズ
    
    RingDP(int size) : n(size) {}
    
    // 環状での距離計算（最短距離）
    int distance(int from, int to) {
        if (from == to) return 0;
        int forward = (to - from + n) % n;
        int backward = (from - to + n) % n;
        return min(forward, backward);
    }
    
    // 時計回りの距離
    int distance_clockwise(int from, int to) {
        return (to - from + n) % n;
    }
    
    // 反時計回りの距離
    int distance_counter_clockwise(int from, int to) {
        return (from - to + n) % n;
    }
    
    // posからtargetに移動する際、avoidを通過しない最短距離
    int distance_avoiding(int pos, int target, int avoid) {
        if (pos == target) return 0;
        if (avoid == pos || avoid == target) {
            return distance(pos, target);
        }
        
        // 時計回りでavoidを通過するかチェック
        bool cw_pass = false;
        if (pos < target) {
            cw_pass = (pos < avoid && avoid < target);
        } else {
            cw_pass = (pos < avoid || avoid < target);
        }
        
        // 反時計回りでavoidを通過するかチェック
        bool ccw_pass = false;
        if (pos > target) {
            ccw_pass = (target < avoid && avoid < pos);
        } else {
            ccw_pass = (target < avoid || avoid < pos);
        }
        
        int result = INT_MAX;
        if (!cw_pass) {
            result = min(result, distance_clockwise(pos, target));
        }
        if (!ccw_pass) {
            result = min(result, distance_counter_clockwise(pos, target));
        }
        
        // どちらも通過する場合は回り道
        if (cw_pass && ccw_pass) {
            // avoidの反対側を経由
            result = n - 1;  // 最大距離
        }
        
        return result;
    }
    
    // 2つのポインタを管理するDP（ABC376 F用）
    struct TwoHandsDP {
        int n;
        vector<pair<int, int>> tasks;  // (hand_type, position)
        
        TwoHandsDP(int size) : n(size) {}
        
        void add_task(int hand, int pos) {
            tasks.push_back({hand, pos});
        }
        
        long long solve(int left_start, int right_start) {
            int m = tasks.size();
            if (m == 0) return 0;
            
            // dp[i][l][r] = i番目まで処理して、左手がl、右手がrにある最小コスト
            // メモリ節約のため、直前の状態のみ保持
            map<pair<int, int>, long long> dp;
            dp[{left_start, right_start}] = 0;
            
            for (int i = 0; i < m; i++) {
                int hand = tasks[i].first;
                int target = tasks[i].second;
                
                map<pair<int, int>, long long> new_dp;
                
                for (auto& [state, cost] : dp) {
                    int left = state.first;
                    int right = state.second;
                    
                    if (hand == 0) {  // 左手を動かす
                        // 右手を避けて移動
                        RingDP ring(n);
                        int dist = ring.distance_avoiding(left, target, right);
                        
                        if (dist != INT_MAX) {
                            auto new_state = make_pair(target, right);
                            if (new_dp.find(new_state) == new_dp.end()) {
                                new_dp[new_state] = cost + dist;
                            } else {
                                new_dp[new_state] = min(new_dp[new_state], cost + dist);
                            }
                        }
                    } else {  // 右手を動かす
                        // 左手を避けて移動
                        RingDP ring(n);
                        int dist = ring.distance_avoiding(right, target, left);
                        
                        if (dist != INT_MAX) {
                            auto new_state = make_pair(left, target);
                            if (new_dp.find(new_state) == new_dp.end()) {
                                new_dp[new_state] = cost + dist;
                            } else {
                                new_dp[new_state] = min(new_dp[new_state], cost + dist);
                            }
                        }
                    }
                }
                
                dp = new_dp;
            }
            
            // 最小コストを返す
            long long result = LLONG_MAX;
            for (auto& [state, cost] : dp) {
                result = min(result, cost);
            }
            
            return result;
        }
    };
};

// 環状配列上の区間DP
struct CircularRangeDP {
    int n;
    vector<int> values;
    
    CircularRangeDP(vector<int>& v) : n(v.size()), values(v) {}
    
    // 環状配列の最大部分和（Kadaneのアルゴリズムの環状版）
    int max_circular_subarray() {
        // ケース1: 通常の最大部分和
        int max_kadane = kadane(values);
        
        // ケース2: 環状を跨ぐ場合
        int total = 0;
        for (int v : values) total += v;
        
        // 最小部分和を求めて、全体から引く
        vector<int> neg_values(n);
        for (int i = 0; i < n; i++) {
            neg_values[i] = -values[i];
        }
        int min_sum = -kadane(neg_values);
        
        // 全て負の場合の処理
        if (total == min_sum) {
            return max_kadane;
        }
        
        return max(max_kadane, total - min_sum);
    }
    
private:
    int kadane(vector<int>& arr) {
        int max_sum = arr[0];
        int current = arr[0];
        
        for (int i = 1; i < arr.size(); i++) {
            current = max(arr[i], current + arr[i]);
            max_sum = max(max_sum, current);
        }
        
        return max_sum;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 環状距離計算
    cout << "例1: 環状距離" << endl;
    RingDP ring1(10);
    cout << "n=10の環で:" << endl;
    cout << "  2から7への最短距離: " << ring1.distance(2, 7) << endl;
    cout << "  7から2への最短距離: " << ring1.distance(7, 2) << endl;
    cout << "  0から9への最短距離: " << ring1.distance(0, 9) << endl;
    cout << endl;
    
    // 例2: 障害物を避けた移動
    cout << "例2: 障害物回避" << endl;
    RingDP ring2(8);
    cout << "n=8の環で:" << endl;
    cout << "  1から5へ（障害物3）: " 
         << ring2.distance_avoiding(1, 5, 3) << endl;
    cout << "  1から7へ（障害物0）: " 
         << ring2.distance_avoiding(1, 7, 0) << endl;
    cout << endl;
    
    // 例3: ABC376 F タイプの問題
    cout << "例3: 2つのハンドの操作" << endl;
    RingDP::TwoHandsDP hands(6);
    hands.add_task(1, 4);  // 右手を4へ
    hands.add_task(0, 5);  // 左手を5へ
    hands.add_task(1, 0);  // 右手を0へ
    
    cout << "初期位置: 左=0, 右=1" << endl;
    cout << "最小移動コスト: " << hands.solve(0, 1) << endl;
    cout << endl;
    
    // 例4: 環状配列の最大部分和
    cout << "例4: 環状最大部分和" << endl;
    vector<int> arr1 = {5, -3, 5};
    CircularRangeDP crdp1(arr1);
    cout << "配列: [5, -3, 5]" << endl;
    cout << "環状最大部分和: " << crdp1.max_circular_subarray() << endl;
    cout << "(環状を跨いで5+5=10)" << endl;
    cout << endl;
    
    // 例5: 負の数が含まれる場合
    cout << "例5: 負の数を含む環状配列" << endl;
    vector<int> arr2 = {1, -2, 3, -2};
    CircularRangeDP crdp2(arr2);
    cout << "配列: [1, -2, 3, -2]" << endl;
    cout << "環状最大部分和: " << crdp2.max_circular_subarray() << endl;
    cout << "(環状を跨がない3が最大)" << endl;
    
    return 0;
}