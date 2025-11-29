#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

int N;
int HEIGHT, WIDTH;

// 構造体
struct Pos {
    int h;
    int w;

    Pos() {};
    Pos(int hh, int ww) {
        h = hh;
        w = ww;
    }

    bool is_oob() {
        // assert(0<=h);
        // assert(h<n);
        // assert(0<=w);
        // assert(w<=h);
        return !(0 <= h && h < HEIGHT && 0 <= w && w < WIDTH);
    }
    int manhattan(Pos pos) { return abs(h - pos.h) + abs(w - pos.w); }
    int index() { return h * WIDTH + w; }
    void print() { cout << "(" << h << ", " << w << ")" << endl; }
    // 受け取った近傍でPosを作る
    vector<Pos> around_pos(const vector<Pos> &dir) {
        vector<Pos> rtn;
        Pos new_pos;
        for (int i = 0; i < dir.size(); i++) {
            new_pos = {h + dir[i].h, w + dir[i].w};
            if (!new_pos.is_oob())
                rtn.emplace_back(new_pos);
        }
        return rtn;
    }

    bool operator<(const Pos &in) const {
        return h != in.h ? h < in.h : w < in.w;
    };
    bool operator==(const Pos &cpos) const {
        return (h == cpos.h && w == cpos.w);
    };
    Pos operator+(const Pos pos) {
        Pos rtn;
        rtn.h = h + pos.h;
        rtn.w = w + pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos) {
        Pos rtn;
        rtn.h = h - pos.h;
        rtn.w = w - pos.w;
        return rtn;
    }
};

struct Grid {};

// Union-Find構造体は不要なので削除

Pos itop(int idx) { return {idx / WIDTH, idx % WIDTH}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

void inpt() { cin >> N >> HEIGHT >> WIDTH; }

// torus_distをdouble対応に修正
double torus_dist(double x1, double y1, double x2, double y2, double L) {
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);
    dx = min(dx, L - dx);
    dy = min(dy, L - dy);
    return round(sqrt(dx * dx + dy * dy));
}

// グループサイズ配列から、愚直に合体してKのグループをM個作れるか判定する関数
bool can_make_M_groups(vector<int> sizes, int K, int M) {
    multiset<int> ms(sizes.begin(), sizes.end());
    int count_K = 0;
    while (!ms.empty()) {
        // 一番大きいグループを取り出す
        auto it1 = prev(ms.end());
        int a = *it1;
        if (a == K) {
            ms.erase(it1);
            count_K++;
            continue;
        }
        // 2番目に大きいグループを探す
        bool merged = false;
        auto it2 = it1;
        if (ms.size() == 1)
            break;
        --it2;
        while (true) {
            int b = *it2;
            if (a + b > K) {
                if (it2 == ms.begin())
                    break;
                --it2;
                continue;
            }
            // 合体できる
            ms.erase(it1);
            ms.erase(it2);
            if (a + b == K) {
                count_K++;
            } else {
                ms.insert(a + b);
            }
            merged = true;
            break;
        }
        if (!merged)
            break;
    }
    return count_K == M && ms.empty();
}

