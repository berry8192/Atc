#include <atcoder/all>
#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] << ", ";
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) cout << pvv[i] << ", ";
// 	// rep(i, pvv.size()-1) cout<< pvv[i]/20 SP << pvv[i]%20 <<endl;
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
//         // outputFile<< "i: " << i <<endl;
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		if(pvv[i].size()) outputFile<< pvv[i][pvv[i].size()-1] <<endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

int imax = 2147483647;
long long llimax = 9223372036854775807;

// 焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT = 1900.0;
// double TIME_LIMIT=190.0;
double start_temp = 10000000.0;
double end_temp = 10000.0;

struct Timer {
    chrono::_V2::system_clock::time_point start;

    Timer() { start = chrono::system_clock::now(); }
    double progress() {
        chrono::_V2::system_clock::time_point current =
            chrono::system_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(current - start)
                   .count() /
               TIME_LIMIT;
    }
};
Timer timer;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed = 1;
mt19937 mt(seed);

int HEIGHT = 100000, WIDTH = 100000;

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
    double euclid(Pos pos) { return hypot(pos.h - h, pos.w - w); }
    bool is_include(Pos pos, int height, int width) {
        if (pos.h < h - height)
            return false;
        if (pos.h > h + height)
            return false;
        if (pos.w < w - width)
            return false;
        if (pos.w > w + width)
            return false;
        return true;
    }
    int index() { return h * WIDTH + w; }
    void print() { cout << h << " " << w << endl; }
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
    Pos operator/(const int x) {
        Pos rtn;
        rtn.h = h / x;
        rtn.w = w / x;
        return rtn;
    }
};

int N;
vector<Pos> saba, iwashi;

struct Edge {
    Pos from;
    Pos to;

    Edge() {}
    Edge(Pos f, Pos t) {
        from = f;
        to = t;
    }
};

struct Cluster {
    Pos center_pos;
    vector<int> vertexes;
    double density;
    int height, width;

    Cluster() {}
    Cluster(Pos c, vector<int> v, double d) {
        center_pos = c;
        vertexes = v;
        density = d;
        // cerr << "d: " << d << endl;
    }

    void calc_limit(int &height_limit, int &width_limit) {
        height_limit = 0;
        width_limit = 0;
        rep(i, vertexes.size()) {
            height_limit =
                max(height_limit, abs(center_pos.h - saba[vertexes[i]].h));
            width_limit =
                max(width_limit, abs(center_pos.w - saba[vertexes[i]].w));
        }
    }
    void calc_rectangle() {
        int height_limit, width_limit;
        calc_limit(height_limit, width_limit);
        int best_height = -1, best_width = -1;
        int best_score = -10000;

        int new_height, new_width;
        int score;
        rep(lp, 40) {
            new_height = mt() % (height_limit + 1);
            new_width = mt() % (width_limit + 1);
            score = 0;
            rep(i, vertexes.size()) {
                if (center_pos.is_include(saba[vertexes[i]], new_height,
                                          new_width)) {
                    score++;
                }
            }
            rep(i, N) {
                if (center_pos.is_include(iwashi[i], new_height, new_width)) {
                    score--;
                }
            }
            if (best_score < score) {
                best_score = score;
                best_height = new_height;
                best_width = new_width;
            }
        }
        height = best_height;
        width = best_width;
    }
    bool is_covered(Cluster clu) {
        // preview_rectangle();
        // clu.preview_rectangle();
        int mx1 = center_pos.h - height;
        int mx2 = center_pos.h + height;
        int my1 = center_pos.w - width;
        int my2 = center_pos.w + width;
        int ex1 = clu.center_pos.h - clu.height;
        int ex2 = clu.center_pos.h + clu.height;
        int ey1 = clu.center_pos.w - clu.width;
        int ey2 = clu.center_pos.w + clu.width;
        // center_pos.print();
        // clu.center_pos.print();
        // cout << mx1 SP << ex2 SP << mx2 SP << ex1 SP << my1 SP << ey2 SP
        //      << my2 SP << ey1 << endl;
        // if (mx1 <= ex2 && mx2 <= ex1 && my1 <= ey2 && my2 <= ey1) {
        //     cout << "true" << endl;
        // } else {
        //     cout << "false" << endl;
        // }
        // exit(0);
        return mx1 <= ex2 && mx2 >= ex1 && my1 <= ey2 && my2 >= ey1;
    }

