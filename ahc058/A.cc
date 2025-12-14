#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n - 1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " "
#define ll long long

using namespace std;
// using namespace atcoder;

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

int N, L, T, K;
vector<int> A;
vector<vector<long long>> C;

struct Factory {
    vector<vector<long long>> B; // 機械の個数
    vector<vector<long long>> P; // 機械のパワー
    long long apples;            // りんごの数
    vector<int> selected_ids;    // 選択されたID
    vector<pair<long long, pair<int, int>>>
        target_machines; // {cost, {level, id}}

    Factory(const vector<int> &ids) : selected_ids(ids) {
        B.resize(L, vector<long long>(N, 1));
        P.resize(L, vector<long long>(N, 0));
        apples = K;

        // 各レベルで最もコストが小さい機械を選ぶ
        target_machines.resize(L);
        rep(level, L) {
            long long min_cost = llimax;
            int best_id = -1;
            for (int id : selected_ids) {
                if (C[level][id] < min_cost) {
                    min_cost = C[level][id];
                    best_id = id;
                }
            }
            target_machines[level] = {min_cost, {level, best_id}};
        }
    }

    // 1ターンあたりのりんご生産量を計算
    long long apples_per_turn() {
        long long production = 0;
        rep(j, N) { production += A[j] * B[0][j] * P[0][j]; }
        return production;
    }

    // 機械を強化
    bool upgrade(int level, int id) {
        long long cost = C[level][id] * (P[level][id] + 1);
        if (apples >= cost) {
            apples -= cost;
            P[level][id]++;
            return true;
        }
        return false;
    }

    // 生産処理
    void produce() {
        rep(i, L) {
            rep(j, N) {
                if (i == 0) {
                    apples += A[j] * B[i][j] * P[i][j];
                } else {
                    B[i - 1][j] += B[i][j] * P[i][j];
                }
            }
        }
    }

    // 最も効率の良い強化を探す（りんごの生産量を増やす）
    pair<int, int> find_best_upgrade() {
        double best_efficiency = -1;
        int best_level = -1, best_id = -1;

        for (int id : selected_ids) {
            rep(level, L) {
                long long cost = C[level][id] * (P[level][id] + 1);
                if (apples >= cost) {
                    // 効率を計算（生産量増加 / コスト）
                    double efficiency = 0;
                    if (level == 0) {
                        // Level 0: 直接りんごを生産
                        efficiency = (double)A[id] * B[level][id] / cost;
                    } else {
                        // Level 1以上: 下のレベルの機械を増やす
                        // より正確に評価するため、下のレベルの機械の生産力を考慮
                        long long increase = B[level][id];
                        if (level == 1) {
                            // Level 1なら、Level 0の機械が増える
                            efficiency = (double)A[id] * increase * 0.01 / cost;
                        } else {
                            // Level 2以上は長期的な効果
                            efficiency = (double)increase / cost * 0.001;
                        }
                    }

                    if (efficiency > best_efficiency) {
                        best_efficiency = efficiency;
                        best_level = level;
                        best_id = id;
                    }
                }
            }
        }

        return {best_level, best_id};
    }

    // シミュレーション実行
    pair<long long, vector<pair<int, int>>> simulate() {
        vector<pair<int, int>> actions;

        rep(turn, T) {
            bool did_action = false;

            // 各レベルの目標機械のコストをチェック
            long long production = apples_per_turn();
            long long min_target_cost = llimax;

            rep(level, L) {
                int id = target_machines[level].second.second;
                if (id != -1) {
                    long long cost = C[level][id] * (P[level][id] + 1);
                    min_target_cost = min(min_target_cost, cost);
                }
            }

            // 生産量がコスト/10を上回っていれば待つ（ただし初期の低生産時は待たない）
            if (production > 100 && production * 10 > min_target_cost) {
                actions.push_back({-1, -1});
            } else {
                // 最も効率の良い強化を実行
                pair<int, int> upgrade_pair = find_best_upgrade();
                int level = upgrade_pair.first;
                int id = upgrade_pair.second;
                if (level != -1 && upgrade(level, id)) {
                    actions.push_back({level, id});
                    did_action = true;
                }

                if (!did_action) {
                    actions.push_back({-1, -1});
                }
            }

            produce();
        }

        return {apples, actions};
    }
};

struct Grid {};

void inpt() {
    cin >> N >> L >> T >> K;
    A.resize(N);
    rep(i, N) cin >> A[i];
    C.resize(L, vector<long long>(N));
    rep(i, L) {
        rep(j, N) { cin >> C[i][j]; }
    }
}

int main() {
    start = chrono::system_clock::now();

    inpt();

    long long best_apples = 0;
    vector<pair<int, int>> best_actions;

    // ID 0は固定、ID 6, 8を選択
    vector<int> selected_ids = {0, 6, 8};

    Factory factory(selected_ids);
    pair<long long, vector<pair<int, int>>> result = factory.simulate();
    long long apples = result.first;
    vector<pair<int, int>> actions = result.second;

    best_apples = apples;
    best_actions = actions;

    // 最良の行動列を出力（デバッグ情報付き）
    Factory replay_factory(selected_ids);
    rep(turn, T) {
        // デバッグ情報を出力
        cout << "# Turn " << turn << " Apples: " << replay_factory.apples;
        cout << " | A*B*P: ";
        rep(id, N) {
            long long abp =
                A[id] * replay_factory.B[0][id] * replay_factory.P[0][id];
            cout << "ID" << id << "=" << abp;
            if (id < N - 1)
                cout << ", ";
        }
        cout << endl;

        // 行動を出力
        int level = best_actions[turn].first;
        int id = best_actions[turn].second;
        if (level == -1) {
            cout << -1 << endl;
        } else {
            cout << level SP << id << endl;
            replay_factory.upgrade(level, id);
        }

        replay_factory.produce();
    }

    return 0;
}
