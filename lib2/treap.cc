// Treap 平衡二分探索木 ランダム優先度 O(log N)

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

// ========== ライブラリ部分 ==========

// Treap（平衡二分探索木）
template<typename T>
class Treap {
private:
    struct Node {
        T key;
        int priority;
        int size;
        Node* left;
        Node* right;

        Node(T k) : key(k), priority(rand()), size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    mt19937 rng;

    // ノードのサイズを取得
    int get_size(Node* node) {
        return node ? node->size : 0;
    }

    // ノードの情報を更新
    void update(Node* node) {
        if (!node) return;
        node->size = 1 + get_size(node->left) + get_size(node->right);
    }

    // 右回転
    Node* rotate_right(Node* node) {
        Node* left_child = node->left;
        node->left = left_child->right;
        left_child->right = node;
        update(node);
        update(left_child);
        return left_child;
    }

    // 左回転
    Node* rotate_left(Node* node) {
        Node* right_child = node->right;
        node->right = right_child->left;
        right_child->left = node;
        update(node);
        update(right_child);
        return right_child;
    }

    // 要素を挿入
    Node* insert(Node* node, T key) {
        if (!node) return new Node(key);

        if (key <= node->key) {
            node->left = insert(node->left, key);
            if (node->left->priority > node->priority) {
                node = rotate_right(node);
            }
        } else {
            node->right = insert(node->right, key);
            if (node->right->priority > node->priority) {
                node = rotate_left(node);
            }
        }
        update(node);
        return node;
    }