    void preview_rectangle() {
        cout << 4 << endl;
        cout << center_pos.h - height SP << center_pos.w - width << endl;
        cout << center_pos.h + height SP << center_pos.w - width << endl;
        cout << center_pos.h + height SP << center_pos.w + width << endl;
        cout << center_pos.h - height SP << center_pos.w + width << endl;
    }
    void add_edge(vector<Edge> &edges) {
        edges.push_back({{center_pos.h - height, center_pos.w - width},
                         {center_pos.h + height, center_pos.w - width}});
        edges.push_back({{center_pos.h + height, center_pos.w - width},
                         {center_pos.h + height, center_pos.w + width}});
        edges.push_back({{center_pos.h + height, center_pos.w + width},
                         {center_pos.h - height, center_pos.w + width}});
        edges.push_back({{center_pos.h - height, center_pos.w + width},
                         {center_pos.h - height, center_pos.w - width}});
    }
};

vector<Cluster> kmeans(int sz) {
    vector<Pos> centers(sz);
    vector<int> indices(N);
    vector<double> densites(sz);

    rep(i, sz) {
        centers[i].h = mt() % 60001 + 20000;
        centers[i].w = mt() % 60001 + 20000;
    }
    bool not_changed;
    rep(lp, 40) {
        not_changed = true;
        rep(i, sz) { densites[i] = 0.0; }
        rep(i, N) {
            int min_dist = imax;
            int min_idx = -1;
            rep(j, sz) {
                int dist = centers[j].euclid(saba[i]);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_idx = j;
                }
            }
            if (indices[i] != min_idx) {
                not_changed = false;
            }
            indices[i] = min_idx;
            densites[min_idx] += min_dist;
        }
        vector<int> new_cluster_size(sz);
        rep(i, sz) { centers[i] = {0, 0}; }
        rep(i, N) {
            assert(indices[i] != -1);
            new_cluster_size[indices[i]]++;
            centers[indices[i]] = centers[indices[i]] + saba[i];
        }
        rep(i, sz) {
            if (new_cluster_size[i] > 0) {
                centers[i] = centers[i] / new_cluster_size[i];
                densites[i] /= new_cluster_size[i];
            } else {
                densites[i] += imax;
                // cerr << "error: no cluster at " << densites[i] << endl;
            }
        }
        if (not_changed) {
            // cout << "breaked: " << lp;
            break;
        }
    }
    // cout << " loop end" << endl;

    vector<Cluster> rtn;
    rep(i, sz) { rtn.push_back({centers[i], {}, densites[i]}); }
    rep(i, N) { rtn[indices[i]].vertexes.push_back(i); }
    return rtn;
}

struct Grid {
    vector<Edge> edges;
    vector<Cluster> clusters;

    Grid() {}

    void init() {
        // edges.push_back(Edge({0, 0}, {HEIGHT, 0}));
        // edges.push_back(Edge({HEIGHT, 0}, {HEIGHT, WIDTH}));
        // edges.push_back(Edge({HEIGHT, WIDTH}, {0, WIDTH}));
        // edges.push_back(Edge({0, WIDTH}, {0, 0}));
    }

