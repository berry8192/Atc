#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
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

int imax=2147483647;
long long llimax=9223372036854775807;

//焼きなましの定数
chrono::system_clock::time_point start, current;
double TIME_LIMIT=1900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int T, K, H, W, i0;
int S[8010], D[8010];
int h[21][21], v[21][21];

// 構造体
struct Pos{
    int h;
    int w;

    Pos(){};
    Pos(int hh, int ww){
        h=hh;
        w=ww;
    }

    int index(){
        return h*W+w;
    }
    void print(){
        cout<< "(" << h << ", " << w << ")" <<endl;
    }
    bool operator<(const Pos &in) const{
		return h!=in.h ? h<in.h : w<in.w;
	};
    bool operator==(const Pos &cpos) const{
        return (h==cpos.h && w==cpos.w);
    };
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.h=h+pos.h;
        rtn.w=w+pos.w;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.h=h-pos.h;
        rtn.w=w-pos.w;
        return rtn;
    }
};

Pos itop(int idx){
    return {idx/W, idx%W};
}

Pos d4[]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

int around_wall(Pos pos){
    int rtn=0;
    if(pos.h==0){
        rtn++;
    }else if(h[pos.h-1][pos.w]==1){
        rtn++;
    }
    if(pos.h==H-1){
        rtn++;
    }else if(h[pos.h][pos.w]==1){
        rtn++;
    }

    if(pos.w==0){
        rtn++;
    }else if(v[pos.h][pos.w-1]==1){
        rtn++;
    }
    if(pos.w==W-1){
        rtn++;
    }else if(v[pos.h][pos.w]==1){
        rtn++;
    }
    return rtn;
}

// struct itv{
// 	int le, ri;

// 	// 区間スケジュール的な、終わるのが早い順で始まるのが遅い順のソート用
// 	bool operator<(const itv &in) const{
// 		return ri!=in.ri ? ri<in.ri : le>in.le;
// 	};

// 	// 区間が重なっているかどうか（端点を含ませたい場合は<=を使う）
// 	bool cover(itv x, itv y){
// 		return max(x.le, y.le)<min(x.ri, y.ri);
// 	}
// };
// vector<itv> crops;

struct Dependent{
    int parent;
    vector<int> child;

    Dependent(){};
    Dependent(int par, vector<int> &chi){
        parent=par;
        rep(i, chi.size()) child.push_back(chi[i]);
    }
};

struct Placement{
    Pos pos={0, 0};
    int plant_s=0;

    Placement(){};
    Placement(Pos ipos, int is){
        pos=ipos;
        plant_s=is;
    }
    
    // 出力の時は1-indexにする
    void print(int index){
        cout<< index+1 SP << pos.h SP << pos.w SP << plant_s <<endl;
    }
};

struct Far{
    int index;
    int dist;
    bool is_hatake;

    Far(){};
    Far(int iidx, int idist, bool iis_hatake){
        index=iidx;
        dist=idist;
        is_hatake=iis_hatake;
    }
    
    bool operator<(const Far &in) const{
		return dist>in.dist; // 遠い方を優先
	};
};

struct PlanDulation{
    int plan_index;
    int dulation;

    PlanDulation(){};
    PlanDulation(int iidx, int idula){
        plan_index=iidx;
        dulation=idula;
    }
    
    bool operator<(const PlanDulation &in) const{
		return dulation>in.dulation; // 長い方を優先
	};

    void print(){
        cout<< "idx: " << plan_index SP << "dulation: " << dulation <<endl;
    }
};
vector<PlanDulation> dulations;

vector<vector<vector<int>>> plans;

