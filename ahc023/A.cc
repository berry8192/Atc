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
    int k;
    Pos pos;
    int s;

    Placement(){};
    Placement(int ik, Pos ipos, int is){
        k=ik;
        pos=ipos;
        s=is;
    }
    
    void print(){
        cout<< k SP << pos.h SP << pos.w SP << s <<endl;
    }
};

struct Space{
    vector<vector<int>> graph;
    vector<Placement> placement;

    void init(){
        create_graph();
        calc_dist_from_enter();
    }

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
    void calc_dist_from_enter(){
        vector<vector<int>> enter_dist(H, vector<int>(W, -1));
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
    bool reachable_all(vector<vector<int>> &bor){
        vector<vector<int>> current_graph=graph;
        vector<vector<int>> enter_dist(H, vector<int>(W, -1));
        bitset<400> reached;
        queue<Pos> q;
        q.push({i0, 0});
        enter_dist[i0][0]=0;
        int count=0;
        while(!q.empty()){
            Pos pos=q.front();
            int pindex=pos.index();
            q.pop();
            if(bor[pos.h][pos.w]==1) continue;
            rep(i, graph[pindex].size()){
                Pos npos=itop(graph[pindex][i]);
                reached.set(graph[pindex][i]);
                if(enter_dist[npos.h][npos.w]==-1){
                    enter_dist[npos.h][npos.w]=enter_dist[pos.h][pos.w]+1;
                    q.push(npos);
                }
            }
        }
        // outputFile<< reached.count() <<endl;
        // PVV(enter_dist);
        return (reached.count()==H*W);
    }
    void find_placement(){
        vector<vector<int>> board(H, vector<int>(W));
        vector<int> perm(H*W);
        rep(i, H*W) perm[i]=i;
        shuffle(all(perm), mt);
        rep(i, H*W){
            Pos pos=itop(perm[i]);
            board[pos.h][pos.w]=1;
            if(!reachable_all(board)) board[pos.h][pos.w]=0;
        }
        // PVV(board);
        int count=0;
        rep(i, H){
            rep(j, W){
                if(board[i][j]) count++;
            }
        }
        cout<< count <<endl;
        rep(i, H){
            rep(j, W){
                if(board[i][j]) cout<< i*W+j+1 SP << i SP << j SP << 1 <<endl;
            }
        }
    }
    void interval_scheduling(int index){

    }
    void print_ans(){
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

    // sort(all(crops));
    // rep(i, K) outputFile<< crops[i].le SP << crops[i].ri <<endl;
    // cout<< K << endl;
    // int su=0;
    // for (int i = 0; i < K; ++i){
    //     su+=D[i]-S[i]+1;
    //     // cout<< S[i] SP << D[i] <<endl;
    // }
    // cout<< su <<endl;
}

int main(){
    inpt();
    Space space;
    space.init();
    space.find_placement();

    return 0;
}
