#include <bits/stdc++.h>
using namespace std;

// AHC064 - Pair-based parallel sort
// Pair k uses lines/sidings {2k, 2k+1}, holds car IDs [20k, 20k+19].
// Phase 1a: dep[r] -> sid[r] (5 parallel, 1 turn).
// Phase 1b: drain each sid; route each car to its target pair.
// Phase 2: per-pair sort using stack-sort, 5 pairs in parallel.

const int R = 10;
const int DEP_CAP = 15;
const int SID_CAP = 20;
const int NUM_PAIRS = 5;

struct Move {
    int type, i, j, k;
};

deque<int> dep[R], sid[R];
vector<vector<Move>> turns;

void apply_move(deque<int>* dpa, deque<int>* spa, const Move& m) {
    if (m.type == 0) {
        // last k of dpa[i] -> front of spa[j], chunk order preserved
        int sz = dpa[m.i].size();
        deque<int> chunk(dpa[m.i].begin() + sz - m.k, dpa[m.i].end());
        dpa[m.i].erase(dpa[m.i].begin() + sz - m.k, dpa[m.i].end());
        for (auto it = chunk.rbegin(); it != chunk.rend(); ++it) {
            spa[m.j].push_front(*it);
        }
    } else {
        // first k of spa[j] -> end of dpa[i], chunk order preserved
        for (int t = 0; t < m.k; t++) {
            dpa[m.i].push_back(spa[m.j].front());
            spa[m.j].pop_front();
        }
    }
}

void emit(vector<Move> moves) {
    if (moves.empty()) return;
    sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) { return a.i < b.i; });
    for (int x = 1; x < (int)moves.size(); x++) {
        assert(moves[x-1].i != moves[x].i);
        assert(moves[x-1].j < moves[x].j);
    }
    for (auto& m : moves) apply_move(dep, sid, m);
    turns.push_back(moves);
}

int target_pair(int car) { return car / 20; }

// =============== Phase 1 ===============

void phase1a() {
    vector<Move> mv;
    for (int r = 0; r < R; r++) {
        if (!dep[r].empty()) {
            mv.push_back({0, r, r, (int)dep[r].size()});
        }
    }
    emit(mv);
}

// LIS by j among (s, j) candidates pre-sorted by s.
static vector<int> pick_lis(const vector<pair<int,int>>& cands) {
    int n = cands.size();
    if (n == 0) return {};
    vector<int> dp(n, 1), parent(n, -1);
    int best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (cands[j].second < cands[i].second && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[best]) best = i;
    }
    vector<int> res;
    while (best != -1) { res.push_back(best); best = parent[best]; }
    reverse(res.begin(), res.end());
    return res;
}

int decide_push_target_balanced(int car, int s) {
    int tp = target_pair(car);
    int t0 = 2 * tp, t1 = 2 * tp + 1;
    if (tp == s / 2) {
        return (s == t0) ? t1 : t0;
    }
    bool t0ok = (int)sid[t0].size() < SID_CAP;
    bool t1ok = (int)sid[t1].size() < SID_CAP;
    if (t0ok && t1ok) return ((int)sid[t0].size() <= (int)sid[t1].size()) ? t0 : t1;
    if (t0ok) return t0;
    if (t1ok) return t1;
    assert(false);
    return -1;
}

void phase1b() {
    bool pending_push[R] = {false};
    int iter = 0;
    while (true) {
        if (++iter > 5000) { assert(false); }
        bool any_work = false;
        for (int s = 0; s < R; s++) {
            if (!sid[s].empty() || pending_push[s]) { any_work = true; break; }
        }
        if (!any_work) break;

        // Build candidates: (s, j, type)
        vector<pair<int,int>> sj;
        vector<int> ctype;
        for (int s = 0; s < R; s++) {
            if (pending_push[s]) {
                int car = dep[s].back();
                int target = decide_push_target_balanced(car, s);
                sj.push_back({s, target});
                ctype.push_back(0);
            } else if (!sid[s].empty() && (int)dep[s].size() < DEP_CAP) {
                sj.push_back({s, s});
                ctype.push_back(1);
            } else if (!sid[s].empty() && (int)dep[s].size() >= DEP_CAP && !dep[s].empty()) {
                // dep full, force-evict the top parked car
                int car = dep[s].back();
                int target = decide_push_target_balanced(car, s);
                sj.push_back({s, target});
                ctype.push_back(0);
            }
        }
        if (sj.empty()) break;

        vector<int> sel = pick_lis(sj);
        vector<Move> moves;
        for (int idx : sel) {
            int s = sj[idx].first;
            int j = sj[idx].second;
            int t = ctype[idx];
            moves.push_back({t, s, j, 1});
        }
        emit(moves);

        for (int idx : sel) {
            int s = sj[idx].first;
            int t = ctype[idx];
            if (t == 0) {
                pending_push[s] = false;
            } else {
                int car = dep[s].back();
                int tp = target_pair(car);
                if (tp != s/2) {
                    pending_push[s] = true;
                } else if ((int)dep[s].size() >= DEP_CAP - 2) {
                    pending_push[s] = true;  // force-route same-pair when dep nearly full
                }
            }
        }
    }
    // Cleanup: parked cars on dep[s] -> sid[s] head, all in 1 turn
    {
        vector<Move> mv;
        for (int s = 0; s < R; s++) {
            if (!dep[s].empty()) {
                mv.push_back({0, s, s, (int)dep[s].size()});
            }
        }
        emit(mv);
    }
}

