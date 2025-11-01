// Mo's Algorithm モーのアルゴリズム 平方分割 区間クエリ O(N√N)

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ========== ライブラリ部分 ==========

// Mo's Algorithmクラス
template<typename T>
class MoAlgorithm {
private:
    struct Query {
        int left, right, index;
        int block;

        bool operator<(const Query& other) const {
            if (block != other.block) {
                return block < other.block;
            }
            return (block & 1) ? right < other.right : right > other.right;
        }
    };

    vector<T> data;
    vector<Query> queries;
    vector<T> answers;
    int block_size;
    int current_left, current_right;
    T current_answer;

    // データ構造に要素を追加
    virtual void add(int index) = 0;

    // データ構造から要素を削除
    virtual void remove(int index) = 0;

    // 現在の答えを取得
    virtual T get_answer() = 0;

protected:
    // データ配列にアクセス
    T get_data(int index) const {
        return data[index];
    }

public:
    // コンストラクタ
    MoAlgorithm(const vector<T>& input_data) : data(input_data) {
        block_size = max(1, (int)sqrt(data.size()));
        current_left = 0;
        current_right = -1;
    }

    // クエリを追加
    void add_query(int left, int right) {
        Query q;
        q.left = left;
        q.right = right;
        q.index = queries.size();
        q.block = left / block_size;
        queries.push_back(q);
    }

    // すべてのクエリを処理
    vector<T> solve() {
        sort(queries.begin(), queries.end());
        answers.resize(queries.size());

        for (const Query& q : queries) {
            // 右端を調整
            while (current_right < q.right) {
                current_right++;
                add(current_right);
            }
            while (current_right > q.right) {
                remove(current_right);
                current_right--;
            }

            // 左端を調整
            while (current_left < q.left) {
                remove(current_left);
                current_left++;
            }
            while (current_left > q.left) {
                current_left--;
                add(current_left);
            }

            answers[q.index] = get_answer();
        }

        return answers;
    }
};

// 区間内の異なる要素数を求めるクラス
class DistinctElementsMo : public MoAlgorithm<int> {
private:
    vector<int> frequency;
    int distinct_count;

    void add(int index) override {
        int value = get_data(index);
        if (frequency[value] == 0) {
            distinct_count++;
        }
        frequency[value]++;
    }

    void remove(int index) override {
        int value = get_data(index);
        frequency[value]--;
        if (frequency[value] == 0) {
            distinct_count--;
        }
    }

    int get_answer() override {
        return distinct_count;
    }

public:
    DistinctElementsMo(const vector<int>& data, int max_value)
        : MoAlgorithm<int>(data), frequency(max_value + 1, 0), distinct_count(0) {}
};

// 区間内の要素の合計を求めるクラス
class SumMo : public MoAlgorithm<long long> {
private:
    long long current_sum;

    void add(int index) override {
        current_sum += get_data(index);
    }

    void remove(int index) override {
        current_sum -= get_data(index);
    }

    long long get_answer() override {
        return current_sum;
    }

public:
    SumMo(const vector<long long>& data) : MoAlgorithm<long long>(data), current_sum(0) {}
};

// 区間内の要素の出現回数を管理するクラス
class FrequencyMo : public MoAlgorithm<int> {
private:
    vector<int> frequency;
    vector<int> freq_count;  // 出現回数iの要素が何個あるか
    int max_freq;

    void add(int index) override {
        int value = get_data(index);
        if (frequency[value] > 0) {
            freq_count[frequency[value]]--;
        }
        frequency[value]++;
        freq_count[frequency[value]]++;
        max_freq = max(max_freq, frequency[value]);
    }

    void remove(int index) override {
        int value = get_data(index);
        freq_count[frequency[value]]--;
        if (freq_count[max_freq] == 0 && frequency[value] == max_freq) {
            max_freq--;
        }
        frequency[value]--;
        if (frequency[value] > 0) {
            freq_count[frequency[value]]++;
        }
    }

    int get_answer() override {
        return max_freq;  // 最大出現回数
    }

public:
    FrequencyMo(const vector<int>& data, int max_value)
        : MoAlgorithm<int>(data), frequency(max_value + 1, 0),
          freq_count(data.size() + 1, 0), max_freq(0) {}

    // 出現回数がexactly kの要素数を取得
    int get_frequency_count(int k) const {
        return freq_count[k];
    }
};

// 区間内でのMEX（minimum excludant）を求めるクラス
class MexMo : public MoAlgorithm<int> {
private:
    vector<bool> present;
    int current_mex;

    void update_mex() {
        while (current_mex < (int)present.size() && present[current_mex]) {
            current_mex++;
        }
    }

    void add(int index) override {
        int value = get_data(index);
        if (value < (int)present.size()) {
            present[value] = true;
            if (value < current_mex) {
                // MEXは変わらない
            } else {
                update_mex();
            }
        }
    }

