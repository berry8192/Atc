// 順列全探索・ビット全探索 search_all 全通り列挙 O(N!)、O(2^N)

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
#include <set>
#include <map>
using namespace std;

// ========== ライブラリ部分 ==========

// 順列全探索（next_permutation使用）
template<typename T>
void permutation_search(vector<T> arr, function<void(const vector<T>&)> callback) {
    sort(arr.begin(), arr.end());
    do {
        callback(arr);
    } while (next_permutation(arr.begin(), arr.end()));
}

// 順列全探索（再帰版）
template<typename T>
void permutation_recursive(vector<T>& arr, int pos, function<void(const vector<T>&)> callback) {
    if (pos == arr.size()) {
        callback(arr);
        return;
    }

    for (int i = pos; i < arr.size(); i++) {
        swap(arr[pos], arr[i]);
        permutation_recursive(arr, pos + 1, callback);
        swap(arr[pos], arr[i]); // backtrack
    }
}

// 重複を考慮した順列全探索
template<typename T>
void unique_permutation_search(vector<T> arr, function<void(const vector<T>&)> callback) {
    sort(arr.begin(), arr.end());
    set<vector<T>> seen;

    do {
        if (seen.find(arr) == seen.end()) {
            seen.insert(arr);
            callback(arr);
        }
    } while (next_permutation(arr.begin(), arr.end()));
}

// nPr（一部取り出し順列）
template<typename T>
void partial_permutation(const vector<T>& arr, int r, function<void(const vector<T>&)> callback) {
    vector<T> current;
    vector<bool> used(arr.size(), false);

    function<void()> dfs = [&]() {
        if (current.size() == r) {
            callback(current);
            return;
        }

        for (int i = 0; i < arr.size(); i++) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(arr[i]);
                dfs();
                current.pop_back();
                used[i] = false;
            }
        }
    };

    dfs();
}

// ビット全探索（基本版）
void bit_search(int n, function<void(int, const vector<int>&)> callback) {
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> selected;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                selected.push_back(i);
            }
        }
        callback(mask, selected);
    }
}

// ビット全探索（配列版）
template<typename T>
void bit_search_array(const vector<T>& arr, function<void(int, const vector<T>&)> callback) {
    int n = arr.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<T> selected;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                selected.push_back(arr[i]);
            }
        }
        callback(mask, selected);
    }
}

// 指定個数のビット全探索
void bit_search_k(int n, int k, function<void(int, const vector<int>&)> callback) {
    function<void(int, int, int, vector<int>&)> dfs = [&](int pos, int selected, int mask, vector<int>& current) {
        if (selected == k) {
            callback(mask, current);
            return;
        }
        if (pos == n || selected + (n - pos) < k) return;

        // pos番目を選ぶ
        current.push_back(pos);
        dfs(pos + 1, selected + 1, mask | (1 << pos), current);
        current.pop_back();

        // pos番目を選ばない
        dfs(pos + 1, selected, mask, current);
    };

    vector<int> current;
    dfs(0, 0, 0, current);
}

// 組み合わせ全探索（nCr）
template<typename T>
void combination_search(const vector<T>& arr, int r, function<void(const vector<T>&)> callback) {
    vector<T> current;

    function<void(int)> dfs = [&](int start) {
        if (current.size() == r) {
            callback(current);
            return;
        }

        for (int i = start; i < arr.size(); i++) {
            current.push_back(arr[i]);
            dfs(i + 1);
            current.pop_back();
        }
    };

    dfs(0);
}

// 重複組み合わせ（多重集合）
template<typename T>
void multicombination_search(const vector<T>& arr, int r, function<void(const vector<T>&)> callback) {
    vector<T> current;

    function<void(int)> dfs = [&](int start) {
        if (current.size() == r) {
            callback(current);
            return;
        }

        for (int i = start; i < arr.size(); i++) {
            current.push_back(arr[i]);
            dfs(i); // 同じ要素を再度選択可能
            current.pop_back();
        }
    };

    dfs(0);
}

// 文字列の順列（辞書順）
void string_permutation(string s, function<void(const string&)> callback) {
    sort(s.begin(), s.end());
    do {
        callback(s);
    } while (next_permutation(s.begin(), s.end()));
}