int main() {
    // 問題用の入力
    int T, M, K, L;
    cin >> N >> T >> M >> K >> L;
    vector<int> xi(N), yi(N), vxi(N), vyi(N);
    vector<double> x(N), y(N), vx(N), vy(N);
    rep(i, N) {
        cin >> xi[i] >> yi[i] >> vxi[i] >> vyi[i];
        x[i] = xi[i];
        y[i] = yi[i];
        vx[i] = vxi[i];
        vy[i] = vyi[i];
    }

    // タイマー開始
    auto time_start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 rng(rd());

    double best_score = -1e18;
    vector<tuple<int, int, int>> best_ans;
    ll best_total_cost = 0;

    set<pair<int, int>> blacklist;         // ブラックリスト
    vector<tuple<int, int, int>> prev_ans; // 直前施行の結合リスト

    int iter = 0; // イテレーションカウンタ

    while (true) {
        // 時間チェック
        auto now = chrono::high_resolution_clock::now();
        auto ms = chrono::duration_cast<chrono::milliseconds>(now - time_start)
                      .count();
        if (ms > 1900)
            break;

        // 状態初期化
        vector<double> cx = x, cy = y, cvx = vx, cvy = vy;
        dsu uf(N);
        vector<tuple<int, int, int>> ans;

        int threshold = 4000;
        int step = 20;
        for (int t = 0; t < T; t += step) {
            // 1. 結合フェーズ
            auto group_list = uf.groups();
            vector<int> group_sizes;
            for (auto &g : group_list)
                group_sizes.push_back(g.size());
            sort(group_sizes.rbegin(), group_sizes.rend());

            int cnt_K = 0;
            for (int sz : group_sizes)
                if (sz == K)
                    cnt_K++;

            bool rest_all_one = true;
            for (int sz : group_sizes) {
                if (sz != K && sz != 1)
                    rest_all_one = false;
            }

            if (cnt_K == M && rest_all_one)
                break;

            vector<pair<int, int>> merge_candidates;
            vector<pair<int, int>> size_leader;
            for (auto &g : group_list)
                size_leader.emplace_back(g.size(), g[0]);
            sort(size_leader.rbegin(), size_leader.rend());

            vector<bool> merged_flag(N, false);
            for (size_t i = 0; i < size_leader.size(); ++i) {
                int a = size_leader[i].second;
                if (merged_flag[uf.leader(a)])
                    continue;
                for (size_t j = i + 1; j < size_leader.size(); ++j) {
                    int b = size_leader[j].second;
                    if (merged_flag[uf.leader(b)])
                        continue;
                    int sz_a = uf.size(a), sz_b = uf.size(b);
                    if (uf.leader(a) == uf.leader(b))
                        continue;
                    if (sz_a + sz_b > K)
                        continue;
                    int u = min(a, b), v = max(a, b);
                    if (blacklist.count({u, v}))
                        continue; // ブラックリスト
                    double cost = torus_dist(cx[a], cy[a], cx[b], cy[b], L);
                    if (cost <= threshold) {
                        merge_candidates.emplace_back(a, b);
                        merged_flag[uf.leader(a)] = true;
                        merged_flag[uf.leader(b)] = true;
                        break; // aは1回だけ結合
                    }
                }
            }
            // 実際に結合
            for (size_t idx = 0; idx < merge_candidates.size(); ++idx) {
                int i = merge_candidates[idx].first;
                int j = merge_candidates[idx].second;
                uf.merge(i, j);
                ans.emplace_back(t, i, j);
            }

            // 2. 移動フェーズ
            // 各グループの速度を計算
            vector<pair<double, double>> group_v(N); // (vx, vy)
            vector<int> group_cnt(N, 0);
            rep(i, N) {
                int g = uf.leader(i);
                group_v[g].first += cvx[i];
                group_v[g].second += cvy[i];
                group_cnt[g]++;
            }
            rep(i, N) {
                int g = uf.leader(i);
                if (group_cnt[g] > 0) {
                    cvx[i] = group_v[g].first / group_cnt[g];
                    cvy[i] = group_v[g].second / group_cnt[g];
                }
            }
            // 位置更新
            // 10ステップ分まとめて移動
            rep(i, N) {
                cx[i] = fmod(cx[i] + cvx[i] * step + L, L);
                cy[i] = fmod(cy[i] + cvy[i] * step + L, L);
            }
        }

        // T-1時点でグループサイズがK未満のものを結合してKにする
        // グループ一覧
        auto group_list = uf.groups();

        // サイズK未満のグループを結合してKにする
        vector<vector<int>> smalls;
        for (auto &g : group_list)
            if (g.size() < K)
                smalls.push_back(g);

        // グループサイズが大きい順に結合
        vector<pair<int, int>> size_idx;
        for (int i = 0; i < (int)smalls.size(); ++i) {
            size_idx.emplace_back(smalls[i].size(), i);
        }
        sort(size_idx.rbegin(), size_idx.rend());

        vector<bool> used(smalls.size(), false);
        for (int si = 0; si < (int)size_idx.size(); ++si) {
            int i = size_idx[si].second;
            if (used[i])
                continue;
            vector<int> merged = smalls[i];
            used[i] = true;
            // 残りのグループも大きい順に
            for (int sj = si + 1; sj < (int)size_idx.size(); ++sj) {
                int j = size_idx[sj].second;
                if (used[j])
                    continue;
                if (merged.size() + smalls[j].size() > K)
                    continue;
                // 代表点同士のみを結合
                ans.emplace_back(T - 1, merged[0], smalls[j][0]);
                uf.merge(merged[0], smalls[j][0]);
                merged.insert(merged.end(), smalls[j].begin(), smalls[j].end());
                used[j] = true;
                if (merged.size() == K)
                    break;
            }
            // ぴったりKにならなければキャンセル（出力から削除）
            if (merged.size() != K) {
                int cancel_cnt = merged.size() - smalls[i].size();
                while (cancel_cnt--)
                    ans.pop_back();
            }
        }

        // コスト計算
        ll total_cost = 0;
        for (size_t idx = 0; idx < ans.size(); ++idx) {
            int t = std::get<0>(ans[idx]);
            int i = std::get<1>(ans[idx]);
            int j = std::get<2>(ans[idx]);
            double dx = abs(cx[i] - cx[j]);
            double dy = abs(cy[i] - cy[j]);
            dx = min(dx, (double)L - dx);
            dy = min(dy, (double)L - dy);
            ll cost = llround(sqrt(dx * dx + dy * dy));
            total_cost += cost;
        }

        // 最終グループサイズ配列
        auto final_groups = uf.groups();
        vector<int> final_sizes;
        for (auto &g : final_groups)
            final_sizes.push_back(g.size());

        // スコア計算
        double score = 0.0;
        if (can_make_M_groups(final_sizes, K, M)) {
            score = round(1e6 * log2((double)(L * (N - M)) / (total_cost + 1)));
        }

        if (score > best_score) {
            best_score = score;
            best_ans = ans;
            best_total_cost = total_cost;
            // 最高スコアを更新したらイテレーション回数とスコアを標準エラー出力
            cerr << "iter: " << iter << " score: " << best_score << endl;
        }

        // ブラックリスト更新
        blacklist.clear();
        if (!prev_ans.empty()) {
            vector<pair<int, int>> pairs;
            for (auto &tij : prev_ans) {
                int i = std::get<1>(tij), j = std::get<2>(tij);
                int u = min(i, j), v = max(i, j);
                pairs.emplace_back(u, v);
            }
            shuffle(pairs.begin(), pairs.end(), rng);
            int n_bl = max(1, (int)(pairs.size() / 30));
            for (int i = 0; i < n_bl; ++i) {
                blacklist.insert(pairs[i]);
            }
        }
        prev_ans = ans;

        ++iter;
    }

    // 出力
    for (size_t idx = 0; idx < best_ans.size(); ++idx) {
        int t = std::get<0>(best_ans[idx]);
        int i = std::get<1>(best_ans[idx]);
        int j = std::get<2>(best_ans[idx]);
        cout << t << " " << i << " " << j << endl;
    }

    cerr << "total_cost: " << best_total_cost << endl;
    cerr << "score: " << best_score << endl;

    return 0;
}
