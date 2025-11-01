// Aho-Corasick アホコラシック 複数パターンマッチング O(N + M + Z)

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

// ========== ライブラリ部分 ==========

// Aho-Corasickオートマトン
class AhoCorasick {
private:
    struct TrieNode {
        map<char, int> children;
        int failure_link;
        int output_link;
        vector<int> output;  // このノードで終わるパターンのID
        bool is_end;

        TrieNode() : failure_link(0), output_link(0), is_end(false) {}
    };

    vector<TrieNode> nodes;
    vector<string> patterns;
    int node_count;

    // パターンをTrieに挿入
    void build_trie() {
        node_count = 1;
        nodes.resize(1);  // ルートノード

        for (int i = 0; i < (int)patterns.size(); i++) {
            int current = 0;
            for (char ch : patterns[i]) {
                if (nodes[current].children.find(ch) == nodes[current].children.end()) {
                    nodes[current].children[ch] = node_count++;
                    nodes.resize(node_count);
                }
                current = nodes[current].children[ch];
            }
            nodes[current].output.push_back(i);
            nodes[current].is_end = true;
        }
    }

    // Failure LinkとOutput Linkを構築
    void build_failure_links() {
        queue<int> q;

        // ルートの直接の子のfailure linkはルートに設定
        for (auto& [ch, child] : nodes[0].children) {
            nodes[child].failure_link = 0;
            q.push(child);
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (auto& [ch, child] : nodes[current].children) {
                q.push(child);

                // failure linkを計算
                int failure = nodes[current].failure_link;
                while (failure != 0 && nodes[failure].children.find(ch) == nodes[failure].children.end()) {
                    failure = nodes[failure].failure_link;
                }

                if (nodes[failure].children.find(ch) != nodes[failure].children.end() &&
                    nodes[failure].children[ch] != child) {
                    nodes[child].failure_link = nodes[failure].children[ch];
                } else {
                    nodes[child].failure_link = 0;
                }

                // output linkを計算
                int fail_node = nodes[child].failure_link;
                if (nodes[fail_node].is_end) {
                    nodes[child].output_link = fail_node;
                } else {
                    nodes[child].output_link = nodes[fail_node].output_link;
                }
            }
        }
    }

public:
    // コンストラクタ
    AhoCorasick(const vector<string>& pats) : patterns(pats) {
        build_trie();
        build_failure_links();
    }

    // テキスト内でパターンマッチングを実行
    vector<pair<int, int>> search(const string& text) {
        vector<pair<int, int>> matches;  // (position, pattern_id)
        int current = 0;

        for (int i = 0; i < (int)text.length(); i++) {
            char ch = text[i];

            // 遷移先を探す
            while (current != 0 && nodes[current].children.find(ch) == nodes[current].children.end()) {
                current = nodes[current].failure_link;
            }

            if (nodes[current].children.find(ch) != nodes[current].children.end()) {
                current = nodes[current].children[ch];
            }

            // マッチを報告
            int output_node = current;
            while (output_node != 0) {
                if (nodes[output_node].is_end) {
                    for (int pattern_id : nodes[output_node].output) {
                        int start_pos = i - patterns[pattern_id].length() + 1;
                        matches.emplace_back(start_pos, pattern_id);
                    }
                }
                output_node = nodes[output_node].output_link;
            }
        }

        return matches;
    }

    // パターン数を取得
    int pattern_count() const {
        return patterns.size();
    }

    // パターンを取得
    string get_pattern(int id) const {
        if (id < 0 || id >= (int)patterns.size()) return "";
        return patterns[id];
    }

    // すべてのパターンマッチ情報を詳細に取得
    struct MatchInfo {
        int position;
        int pattern_id;
        string pattern;
        int length;
    };

    vector<MatchInfo> search_detailed(const string& text) {
        vector<MatchInfo> detailed_matches;
        auto matches = search(text);

        for (auto [pos, pattern_id] : matches) {
            MatchInfo info;
            info.position = pos;
            info.pattern_id = pattern_id;
            info.pattern = patterns[pattern_id];
            info.length = patterns[pattern_id].length();
            detailed_matches.push_back(info);
        }

        return detailed_matches;
    }

    // パターンごとの出現回数をカウント
    vector<int> count_matches(const string& text) {
        vector<int> counts(patterns.size(), 0);
        auto matches = search(text);

        for (auto [pos, pattern_id] : matches) {
            counts[pattern_id]++;
        }

        return counts;
    }
};

// ========== サンプルコード ==========

