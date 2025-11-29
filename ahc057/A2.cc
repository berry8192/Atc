#include <atcoder/dsu>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

struct Atom {
    int id;
    double x, y, vx, vy;
    Atom(int id_, double x_, double y_, double vx_, double vy_)
        : id(id_), x(x_), y(y_), vx(vx_), vy(vy_) {}
};

struct MergeStep {
    int t, i, j;
};

const int K = 30;

double torus_dist(double x1, double y1, double x2, double y2, double L) {
    double dx = abs(x1 - x2);
    double dy = abs(y1 - y2);
    dx = min(dx, L - dx);
    dy = min(dy, L - dy);
    return sqrt(dx * dx + dy * dy);
}

// 2頂点が最も近づく時刻tとその距離dをO(1)で計算
pair<double, double> best_time_and_dist(const Atom &a, const Atom &b,
                                        double T_max, double L) {
    // 相対位置・相対速度
    double rx = a.x - b.x;
    double ry = a.y - b.y;
    double rvx = a.vx - b.vx;
    double rvy = a.vy - b.vy;

    // 初期相対位置を -L/2～L/2 に正規化
    auto wrap = [&](double d) {
        if (d > L / 2)
            d -= L;
        if (d < -L / 2)
            d += L;
        return d;
    };
    rx = wrap(rx);
    ry = wrap(ry);

    double v2 = rvx * rvx + rvy * rvy;

    // v = 0 → 距離は変わらない
    if (v2 == 0) {
        double d0 = sqrt(rx * rx + ry * ry);
        return {0.0, d0};
    }

    double best_t = 0.0;
    double best_d = 1e300;

    // 9通りのコピーを試す (kx, ky in {-1, 0, 1})
    for (int kx = -1; kx <= 1; kx++) {
        for (int ky = -1; ky <= 1; ky++) {

            double r0x = rx + kx * L;
            double r0y = ry + ky * L;

            // t* = - (r0·v)/|v|^2
            double dot = r0x * rvx + r0y * rvy;
            double t_star = -dot / v2;

            // t >= 0 にクリップ（上限が欲しければ T_max で切る）
            if (t_star < 0)
                t_star = 0;
            if (t_star >= T_max)
                t_star = T_max - 1;

            // r(t*) = r0 + v t
            double px = r0x + rvx * t_star;
            double py = r0y + rvy * t_star;

            double d = sqrt(px * px + py * py);

            if (d < best_d) {
                best_d = d;
                best_t = t_star;
            }
        }
    }

    return {best_t, best_d};
}

// Union-Find
struct UF {
    vector<int> par, sz;
    UF(int n) : par(n), sz(n, 1) {
        for (int i = 0; i < n; ++i)
            par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }
    int size(int x) { return sz[find(x)]; }
    vector<vector<int>> groups() {
        int n = par.size();
        vector<vector<int>> ret(n);
        for (int i = 0; i < n; ++i)
            ret[find(i)].push_back(i);
        vector<vector<int>> res;
        for (auto &v : ret)
            if (!v.empty())
                res.push_back(v);
        return res;
    }
};

