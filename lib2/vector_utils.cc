// vectorの便利関数 vector_utils 操作・統計・変換 O(N)

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include <vector>
using namespace std;

// ========== ライブラリ部分 ==========

// 基本統計
template <typename T> struct vector_stats {
    T sum;
    T min_val;
    T max_val;
    double mean;
    double median;
    double variance;
    double stddev;

    vector_stats(const vector<T> &v) {
        if (v.empty())
            return;

        sum = accumulate(v.begin(), v.end(), T(0));
        min_val = *min_element(v.begin(), v.end());
        max_val = *max_element(v.begin(), v.end());
        mean = (double)sum / v.size();

        vector<T> sorted_v = v;
        sort(sorted_v.begin(), sorted_v.end());
        int n = sorted_v.size();
        if (n % 2 == 0) {
            median = (double)(sorted_v[n / 2 - 1] + sorted_v[n / 2]) / 2.0;
        } else {
            median = (double)sorted_v[n / 2];
        }

        double var_sum = 0;
        for (const T &val : v) {
            var_sum += (val - mean) * (val - mean);
        }
        variance = var_sum / v.size();
        stddev = sqrt(variance);
    }
};

// 要素の出現回数
template <typename T> map<T, int> count_elements(const vector<T> &v) {
    map<T, int> count;
    for (const T &elem : v) {
        count[elem]++;
    }
    return count;
}

// 最頻値
template <typename T> T mode(const vector<T> &v) {
    auto count = count_elements(v);
    T result = T();
    int max_count = 0;
    for (const auto &p : count) {
        if (p.second > max_count) {
            max_count = p.second;
            result = p.first;
        }
    }
    return result;
}

// 重複削除（順序保持）
template <typename T> vector<T> unique_preserve_order(const vector<T> &v) {
    vector<T> result;
    set<T> seen;
    for (const T &elem : v) {
        if (seen.find(elem) == seen.end()) {
            seen.insert(elem);
            result.push_back(elem);
        }
    }
    return result;
}