    void make_cluster() {
        double min_density = llimax;
        double density;
        rep3(i, 26, 10) {
            density = 0.0;
            vector<Cluster> new_clusters = kmeans(i);
            rep(j, new_clusters.size()) { density += new_clusters[j].density; }
            // cerr << i SP << density << endl;
            if (density < min_density) {
                min_density = density;
                clusters = new_clusters;
            }
        }
    }
    void calc_clusters_rectangle() {
        rep(i, clusters.size()) {
            clusters[i].calc_rectangle();
            // clusters[i].preview_rectangle();
        }
    }
    void optimized_clusters_rectangle() {
        bool covered = true;
        while (covered) {
            covered = false;
            rep(i, clusters.size()) {
                rep3(j, clusters.size(), i + 1) {

                    if (clusters[i].is_covered(clusters[j])) {
                        covered = true;
                        int height_diff = abs(clusters[i].center_pos.h -
                                              clusters[j].center_pos.h) +
                                          clusters[i].height +
                                          clusters[j].height;
                        int width_diff = abs(clusters[i].center_pos.w -
                                             clusters[j].center_pos.w) +
                                         clusters[i].width + clusters[j].width;
                        if (height_diff > width_diff) {
                            if (clusters[i].height > 10) {
                                clusters[i].height -= 10;
                            }
                            if (clusters[j].height > 10) {
                                clusters[j].height -= 10;
                            }
                            // cerr << "height" << endl;
                            assert(clusters[i].height > 0);
                            assert(clusters[j].height > 0);
                        } else {
                            if (clusters[i].width > 10) {
                                clusters[i].width -= 10;
                            }
                            if (clusters[j].width > 10) {
                                clusters[j].width -= 10;
                            }
                            // cerr << "width" << endl;
                            assert(clusters[i].width > 0);
                            assert(clusters[j].width > 0);
                        }
                        // clusters[i].preview_rectangle();
                        // clusters[j].preview_rectangle();
                    }
                }
            }
        }
    }
    void cluster_to_edge() {
        rep(i, clusters.size()) { clusters[i].add_edge(edges); }
    }
    void connect_cluster(int idx1, int idx2) {
        Pos joint_pos = {clusters[idx1].center_pos.h,
                         clusters[idx2].center_pos.w};
        if (!clusters[idx1].center_pos.is_include(
                joint_pos, clusters[idx1].height, clusters[idx1].width)) {
            int le = abs(clusters[idx1].center_pos.w - clusters[idx1].width -
                         joint_pos.w);
            int ri = abs(clusters[idx1].center_pos.w + clusters[idx1].width -
                         joint_pos.w);
            int cw = le <= ri
                         ? clusters[idx1].center_pos.w - clusters[idx1].width
                         : clusters[idx1].center_pos.w + clusters[idx1].width;
            Pos cpos1 = {clusters[idx1].center_pos.h, cw};
            rep(i, edges.size()) {
                // cpos1を通っているedgeを見つけ出して分断する
            }
        }
    }
    void connect_clusters() {
        int sz = clusters.size();
        dsu d(sz);
        int min_dist = imax;
        int min_dist_idx1;
        int min_dist_idx2;
        rep(lp, sz - 1) {
            rep(i, sz) {
                rep(j, sz) {
                    if (d.same(i, j)) {
                        continue;
                    }
                    int dist = clusters[i].center_pos.manhattan(
                        clusters[j].center_pos);
                    if (dist < min_dist) {
                        min_dist = dist;
                        min_dist_idx1 = i;
                        min_dist_idx2 = j;
                    }
                }
            }
            d.merge(min_dist_idx1, min_dist_idx2);
            connect_cluster(min_dist_idx1, min_dist_idx2);
        }
    }

    void calc_score() {}
    void preview_clusters() {
        cout << clusters.size() << endl;
        rep(i, clusters.size()) {
            clusters[i].center_pos.print();
            // printf("%8.1lf\n", clusters[i].density);
        }
    }
    void print_ans() {
        cout << edges.size() << endl;
        rep(i, edges.size()) { edges[i].from.print(); }
    }
};

Pos itop(int idx) { return {idx / WIDTH, idx % WIDTH}; }

Pos d4[] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

void zatsu() {
    int maxh = 0, minh = HEIGHT, maxw = 0, minw = WIDTH;
    rep(i, N) {
        maxh = max(maxh, saba[i].h);
        minh = min(minh, saba[i].h);
        maxw = max(maxw, saba[i].w);
        minw = min(minw, saba[i].w);
    }
    cout << 4 << endl;
    cout << maxh SP << maxw << endl;
    cout << maxh SP << minw << endl;
    cout << minh SP << minw << endl;
    cout << minh SP << maxw << endl;
    exit(0);
}

void random_rectangle() {
    Pos best_start, best_end, start, end;
    int best_score = -10000;

    while (timer.progress() < 1) {
        int score = 0;
        start.h = mt() % (HEIGHT + 1);
        start.w = mt() % (WIDTH + 1);
        end.h = mt() % (HEIGHT + 1);
        end.w = mt() % (WIDTH + 1);

        rep(i, N) {
            if (start.h <= saba[i].h && saba[i].h <= end.h &&
                start.w <= saba[i].w && saba[i].w <= end.w) {
                score++;
            }
        }
        rep(i, N) {
            if (start.h <= iwashi[i].h && iwashi[i].h <= end.h &&
                start.w <= iwashi[i].w && iwashi[i].w <= end.w)
                score--;
        }
        if (best_score < score) {
            best_start = start;
            best_end = end;
            best_score = score;
        }
    }
    cout << 4 << endl;
    cout << best_start.h SP << best_start.w << endl;
    cout << best_start.h SP << best_end.w << endl;
    cout << best_end.h SP << best_end.w << endl;
    cout << best_end.h SP << best_start.w << endl;
    exit(0);
}

void inpt() {
    cin >> N;
    saba.resize(N);
    iwashi.resize(N);
    Pos pos;
    rep(i, N) {
        cin >> pos.h >> pos.w;
        saba[i] = pos;
    }
    rep(i, N) {
        cin >> pos.h >> pos.w;
        iwashi[i] = pos;
    }
}

int main() {
    inpt();
    Grid best;
    best.make_cluster();
    // best.preview_clusters();
    best.calc_clusters_rectangle();
    best.optimized_clusters_rectangle();
    rep(i, best.clusters.size()) { best.clusters[i].preview_rectangle(); }

    return 0;
}
