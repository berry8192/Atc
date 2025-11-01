// Trie トライ木 文字列検索 辞書 O(M) 挿入・検索

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
using namespace std;

// ========== ライブラリ部分 ==========

// Trie（トライ木）
class Trie {
private:
    struct TrieNode {
        map<char, shared_ptr<TrieNode>> children;
        bool is_end;
        int count;  // この位置で終わる文字列の数

        TrieNode() : is_end(false), count(0) {}
    };

    shared_ptr<TrieNode> root;

    // DFSで全文字列を取得
    void dfs_collect(shared_ptr<TrieNode> node, string& current, vector<string>& result) {
        if (node->is_end) {
            for (int i = 0; i < node->count; i++) {
                result.push_back(current);
            }
        }

        for (auto& [ch, child] : node->children) {
            current.push_back(ch);
            dfs_collect(child, current, result);
            current.pop_back();
        }
    }

    // プレフィックスを持つ文字列を収集
    void collect_with_prefix(shared_ptr<TrieNode> node, string& current, vector<string>& result) {
        if (node->is_end) {
            for (int i = 0; i < node->count; i++) {
                result.push_back(current);
            }
        }

        for (auto& [ch, child] : node->children) {
            current.push_back(ch);
            collect_with_prefix(child, current, result);
            current.pop_back();
        }
    }

public:
    // コンストラクタ
    Trie() : root(make_shared<TrieNode>()) {}

    // 文字列を挿入
    void insert(const string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->is_end = true;
        current->count++;
    }

    // 文字列を検索（完全一致）
    bool search(const string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->is_end;
    }

    // プレフィックスが存在するか確認
    bool starts_with(const string& prefix) {
        auto current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return true;
    }

    // 文字列の出現回数を取得
    int count_word(const string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return 0;
            }
            current = current->children[ch];
        }
        return current->is_end ? current->count : 0;
    }

    // 文字列を削除（1回分）
    bool erase(const string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        if (current->is_end && current->count > 0) {
            current->count--;
            if (current->count == 0) {
                current->is_end = false;
            }
            return true;
        }
        return false;
    }

    // すべての文字列を取得
    vector<string> get_all_words() {
        vector<string> result;
        string current = "";
        dfs_collect(root, current, result);
        return result;
    }

    // 指定プレフィックスで始まる文字列をすべて取得
    vector<string> words_with_prefix(const string& prefix) {
        vector<string> result;
        auto current = root;

        // プレフィックスまで移動
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return result;  // プレフィックスが存在しない
            }
            current = current->children[ch];
        }

        // プレフィックス以降の文字列を収集
        string current_word = prefix;
        collect_with_prefix(current, current_word, result);
        return result;
    }

    // Trieに格納されている文字列の総数
    int size() {
        auto words = get_all_words();
        return words.size();
    }

    // Trieが空かどうか
    bool empty() {
        return size() == 0;
    }
};

// 数値専用Trie（Binary Trie）
class BinaryTrie {
private:
    struct BinaryTrieNode {
        shared_ptr<BinaryTrieNode> children[2];
        int count;

        BinaryTrieNode() : count(0) {
            children[0] = children[1] = nullptr;
        }
    };

    shared_ptr<BinaryTrieNode> root;
    int max_bits;

public:
    // コンストラクタ（max_bits: 扱う数値の最大ビット数）
    BinaryTrie(int bits = 30) : root(make_shared<BinaryTrieNode>()), max_bits(bits) {}