struct Space{
    vector<vector<int>> graph; // [400][0~4] [頂点idx][到達可能な頂点idx] 盤面の移動可否を計算するためのグラフ
    vector<vector<int>> board; // [20][20] [h][w] 常に畑とするマスが1、未定が0、通路にするのが-1
    vector<vector<int>> enter_dist; // 入口からの距離
    vector<int> highest_pos_idx; // 周りの4近傍のどのマスよりも入口から遠いマス
    vector<Dependent> blocking_tree;
    vector<Far> hatake_priority;
    // vector<vector<int>> blocking; // マスidが埋まっていると辿り着けないマスのidたち
    // ここから下の変数は直接触らない
    map<int, Placement> placement; // 出力となる農耕計画
    bitset<8010> used_plan; // 使用した農耕プラン
    // vector<vector<vector<int>>> plant; // [T][H][W]=val番のplanで利用中、負の時は早く置いているとき、0以外が入っているときは使用中
    vector<vector<bitset<102>>> plant_blocking; // [H][W]の各ターンで植えられないときを1とする
    vector<vector<bitset<102>>> plant_using; // [H][W]の各ターンで植えたいときを1とする
    vector<vector<bitset<102>>> harvest_blocking; // [H][W]の各ターンで収穫できないときを1とする
    vector<vector<bitset<102>>> harvest_using; // [H][W]の各ターンで収穫したいときを1とする
    // int harvest[110][21][21];
    int score; // 現在のスコア、H*W*T=40000点満点

    void init(){
        score=0;
        // plant.resize(T);
        // rep(i, T) plant[i].resize(H);
        // rep(i, T) rep(j, H) plant[i][j].resize(W, imax);
        plant_blocking.resize(H, vector<bitset<102>>(W));
        plant_using.resize(H, vector<bitset<102>>(W));
        harvest_blocking.resize(H, vector<bitset<102>>(W));
        harvest_using.resize(H, vector<bitset<102>>(W));
        blocking_tree.resize(H*W);
        rep(i, H*W) blocking_tree[i].parent=-1;
        board.resize(H, vector<int>(W));
        board[i0][0]=-1; // 入口は確実に通路にする
        enter_dist.resize(H, vector<int>(W, -1));
        // blocking.resize(H*W);
        create_graph();
        calc_dist_from_enter();
    }

