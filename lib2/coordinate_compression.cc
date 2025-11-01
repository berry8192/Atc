// 座標圧縮 Coordinate Compression 離散化 大きな座標を小さく

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

// ========== ライブラリ部分 ==========

// 座標圧縮クラス
template<typename T>
class CoordinateCompression {
private:
    vector<T> sorted_values;
    map<T, int> value_to_index;
    bool is_built;

public:
    // コンストラクタ
    CoordinateCompression() : is_built(false) {}

    CoordinateCompression(const vector<T>& values) : is_built(false) {
        add_values(values);
        build();
    }

    // 値を追加
    void add_value(T value) {
        if (is_built) {
            throw runtime_error("Cannot add values after build()");
        }
        sorted_values.push_back(value);
    }

    // 複数の値を追加
    void add_values(const vector<T>& values) {
        for (T value : values) {
            add_value(value);
        }
    }

    // 座標圧縮を構築
    void build() {
        sort(sorted_values.begin(), sorted_values.end());
        sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());

        value_to_index.clear();
        for (int i = 0; i < (int)sorted_values.size(); i++) {
            value_to_index[sorted_values[i]] = i;
        }

        is_built = true;
    }

    // 元の値から圧縮後のインデックスを取得
    int compress(T value) const {
        if (!is_built) {
            throw runtime_error("Call build() before compress()");
        }
        auto it = value_to_index.find(value);
        if (it == value_to_index.end()) {
            return -1;  // 見つからない
        }
        return it->second;
    }

    // 圧縮後のインデックスから元の値を取得
    T decompress(int index) const {
        if (!is_built) {
            throw runtime_error("Call build() before decompress()");
        }
        if (index < 0 || index >= (int)sorted_values.size()) {
            throw out_of_range("Index out of range");
        }
        return sorted_values[index];
    }

    // 値が存在するかチェック
    bool contains(T value) const {
        return compress(value) != -1;
    }

    // 圧縮後のサイズ
    int size() const {
        if (!is_built) return 0;
        return sorted_values.size();
    }

    // すべての圧縮後の値を取得
    vector<T> get_values() const {
        if (!is_built) {
            throw runtime_error("Call build() before get_values()");
        }
        return sorted_values;
    }

    // valueより小さい要素の個数
    int lower_bound_index(T value) const {
        if (!is_built) {
            throw runtime_error("Call build() before lower_bound_index()");
        }
        return lower_bound(sorted_values.begin(), sorted_values.end(), value) - sorted_values.begin();
    }

    // valueより大きい要素の個数
    int upper_bound_index(T value) const {
        if (!is_built) {
            throw runtime_error("Call build() before upper_bound_index()");
        }
        return upper_bound(sorted_values.begin(), sorted_values.end(), value) - sorted_values.begin();
    }

    // 元の配列を圧縮
    vector<int> compress_array(const vector<T>& arr) const {
        vector<int> result;
        for (T value : arr) {
            result.push_back(compress(value));
        }
        return result;
    }

    // 圧縮された配列を復元
    vector<T> decompress_array(const vector<int>& compressed_arr) const {
        vector<T> result;
        for (int index : compressed_arr) {
            result.push_back(decompress(index));
        }
        return result;
    }
};

// 2次元座標圧縮クラス
template<typename T>
class CoordinateCompression2D {
private:
    CoordinateCompression<T> x_compressor, y_compressor;

public:
    // 点を追加
    void add_point(T x, T y) {
        x_compressor.add_value(x);
        y_compressor.add_value(y);
    }

    // 複数の点を追加
    void add_points(const vector<pair<T, T>>& points) {
        for (auto [x, y] : points) {
            add_point(x, y);
        }
    }

    // 構築
    void build() {
        x_compressor.build();
        y_compressor.build();
    }

    // 座標を圧縮
    pair<int, int> compress(T x, T y) const {
        return {x_compressor.compress(x), y_compressor.compress(y)};
    }

    // 座標を復元
    pair<T, T> decompress(int x_idx, int y_idx) const {
        return {x_compressor.decompress(x_idx), y_compressor.decompress(y_idx)};
    }

    // サイズ
    pair<int, int> size() const {
        return {x_compressor.size(), y_compressor.size()};
    }

    // 点の配列を圧縮
    vector<pair<int, int>> compress_points(const vector<pair<T, T>>& points) const {
        vector<pair<int, int>> result;
        for (auto [x, y] : points) {
            result.push_back(compress(x, y));
        }
        return result;
    }
};

// 区間を扱う座標圧縮（区間の端点を考慮）
template<typename T>
class IntervalCompression {
private:
    CoordinateCompression<T> compressor;

public:
    // 区間を追加
    void add_interval(T left, T right) {
        compressor.add_value(left);
        compressor.add_value(right);
        if (left + 1 <= right - 1) {
            compressor.add_value(left + 1);
            compressor.add_value(right - 1);
        }
    }

    // 構築
    void build() {
        compressor.build();
    }

    // 値を圧縮
    int compress(T value) const {
        return compressor.compress(value);
    }

    // インデックスを復元
    T decompress(int index) const {
        return compressor.decompress(index);
    }