    void remove(int index) override {
        int value = get_data(index);
        if (value < (int)present.size()) {
            present[value] = false;
            current_mex = min(current_mex, value);
        }
    }

    int get_answer() override {
        return current_mex;
    }

public:
    MexMo(const vector<int>& data, int max_value)
        : MoAlgorithm<int>(data), present(max_value + 1, false), current_mex(0) {}
};

// ========== サンプルコード ==========

int main() {
    // 例1: 区間内の異なる要素数
    cout << "例1: 区間内の異なる要素数" << endl;
    vector<int> arr1 = {1, 2, 1, 3, 2, 4, 1};
    DistinctElementsMo demo1(arr1, 5);

    cout << "配列: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    // クエリを追加
    vector<pair<int, int>> queries1 = {{0, 2}, {1, 4}, {2, 6}, {0, 6}};
    for (auto [l, r] : queries1) {
        demo1.add_query(l, r);
    }

    auto answers1 = demo1.solve();
    cout << "クエリ結果:" << endl;
    for (int i = 0; i < (int)queries1.size(); i++) {
        auto [l, r] = queries1[i];
        cout << "範囲[" << l << ", " << r << "]: " << answers1[i] << "個の異なる要素" << endl;
    }
    cout << endl;

    // 例2: 区間和
    cout << "例2: 区間和" << endl;
    vector<long long> arr2 = {1, 3, 2, 7, 4, 1, 6};
    SumMo demo2(arr2);

    cout << "配列: ";
    for (long long x : arr2) cout << x << " ";
    cout << endl;

    vector<pair<int, int>> queries2 = {{0, 2}, {1, 4}, {2, 5}, {0, 6}};
    for (auto [l, r] : queries2) {
        demo2.add_query(l, r);
    }

    auto answers2 = demo2.solve();
    cout << "クエリ結果:" << endl;
    for (int i = 0; i < (int)queries2.size(); i++) {
        auto [l, r] = queries2[i];
        cout << "範囲[" << l << ", " << r << "]: 合計 " << answers2[i] << endl;
    }
    cout << endl;

    // 例3: 最大出現回数
    cout << "例3: 区間内での最大出現回数" << endl;
    vector<int> arr3 = {1, 2, 1, 1, 2, 3, 1, 2};
    FrequencyMo demo3(arr3, 5);

    cout << "配列: ";
    for (int x : arr3) cout << x << " ";
    cout << endl;

    vector<pair<int, int>> queries3 = {{0, 3}, {1, 5}, {2, 7}, {0, 7}};
    for (auto [l, r] : queries3) {
        demo3.add_query(l, r);
    }

    auto answers3 = demo3.solve();
    cout << "クエリ結果:" << endl;
    for (int i = 0; i < (int)queries3.size(); i++) {
        auto [l, r] = queries3[i];
        cout << "範囲[" << l << ", " << r << "]: 最大出現回数 " << answers3[i] << endl;
    }
    cout << endl;

    // 例4: MEX（minimum excludant）
    cout << "例4: 区間内でのMEX" << endl;
    vector<int> arr4 = {1, 0, 2, 0, 3, 1, 4};
    MexMo demo4(arr4, 10);

    cout << "配列: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;

    vector<pair<int, int>> queries4 = {{0, 1}, {0, 2}, {1, 4}, {0, 6}};
    for (auto [l, r] : queries4) {
        demo4.add_query(l, r);
    }

    auto answers4 = demo4.solve();
    cout << "クエリ結果:" << endl;
    for (int i = 0; i < (int)queries4.size(); i++) {
        auto [l, r] = queries4[i];
        cout << "範囲[" << l << ", " << r << "]: MEX = " << answers4[i] << endl;
    }
    cout << endl;

    // 例5: 大きなデータでの性能確認
    cout << "例5: 大きなデータでの性能確認" << endl;
    vector<int> large_data(10000);
    for (int i = 0; i < 10000; i++) {
        large_data[i] = rand() % 100;
    }

    DistinctElementsMo large_demo(large_data, 100);

    // ランダムなクエリを追加
    for (int i = 0; i < 100; i++) {
        int l = rand() % 10000;
        int r = rand() % 10000;
        if (l > r) swap(l, r);
        large_demo.add_query(l, r);
    }

    cout << "データサイズ: " << large_data.size() << endl;
    cout << "クエリ数: 100" << endl;

    auto large_answers = large_demo.solve();
    cout << "処理完了" << endl;

    // 最初の5つのクエリ結果を表示
    cout << "最初の5つのクエリ結果: ";
    for (int i = 0; i < min(5, (int)large_answers.size()); i++) {
        cout << large_answers[i] << " ";
    }
    cout << endl;

    return 0;
}