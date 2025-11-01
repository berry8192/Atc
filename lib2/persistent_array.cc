// 永続配列 persistent_array 関数型データ構造 O(log N)

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// ========== ライブラリ部分 ==========

// 永続配列（Persistent Array）
// 過去の状態を保持しつつ配列の更新ができるデータ構造
template<typename T>
class PersistentArray {
private:
    struct Node {
        T value;
        shared_ptr<Node> left, right;

        Node(T v = T()) : value(v), left(nullptr), right(nullptr) {}
        Node(T v, shared_ptr<Node> l, shared_ptr<Node> r) : value(v), left(l), right(r) {}
    };

    shared_ptr<Node> root;
    int size;

    // 指定位置の値を取得
    T get_impl(shared_ptr<Node> node, int pos, int l, int r) const {
        if (l == r) return node->value;
        int mid = (l + r) / 2;
        if (pos <= mid) {
            return get_impl(node->left, pos, l, mid);
        } else {
            return get_impl(node->right, pos, mid + 1, r);
        }
    }

    // 指定位置の値を更新（新しいノードを作成）
    shared_ptr<Node> set_impl(shared_ptr<Node> node, int pos, T val, int l, int r) const {
        if (l == r) {
            return make_shared<Node>(val);
        }
        int mid = (l + r) / 2;
        if (pos <= mid) {
            auto new_left = set_impl(node->left, pos, val, l, mid);
            return make_shared<Node>(node->value, new_left, node->right);
        } else {
            auto new_right = set_impl(node->right, pos, val, mid + 1, r);
            return make_shared<Node>(node->value, node->left, new_right);
        }
    }

    // 初期化用の再帰関数
    shared_ptr<Node> build(const vector<T>& arr, int l, int r) {
        if (l == r) {
            return make_shared<Node>(arr[l]);
        }
        int mid = (l + r) / 2;
        auto left = build(arr, l, mid);
        auto right = build(arr, mid + 1, r);
        return make_shared<Node>(T(), left, right);
    }

public:
    // コンストラクタ
    PersistentArray() : root(nullptr), size(0) {}

    PersistentArray(const vector<T>& arr) : size(arr.size()) {
        if (size > 0) {
            root = build(arr, 0, size - 1);
        }
    }

    PersistentArray(shared_ptr<Node> r, int s) : root(r), size(s) {}

    // 指定位置の値を取得
    T get(int pos) const {
        if (pos < 0 || pos >= size) return T();
        return get_impl(root, pos, 0, size - 1);
    }

    // 指定位置の値を更新した新しい永続配列を返す
    PersistentArray set(int pos, T val) const {
        if (pos < 0 || pos >= size) return *this;
        auto new_root = set_impl(root, pos, val, 0, size - 1);
        return PersistentArray(new_root, size);
    }

    // 配列のサイズを取得
    int get_size() const { return size; }

    // 演算子オーバーロード
    T operator[](int pos) const { return get(pos); }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な使用方法
    cout << "例1: 基本的な永続配列の操作" << endl;
    vector<int> initial = {1, 2, 3, 4, 5};
    PersistentArray<int> arr1(initial);

    cout << "初期配列: ";
    for (int i = 0; i < arr1.get_size(); i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    // 位置2の値を10に変更
    auto arr2 = arr1.set(2, 10);
    cout << "arr2 (位置2を10に変更): ";
    for (int i = 0; i < arr2.get_size(); i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    // 元の配列は変更されていない
    cout << "arr1 (変更されていない): ";
    for (int i = 0; i < arr1.get_size(); i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << endl;

    // 例2: 複数の履歴を管理
    cout << "例2: 複数の履歴管理" << endl;
    vector<PersistentArray<int>> history;
    history.push_back(arr1);  // バージョン0

    auto current = arr1;
    for (int i = 0; i < 3; i++) {
        current = current.set(i, (i + 1) * 100);
        history.push_back(current);
        cout << "バージョン" << (i + 1) << ": ";
        for (int j = 0; j < current.get_size(); j++) {
            cout << current[j] << " ";
        }
        cout << endl;
    }

    cout << "\n過去のバージョンにアクセス:" << endl;
    for (int v = 0; v < history.size(); v++) {
        cout << "バージョン" << v << ": ";
        for (int i = 0; i < history[v].get_size(); i++) {
            cout << history[v][i] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 例3: 文字列での使用例
    cout << "例3: 文字列での永続配列" << endl;
    vector<char> chars = {'a', 'b', 'c', 'd', 'e'};
    PersistentArray<char> char_arr(chars);

    cout << "初期文字列: ";
    for (int i = 0; i < char_arr.get_size(); i++) {
        cout << char_arr[i];
    }
    cout << endl;

    auto char_arr2 = char_arr.set(2, 'X').set(4, 'Y');
    cout << "変更後: ";
    for (int i = 0; i < char_arr2.get_size(); i++) {
        cout << char_arr2[i];
    }
    cout << endl;

    cout << "元の文字列: ";
    for (int i = 0; i < char_arr.get_size(); i++) {
        cout << char_arr[i];
    }
    cout << endl;

    return 0;
}