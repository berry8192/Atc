// 順列の累乗 permutation power cycle decomposition 置換のべき乗
// ABC377 E - Permutation Sigma Problem 用

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

// ========== ライブラリ本体 ==========

// 順列のサイクル分解と累乗計算
struct PermutationPower {
    int n;
    vector<int> perm;  // 0-indexed
    vector<vector<int>> cycles;  // サイクル分解
    vector<int> cycle_id;  // 各要素が属するサイクル番号
    vector<int> cycle_pos;  // サイクル内での位置

    PermutationPower(vector<int>& p) : n(p.size()), perm(p) {
        decompose();
    }

    // サイクル分解
    void decompose() {
        cycle_id.assign(n, -1);
        cycle_pos.assign(n, -1);
        
        for (int i = 0; i < n; i++) {
            if (cycle_id[i] != -1) continue;
            
            vector<int> cycle;
            int curr = i;
            
            while (cycle_id[curr] == -1) {
                cycle_id[curr] = cycles.size();
                cycle_pos[curr] = cycle.size();
                cycle.push_back(curr);
                curr = perm[curr];
            }
            
            cycles.push_back(cycle);
        }
    }

    // 順列のk乗を計算
    vector<int> power(long long k) {
        vector<int> result(n);
        
        for (const auto& cycle : cycles) {
            int len = cycle.size();
            long long shift = k % len;
            
            for (int i = 0; i < len; i++) {
                result[cycle[i]] = cycle[(i + shift) % len];
            }
        }
        
        return result;
    }

    // i番目の要素がk回適用後にどこに移動するか
    int apply(int i, long long k) {
        int cid = cycle_id[i];
        int pos = cycle_pos[i];
        int len = cycles[cid].size();
        
        return cycles[cid][(pos + k) % len];
    }

    // 順列の合成 p1[p2[i]]
    static vector<int> compose(const vector<int>& p1, const vector<int>& p2) {
        int n = p1.size();
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = p1[p2[i]];
        }
        return result;
    }

    // 順列の逆置換
    static vector<int> inverse(const vector<int>& p) {
        int n = p.size();
        vector<int> inv(n);
        for (int i = 0; i < n; i++) {
            inv[p[i]] = i;
        }
        return inv;
    }

    // 順列の符号（偶置換なら1、奇置換なら-1）
    static int sign(const vector<int>& p) {
        int n = p.size();
        int inversions = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (p[i] > p[j]) inversions++;
            }
        }
        return (inversions % 2 == 0) ? 1 : -1;
    }

    // 順列の位数（何乗すると恒等置換になるか）
    int order() {
        long long ord = 1;
        for (const auto& cycle : cycles) {
            ord = lcm(ord, (long long)cycle.size());
        }
        return ord;
    }
};

// ABC377 E用: Σ(i+1) * P^K[i] mod M の計算
long long solve_permutation_sigma(vector<int>& perm, long long k, long long mod) {
    int n = perm.size();
    PermutationPower pp(perm);
    
    vector<int> pk = pp.power(k);
    
    long long result = 0;
    for (int i = 0; i < n; i++) {
        result = (result + (long long)(i + 1) * (pk[i] + 1)) % mod;
    }
    
    return result;
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なサイクル分解
    cout << "例1: サイクル分解" << endl;
    vector<int> p1 = {2, 0, 1, 4, 3};  // 0→2→1→0, 3→4→3
    
    PermutationPower pp1(p1);
    cout << "サイクル数: " << pp1.cycles.size() << endl;
    
    for (int i = 0; i < pp1.cycles.size(); i++) {
        cout << "サイクル" << i << ": ";
        for (int v : pp1.cycles[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
    cout << "位数: " << pp1.order() << endl;
    cout << endl;

    // 例2: 順列の累乗
    cout << "例2: 順列の累乗" << endl;
    vector<int> p2 = {1, 2, 0};  // 0→1→2→0 (長さ3のサイクル)
    PermutationPower pp2(p2);
    
    for (int k = 0; k <= 4; k++) {
        vector<int> pk = pp2.power(k);
        cout << "P^" << k << ": ";
        for (int v : pk) cout << v << " ";
        cout << endl;
    }
    cout << endl;

    // 例3: ABC377 E の例
    cout << "例3: ABC377 E タイプの問題" << endl;
    int n = 3;
    long long k = 1;
    vector<int> perm = {1, 2, 0};  // 1-indexed を 0-indexed に変換済み
    
    long long ans = solve_permutation_sigma(perm, k, 998244353);
    cout << "答え: " << ans << endl;
    cout << endl;

    // 例4: 大きなkでの計算
    cout << "例4: 大きなkでの計算" << endl;
    vector<int> p4 = {1, 2, 3, 0};  // 0→1→2→3→0
    PermutationPower pp4(p4);
    
    long long big_k = 1000000000;
    cout << "0が10^9回適用後に移動する先: " << pp4.apply(0, big_k) << endl;
    
    vector<int> pbig = pp4.power(big_k);
    cout << "P^(10^9): ";
    for (int v : pbig) cout << v << " ";
    cout << endl;

    return 0;
}