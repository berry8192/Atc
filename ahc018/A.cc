// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

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

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;
// int excavation_count=0; //testtest
// int score=0; //testtest

// 構造体
struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2

    UnionFind(int N) : par(N) { //最初は全てが根であるとして初期化
        for(int i = 0; i < N; i++) par[i] = i;
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx>ry) swap(rx, ry); // 超頂点を優先
        par[rx] = ry; //xの根rxをyの根ryにつける
    }

    bool same(int x, int y) { // 2つのデータx, yが属する木が同じならtrueを返す
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }
};

struct Pos{
    int y;
    int x;

    Pos(){};
    Pos(int yy, int xx){
        y=yy;
        x=xx;
    }
    // int weight(){
    //     //cout<< "weight" <<endl;
    //     return (x-n/2)*(x-n/2)+(y-n/2)*(y-n/2)+1;
    // }
    int get_id(){
        return y*200+x;
    }
    bool is_out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        if(x<0 || 199<x || y<0 || 199<y){
            // cout<< "y, x " << y SP << x <<endl;
        }
        return (x<0 || 199<x || y<0 || 199<y);
    }
    int manhattan(Pos a){
        //cout<< "manhattan" <<endl;
        if(a.is_out_of_bounce()){
            return 1000;
            // a.print();
            // assert(!a.is_out_of_bounce());
        }
        // if(is_out_of_bounce()){
        //     // print();
        //     assert(!is_out_of_bounce());
        // }
        return (abs(a.x-x)+abs(a.y-y));
    }

    // void print(){
    //     cout<< "(" << x << ", " << y << ")";
    // }
    friend ostream &operator<<(ostream &os, const Pos &d) {
        os << d.y << " " << d.x;
        return os;
    }

    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.x=x+pos.x;
        rtn.y=y+pos.y;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.x=x-pos.x;
        rtn.y=y-pos.y;
        return rtn;
    }
    void operator+=(const Pos pos){
        x+=pos.x;
        y+=pos.y;
    }
    bool operator<(const Pos &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
    bool operator==(const Pos &in) const{
		return x==in.x && y==in.y;
	};
};
Pos d4[]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

struct Excavator{
    Pos pos; // 現在地
    double direction; // 次の掘削地
    int prio; // 掘削優先度
    int relate; // 出発地にあった水源家をbit列

    bool operator<(const Excavator& in) const {
        return prio < in.prio;
    }
};

//グローバル
int N, W, K, C;
// int S[210][210]; //testtest
vector<int> a, b, c, d;
Pos water[4], house[10];
UnionFind uf(40010);
int HYPER_V_IDX =40000;
int need_power[200][200];
int is_broken[200][200];

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}
template <class T> void PS(T ps) {
    cout<< "{";
	for(auto itr = ps.begin(); itr != ps.end(); ++itr) cout<< *itr SP;
	cout<< "}" <<endl;
}

void set_hyper_v_set(){
    rep(i, W){
        uf.par[water[i].get_id()]=HYPER_V_IDX;
    }
}

// ジャッジ
// bool does_water_complete(){
//     int cnt=0;
//     rep(i, K){
//         int id=c[i]*N+d[i];
//         if(uf.par[id]==HYPER_V_IDX) cnt++;
//     }
//     return (cnt==K);
// }
void merge_uf(Pos pos){
    // 繋がっていればつなげる
    int id=pos.get_id();
    rep(i, 4){
        Pos npos=pos+d4[i];
        if(npos.is_out_of_bounce()){
            continue;
        }
        int nid=npos.get_id();
        uf.unite(id, nid);
    }
}
//testtest
// int excavation_local(int y, int x, int power){
//     excavation_count++;
//     score+=C+power;
//     if(S[y][x]<=0){
//         cout<< "S[y][x]<=0" <<endl;
//         return -1;
//     }
//     S[y][x]-=power;
//     if(S[y][x]>0) return 0;

//     merge_uf(y, x);

//     if(does_water_complete()) return 2;
//     else return 1;
// }
int excavation(Pos pos, int power){
    // excavation_count++;
    // score+=C+power;
    assert(!pos.is_out_of_bounce());
    // assert(power>0);
    power=min(5000, power);
    power=max(10, power);
    assert(is_broken[pos.y][pos.x]==0);
    cout<< pos SP << power <<endl;
    int tmp;
    cin>> tmp;

    if(tmp==0){
        return 0;
    }else if(tmp==1){
        merge_uf(pos);
        is_broken[pos.y][pos.x]=1;
        return 1;
    }else{
        // -1か2が返ってきたら勝手にプログラムを終了する
        if(tmp==-1) cout<< "return -1 from excavation." <<endl;
        exit(0);
    }
}
void break_bedrock(Pos pos, int power=20){
    assert(!pos.is_out_of_bounce());
    // assert(power>0);
    // assert(power<=5000);
    if(is_broken[pos.y][pos.x]) return;
    int cost=0;
    while(1){
        cost+=power;
        if(excavation(pos, power)) break;
        power*=2;
    }
    need_power[pos.y][pos.x]=cost;
}
void straight_connect(Pos pos1, Pos pos2){
    // cout<< "straight_connect" << endl;
    Pos npos=pos1;
    int dir=0;
    int power=need_power[npos.y][npos.x];
    while(1){
        power=need_power[npos.y][npos.x]*9/10;
        // cout<< npos <<endl;
        if((npos+d4[dir]).manhattan(pos2)<npos.manhattan(pos2)){
            break_bedrock(npos+d4[dir], power);
            npos+=d4[dir];
            if(npos==pos2) break;
        }
        dir=(dir+1)%4;
    }
}
void simple_straight_connect(){
    rep(i, K){
        int mi=500;
        int midx;
        int type;
        rep(j, W){
            if(mi>house[i].manhattan(water[j])){
                mi=house[i].manhattan(water[j]);
                midx=j;
                type=1;
            }
        }
        rep(j, i){
            if(mi>house[i].manhattan(house[j])){
                mi=house[i].manhattan(house[j]);
                midx=j;
                type=0;
            }
        }
        if(type==1) straight_connect(water[midx], house[i]);
        else straight_connect(house[midx], house[i]);
    }
}

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> N >> W >> K >> C;
    // rep(i, 200){
    //     rep(j, 200){
    //         cin>> S[i][j];
    //     }
    // }
    a.resize(W);
    b.resize(W);
    c.resize(K);
    d.resize(K);
    rep(i, W){
        cin>> a[i] >> b[i];
        water[i]=Pos(a[i], b[i]);
    }
    rep(i, K){
        cin>> c[i] >> d[i];
        house[i]=Pos(c[i], d[i]);
    }
}

void init(){
    inpt();
    set_hyper_v_set();
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    init();

    // rep(i, W) break_bedrock(water[i]);
    rep(i, K) break_bedrock(house[i]);

    

    return 0;
}
