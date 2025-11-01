// Link-Cut Tree 動的木 動的連結性 O(log N)

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ========== ライブラリ部分 ==========

// Link-Cut Tree
// 動的に辺の追加・削除ができる森で、パス上の情報を効率的に管理
template<typename T>
class LinkCutTree {
private:
    struct Node {
        Node *left, *right, *parent;
        T value, sum;
        bool reversed;

        Node(T v = T()) : left(nullptr), right(nullptr), parent(nullptr),
                         value(v), sum(v), reversed(false) {}
    };

    vector<Node*> nodes;

    // ノードの情報を更新
    void update(Node* x) {
        if (!x) return;
        x->sum = x->value;
        if (x->left) x->sum += x->left->sum;
        if (x->right) x->sum += x->right->sum;
    }

    // 遅延評価を適用
    void push(Node* x) {
        if (!x || !x->reversed) return;
        swap(x->left, x->right);
        if (x->left) x->left->reversed ^= true;
        if (x->right) x->right->reversed ^= true;
        x->reversed = false;
    }

    // xがyの子かどうか判定
    bool is_child(Node* x, Node* y) {
        return y && (y->left == x || y->right == x);
    }

    // 回転操作
    void rotate(Node* x) {
        Node* y = x->parent;
        Node* z = y->parent;

        if (y->left == x) {
            y->left = x->right;
            if (x->right) x->right->parent = y;
            x->right = y;
        } else {
            y->right = x->left;
            if (x->left) x->left->parent = y;
            x->left = y;
        }

        x->parent = z;
        y->parent = x;

        if (z && is_child(y, z)) {
            if (z->left == y) z->left = x;
            else z->right = x;
        }

        update(y);
        update(x);
    }

    // splay操作
    void splay(Node* x) {
        push(x);
        while (is_child(x, x->parent)) {
            Node* y = x->parent;
            Node* z = y->parent;

            if (is_child(y, z)) {
                push(z); push(y); push(x);
                if ((z->left == y) == (y->left == x)) {
                    rotate(y);
                } else {
                    rotate(x);
                }
            } else {
                push(y); push(x);
            }
            rotate(x);
        }
    }

    // xを根まで持ち上げ、preferred pathにする
    void expose(Node* x) {
        splay(x);
        push(x);
        x->right = nullptr;
        update(x);

        while (x->parent) {
            Node* y = x->parent;
            splay(y);
            push(y);
            y->right = x;
            update(y);
            splay(x);
        }
    }

