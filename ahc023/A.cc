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
// 	cout<< pvv[pvv.size()-1] <<endl;
// }

// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
// 		rep(j, pvv[i].size()-1){
// 			outputFile<< pvv[i][j] << ", ";
// 		}
// 		outputFile<< pvv[i][pvv[i].size()-1] <<endl;
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

struct itv{
	int le, ri;

	// 区間スケジュール的な、終わるのが早い順で始まるのが遅い順のソート用
	bool operator<(const itv &in) const{
		return ri!=in.ri ? ri<in.ri : le>in.le;
	};

	// 区間が重なっているかどうか（端点を含ませたい場合は<=を使う）
	bool cover(itv x, itv y){
		return max(x.le, y.le)<min(x.ri, y.ri);
	}
};
vector<itv> crops;

struct Placement{
    Pos pos={0, 0};
    int s=0;

    Placement(){};
    Placement(Pos ipos, int is){
        pos=ipos;
        s=is;
    }

    bool is_empty(){
        return (s==0);
    }
    void init(){
        assert(s!=0);
        pos={0, 0};
        s=0;
    }
    
    // 出力の時は1-indexにする
    void print(int index){
        cout<< index+1 SP << pos.h SP << pos.w SP << s <<endl;
    }
};

struct Space{
    vector<vector<int>> graph; // [400][0~4] [頂点idx][到達可能な頂点idx] 盤面の移動可否を計算するためのグラフ
    vector<vector<int>> board; // [20][20] [h][w] 常に畑とするマスが1、未定が0、通路にするのが-1
    vector<vector<int>> enter_dist; // 入口からの距離
    vector<int> highest_pos_idx; // 周りの4近傍のどのマスよりも入口から遠いマス
    // vector<vector<int>> blocking; // マスidが埋まっていると辿り着けないマスのidたち
    // ここから下の変数は直接触らない
    vector<Placement> placement; // 出力となる農耕計画
    bitset<8010> used_plan; // 使用した農耕プラン
    int plant[110][21][21]; // [T][H][W]=val番のplanで利用中、負の時は早く置いているとき、0以外が入っているときは使用中
    // int harvest[110][21][21];
    int score; // 現在のスコア、H*W*T=40000点満点

    void init(){
        score=0;
        rep(i, 110){
            rep(j, 21){
                rep(k, 21){
                    plant[i][j][k]=0;
                    // harvest[i][j][k]=0;
                }
            }
        }
        placement.resize(K);
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
            board[pos.h][pos.w]=-1;
            calc_ng_load(second_high_idx);
        }
        // PVV(board);
    }
    // 最短経路の通路を決める
    void calc_ng_load(int idx){
        int min_around_wall=555;
        int min_i;
        Pos cpos=itop(idx);
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
        calc_ng_load(min_idx);
    }

    // boardを渡し、すべてのマスに到達できるかを算出
    bool reachable_all(vector<vector<int>> &bor){
        vector<vector<int>> current_graph=graph;
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

    // void random_add_delete(){
    //     int plan_idx;
    //     if(mt()%2){
    //         while(1){
    //             plan_idx=mt()%K;
    //             if(used_plan[plan_idx]) continue;
    //         }

    //     }else{
    //         while(1){
    //             plan_idx=mt()%K;
    //             if(!used_plan[plan_idx]) continue;
    //         }
    //     }
    // }

    void add_schedule(int plan_idx, Pos Plan_pos, int plant_t){
        assert(placement[plan_idx].is_empty());
        placement[plan_idx]={Plan_pos, plant_t};
        assert(!used_plan[plan_idx]);
        used_plan.set(plan_idx);
        rep3(i, S[plan_idx], plant_t){
            assert(plant[i][Plan_pos.h][Plan_pos.w]==0);
            // assert(harvest[i][Plan_pos.h][Plan_pos.w]==0);
            plant[i][Plan_pos.h][Plan_pos.w]=plan_idx;
            // harvest[i][Plan_pos.h][Plan_pos.w]=plan_idx;
        }
        rep3(i, D[plan_idx]+1, S[plan_idx]){
            assert(plant[i][Plan_pos.h][Plan_pos.w]==0);
            // assert(harvest[i][Plan_pos.h][Plan_pos.w]==0);
            plant[i][Plan_pos.h][Plan_pos.w]=plan_idx;
            // harvest[i][Plan_pos.h][Plan_pos.w]=plan_idx;
        }
        score+=D[plan_idx]-S[plan_idx]+1;
        assert(0<=score);
        assert(score<=40000);
    }
    // 後で計算量を削減したくなったらplan_posを渡さなくてよくする
    void delete_schedule(int plan_idx, Pos Plan_pos){
        assert(placement[plan_idx].pos==Plan_pos); // 消そうとしているものの座標がちゃんと把握できているかを念のため確認
        placement[plan_idx].init();
        assert(used_plan[plan_idx]);
        used_plan.reset(plan_idx);
        for(int i=S[plan_idx]-1;i>0;i--){
            if(plant[i][Plan_pos.h][Plan_pos.w]<0) plant[i][Plan_pos.h][Plan_pos.w]=0;
            else break;
            // if(harvest[i][Plan_pos.h][Plan_pos.w]<0) harvest[i][Plan_pos.h][Plan_pos.w]=0;
            // else break;
        }
        rep3(i, D[plan_idx]+1, S[plan_idx]){
            assert(plant[i][Plan_pos.h][Plan_pos.w]!=0);
            // assert(harvest[i][Plan_pos.h][Plan_pos.w]!=0);
            plant[i][Plan_pos.h][Plan_pos.w]=0;
            // harvest[i][Plan_pos.h][Plan_pos.w]=plan_idx;
        }
        score-=D[plan_idx]-S[plan_idx]+1;
        assert(0<=score);
        assert(score<=40000);
    }
    void print_ans(){
        cout<< used_plan.count() <<endl;
        rep(lp, K){
            if(placement[lp].s){
                placement[lp].print(lp);
            }
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
    crops.resize(K);
    for (int i = 0; i < K; ++i){
        cin >> S[i] >> D[i];
        crops[i]={S[i], D[i]};
    }

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
    inpt();
    Space space;
    space.init();
    space.calc_highest_pos_idx();
    space.calc_board_ng_place();
    space.find_placement(true);
    space.find_placement(false);
    // PVV(space.board);
    space.interval_scheduling_all();
    // cout<< space.score SP << space.score*25 <<endl;
    space.print_ans();

    return 0;
}

// 畑確定のマスはなにも制約がない
// 通路のマスは自分がいるとふさがるマスの制約を守る
  // ただし畑のマスが一斉に留守になるタイミングがあるならなんとかなる
  // ふさがるマスが多いマスはあきらめる
  // 2通り以上アクセスする方法があるマスはどうしよう
  // 時刻tのときにアクセスできる必要があるマスの一覧と、盤面の状態がほしい
  // これがあればひとまず設置可能かどうかの判定はできる
  // 各マスについてbitset<T>でブロッキング時間とアクセスしたい時間を管理できるとよさそう
// 通路になっているマスの入口からの距離が極大なマスから最短距離を求める。遡っている途中で進行方向以外の3近傍になったマスは畑・通路すべて自分のふさぐ範囲