    // graphを作成
    void create_graph(){
        graph.clear();
        graph.resize(H*W);
        for (int i = 0; i < H - 1; ++i) {
            for (int j = 0; j < W; ++j){
                // cout<< h[i][j] <<endl;
                if(h[i][j]==0){
                    // cout<< "h: " << i SP << j <<endl;
                    int from=(Pos{i, j}).index();
                    int to=(Pos{i+1, j}).index();
                    graph[from].push_back(to);
                    graph[to].push_back(from);
                }
            }
        }
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W - 1; ++j){
                if(v[i][j]==0){
                    // cout<< "v: " << i SP << j <<endl;
                    int from=(Pos{i, j}).index();
                    int to=(Pos{i, j+1}).index();
                    graph[from].push_back(to);
                    graph[to].push_back(from);
                }
            }
        }
        // PVV(graph);
    }
    // graphを使って初期状態での入口からの距離を算出
    void calc_dist_from_enter(){
        queue<Pos> q;
        q.push({i0, 0});
        enter_dist[i0][0]=0;
        while(!q.empty()){
            Pos pos=q.front();
            int pindex=pos.index();
            q.pop();
            rep(i, graph[pindex].size()){
                Pos npos=itop(graph[pindex][i]);
                if(enter_dist[npos.h][npos.w]==-1){
                    enter_dist[npos.h][npos.w]=enter_dist[pos.h][pos.w]+1;
                    q.push(npos);
                }
            }
        }
        // PVV(enter_dist);
    }
    void calc_highest_pos_idx(){
        rep(i, H){
            rep(j, W){
                int cpos_idx=i*W+j;
                int current_dist=enter_dist[i][j];
                bool is_highest=true;
                rep(k, graph[cpos_idx].size()){
                    Pos npos=itop(graph[cpos_idx][k]);
                    if(current_dist<enter_dist[npos.h][npos.w]){
                        is_highest=false;
                        break;
                    }
                }
                if(is_highest) highest_pos_idx.push_back(cpos_idx);
            }
        }
    }
    void calc_board_ng_place(){
        rep(i, highest_pos_idx.size()){
            int second_high_idx=graph[highest_pos_idx[i]][0]; // 乱数の余地あり
            Pos pos=itop(second_high_idx);
            if(pos==Pos{i0, 0}) continue;
            calc_ng_load(second_high_idx, 0);
        }
        // PVV(board);
    }
    // 最短経路の通路を決める
    void calc_ng_load(int idx, int depth){
        Pos cpos=itop(idx);
        board[cpos.h][cpos.w]=-1;
        int min_around_wall=555;
        int min_i;
        int current_dist=enter_dist[cpos.h][cpos.w];
        rep(i, graph[idx].size()){
            Pos pos=itop(graph[idx][i]);
            if(enter_dist[pos.h][pos.w]>=current_dist) continue;
            if(board[pos.h][pos.w]==-1) return; // 既に通路になっているところに隣接したら終わりで良い
            int tmp=around_wall(itop(graph[idx][i])); // 周りに壁がいくつあるか
            if(tmp<min_around_wall){
                min_around_wall=tmp;
                min_i=i;
            }
        }
        int min_idx=graph[idx][min_i];
        Pos mpos=itop(min_idx);
        board[mpos.h][mpos.w]=-1;
        calc_ng_load(min_idx, depth+1);
    }

    // boardを渡し、すべてのマスに到達できるかを算出
    bool reachable_all(vector<vector<int>> &bor){
        bitset<400> reached;
        queue<Pos> q;
        Pos init_pos={i0, 0};
        q.push(init_pos);
        reached.set(init_pos.index());
        while(!q.empty()){
            Pos pos=q.front();
            int pindex=pos.index();
            q.pop();
            if(bor[pos.h][pos.w]==1) continue;
            rep(i, graph[pindex].size()){
                int n_index=graph[pindex][i];
                if(!reached[n_index]){
                    reached.set(n_index);
                    q.push(itop(n_index));
                }
            }
        }
        // outputFile<< reached.count() <<endl;
        // PVV(enter_dist);
        return (reached.count()==H*W);
    }
    void make_tree(){
        bitset<400> reached;
        queue<Pos> q;
        queue<int> parent_q;
        Pos init_pos={i0, 0};
        q.push(init_pos);
        parent_q.push(-1);
        reached.set(init_pos.index());
        while(!q.empty()){
            Pos pos=q.front();
            // pos.print();
            int pindex=pos.index();
            int parent=parent_q.front();
            q.pop();
            parent_q.pop();
            blocking_tree[pindex].parent=parent;
            if(board[pos.h][pos.w]==1) continue;
            rep(i, graph[pindex].size()){
                int n_index=graph[pindex][i];
                if(!reached[n_index]){
                    blocking_tree[pindex].child.push_back(n_index);
                    reached.set(n_index);
                    q.push(itop(n_index));
                    parent_q.push(pindex);
                }
            }
        }
    }
    void calc_dependent_depth(){
        bitset<400> reached;
        queue<Pos> q;
        queue<int> dist_q;
        Pos init_pos={i0, 0};
        q.push(init_pos);
        dist_q.push(0);
        reached.set(init_pos.index());
        while(!q.empty()){
            Pos pos=q.front();
            int pindex=pos.index();
            q.pop();
            int dist=dist_q.front();
            dist_q.pop();
            if(board[pos.h][pos.w]==1) continue;
            rep(i, graph[pindex].size()){
                int n_index=graph[pindex][i];
                Pos npos=itop(n_index);
                if(!reached[n_index]){
                    hatake_priority.push_back({n_index, dist+1, board[npos.h][npos.w]==1});
                    reached.set(n_index);
                    q.push(itop(n_index));
                    dist_q.push(dist+1);
                }
            }
        }
        sort(all(hatake_priority));
    }
    bool reachable_all_all(){
        // 入口からBFSしながらblockingのorをとっていき、隣接したマスのusingとの積がnoneでなければfalseを返す
        bitset<400> reached;
        queue<int> q;
        queue<bitset<102>> plant_q, harvest_q;
        Pos init_pos={i0, 0};
        q.push(init_pos.index());
        bitset<102> emp;
        plant_q.push(emp);
        harvest_q.push(emp);
        reached.set(init_pos.index());
        while(!q.empty()){
            int pindex=q.front();
            Pos pos=itop(pindex);
            q.pop();
            bitset<102> pla=((plant_q.front())|(plant_blocking[pos.h][pos.w]));
            plant_q.pop();
            bitset<102> har=((harvest_q.front())|(harvest_blocking[pos.h][pos.w]));
            harvest_q.pop();

            if(board[pos.h][pos.w]==1) continue;
            rep(i, blocking_tree[pindex].child.size()){
                int n_index=blocking_tree[pindex].child[i];
                if(!reached[n_index]){
                    reached.set(n_index);
                    Pos npos=itop(n_index);
                    if((pla&(plant_using[npos.h][npos.w])).any()) return false;
                    if((har&(harvest_using[npos.h][npos.w])).any()) return false;
                    plant_q.push(pla);
                    harvest_q.push(har);
                    q.push(n_index);
                }
            }
        }
        return true;
    }
    // ランダムな順番に、各マスを畑にしてもたどり着けないマスがないかを確認し、大丈夫なら畑にする
    void find_placement(bool avoid_load){
        vector<int> perm(H*W);
        rep(i, H*W) perm[i]=i;
        shuffle(all(perm), mt);

        rep(i, H*W){
            Pos pos=itop(perm[i]);
            if(avoid_load && board[pos.h][pos.w]==-1) continue; // 通路にしたいマスはそもそも試さない
            board[pos.h][pos.w]=1;
            if(!reachable_all(board)) board[pos.h][pos.w]=0;
        }
        // PVV(board);
        // int count=0;
        // rep(i, H){
        //     rep(j, W){
        //         if(board[i][j]) count++;
        //     }
        // }
        // cout<< count <<endl;
        // rep(i, H){
        //     rep(j, W){
        //         if(board[i][j]) cout<< i*W+j+1 SP << i SP << j SP << 1 <<endl;
        //     }
        // }
    }
    void hatake_scheduling(bool shcedule_load){
        // cout<< hatake_priority.size() <<endl;
        rep(i, K){
            // cout<< "dulation " << i << ": " << dulations[i].dulation <<endl;
            if(dulations[i].dulation<12 && !shcedule_load) break;
            rep(j, hatake_priority.size()){
                if(used_plan[i]) continue;
                // cout<< "hatake_priority " << j << ": " << hatake_priority[j].dist <<endl;
                if(shcedule_load || hatake_priority[j].is_hatake){
                    if(try_add_schedule(i, itop(hatake_priority[j].index), S[i])) break;
                }
            }
        }
    }
    void scheduling(){
        rep(i, hatake_priority.size()){
            if(hatake_priority[i].is_hatake) continue;
            // cout<< "hatake: " << hatake_priority[i].index <<endl;
            rep(lp, 10){
                int end_t=mt()%96+5;
                int start_t=max(0, int(end_t-mt()%12));
                int allow_eps=mt()%5;
                // cout<< "end_t start_t allow_eps: " << end_t SP << start_t SP << allow_eps <<endl;
                vector<vector<int>> usable_plans(allow_eps);
                vector<Pos> plan_pos;
                int flg=1;
                int set_time;
                rep(j, allow_eps){
                    set_time=start_t-j;
                    if(set_time<=0){
                        flg=0;
                        break;
                    }
                    repr(k, plans[set_time][end_t].size()){
                        // cout<< "plans: " SP << k <<endl;
                        // cout<< plans[set_time][end_t][k] <<endl;
                        usable_plans[j].push_back(plans[set_time][end_t][k]);
                    }
                    if(usable_plans.size()>=blocking_tree[hatake_priority[i].index].child.size()+1) break;
                }
                if(usable_plans.size()<blocking_tree[hatake_priority[i].index].child.size()+1) continue;
                if(flg){
                    // cout<< "try execute" <<endl;
                    bool exec=true;
                    int loop=0;
                    plan_pos.push_back(itop(hatake_priority[i].index));
                    rep(j, usable_plans.size()-1) plan_pos.push_back(itop(blocking_tree[hatake_priority[i].index].child[j]));
                    rep(j, allow_eps){
                        rep(k, usable_plans[j].size()){
                            if(!try_add_schedule(usable_plans[j][k], plan_pos[loop], set_time, false)){
                                exec=false;
                                break;
                            }
                        }
                        if(!exec) break;
                    }
                    // cout<< "execute" <<endl;
                    loop=0;
                    if(exec){
                        rep(j, allow_eps){
                            rep(k, usable_plans[j].size()){
                                try_add_schedule(usable_plans[j][k], plan_pos[loop], set_time);
                                plans[start_t-j][end_t].pop_back();
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    // 1つのマスについて、なるべく農耕時間が長くなるように農耕計画を立てる
    void interval_scheduling(int index){
        int empty_time=1;
        bool planned=true;
        while(planned){
            planned=false;
            rep(lp, 20){
                rep(i, K){
                    if(empty_time<=S[i] && S[i]-empty_time<=lp){
                        if(used_plan[i]) continue;
                        // outputFile<< index SP << S[i] SP << D[i] <<endl;
                        empty_time=D[i]+1;
                        add_schedule(i, itop(index), S[i]);
                        planned=true;
                    }
                    if(empty_time==T) break;
                }
            }
        }
    }
    void interval_scheduling_all(){
        rep(i, H){
            rep(j, W){
                if(board[i][j]==1) interval_scheduling(i*W+j);
            }
        }
    }

    void delete_dfs(int x, set<int> &st){
        rep(i, blocking_tree[x].child.size()){
            st.insert(blocking_tree[x].child[i]);
            delete_dfs(blocking_tree[x].child[i], st);
        }
    }
    void random_add_delete(){
        int hatake_idx;
        int lp=0;
        set<int> delete_list;
        while(1){
            // current = chrono::system_clock::now();
            // if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
            // cout<< "rand" <<endl;
            hatake_idx=mt()%(mt()%(H*W)+1);
            // cout<< "rand2" <<endl;
            if(!hatake_priority[hatake_idx].is_hatake) continue;
            delete_list.insert(hatake_idx);
            delete_dfs(hatake_idx, delete_list);
            break;
        }
            // cout<< "rand3" <<endl;
        rep(i, K){
            if(used_plan[i] && placement[i].plant_s!=0 && delete_list.find(i)!=delete_list.end()){
                delete_schedule(i);
            } 
        }
            cout<< "delete: " << delete_list.size() <<endl;
        rep(lp, 1000*delete_list.size()){
            int plan_idx=mt()%K;
            int idx=mt()%(H*W);
            if(delete_list.find(idx)==delete_list.end()) continue;
            Pos pos=itop(idx);
            try_add_schedule(plan_idx, pos, max(1, int(S[plan_idx])));
        }
    }

    bool try_add_schedule(int plan_idx, Pos plan_pos, int plant_t, bool execute=true){
        assert(plant_t<=S[plan_idx]);
        assert(0<plant_t);
        // assert(!used_plan[plan_idx]);
        // assert(placement.find(plan_idx)==placement.end());
        if(used_plan[plan_idx]) return false;
        if(placement.find(plan_idx)!=placement.end()) return false;
        bitset<102> bs;
        rep3(i, D[plan_idx]+2, plant_t) bs.set(i); // plan_posにおいて農耕をしてしまっていないか
        if((bs&(plant_blocking[plan_pos.h][plan_pos.w])).any()) return false;
        if(plant_using[plan_pos.h][plan_pos.w].test(plant_t)) return false;
        if(harvest_using[plan_pos.h][plan_pos.w].test(D[plan_idx])) return false;
        rep3(i, D[plan_idx]+1, plant_t+1){
            if(plant_blocking[plan_pos.h][plan_pos.w].test(i)) return false;
        }
        rep3(i, D[plan_idx], plant_t){
            if(harvest_blocking[plan_pos.h][plan_pos.w].test(i)) return false;
        }
        if(!execute) return true;
        int next_score=score+D[plan_idx]-S[plan_idx]+1;
        assert(0<=next_score);
        assert(next_score<=40000);

        add_schedule(plan_idx, plan_pos, plant_t);
        if(reachable_all_all()){
            // outputFile<< "added: " << plan_idx <<endl;
            return true;
        }else{
            // outputFile<< "not added: " << plan_idx <<endl;
            delete_schedule(plan_idx);
            return false;
        }
    }
    void add_schedule(int plan_idx, Pos plan_pos, int plant_t){
        assert(plant_t<=S[plan_idx]);
        assert(0<plant_t);
        assert(placement.find(plan_idx)==placement.end());
        placement[plan_idx]={plan_pos, plant_t};
        assert(!used_plan[plan_idx]);
        used_plan.set(plan_idx);
        bitset<102> bs;
        rep3(i, D[plan_idx]+2, plant_t) bs.set(i); // plan_posにおいて農耕をしてしまっていないか
        // outputFile<< (bs&(plant_blocking[plan_pos.h][plan_pos.w])) <<endl;
        assert((bs&(plant_blocking[plan_pos.h][plan_pos.w])).none());

        assert(!plant_using[plan_pos.h][plan_pos.w].test(plant_t));
        plant_using[plan_pos.h][plan_pos.w].set(plant_t);
        assert(!harvest_using[plan_pos.h][plan_pos.w].test(D[plan_idx]));
        harvest_using[plan_pos.h][plan_pos.w].set(D[plan_idx]);
        rep3(i, D[plan_idx]+1, plant_t+1){
            assert(!plant_blocking[plan_pos.h][plan_pos.w].test(i));
            plant_blocking[plan_pos.h][plan_pos.w].set(i);
        }
        rep3(i, D[plan_idx], plant_t){
            assert(!harvest_blocking[plan_pos.h][plan_pos.w].test(i));
            harvest_blocking[plan_pos.h][plan_pos.w].set(i);
        }
        // rep3(i, S[plan_idx], plant_t){
        //     assert(plant[i][plan_pos.h][plan_pos.w]==imax);
        //     // assert(harvest[i][plan_pos.h][plan_pos.w]==0);
        //     plant[i][plan_pos.h][plan_pos.w]=plan_idx;
        //     // harvest[i][plan_pos.h][plan_pos.w]=plan_idx;
        // }
        // rep3(i, D[plan_idx]+1, S[plan_idx]){
        //     assert(plant[i][plan_pos.h][plan_pos.w]==imax);
        //     // assert(harvest[i][plan_pos.h][plan_pos.w]==0);
        //     plant[i][plan_pos.h][plan_pos.w]=plan_idx;
        //     // harvest[i][plan_pos.h][plan_pos.w]=plan_idx;
        // }
        score+=D[plan_idx]-S[plan_idx]+1;
        assert(0<=score);
        assert(score<=40000);
    }
    // 後で計算量を削減したくなったらplan_posを渡さなくてよくする
    void delete_schedule(int plan_idx){
        Pos plan_pos=placement[plan_idx].pos;
        int plant_t=placement[plan_idx].plant_s;
        assert(placement.find(plan_idx)!=placement.end());
        // assert(placement[plan_idx].pos==plan_pos); // 消そうとしているものの座標がちゃんと把握できているかを念のため確認
        placement.erase(plan_idx);
        assert(used_plan[plan_idx]);
        used_plan.reset(plan_idx);

        assert(plant_using[plan_pos.h][plan_pos.w].test(plant_t));
        plant_using[plan_pos.h][plan_pos.w].reset(plant_t);
        assert(harvest_using[plan_pos.h][plan_pos.w].test(D[plan_idx]));
        harvest_using[plan_pos.h][plan_pos.w].reset(D[plan_idx]);
        rep3(i, D[plan_idx]+1, plant_t+1){
            assert(plant_blocking[plan_pos.h][plan_pos.w].test(i));
            plant_blocking[plan_pos.h][plan_pos.w].reset(i);
        }
        rep3(i, D[plan_idx], plant_t){
            assert(harvest_blocking[plan_pos.h][plan_pos.w].test(i));
            harvest_blocking[plan_pos.h][plan_pos.w].reset(i);
        }
        // for(int i=S[plan_idx]-1;i>0;i--){
        //     if(plant[i][plan_pos.h][plan_pos.w]<0) plant[i][plan_pos.h][plan_pos.w]=imax;
        //     else break;
        //     // if(harvest[i][plan_pos.h][plan_pos.w]<0) harvest[i][plan_pos.h][plan_pos.w]=0;
        //     // else break;
        // }
        // rep3(i, D[plan_idx]+1, S[plan_idx]){
        //     assert(plant[i][plan_pos.h][plan_pos.w]!=imax);
        //     // assert(harvest[i][plan_pos.h][plan_pos.w]!=0);
        //     plant[i][plan_pos.h][plan_pos.w]=imax;
        //     // harvest[i][plan_pos.h][plan_pos.w]=plan_idx;
        // }
        score-=D[plan_idx]-S[plan_idx]+1;
        assert(0<=score);
        assert(score<=40000);
    }
    void print_ans(){
        cout<< used_plan.count() <<endl;
        for(auto p : placement){
            p.second.print(p.first);
        }
    }
};

void inpt(){
    cin >> T >> H >> W >> i0;
    for (int i = 0; i < H - 1; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W; ++j) h[i][j] = int(s[j]-'0');
    }
    for (int i = 0; i < H; ++i) {
        string s; cin >> s;
        for (int j = 0; j < W - 1; ++j) v[i][j] = int(s[j]-'0');
    }
    cin >> K;
    // crops.resize(K);
    for (int i = 0; i < K; ++i){
        cin >> S[i] >> D[i];
        // crops[i]={S[i], D[i]};
        dulations.push_back({i, D[i]-S[i]+1});
        plans[S[i]][D[i]].push_back(i);
    }
    sort(all(dulations));
    // rep(i, H*W) dulations[i].print();
    
    // vector<int> vv(100);
    // for (int i = 0; i < K; ++i){
    //     rep3(j, D[i], S[i]-1) vv[j]++;
    // }
    // PV(vv);
    // exit(0);

    // 雑crops
    // sort(all(crops));
    // rep(i, K) outputFile<< crops[i].le SP << crops[i].ri <<endl;
    // cout<< K << endl;
    // int su=0;
    // for (int i = 0; i < K; ++i){
    //     su+=D[i]-S[i]+1;
    //     // cout<< S[i] SP << D[i] <<endl;
    // }
    // cout<< su <<endl;

    // vector<int> count(110);
    // for (int i = 0; i < K; ++i){
    //     count[D[i]-S[i]+1]++;
    // }
    // PV(count);
    // exit(0);
}

int main(){
    start = chrono::system_clock::now();
    plans.resize(101);
    rep(i, 101) plans[i].resize(101);
    inpt();
    Space space, best;
    space.init();
    space.calc_highest_pos_idx();
    space.calc_board_ng_place();
    // PVV(space.board);
    space.find_placement(true);
    space.find_placement(false);
    space.make_tree();
    // rep(i, H*W){
    //     cout<< endl;
    //     itop(i).print();
    //     cout<< "parent: " << space.blocking_tree[i].parent <<endl;
    //     cout<< "child: ";
    //     PV(space.blocking_tree[i].child);
    // }
    // PVV(space.board);
    space.calc_dependent_depth();
    // rep(i, H*W){
    //     itop(space.hatake_priority[i].index).print();
    //     cout<< space.hatake_priority[i].dist <<endl;
    // }
    // space.interval_scheduling_all();
    space.hatake_scheduling(false);
    // rep(i, 100) space.scheduling();
    // space.hatake_scheduling(true);
    // space.print_ans();
    // PVV(space.blocking_tree);
    // PVV(space.board);
    // return 0;
    int loop=0;
    while(1){
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) {
            // break;
        }
        
        space.random_add_delete();
        loop++;
        // rep(i, 1000) space.scheduling();
        // if(space.score<best.score){
        //     space=best;
        // }
        // if(loop%1000==999){
            cout<< "standard loop: " << loop <<endl;
            cout<< "score: " << space.score SP << space.score*25 <<endl;
            
        //     // space.print_ans();
        // }
        if(best.score<space.score){
            best=space;
            // cout<< "loop: " << loop <<endl;
            // best.print_ans();
            // cout<< "score: " << space.score SP << space.score*25 <<endl;
        }
    }
    // cout<< space.score SP << space.score*25 <<endl;
    best.print_ans();

    return 0;
}

// ただし畑のマスが一斉に留守になるタイミングがあるならなんとかなる
// ふさがるマスが多いマスはあきらめる
// 2通り以上アクセスする方法があるマスはどうしよう

// 行き止まりに近いマスは長い区間の計画を使う
// 迷路の形を何回か試す

// ###
// AB#
// ###
// のような形のとき、BがS=5, D=10なら
// AがS=5, D=10なら最高
// AがS=7, D=10ならAのplant_tを5以下にしてもよい
// AがS=3, D=10ならBのplant_tを3以下にする必要がある
// AがS=5, D=9ならまあ許せる
// AがS=4, D=9ならBのplant_tを4以下にする必要がある
// AがS=6, D=9ならAのplant_tを6以下にしてもよい
// AがD=11なら無理