// 重複削除（ソート版）
template <typename T> vector<T> unique_sorted(vector<T> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

// 配列の逆順
template <typename T> vector<T> reverse_vector(vector<T> v) {
    reverse(v.begin(), v.end());
    return v;
}

// 配列の回転（左）
template <typename T> vector<T> rotate_left(vector<T> v, int k) {
    if (v.empty())
        return v;
    k = k % v.size();
    rotate(v.begin(), v.begin() + k, v.end());
    return v;
}

// 配列の回転（右）
template <typename T> vector<T> rotate_right(vector<T> v, int k) {
    if (v.empty())
        return v;
    k = k % v.size();
    rotate(v.rbegin(), v.rbegin() + k, v.rend());
    return v;
}

// 配列のシャッフル
template <typename T> vector<T> shuffle_vector(vector<T> v, unsigned seed = 0) {
    if (seed == 0)
        seed = random_device{}();
    mt19937 gen(seed);
    shuffle(v.begin(), v.end(), gen);
    return v;
}

// 配列の分割
template <typename T>
vector<vector<T>> chunk(const vector<T> &v, int chunk_size) {
    vector<vector<T>> result;
    for (int i = 0; i < v.size(); i += chunk_size) {
        int end = min(i + chunk_size, (int)v.size());
        result.push_back(vector<T>(v.begin() + i, v.begin() + end));
    }
    return result;
}

// 配列の結合
template <typename T> vector<T> flatten(const vector<vector<T>> &vv) {
    vector<T> result;
    for (const auto &v : vv) {
        result.insert(result.end(), v.begin(), v.end());
    }
    return result;
}

// 条件を満たす要素のフィルタリング
template <typename T>
vector<T> filter(const vector<T> &v, function<bool(const T &)> predicate) {
    vector<T> result;
    for (const T &elem : v) {
        if (predicate(elem)) {
            result.push_back(elem);
        }
    }
    return result;
}

// 配列の変換（map）
template <typename T, typename U>
vector<U> map_vector(const vector<T> &v, function<U(const T &)> mapper) {
    vector<U> result;
    result.reserve(v.size());
    for (const T &elem : v) {
        result.push_back(mapper(elem));
    }
    return result;
}

// 配列の畳み込み（reduce）
template <typename T, typename U>
U reduce(const vector<T> &v, U init,
         function<U(const U &, const T &)> reducer) {
    U result = init;
    for (const T &elem : v) {
        result = reducer(result, elem);
    }
    return result;
}

// 二つの配列のzip
template <typename T, typename U>
vector<pair<T, U>> zip(const vector<T> &v1, const vector<U> &v2) {
    vector<pair<T, U>> result;
    int n = min(v1.size(), v2.size());
    for (int i = 0; i < n; i++) {
        result.push_back({v1[i], v2[i]});
    }
    return result;
}

// 配列の差集合
template <typename T>
vector<T> difference(const vector<T> &v1, const vector<T> &v2) {
    set<T> s2(v2.begin(), v2.end());
    vector<T> result;
    for (const T &elem : v1) {
        if (s2.find(elem) == s2.end()) {
            result.push_back(elem);
        }
    }
    return result;
}

// 配列の積集合
template <typename T>
vector<T> intersection(const vector<T> &v1, const vector<T> &v2) {
    set<T> s1(v1.begin(), v1.end());
    set<T> s2(v2.begin(), v2.end());
    vector<T> result;
    for (const T &elem : s1) {
        if (s2.find(elem) != s2.end()) {
            result.push_back(elem);
        }
    }
    return result;
}

// 配列の和集合
template <typename T>
vector<T> union_vector(const vector<T> &v1, const vector<T> &v2) {
    set<T> s(v1.begin(), v1.end());
    s.insert(v2.begin(), v2.end());
    return vector<T>(s.begin(), s.end());
}

// 累積和
template <typename T> vector<T> cumulative_sum(const vector<T> &v) {
    vector<T> result(v.size());
    if (!v.empty()) {
        result[0] = v[0];
        for (int i = 1; i < v.size(); i++) {
            result[i] = result[i - 1] + v[i];
        }
    }
    return result;
}

// 累積和0から
template <typename T> vector<T> cumulative_sum(const vector<T> &v) {
    vector<T> result(v.size() + 1);
    result[0] = 0;
    for (int i = 0; i < v.size(); i++) {
        result[i + 1] = result[i] + v[i];
    }
    return result;
}

// 階差数列
template <typename T> vector<T> differences(const vector<T> &v) {
    vector<T> result;
    for (int i = 1; i < v.size(); i++) {
        result.push_back(v[i] - v[i - 1]);
    }
    return result;
}

// 配列の部分配列抽出
template <typename T>
vector<T> slice(const vector<T> &v, int start, int end = -1) {
    if (end == -1)
        end = v.size();
    start = max(0, start);
    end = min((int)v.size(), end);
    if (start >= end)
        return vector<T>();
    return vector<T>(v.begin() + start, v.begin() + end);
}

// n番目の要素を取得（負のインデックス対応）
template <typename T> T at(const vector<T> &v, int index) {
    if (index < 0)
        index += v.size();
    return v[index];
}

// 配列の検索（線形）
template <typename T> int find_index(const vector<T> &v, const T &target) {
    auto it = find(v.begin(), v.end(), target);
    return (it != v.end()) ? distance(v.begin(), it) : -1;
}

// 配列の二分探索（lower_bound）
template <typename T>
int binary_search_lower(const vector<T> &v, const T &target) {
    auto it = lower_bound(v.begin(), v.end(), target);
    return distance(v.begin(), it);
}

// 配列の二分探索（upper_bound）
template <typename T>
int binary_search_upper(const vector<T> &v, const T &target) {
    auto it = upper_bound(v.begin(), v.end(), target);
    return distance(v.begin(), it);
}

// 最大値のインデックス
template <typename T> int argmax(const vector<T> &v) {
    return distance(v.begin(), max_element(v.begin(), v.end()));
}

// 最小値のインデックス
template <typename T> int argmin(const vector<T> &v) {
    return distance(v.begin(), min_element(v.begin(), v.end()));
}

// ========== サンプルコード ==========

int main() {
    // 例1: 基本統計
    cout << "例1: 基本統計" << endl;
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector_stats<int> stats(data);

    cout << "配列: ";
    for (int x : data)
        cout << x << " ";
    cout << endl;
    cout << "合計: " << stats.sum << endl;
    cout << "最小値: " << stats.min_val << endl;
    cout << "最大値: " << stats.max_val << endl;
    cout << "平均: " << stats.mean << endl;
    cout << "中央値: " << stats.median << endl;
    cout << "分散: " << stats.variance << endl;
    cout << "標準偏差: " << stats.stddev << endl;
    cout << endl;

    // 例2: 要素の出現回数と最頻値
    cout << "例2: 要素の出現回数と最頻値" << endl;
    vector<char> chars = {'a', 'b', 'a', 'c', 'b', 'a'};
    auto count = count_elements(chars);

    cout << "配列: ";
    for (char c : chars)
        cout << c << " ";
    cout << endl;
    cout << "出現回数: ";
    for (auto p : count)
        cout << p.first << ":" << p.second << " ";
    cout << endl;
    cout << "最頻値: " << mode(chars) << endl;
    cout << endl;

    // 例3: 重複削除
    cout << "例3: 重複削除" << endl;
    vector<int> duplicates = {1, 2, 2, 3, 1, 4, 3, 5};
    cout << "元の配列: ";
    for (int x : duplicates)
        cout << x << " ";
    cout << endl;

    auto unique1 = unique_preserve_order(duplicates);
    cout << "順序保持重複削除: ";
    for (int x : unique1)
        cout << x << " ";
    cout << endl;

    auto unique2 = unique_sorted(duplicates);
    cout << "ソート版重複削除: ";
    for (int x : unique2)
        cout << x << " ";
    cout << endl;
    cout << endl;

    // 例4: 配列操作
    cout << "例4: 配列操作" << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "元の配列: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    auto reversed = reverse_vector(arr);
    cout << "逆順: ";
    for (int x : reversed)
        cout << x << " ";
    cout << endl;

    auto rotated_left = rotate_left(arr, 2);
    cout << "左回転(2): ";
    for (int x : rotated_left)
        cout << x << " ";
    cout << endl;

    auto rotated_right = rotate_right(arr, 2);
    cout << "右回転(2): ";
    for (int x : rotated_right)
        cout << x << " ";
    cout << endl;
    cout << endl;

    // 例5: フィルタリングとマッピング
    cout << "例5: フィルタリングとマッピング" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 偶数のみフィルタ
    auto evens = filter(numbers, [](int x) { return x % 2 == 0; });
    cout << "偶数: ";
    for (int x : evens)
        cout << x << " ";
    cout << endl;

    // 各要素を2倍
    auto doubled = map_vector<int, int>(numbers, [](int x) { return x * 2; });
    cout << "2倍: ";
    for (int x : doubled)
        cout << x << " ";
    cout << endl;

    // 合計をreduce
    int sum = reduce(numbers, 0, [](int acc, int x) { return acc + x; });
    cout << "合計: " << sum << endl;
    cout << endl;

    // 例6: 配列の集合演算
    cout << "例6: 配列の集合演算" << endl;
    vector<int> set1 = {1, 2, 3, 4, 5};
    vector<int> set2 = {4, 5, 6, 7, 8};

    cout << "集合1: ";
    for (int x : set1)
        cout << x << " ";
    cout << endl;
    cout << "集合2: ";
    for (int x : set2)
        cout << x << " ";
    cout << endl;

    auto diff = difference(set1, set2);
    cout << "差集合: ";
    for (int x : diff)
        cout << x << " ";
    cout << endl;

    auto inter = intersection(set1, set2);
    cout << "積集合: ";
    for (int x : inter)
        cout << x << " ";
    cout << endl;

    auto union_set = union_vector(set1, set2);
    cout << "和集合: ";
    for (int x : union_set)
        cout << x << " ";
    cout << endl;
    cout << endl;

    // 例7: 累積和と階差
    cout << "例7: 累積和と階差" << endl;
    vector<int> sequence = {1, 3, 2, 4, 1};
    cout << "数列: ";
    for (int x : sequence)
        cout << x << " ";
    cout << endl;

    auto cumsum = cumulative_sum(sequence);
    cout << "累積和: ";
    for (int x : cumsum)
        cout << x << " ";
    cout << endl;

    auto diffs = differences(sequence);
    cout << "階差: ";
    for (int x : diffs)
        cout << x << " ";
    cout << endl;
    cout << endl;

    // 例8: 検索とインデックス
    cout << "例8: 検索とインデックス" << endl;
    vector<int> search_array = {10, 20, 30, 40, 50};
    cout << "配列: ";
    for (int x : search_array)
        cout << x << " ";
    cout << endl;

    cout << "30のインデックス: " << find_index(search_array, 30) << endl;
    cout << "最大値のインデックス: " << argmax(search_array) << endl;
    cout << "最小値のインデックス: " << argmin(search_array) << endl;
    cout << "負のインデックス(-1): " << at(search_array, -1) << endl;
    cout << endl;

    // 例9: 配列の分割と結合
    cout << "例9: 配列の分割と結合" << endl;
    vector<int> big_array = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto chunks = chunk(big_array, 3);

    cout << "元の配列: ";
    for (int x : big_array)
        cout << x << " ";
    cout << endl;
    cout << "3つずつ分割:" << endl;
    for (auto &chunk_vec : chunks) {
        cout << "  ";
        for (int x : chunk_vec)
            cout << x << " ";
        cout << endl;
    }

    auto flattened = flatten(chunks);
    cout << "結合: ";
    for (int x : flattened)
        cout << x << " ";
    cout << endl;

    return 0;
}