    // xを根にする
    void evert(Node* x) {
        expose(x);
        x->reversed ^= true;
        push(x);
    }

public:
    // コンストラクタ
    LinkCutTree(int n) : nodes(n) {
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node(T());
        }
    }

    LinkCutTree(const vector<T>& values) : nodes(values.size()) {
        for (int i = 0; i < (int)values.size(); i++) {
            nodes[i] = new Node(values[i]);
        }
    }

    // デストラクタ
    ~LinkCutTree() {
        for (Node* node : nodes) {
            delete node;
        }
    }

    // uとvを辺で結ぶ
    void link(int u, int v) {
        if (u < 0 || u >= (int)nodes.size() || v < 0 || v >= (int)nodes.size()) return;
        evert(nodes[u]);
        expose(nodes[v]);
        nodes[u]->parent = nodes[v];
    }

    // uとvの間の辺を切る
    void cut(int u, int v) {
        if (u < 0 || u >= (int)nodes.size() || v < 0 || v >= (int)nodes.size()) return;
        evert(nodes[u]);
        expose(nodes[v]);

        if (nodes[v]->left == nodes[u] && !nodes[u]->right) {
            nodes[v]->left = nullptr;
            nodes[u]->parent = nullptr;
            update(nodes[v]);
        }
    }

    // uとvが同じ木に属するか判定
    bool connected(int u, int v) {
        if (u < 0 || u >= (int)nodes.size() || v < 0 || v >= (int)nodes.size()) return false;
        expose(nodes[u]);
        expose(nodes[v]);
        return nodes[u]->parent != nullptr || nodes[u] == nodes[v];
    }

    // uからvへのパス上の値の和
    T path_sum(int u, int v) {
        if (u < 0 || u >= (int)nodes.size() || v < 0 || v >= (int)nodes.size()) return T();
        evert(nodes[u]);
        expose(nodes[v]);
        return nodes[v]->sum;
    }

    // ノードuの値を取得
    T get_value(int u) {
        if (u < 0 || u >= (int)nodes.size()) return T();
        splay(nodes[u]);
        return nodes[u]->value;
    }

    // ノードuの値を更新
    void set_value(int u, T val) {
        if (u < 0 || u >= (int)nodes.size()) return;
        splay(nodes[u]);
        nodes[u]->value = val;
        update(nodes[u]);
    }

    // 木の根を取得
    int get_root(int u) {
        if (u < 0 || u >= (int)nodes.size()) return -1;
        expose(nodes[u]);
        Node* root = nodes[u];
        push(root);
        while (root->left) {
            root = root->left;
            push(root);
        }
        splay(root);
        return root - &nodes[0];
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な動的連結性
    cout << "例1: 基本的な動的連結性" << endl;
    LinkCutTree<int> lct(6);

    // 初期値を設定
    for (int i = 0; i < 6; i++) {
        lct.set_value(i, i + 1);
    }

    cout << "初期状態（各ノードが独立）" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "ノード" << i << "の値: " << lct.get_value(i) << endl;
    }
    cout << endl;

    // 辺を追加
    cout << "辺を追加: (0,1), (1,2), (3,4)" << endl;
    lct.link(0, 1);
    lct.link(1, 2);
    lct.link(3, 4);

    // 連結性の確認
    cout << "連結性チェック:" << endl;
    cout << "0と2は連結: " << (lct.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "0と3は連結: " << (lct.connected(0, 3) ? "Yes" : "No") << endl;
    cout << "3と4は連結: " << (lct.connected(3, 4) ? "Yes" : "No") << endl;
    cout << endl;

    // 例2: パスクエリ
    cout << "例2: パスクエリ" << endl;
    cout << "パス0→2の和: " << lct.path_sum(0, 2) << endl;
    cout << "パス3→4の和: " << lct.path_sum(3, 4) << endl;
    cout << endl;

    // 例3: 動的な辺の削除と追加
    cout << "例3: 動的な辺の操作" << endl;
    cout << "辺(1,2)を削除" << endl;
    lct.cut(1, 2);

    cout << "削除後の連結性:" << endl;
    cout << "0と1は連結: " << (lct.connected(0, 1) ? "Yes" : "No") << endl;
    cout << "0と2は連結: " << (lct.connected(0, 2) ? "Yes" : "No") << endl;
    cout << "1と2は連結: " << (lct.connected(1, 2) ? "Yes" : "No") << endl;
    cout << endl;

    cout << "新しい辺(2,3)を追加" << endl;
    lct.link(2, 3);

    cout << "追加後の連結性:" << endl;
    cout << "2と3は連結: " << (lct.connected(2, 3) ? "Yes" : "No") << endl;
    cout << "2と4は連結: " << (lct.connected(2, 4) ? "Yes" : "No") << endl;
    cout << "パス2→4の和: " << lct.path_sum(2, 4) << endl;
    cout << endl;

    // 例4: 値の更新
    cout << "例4: 値の更新" << endl;
    cout << "ノード1の値を100に更新" << endl;
    lct.set_value(1, 100);

    cout << "更新後のパス0→1の和: " << lct.path_sum(0, 1) << endl;
    cout << endl;

    // 例5: より複雑な森の構造
    cout << "例5: 複雑な森の管理" << endl;
    LinkCutTree<int> lct2(8);

    // 値を設定
    for (int i = 0; i < 8; i++) {
        lct2.set_value(i, (i + 1) * 10);
    }

    // 複数の木を作成
    // 木1: 0-1-2-3
    lct2.link(0, 1);
    lct2.link(1, 2);
    lct2.link(2, 3);

    // 木2: 4-5, 6-7
    lct2.link(4, 5);
    lct2.link(6, 7);

    cout << "初期の森の状態:" << endl;
    cout << "パス0→3の和: " << lct2.path_sum(0, 3) << endl;
    cout << "パス4→5の和: " << lct2.path_sum(4, 5) << endl;
    cout << "パス6→7の和: " << lct2.path_sum(6, 7) << endl;

    // 森を結合
    cout << "\n森を結合: (3,4), (5,6)" << endl;
    lct2.link(3, 4);
    lct2.link(5, 6);

    cout << "結合後のパス0→7の和: " << lct2.path_sum(0, 7) << endl;

    return 0;
}