    // 数値を挿入
    void insert(int num) {
        auto current = root;
        for (int i = max_bits - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!current->children[bit]) {
                current->children[bit] = make_shared<BinaryTrieNode>();
            }
            current = current->children[bit];
            current->count++;
        }
    }

    // 数値を削除
    bool erase(int num) {
        auto current = root;
        vector<shared_ptr<BinaryTrieNode>> path;

        // パスを記録しながら移動
        path.push_back(current);
        for (int i = max_bits - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!current->children[bit] || current->children[bit]->count == 0) {
                return false;  // 数値が存在しない
            }
            current = current->children[bit];
            path.push_back(current);
        }

        // カウントを減らす
        for (auto node : path) {
            node->count--;
        }
        return true;
    }

    // 数値が存在するか確認
    bool contains(int num) {
        auto current = root;
        for (int i = max_bits - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!current->children[bit] || current->children[bit]->count == 0) {
                return false;
            }
            current = current->children[bit];
        }
        return current->count > 0;
    }

    // numとの最大XORを求める
    int max_xor(int num) {
        auto current = root;
        int result = 0;

        for (int i = max_bits - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int opposite = 1 - bit;

            if (current->children[opposite] && current->children[opposite]->count > 0) {
                result |= (1 << i);
                current = current->children[opposite];
            } else {
                current = current->children[bit];
            }
        }
        return result;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的なTrie操作
    cout << "例1: 基本的なTrie操作" << endl;
    Trie trie;

    vector<string> words = {"cat", "car", "card", "care", "careful", "can", "dog"};
    cout << "挿入する単語: ";
    for (const string& word : words) {
        cout << word << " ";
        trie.insert(word);
    }
    cout << endl;

    // 検索テスト
    vector<string> search_words = {"cat", "car", "care", "carry", "dog", "doggy"};
    cout << "\n検索結果:" << endl;
    for (const string& word : search_words) {
        bool found = trie.search(word);
        cout << "\"" << word << "\": " << (found ? "存在" : "なし") << endl;
    }
    cout << endl;

    // 例2: プレフィックス検索
    cout << "例2: プレフィックス検索" << endl;
    vector<string> prefixes = {"ca", "car", "do", "cat", "x"};

    for (const string& prefix : prefixes) {
        bool has_prefix = trie.starts_with(prefix);
        auto words_with_pref = trie.words_with_prefix(prefix);

        cout << "プレフィックス \"" << prefix << "\": ";
        cout << (has_prefix ? "存在" : "なし");
        if (has_prefix) {
            cout << " -> ";
            for (const string& word : words_with_pref) {
                cout << word << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    // 例3: 重複文字列の処理
    cout << "例3: 重複文字列の処理" << endl;
    Trie trie_dup;
    vector<string> dup_words = {"hello", "hello", "world", "hello", "world"};

    cout << "挿入: ";
    for (const string& word : dup_words) {
        cout << word << " ";
        trie_dup.insert(word);
    }
    cout << endl;

    cout << "単語の出現回数:" << endl;
    cout << "hello: " << trie_dup.count_word("hello") << "回" << endl;
    cout << "world: " << trie_dup.count_word("world") << "回" << endl;

    // 削除テスト
    cout << "\n\"hello\"を1回削除" << endl;
    trie_dup.erase("hello");
    cout << "hello: " << trie_dup.count_word("hello") << "回" << endl;
    cout << endl;

    // 例4: すべての単語を取得
    cout << "例4: Trieに格納されているすべての単語" << endl;
    auto all_words = trie.get_all_words();
    cout << "格納されている単語(" << all_words.size() << "個): ";
    for (const string& word : all_words) {
        cout << word << " ";
    }
    cout << endl << endl;

    // 例5: Binary Trie（数値用）
    cout << "例5: Binary Trie（数値用）" << endl;
    BinaryTrie binary_trie;

    vector<int> numbers = {1, 3, 5, 7, 9, 15, 31};
    cout << "挿入する数値: ";
    for (int num : numbers) {
        cout << num << " ";
        binary_trie.insert(num);
    }
    cout << endl;

    // 最大XOR検索
    vector<int> query_numbers = {2, 8, 16, 0};
    cout << "\n最大XOR検索:" << endl;
    for (int num : query_numbers) {
        if (binary_trie.contains(numbers[0])) {  // Trieが空でないことを確認
            int max_xor_val = binary_trie.max_xor(num);
            cout << num << " との最大XOR: " << max_xor_val << endl;
        }
    }

    // 存在確認
    cout << "\n存在確認:" << endl;
    for (int num : {1, 2, 7, 8, 15, 16}) {
        bool exists = binary_trie.contains(num);
        cout << num << ": " << (exists ? "存在" : "なし") << endl;
    }

    return 0;
}