int main() {
    // 例1: 基本的な複数パターンマッチング
    cout << "例1: 基本的な複数パターンマッチング" << endl;
    vector<string> patterns1 = {"he", "she", "his", "hers"};
    AhoCorasick ac1(patterns1);

    string text1 = "ushers";
    cout << "テキスト: " << text1 << endl;
    cout << "パターン: ";
    for (int i = 0; i < (int)patterns1.size(); i++) {
        cout << i << ":\"" << patterns1[i] << "\" ";
    }
    cout << endl;

    auto matches1 = ac1.search(text1);
    cout << "マッチ結果:" << endl;
    for (auto [pos, pattern_id] : matches1) {
        cout << "位置 " << pos << ": パターン " << pattern_id << " (\"" << ac1.get_pattern(pattern_id) << "\")" << endl;
    }
    cout << endl;

    // 例2: より複雑なパターンセット
    cout << "例2: より複雑なパターンセット" << endl;
    vector<string> patterns2 = {"a", "ab", "abc", "bc", "c"};
    AhoCorasick ac2(patterns2);

    string text2 = "abcabc";
    cout << "テキスト: " << text2 << endl;
    cout << "パターン: ";
    for (int i = 0; i < (int)patterns2.size(); i++) {
        cout << i << ":\"" << patterns2[i] << "\" ";
    }
    cout << endl;

    auto detailed_matches = ac2.search_detailed(text2);
    cout << "詳細マッチ結果:" << endl;
    for (const auto& match : detailed_matches) {
        cout << "位置 " << match.position << ": \"" << match.pattern << "\" (ID=" << match.pattern_id << ", 長さ=" << match.length << ")" << endl;
    }
    cout << endl;

    // 例3: パターンの出現回数
    cout << "例3: パターンの出現回数" << endl;
    vector<string> patterns3 = {"cat", "dog", "at", "og"};
    AhoCorasick ac3(patterns3);

    string text3 = "The cat and dog are at the doghouse. The cat is on the caterpillar.";
    cout << "テキスト: " << text3 << endl;

    auto counts = ac3.count_matches(text3);
    cout << "出現回数:" << endl;
    for (int i = 0; i < (int)patterns3.size(); i++) {
        cout << "\"" << patterns3[i] << "\": " << counts[i] << "回" << endl;
    }
    cout << endl;

    // 例4: 重複するパターン
    cout << "例4: 重複するパターン" << endl;
    vector<string> patterns4 = {"aba", "bab", "ab", "ba"};
    AhoCorasick ac4(patterns4);

    string text4 = "abababa";
    cout << "テキスト: " << text4 << endl;
    cout << "パターン: ";
    for (int i = 0; i < (int)patterns4.size(); i++) {
        cout << "\"" << patterns4[i] << "\" ";
    }
    cout << endl;

    auto matches4 = ac4.search(text4);
    cout << "マッチ結果 (位置順):" << endl;
    for (auto [pos, pattern_id] : matches4) {
        cout << "位置 " << pos << ": \"" << ac4.get_pattern(pattern_id) << "\"" << endl;
    }
    cout << endl;

    // 例5: DNA配列での使用例
    cout << "例5: DNA配列での使用例" << endl;
    vector<string> dna_patterns = {"ATG", "TAG", "TAA", "TGA", "GCA"};
    AhoCorasick ac_dna(dna_patterns);

    string dna_sequence = "ATGCGATAGCAATGCTAGCATAA";
    cout << "DNA配列: " << dna_sequence << endl;
    cout << "検索パターン: ";
    for (const string& pat : dna_patterns) {
        cout << pat << " ";
    }
    cout << endl;

    auto dna_matches = ac_dna.search_detailed(dna_sequence);
    cout << "見つかったパターン:" << endl;
    for (const auto& match : dna_matches) {
        cout << "位置 " << match.position << ": " << match.pattern;
        if (match.pattern == "ATG") cout << " (開始コドン)";
        else if (match.pattern == "TAG" || match.pattern == "TAA" || match.pattern == "TGA") cout << " (終止コドン)";
        cout << endl;
    }
    cout << endl;

    // 例6: 性能確認（大きなテキスト）
    cout << "例6: 性能確認" << endl;
    vector<string> perf_patterns = {"pattern1", "pattern2", "test", "example"};
    AhoCorasick ac_perf(perf_patterns);

    // 長いテキストを生成
    string long_text = "";
    for (int i = 0; i < 1000; i++) {
        long_text += "This is a test example with pattern1 and pattern2. ";
    }

    cout << "長いテキスト (長さ: " << long_text.length() << ") での検索実行" << endl;
    auto perf_counts = ac_perf.count_matches(long_text);
    cout << "結果:" << endl;
    for (int i = 0; i < (int)perf_patterns.size(); i++) {
        cout << "\"" << perf_patterns[i] << "\": " << perf_counts[i] << "回" << endl;
    }

    return 0;
}