    // 要素を削除
    Node* erase(Node* node, T key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = erase(node->left, key);
        } else if (key > node->key) {
            node->right = erase(node->right, key);
        } else {
            // キーが一致した場合
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            } else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                // 両方の子がある場合、優先度の高い方を上に
                if (node->left->priority > node->right->priority) {
                    node = rotate_right(node);
                    node->right = erase(node->right, key);
                } else {
                    node = rotate_left(node);
                    node->left = erase(node->left, key);
                }
            }
        }
        update(node);
        return node;
    }

    // 要素を検索
    bool find(Node* node, T key) {
        if (!node) return false;
        if (key == node->key) return true;
        if (key < node->key) return find(node->left, key);
        return find(node->right, key);
    }

    // k番目（0-indexed）の要素を取得
    T kth_element(Node* node, int k) {
        if (!node) return T();
        int left_size = get_size(node->left);
        if (k == left_size) return node->key;
        if (k < left_size) return kth_element(node->left, k);
        return kth_element(node->right, k - left_size - 1);
    }

    // keyより小さい要素の個数
    int count_less(Node* node, T key) {
        if (!node) return 0;
        if (key <= node->key) {
            return count_less(node->left, key);
        } else {
            return get_size(node->left) + 1 + count_less(node->right, key);
        }
    }

    // keyより小さいか等しい要素の個数
    int count_less_equal(Node* node, T key) {
        if (!node) return 0;
        if (key < node->key) {
            return count_less_equal(node->left, key);
        } else {
            return get_size(node->left) + 1 + count_less_equal(node->right, key);
        }
    }

    // 中序走査
    void inorder(Node* node, vector<T>& result) {
        if (!node) return;
        inorder(node->left, result);
        result.push_back(node->key);
        inorder(node->right, result);
    }

    // メモリを解放
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    // コンストラクタ
    Treap() : root(nullptr), rng(random_device{}()) {}

    // デストラクタ
    ~Treap() {
        clear(root);
    }

    // 要素を挿入
    void insert(T key) {
        root = insert(root, key);
    }

    // 要素を削除
    void erase(T key) {
        root = erase(root, key);
    }

    // 要素を検索
    bool find(T key) {
        return find(root, key);
    }

    // 要素数を取得
    int size() {
        return get_size(root);
    }

    // 空かどうか判定
    bool empty() {
        return root == nullptr;
    }

    // k番目（0-indexed）の要素を取得
    T kth_element(int k) {
        if (k < 0 || k >= size()) return T();
        return kth_element(root, k);
    }

    // keyより小さい要素の個数
    int count_less(T key) {
        return count_less(root, key);
    }

    // keyより小さいか等しい要素の個数
    int count_less_equal(T key) {
        return count_less_equal(root, key);
    }

    // 最小値を取得
    T min_element() {
        if (empty()) return T();
        return kth_element(0);
    }

    // 最大値を取得
    T max_element() {
        if (empty()) return T();
        return kth_element(size() - 1);
    }

    // すべての要素を取得（ソート済み）
    vector<T> to_vector() {
        vector<T> result;
        inorder(root, result);
        return result;
    }

    // lower_bound: key以上の最小要素のインデックス
    int lower_bound(T key) {
        return count_less(key);
    }

    // upper_bound: keyより大きい最小要素のインデックス
    int upper_bound(T key) {
        return count_less_equal(key);
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な操作
    cout << "例1: 基本的なTreap操作" << endl;
    Treap<int> treap;

    // 要素を挿入
    vector<int> values = {5, 2, 8, 1, 9, 3, 7};
    cout << "挿入する値: ";
    for (int v : values) {
        cout << v << " ";
        treap.insert(v);
    }
    cout << endl;

    cout << "ソート済み順序: ";
    auto sorted = treap.to_vector();
    for (int v : sorted) cout << v << " ";
    cout << endl;

    cout << "サイズ: " << treap.size() << endl;
    cout << "最小値: " << treap.min_element() << endl;
    cout << "最大値: " << treap.max_element() << endl;
    cout << endl;

    // 例2: k番目の要素取得
    cout << "例2: k番目の要素取得" << endl;
    for (int k = 0; k < treap.size(); k++) {
        cout << k << "番目: " << treap.kth_element(k) << endl;
    }
    cout << endl;

    // 例3: 検索とカウント
    cout << "例3: 検索とカウント" << endl;
    vector<int> search_values = {3, 6, 9, 10};
    for (int v : search_values) {
        cout << "値" << v << ": ";
        cout << "存在=" << (treap.find(v) ? "Yes" : "No") << ", ";
        cout << "未満の個数=" << treap.count_less(v) << ", ";
        cout << "以下の個数=" << treap.count_less_equal(v) << endl;
    }
    cout << endl;

    // 例4: lower_bound と upper_bound
    cout << "例4: lower_bound と upper_bound" << endl;
    for (int v : {3, 6, 9}) {
        int lb = treap.lower_bound(v);
        int ub = treap.upper_bound(v);
        cout << "値" << v << ": lower_bound=" << lb;
        if (lb < treap.size()) cout << " (値=" << treap.kth_element(lb) << ")";
        cout << ", upper_bound=" << ub;
        if (ub < treap.size()) cout << " (値=" << treap.kth_element(ub) << ")";
        cout << endl;
    }
    cout << endl;

    // 例5: 要素の削除
    cout << "例5: 要素の削除" << endl;
    cout << "値5を削除前: ";
    auto before_erase = treap.to_vector();
    for (int v : before_erase) cout << v << " ";
    cout << endl;

    treap.erase(5);
    cout << "値5を削除後: ";
    auto after_erase = treap.to_vector();
    for (int v : after_erase) cout << v << " ";
    cout << endl;
    cout << "サイズ: " << treap.size() << endl;
    cout << endl;

    // 例6: 重複要素の処理
    cout << "例6: 重複要素の処理" << endl;
    Treap<int> treap_dup;
    vector<int> dup_values = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    cout << "挿入する値（重複あり）: ";
    for (int v : dup_values) {
        cout << v << " ";
        treap_dup.insert(v);
    }
    cout << endl;

    cout << "結果: ";
    auto dup_result = treap_dup.to_vector();
    for (int v : dup_result) cout << v << " ";
    cout << endl;
    cout << "サイズ: " << treap_dup.size() << endl;

    return 0;
}