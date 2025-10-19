#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    // Input
    int N;
    cin >> N;

    vector<long long> H(N);
    for (int i = 0; i < N; ++i) {
        cin >> H[i];
    }

    vector<int> C(N);
    for (int i = 0; i < N; ++i) {
        cin >> C[i];
    }

    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    vector<bool> is_chest_open(N, false);
    vector<bool> is_weapon_available(N, false);
    int open_chests_count = 0;
    vector<pair<int, int>> attacks;

    // 1. Find the best chest to open first with bare hands
    int first_chest_idx = -1;
    double max_score = -1.0;
    for (int i = 0; i < N; ++i) {
        long long total_power = 0;
        for (int j = 0; j < N; ++j) {
            total_power += A[i][j];
        }
        double score = (double)(total_power * C[i]) / H[i];
        if (score > max_score) {
            max_score = score;
            first_chest_idx = i;
        }
    }

    // Open the first chest
    for (int i = 0; i < H[first_chest_idx]; ++i) {
        attacks.push_back({-1, first_chest_idx});
    }
    H[first_chest_idx] = 0;
    is_chest_open[first_chest_idx] = true;
    is_weapon_available[first_chest_idx] = true;
    open_chests_count++;

    // 2. Open remaining chests using available weapons
    while (open_chests_count < N) {
        int best_weapon = -1;
        int best_chest = -1;
        int max_attack_power = -1;

        for (int w = 0; w < N; ++w) {
            if (is_weapon_available[w] && C[w] > 0) {
                for (int b = 0; b < N; ++b) {
                    if (!is_chest_open[b]) {
                        if (A[w][b] > max_attack_power) {
                            max_attack_power = A[w][b];
                            best_weapon = w;
                            best_chest = b;
                        }
                    }
                }
            }
        }

        if (best_weapon != -1) {
            attacks.push_back({best_weapon, best_chest});
            H[best_chest] -= A[best_weapon][best_chest];
            C[best_weapon]--;

            if (H[best_chest] <= 0) {
                is_chest_open[best_chest] = true;
                is_weapon_available[best_chest] = true;
                open_chests_count++;
            }
        } else {
            // No usable weapon attack found. This means all available weapons
            // are depleted. We must open a new chest with bare hands. Let's
            // choose the unopened chest with the minimum remaining health.
            int target_chest = -1;
            long long min_h = -1;

            for (int i = 0; i < N; ++i) {
                if (!is_chest_open[i]) {
                    if (target_chest == -1 || H[i] < min_h) {
                        min_h = H[i];
                        target_chest = i;
                    }
                }
            }

            if (target_chest != -1) {
                // Open this chest completely with bare hands
                long long remaining_h = H[target_chest];
                if (remaining_h > 0) {
                    for (long long k = 0; k < remaining_h; ++k) {
                        attacks.push_back({-1, target_chest});
                    }
                }
                H[target_chest] = 0;
                is_chest_open[target_chest] = true;
                is_weapon_available[target_chest] = true;
                open_chests_count++;
            }
        }
    }

    // Output the sequence of attacks
    for (const auto &attack : attacks) {
        cout << attack.first << " " << attack.second << endl;
    }

    return 0;
}