// 分割統治的全探索
template<typename T>
void divide_conquer_search(const vector<T>& arr, function<void(const vector<T>&, const vector<T>&)> callback) {
    int n = arr.size();
    int half = n / 2;

    // 前半の全ての部分集合
    vector<vector<T>> first_half, second_half;

    for (int mask = 0; mask < (1 << half); mask++) {
        vector<T> subset;
        for (int i = 0; i < half; i++) {
            if (mask & (1 << i)) {
                subset.push_back(arr[i]);
            }
        }
        first_half.push_back(subset);
    }

    // 後半の全ての部分集合
    for (int mask = 0; mask < (1 << (n - half)); mask++) {
        vector<T> subset;
        for (int i = 0; i < n - half; i++) {
            if (mask & (1 << i)) {
                subset.push_back(arr[half + i]);
            }
        }
        second_half.push_back(subset);
    }

    // 全ての組み合わせ
    for (const auto& first : first_half) {
        for (const auto& second : second_half) {
            callback(first, second);
        }
    }
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な順列全探索
    cout << "例1: 順列全探索 [1,2,3]" << endl;
    vector<int> arr1 = {1, 2, 3};
    permutation_search(arr1, [](const vector<int>& perm) {
        for (int x : perm) cout << x << " ";
        cout << endl;
    });
    cout << endl;

    // 例2: ビット全探索
    cout << "例2: ビット全探索 n=3" << endl;
    bit_search(3, [](int mask, const vector<int>& selected) {
        cout << "mask=" << mask << ": {";
        for (int i = 0; i < selected.size(); i++) {
            if (i > 0) cout << ",";
            cout << selected[i];
        }
        cout << "}" << endl;
    });
    cout << endl;

    // 例3: 配列のビット全探索
    cout << "例3: 配列のビット全探索 [A,B,C]" << endl;
    vector<char> arr2 = {'A', 'B', 'C'};
    bit_search_array(arr2, [](int mask, const vector<char>& selected) {
        cout << "選択: ";
        for (char c : selected) cout << c << " ";
        cout << endl;
    });
    cout << endl;

    // 例4: 組み合わせ全探索
    cout << "例4: 組み合わせ C(4,2)" << endl;
    vector<int> arr3 = {1, 2, 3, 4};
    combination_search(arr3, 2, [](const vector<int>& comb) {
        cout << "{";
        for (int i = 0; i < comb.size(); i++) {
            if (i > 0) cout << ",";
            cout << comb[i];
        }
        cout << "}" << endl;
    });
    cout << endl;

    // 例5: 部分順列 P(4,2)
    cout << "例5: 部分順列 P(4,2)" << endl;
    partial_permutation(arr3, 2, [](const vector<int>& perm) {
        for (int x : perm) cout << x << " ";
        cout << endl;
    });
    cout << endl;

    // 例6: 指定個数のビット全探索
    cout << "例6: 4個中2個選ぶビット全探索" << endl;
    bit_search_k(4, 2, [](int mask, const vector<int>& selected) {
        cout << "mask=" << mask << ": ";
        for (int x : selected) cout << x << " ";
        cout << endl;
    });
    cout << endl;

    // 例7: 文字列の順列
    cout << "例7: 文字列 'ABC' の順列" << endl;
    string_permutation("ABC", [](const string& s) {
        cout << s << endl;
    });
    cout << endl;

    // 例8: 重複組み合わせ
    cout << "例8: 重複組み合わせ {1,2} から3個選ぶ" << endl;
    vector<int> arr4 = {1, 2};
    multicombination_search(arr4, 3, [](const vector<int>& comb) {
        for (int x : comb) cout << x << " ";
        cout << endl;
    });
    cout << endl;

    // 例9: 実用例 - ナップサック問題の全探索
    cout << "例9: ナップサック問題（全探索）" << endl;
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int capacity = 7;

    int max_value = 0;
    vector<int> best_selection;

    bit_search_array(weights, [&](int mask, const vector<int>& selected_weights) {
        int total_weight = 0, total_value = 0;
        vector<int> current_selection;

        for (int i = 0; i < weights.size(); i++) {
            if (mask & (1 << i)) {
                total_weight += weights[i];
                total_value += values[i];
                current_selection.push_back(i);
            }
        }

        if (total_weight <= capacity && total_value > max_value) {
            max_value = total_value;
            best_selection = current_selection;
        }
    });

    cout << "最大価値: " << max_value << endl;
    cout << "選択アイテム: ";
    for (int idx : best_selection) {
        cout << "(" << weights[idx] << "," << values[idx] << ") ";
    }
    cout << endl;

    return 0;
}