    // サイズ
    int size() const {
        return compressor.size();
    }

    // 区間[left, right]に含まれる圧縮後のインデックスの範囲
    pair<int, int> interval_range(T left, T right) const {
        int left_idx = compressor.lower_bound_index(left);
        int right_idx = compressor.upper_bound_index(right) - 1;
        return {left_idx, right_idx};
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な座標圧縮
    cout << "例1: 基本的な座標圧縮" << endl;
    vector<int> values = {1000000, 5, 1000000, 999999, 5, 2};
    CoordinateCompression<int> cc;

    cout << "元の値: ";
    for (int v : values) cout << v << " ";
    cout << endl;

    cc.add_values(values);
    cc.build();

    cout << "圧縮後のサイズ: " << cc.size() << endl;
    cout << "圧縮された一意な値: ";
    auto unique_values = cc.get_values();
    for (int v : unique_values) cout << v << " ";
    cout << endl;

    cout << "各値の圧縮結果:" << endl;
    for (int v : values) {
        cout << v << " -> " << cc.compress(v) << endl;
    }
    cout << endl;

    // 例2: 配列全体の圧縮
    cout << "例2: 配列全体の圧縮" << endl;
    vector<int> original = {100, 5, 100, 50, 5, 1};
    CoordinateCompression<int> cc2(original);

    cout << "元の配列: ";
    for (int v : original) cout << v << " ";
    cout << endl;

    auto compressed = cc2.compress_array(original);
    cout << "圧縮後: ";
    for (int v : compressed) cout << v << " ";
    cout << endl;

    auto decompressed = cc2.decompress_array(compressed);
    cout << "復元後: ";
    for (int v : decompressed) cout << v << " ";
    cout << endl;
    cout << endl;

    // 例3: 2次元座標圧縮
    cout << "例3: 2次元座標圧縮" << endl;
    vector<pair<int, int>> points = {{1000000, 2000000}, {5, 10}, {1000000, 10}, {999999, 2000000}};
    CoordinateCompression2D<int> cc2d;

    cout << "元の点: ";
    for (auto [x, y] : points) cout << "(" << x << "," << y << ") ";
    cout << endl;

    cc2d.add_points(points);
    cc2d.build();

    auto [x_size, y_size] = cc2d.size();
    cout << "圧縮後のサイズ: x=" << x_size << ", y=" << y_size << endl;

    auto compressed_points = cc2d.compress_points(points);
    cout << "圧縮後の点: ";
    for (auto [x, y] : compressed_points) cout << "(" << x << "," << y << ") ";
    cout << endl;
    cout << endl;

    // 例4: 区間での座標圧縮
    cout << "例4: 区間での座標圧縮" << endl;
    vector<pair<int, int>> intervals = {{1, 1000000}, {5, 10}, {999999, 1000000}};
    IntervalCompression<int> ic;

    cout << "区間: ";
    for (auto [l, r] : intervals) cout << "[" << l << "," << r << "] ";
    cout << endl;

    for (auto [l, r] : intervals) {
        ic.add_interval(l, r);
    }
    ic.build();

    cout << "圧縮後のサイズ: " << ic.size() << endl;
    cout << "圧縮された座標: ";
    for (int i = 0; i < ic.size(); i++) {
        cout << ic.decompress(i) << " ";
    }
    cout << endl;

    cout << "各区間の圧縮後の範囲:" << endl;
    for (auto [l, r] : intervals) {
        auto [left_idx, right_idx] = ic.interval_range(l, r);
        cout << "[" << l << "," << r << "] -> [" << left_idx << "," << right_idx << "]" << endl;
    }
    cout << endl;

    // 例5: 実用例 - イベントのタイムスタンプ圧縮
    cout << "例5: イベントのタイムスタンプ圧縮" << endl;
    vector<long long> timestamps = {1609459200, 1609545600, 1609459200, 1609632000, 1609545600};  // Unix timestamp
    CoordinateCompression<long long> time_cc(timestamps);

    cout << "元のタイムスタンプ: ";
    for (long long t : timestamps) cout << t << " ";
    cout << endl;

    auto compressed_times = time_cc.compress_array(timestamps);
    cout << "圧縮後: ";
    for (int t : compressed_times) cout << t << " ";
    cout << endl;

    cout << "圧縮された一意なタイムスタンプ数: " << time_cc.size() << endl;
    cout << endl;

    // 例6: 範囲クエリでの応用
    cout << "例6: 範囲クエリでの応用" << endl;
    vector<int> query_values = {1, 5, 10, 50, 100, 500, 1000, 5000, 10000, 50000};
    CoordinateCompression<int> query_cc(query_values);

    // 値30未満の要素数
    int target = 30;
    int count_less = query_cc.lower_bound_index(target);
    cout << "値" << target << "未満の要素数: " << count_less << endl;

    // 値10以上100以下の要素数
    int lower = 10, upper = 100;
    int lower_idx = query_cc.lower_bound_index(lower);
    int upper_idx = query_cc.upper_bound_index(upper);
    cout << "値" << lower << "以上" << upper << "以下の要素数: " << (upper_idx - lower_idx) << endl;

    return 0;
}