// =============== Phase 2 ===============

vector<Move> run_phase2_pair(int k) {
    int s0 = 2 * k, s1 = 2 * k + 1;
    deque<int> ldep[R], lsid[R];
    for (int r = 0; r < R; r++) { ldep[r] = dep[r]; lsid[r] = sid[r]; }

    vector<Move> moves;
    auto do_move = [&](Move m) {
        moves.push_back(m);
        apply_move(ldep, lsid, m);
    };

    // Step A: consolidate sid[s0] into sid[s1] in chunks (dep[s0] cap 15)
    while (!lsid[s0].empty()) {
        int n = min((int)lsid[s0].size(), DEP_CAP);
        do_move({1, s0, s0, n});
        do_move({0, s0, s1, n});
    }

    // Step B: dispense in target order
    for (int idx = 0; idx < 20; idx++) {
        int target = 20 * k + idx;
        int target_dep = (idx < 10) ? s0 : s1;
        int safety = 0;
        while (true) {
            if (safety++ > 5000) { assert(false); }
            if (!lsid[s1].empty() && lsid[s1].front() == target) {
                do_move({1, target_dep, s1, 1});
                break;
            }
            if (!lsid[s0].empty() && lsid[s0].front() == target) {
                do_move({1, target_dep, s0, 1});
                break;
            }
            int pos1 = -1, pos0 = -1;
            for (int p = 0; p < (int)lsid[s1].size(); p++) if (lsid[s1][p] == target) { pos1 = p; break; }
            for (int p = 0; p < (int)lsid[s0].size(); p++) if (lsid[s0][p] == target) { pos0 = p; break; }
            assert(pos1 >= 0 || pos0 >= 0);
            int dig_from, dig_to;
            if (pos1 >= 0 && (pos0 < 0 || pos1 <= pos0)) {
                dig_from = s1; dig_to = s0;
            } else {
                dig_from = s0; dig_to = s1;
            }
            do_move({1, dig_from, dig_from, 1});
            do_move({0, dig_from, dig_to, 1});
        }
    }
    return moves;
}

void phase2() {
    vector<vector<Move>> per_pair(NUM_PAIRS);
    for (int k = 0; k < NUM_PAIRS; k++) {
        per_pair[k] = run_phase2_pair(k);
    }
    int max_len = 0;
    for (auto& v : per_pair) max_len = max(max_len, (int)v.size());
    for (int t = 0; t < max_len; t++) {
        vector<Move> turn;
        for (int k = 0; k < NUM_PAIRS; k++) {
            if (t < (int)per_pair[k].size()) {
                turn.push_back(per_pair[k][t]);
            }
        }
        emit(turn);
    }
}

// Greedy post-process: merge consecutive turns when combined moves are non-crossing.
void compress_turns() {
    vector<vector<Move>> result;
    int n = turns.size();
    int i = 0;
    while (i < n) {
        vector<Move> cur = turns[i++];
        while (i < n) {
            vector<Move> trial = cur;
            for (auto& m : turns[i]) trial.push_back(m);
            sort(trial.begin(), trial.end(), [](const Move& a, const Move& b) { return a.i < b.i; });
            bool ok = true;
            for (int x = 1; x < (int)trial.size(); x++) {
                if (trial[x-1].i == trial[x].i || trial[x-1].j >= trial[x].j) {
                    ok = false; break;
                }
            }
            if (ok) { cur = trial; i++; }
            else break;
        }
        result.push_back(cur);
    }
    turns = result;
}

int main() {
    int Rin;
    cin >> Rin;
    assert(Rin == R);
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < 10; c++) {
            int y;
            cin >> y;
            dep[r].push_back(y);
        }
    }

    int t0 = turns.size();
    phase1a();
    int t1 = turns.size();
    phase1b();
    int t2 = turns.size();
    phase2();
    int t3 = turns.size();
    compress_turns();
    int t4 = turns.size();
    cerr << "phase1a=" << (t1-t0) << " phase1b=" << (t2-t1) << " phase2=" << (t3-t2)
         << " raw=" << t3 << " compressed=" << t4 << "\n";

    // Verify
    for (int r = 0; r < R; r++) {
        assert((int)dep[r].size() == 10);
        for (int c = 0; c < 10; c++) {
            assert(dep[r][c] == 10*r + c);
        }
        assert(sid[r].empty());
    }

    cout << turns.size() << "\n";
    for (auto& t : turns) {
        cout << t.size() << "\n";
        for (auto& m : t) {
            cout << m.type << " " << m.i << " " << m.j << " " << m.k << "\n";
        }
    }
    return 0;
}