int main() {
    int N, T, M, K_input, L;
    cin >> N >> T >> M >> K_input >> L;
    vector<Atom> atoms;
    vector<double> x, y;
    for (int i = 0; i < N; ++i) {
        int xi, yi, vxi, vyi;
        cin >> xi >> yi >> vxi >> vyi;
        atoms.emplace_back(i, xi, yi, vxi, vyi);
        x.push_back(xi);
        y.push_back(yi);
    }

    // 初期グループ分け: クラスカル法でK個のグループをM個作る
    struct Edge {
        int u, v;
        double score;
    };
    vector<Edge> edges;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j) {
            double cost = torus_dist(x[i], y[i], x[j], y[j], L);
            edges.push_back({i, j, cost});
        }
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) { return a.score < b.score; });

    dsu uf(N);
    int group_target = M;
    int group_cnt = N;
    for (auto &e : edges) {
        if (uf.leader(e.u) == uf.leader(e.v))
            continue;
        if ((int)uf.size(e.u) + (int)uf.size(e.v) > K)
            continue;
        if (group_cnt <= group_target)
            break;
        uf.merge(e.u, e.v);
        --group_cnt;
    }
    vector<vector<int>> groups = uf.groups();

    // K個未満のグループをK個にする（大きい順にマージ）
    vector<vector<int>> smalls;
    for (auto &g : groups)
        if ((int)g.size() < K)
            smalls.push_back(g);

    vector<pair<int, int>> size_idx;
    for (int i = 0; i < (int)smalls.size(); ++i) {
        size_idx.emplace_back(smalls[i].size(), i);
    }
    sort(size_idx.rbegin(), size_idx.rend());

    vector<bool> used(smalls.size(), false);
    vector<vector<int>> final_groups;
    for (int si = 0; si < (int)size_idx.size(); ++si) {
        int i = size_idx[si].second;
        if (used[i])
            continue;
        vector<int> merged = smalls[i];
        used[i] = true;
        for (int sj = si + 1; sj < (int)size_idx.size(); ++sj) {
            int j = size_idx[sj].second;
            if (used[j])
                continue;
            if ((int)merged.size() + (int)smalls[j].size() > K)
                continue;
            merged.insert(merged.end(), smalls[j].begin(), smalls[j].end());
            used[j] = true;
            if ((int)merged.size() == K)
                break;
        }
        if ((int)merged.size() == K) {
            final_groups.push_back(merged);
        }
    }
    // K個のグループはそのまま
    for (auto &g : groups)
        if ((int)g.size() == K)
            final_groups.push_back(g);

    groups = final_groups;

    // 3. 各グループで手順構築（時刻順にシミュレーションしながら結合）
    vector<vector<int>> best_groups = groups;
    double best_score = 1e300;

    // コスト計算（1グループ分のみ）
    auto group_cost = [&](const vector<int> &group_ids) -> double {
        struct Node {
            int id;
            double x, y, vx, vy;
            int appear_time;
            Node(int id_, double x_, double y_, double vx_, double vy_,
                 int appear_time_)
                : id(id_), x(x_), y(y_), vx(vx_), vy(vy_),
                  appear_time(appear_time_) {}
        };
        vector<Node> curr_atoms;
        for (int id : group_ids) {
            const Atom &a = atoms[id];
            curr_atoms.emplace_back(a.id, a.x, a.y, a.vx, a.vy, 0);
        }
        int remain = group_ids.size();
        vector<bool> alive(curr_atoms.size(), true);
        using Eval = tuple<double, int, int, int, int, int, double, int, int>;
        vector<Eval> evals;
        for (int i = 0; i < curr_atoms.size(); ++i) {
            for (int j = i + 1; j < curr_atoms.size(); ++j) {
                int appear1 = curr_atoms[i].appear_time;
                int appear2 = curr_atoms[j].appear_time;
                int min_time = max(appear1, appear2);
                pair<double, double> td = best_time_and_dist(
                    Atom(curr_atoms[i].id, curr_atoms[i].x, curr_atoms[i].y,
                         curr_atoms[i].vx, curr_atoms[i].vy),
                    Atom(curr_atoms[j].id, curr_atoms[j].x, curr_atoms[j].y,
                         curr_atoms[j].vx, curr_atoms[j].vy),
                    T - min_time, L);
                int t = (int)(td.first + 0.5);
                int merge_time = min_time + t;
                double d = td.second;
                evals.emplace_back(d, i, j, curr_atoms[i].id, curr_atoms[j].id,
                                   merge_time, d, appear1, appear2);
            }
        }
        double total_cost = 0.0;
        while (remain > 1) {
            Eval best_eval = make_tuple(1e300, -1, -1, -1, -1, -1, -1, -1, -1);
            bool found = false;
            for (auto &e : evals) {
                double d = get<0>(e);
                int i = get<1>(e), j = get<2>(e);
                int merge_time = get<5>(e);
                int appear1 = get<7>(e), appear2 = get<8>(e);
                if (!alive[i] || !alive[j])
                    continue;
                if (merge_time < appear1 || merge_time < appear2)
                    continue;
                if (!found || d < get<0>(best_eval)) {
                    best_eval = e;
                    found = true;
                }
            }
            if (!found)
                break;
            int i = get<1>(best_eval), j = get<2>(best_eval);
            int merge_time = get<5>(best_eval);
            double d = get<6>(best_eval);
            // merge_timeまで全ノードを移動
            for (int k = 0; k < curr_atoms.size(); ++k) {
                if (!alive[k])
                    continue;
                int dt = merge_time - curr_atoms[k].appear_time;
                if (dt > 0) {
                    curr_atoms[k].x =
                        fmod(curr_atoms[k].x + curr_atoms[k].vx * dt + L, L);
                    curr_atoms[k].y =
                        fmod(curr_atoms[k].y + curr_atoms[k].vy * dt + L, L);
                    curr_atoms[k].appear_time = merge_time;
                }
            }
            total_cost += d;
            // 新ノード作成
            double new_vx = (curr_atoms[i].vx + curr_atoms[j].vx) / 2.0;
            double new_vy = (curr_atoms[i].vy + curr_atoms[j].vy) / 2.0;
            double new_x = curr_atoms[i].x;
            double new_y = curr_atoms[i].y;
            int new_id = curr_atoms[i].id;
            int new_appear = merge_time;
            curr_atoms.push_back(
                Node(new_id, new_x, new_y, new_vx, new_vy, new_appear));
            alive.push_back(true);
            alive[i] = false;
            alive[j] = false;
            remain--;
            int new_idx = (int)curr_atoms.size() - 1;
            for (int k = 0; k < curr_atoms.size(); ++k) {
                if (!alive[k] || k == new_idx)
                    continue;
                int appear1 = curr_atoms[k].appear_time;
                int appear2 = curr_atoms[new_idx].appear_time;
                int min_time = max(appear1, appear2);
                pair<double, double> td = best_time_and_dist(
                    Atom(curr_atoms[k].id, curr_atoms[k].x, curr_atoms[k].y,
                         curr_atoms[k].vx, curr_atoms[k].vy),
                    Atom(curr_atoms[new_idx].id, curr_atoms[new_idx].x,
                         curr_atoms[new_idx].y, curr_atoms[new_idx].vx,
                         curr_atoms[new_idx].vy),
                    T - min_time, L);
                int t = (int)(td.first + 0.5);
                int merge_time2 = min_time + t;
                double d2 = td.second;
                evals.emplace_back(d2, k, new_idx, curr_atoms[k].id,
                                   curr_atoms[new_idx].id, merge_time2, d2,
                                   appear1, appear2);
            }
        }
        return total_cost;
    };

    // 山登り法
    mt19937 rng(42);
    int steps = 0;
    int group_num = groups.size();
    // 初期スコア
    best_score = 0.0;
    vector<double> group_scores(group_num);
    for (int gi = 0; gi < group_num; ++gi) {
        group_scores[gi] = group_cost(groups[gi]);
        best_score += group_scores[gi];
    }
    vector<vector<int>> current_groups = groups;
    best_groups = groups;

    for (int iter = 0; iter < 5000; ++iter) {
        int g1 = rng() % group_num;
        int g2 = rng() % group_num;
        if (g1 == g2)
            continue;
        if ((int)current_groups[g1].size() == 0 ||
            (int)current_groups[g2].size() == 0)
            continue;
        int idx1 = rng() % current_groups[g1].size();
        int idx2 = rng() % current_groups[g2].size();
        swap(current_groups[g1][idx1], current_groups[g2][idx2]);
        double new_score1 = group_cost(current_groups[g1]);
        double new_score2 = group_cost(current_groups[g2]);
        double new_total = best_score - group_scores[g1] - group_scores[g2] +
                           new_score1 + new_score2;
        if (new_total < best_score) {
            best_score = new_total;
            group_scores[g1] = new_score1;
            group_scores[g2] = new_score2;
            cerr << "improved: iter=" << iter << " score=" << best_score
                 << endl;
            best_groups = current_groups;
        } else {
            swap(current_groups[g1][idx1], current_groups[g2][idx2]);
        }
        ++steps;
    }

    // 最良グループで出力
    vector<MergeStep> output;
    for (const vector<int> &group_ids : best_groups) {
        if ((int)group_ids.size() != K)
            continue;
        // ...existing code for per-group merge simulation and output...
        struct Node {
            int id;
            double x, y, vx, vy;
            int appear_time;
            Node(int id_, double x_, double y_, double vx_, double vy_,
                 int appear_time_)
                : id(id_), x(x_), y(y_), vx(vx_), vy(vy_),
                  appear_time(appear_time_) {}
        };
        vector<Node> curr_atoms;
        for (int id : group_ids) {
            const Atom &a = atoms[id];
            curr_atoms.emplace_back(a.id, a.x, a.y, a.vx, a.vy, 0);
        }
        int remain = group_ids.size();
        vector<bool> alive(curr_atoms.size(), true);
        using Eval = tuple<double, int, int, int, int, int, double, int, int>;
        vector<Eval> evals;
        for (int i = 0; i < curr_atoms.size(); ++i) {
            for (int j = i + 1; j < curr_atoms.size(); ++j) {
                int appear1 = curr_atoms[i].appear_time;
                int appear2 = curr_atoms[j].appear_time;
                int min_time = max(appear1, appear2);
                pair<double, double> td = best_time_and_dist(
                    Atom(curr_atoms[i].id, curr_atoms[i].x, curr_atoms[i].y,
                         curr_atoms[i].vx, curr_atoms[i].vy),
                    Atom(curr_atoms[j].id, curr_atoms[j].x, curr_atoms[j].y,
                         curr_atoms[j].vx, curr_atoms[j].vy),
                    T - min_time, L);
                int t = (int)(td.first + 0.5);
                int merge_time = min_time + t;
                double d = td.second;
                evals.emplace_back(d, i, j, curr_atoms[i].id, curr_atoms[j].id,
                                   merge_time, d, appear1, appear2);
            }
        }
        while (remain > 1) {
            Eval best_eval = make_tuple(1e300, -1, -1, -1, -1, -1, -1, -1, -1);
            bool found = false;
            for (auto &e : evals) {
                double d = get<0>(e);
                int i = get<1>(e), j = get<2>(e);
                int merge_time = get<5>(e);
                int appear1 = get<7>(e), appear2 = get<8>(e);
                if (!alive[i] || !alive[j])
                    continue;
                if (merge_time < appear1 || merge_time < appear2)
                    continue;
                if (!found || d < get<0>(best_eval)) {
                    best_eval = e;
                    found = true;
                }
            }
            if (!found)
                break;
            int i = get<1>(best_eval), j = get<2>(best_eval);
            int id1 = get<3>(best_eval), id2 = get<4>(best_eval);
            int merge_time = get<5>(best_eval);
            double d = get<6>(best_eval);
            output.push_back({merge_time, id1, id2});
            // merge_timeまで全ノードを移動
            for (int k = 0; k < curr_atoms.size(); ++k) {
                if (!alive[k])
                    continue;
                int dt = merge_time - curr_atoms[k].appear_time;
                if (dt > 0) {
                    curr_atoms[k].x =
                        fmod(curr_atoms[k].x + curr_atoms[k].vx * dt + L, L);
                    curr_atoms[k].y =
                        fmod(curr_atoms[k].y + curr_atoms[k].vy * dt + L, L);
                    curr_atoms[k].appear_time = merge_time;
                }
            }
            // 新ノード作成
            double new_vx = (curr_atoms[i].vx + curr_atoms[j].vx) / 2.0;
            double new_vy = (curr_atoms[i].vy + curr_atoms[j].vy) / 2.0;
            double new_x = curr_atoms[i].x;
            double new_y = curr_atoms[i].y;
            int new_id = curr_atoms[i].id;
            int new_appear = merge_time;
            curr_atoms.push_back(
                Node(new_id, new_x, new_y, new_vx, new_vy, new_appear));
            alive.push_back(true);
            alive[i] = false;
            alive[j] = false;
            remain--;
            int new_idx = (int)curr_atoms.size() - 1;
            for (int k = 0; k < curr_atoms.size(); ++k) {
                if (!alive[k] || k == new_idx)
                    continue;
                int appear1 = curr_atoms[k].appear_time;
                int appear2 = curr_atoms[new_idx].appear_time;
                int min_time = max(appear1, appear2);
                pair<double, double> td = best_time_and_dist(
                    Atom(curr_atoms[k].id, curr_atoms[k].x, curr_atoms[k].y,
                         curr_atoms[k].vx, curr_atoms[k].vy),
                    Atom(curr_atoms[new_idx].id, curr_atoms[new_idx].x,
                         curr_atoms[new_idx].y, curr_atoms[new_idx].vx,
                         curr_atoms[new_idx].vy),
                    T - min_time, L);
                int t = (int)(td.first + 0.5);
                int merge_time2 = min_time + t;
                double d2 = td.second;
                evals.emplace_back(d2, k, new_idx, curr_atoms[k].id,
                                   curr_atoms[new_idx].id, merge_time2, d2,
                                   appear1, appear2);
            }
        }
    }

    // N個の頂点からM個のグループになるまでN-M回の結合が必要
    int required = N - M;
    if ((int)output.size() > required) {
        output.resize(required);
    }

    for (auto &m : output) {
        cout << m.t << " " << m.i << " " << m.j << endl;
    }
    return 0;
}
