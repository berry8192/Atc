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
int EXCA_WIDTH=8;
int min_power, max_power, giveup_lim;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;
// int excavation_count=0; //testtest
// int score=0; //testtest
double MIN_POWER=4.391397971474189;
double MAX_POWER=37.74416489497335;
double BREAK_BEDROCK_POWER=2.194430142018194;
double KNOWN_BREAK_BASE=12.056256062319171;
double KNOWN_BREAK_TIMES=3.970286600604079;
double KNOWN_BREAK_POWER=4.342452012187933;
double ELSE_DIV=5.73617925099027;
double ELSE_TIMES=2.8015568122342565;
double BINARY_BASE=15.690267222036338;
double BINARY_POWER_DIV=2.9331652601756897;
double DIST_DEL=19.874474646189807;
double GEN_EXCA_BASE=10.69064404923651;
double GEN_EXCA_DIV=5.382294298890818;
double GEN_EXCA_LOG=9.569735594685051;
double GEN_EXCA_DIV_TIMES=2.6497439302656725;
double GEN_EXCA_BASE_TIMES=1.6753105606676344;
double IF_PRIO_TIMES=1.6511419573010544;
double IF_PRIO_ADD=-9.150698072195603;
double IF_POWER_TIMES=1.085667823945677;
double IF_POWER_ADD=-7.967345057084337;
double ELSE_PRIO_TIMES=1.7786317700659156;
double ELSE_PRIO_ADD=-0.44060505969990194;
double ELSE_POWER_TIMES=2.5318440510254265;
double ELSE_POWER_ADD=-3.9977742891019368;
double GIVEUP_BASE=123.73135742311537;
double GIVEUP_DIV=426.88848283732597;
double GIVE_UP_LOG=25.012586159651377;
double EXCA_WIDTH_BASE=7.891676275199719;
double EXCA_WIDTH_TIMES=1.9609223631145543;

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
    Pos midpos(const Pos pos){
        Pos rtn;
        rtn.x=(x+pos.x)/2;
        rtn.y=(y+pos.y)/2;
        return rtn;
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
    Pos operator*(const int a){
        Pos rtn;
        rtn.x=x*a;
        rtn.y=y*a;
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
Pos d8[]={{0, 2}, {-1, 1}, {-2, 0}, {-1, -1}, {0, -2}, {1, -1}, {2, 0}, {1, 1}};

struct Excavator{
    Pos pos; // 現在地
    double prio; // 掘削優先度
    int power;
    int par; // 出発地にあった水源or家のid
    Pos prepos;

    Excavator(){};
    Excavator(Pos ipos, double iprio, int ipower, int ipar, Pos ipre){
        pos=ipos;
        prio=iprio;
        power=ipower;
        par=ipar;
        prepos=ipre;
    }

    bool operator<(const Excavator& in) const {
        return prio > in.prio;
    }
    friend ostream &operator<<(ostream &os, const Excavator &e) {
        os << "pos: " << e.pos << " prio: " << e.prio << " power: " << e.power << " parent: " << e.par << " prepos: " << e.prepos;
        return os;
    }
};

struct Edge{
    Excavator from;
    Excavator to;
    int dist;

    Edge(){};
    Edge(Excavator ifrom, Excavator ito, int idist){
        from=ifrom;
        to=ito;
        dist=idist;
    }

    bool operator<(const Edge& in) const {
        return dist < in.dist;
    }
    // friend ostream &operator<<(ostream &os, const Excavator &e) {
    //     os << "pos: " << e.pos << " prio: " << e.prio << " power: " << e.power << " parent: " << e.par << " prepos: " << e.prepos;
    //     return os;
    // }
};

//グローバル
int N, W, K, C;
// int S[210][210]; //testtest
vector<int> a, b, c, d;
Pos water[4], house[10];
UnionFind uf(15);
bool united[15];
bool does_get_water[10];
bool complete_make_path;
int HYPER_V_IDX=14;
int need_power[200][200];
int is_broken[200][200];
// int made_exca[200][200];
priority_queue<Excavator> excavatores;
map<Pos, vector<Excavator>> exca_map;
vector<pair<Pos, Pos>> path_list;
int step_sum=0;

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
        uf.par[i]=HYPER_V_IDX;
    }
    // rep(i, W+K) cout<< uf.par[i] <<endl;
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
// void merge_uf(Pos pos){
//     // 繋がっていればつなげる
//     int id=pos.get_id();
//     rep(i, 4){
//         Pos npos=pos+d4[i];
//         if(npos.is_out_of_bounce()){
//             continue;
//         }
//         int nid=npos.get_id();
//         uf.unite(id, nid);
//     }
// }
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
int excavation(Pos pos, int power, int &cost){
    step_sum++;
    // excavation_count++;
    // score+=C+power;
    assert(!pos.is_out_of_bounce());
    // assert(power>0);
    power=min(max_power, power);
    power=max(min_power, power);
    cost+=power;
    if(is_broken[pos.y][pos.x]!=0){
        cout<< pos << " is broken. " << is_broken[pos.y][pos.x] <<endl;
        assert(is_broken[pos.y][pos.x]==0);
    }
    cout<< pos SP << power <<endl;
    int tmp;
    cin>> tmp;

    if(tmp==0){
        return 0;
    }else if(tmp==1){
        // merge_uf(pos);
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
    power=max(min_power, power);
    while(1){
        power=min(power, 5000-cost);
        if(excavation(pos, power, cost)) break;
        power*=BREAK_BEDROCK_POWER;
    }
    need_power[pos.y][pos.x]=cost;
}
// void break_known_bedrock(Pos pos, int power=20){
//     // cout<< "#break_known_bedrock " << pos SP << power <<endl;
//     assert(!pos.is_out_of_bounce());
//     // assert(power>0);
//     // assert(power<=5000);
//     if(is_broken[pos.y][pos.x]) return;
//     int cost=0;
//     // power=max(mi, power*C/128);
//     power=max(min_power, power);
//     int cnt=0;
//     while(1){
//         if(excavation(pos, power, cost)) break;
//         cnt++;
//         // if(cnt%(128/C)==0) power*=2;
//         if(10-int(log2(C))<=cnt) power*=2;
//         else power=power/5+int(log2(C));
//     }
//     need_power[pos.y][pos.x]=cost;
// }
void straight_break_known_bedrock(Pos pos, int power=20){
    assert(!pos.is_out_of_bounce());
    // assert(power>0);
    // assert(power<=5000);
    if(is_broken[pos.y][pos.x]) return;
    int cost=0;
    power=max(min_power, power);
    int cnt=0;
    while(1){
        if(excavation(pos, power, cost)) break;
        cnt++;
        if(KNOWN_BREAK_BASE-int(log2(C)*KNOWN_BREAK_TIMES)<=cnt) power*=KNOWN_BREAK_POWER;
        else power=max(min_power, int(power/ELSE_DIV+int(log2(C)*ELSE_TIMES)));
    }
    need_power[pos.y][pos.x]=cost;
}

void binary_connect(Pos pos1, Pos pos2){
    straight_break_known_bedrock(pos1, BINARY_BASE);
    straight_break_known_bedrock(pos2, BINARY_BASE);
    int dist=pos1.manhattan(pos2);
    // int width=Pos({pos1.y, pos2.x}).manhattan({pos2.y, pos1.x});
    // cout<< "#binary connect " << pos1 SP << pos2 <<endl;
    if(pos1==pos2) return;
    // cout<< "#manhattan" <<endl;
    if(dist<=1) return;
    // cout<< "#midpos" <<endl;
    Pos npos=pos1.midpos(pos2);
    if(npos==pos1 || npos==pos2){
        npos={pos1.y, pos2.x};
    }
    // assert(need_power[pos1.y][pos1.x]!=0);
    // assert(need_power[pos2.y][pos2.x]!=0);
    int power=need_power[pos1.y][pos1.x]+need_power[pos2.y][pos2.x];
    power=power/BINARY_POWER_DIV;
    if(dist>EXCA_WIDTH+DIST_DEL) power=(power+(dist-EXCA_WIDTH-1)*min_power)/(dist-EXCA_WIDTH);
    straight_break_known_bedrock(npos, power);
    binary_connect(pos1, npos);
    binary_connect(pos2, npos);
}
// void straight_connect(Pos pos1, Pos pos2){
//     // cout<< "straight_connect" << endl;
//     if(pos1==pos2) return;
//     Pos npos=pos1;
//     int dir=0;
//     int power=max(10, need_power[npos.y][npos.x]);
//     straight_break_known_bedrock(npos, power);
//     int cnt=1;
//     while(1){
//         cnt++;
//         if(cnt==10000) exit(0);
//         // cout<< "# connecting" << npos <<endl;
//         // cout<< npos <<endl;
//         // int delta=need_power[pos2.y][pos2.x]-need_power[npos.y][npos.x];
//         // delta/=2;
//         int delta=0;
//         power=need_power[npos.y][npos.x]*9/10+delta;
//         if((npos+d4[dir]).manhattan(pos2)<npos.manhattan(pos2)){
//             straight_break_known_bedrock(npos+d4[dir], power);
//             npos+=d4[dir];
//             if(npos==pos2) break;
//         }
//         dir=(dir+1)%4;
//     }
// }
// void simple_straight_connect(){
//     rep(i, K){
//         int mi=500;
//         int midx;
//         int type;
//         rep(j, W){
//             if(mi>house[i].manhattan(water[j])){
//                 mi=house[i].manhattan(water[j]);
//                 midx=j;
//                 type=1;
//             }
//         }
//         rep(j, i){
//             if(mi>house[i].manhattan(house[j])){
//                 mi=house[i].manhattan(house[j]);
//                 midx=j;
//                 type=0;
//             }
//         }
//         if(type==1) straight_connect(water[midx], house[i]);
//         else straight_connect(house[midx], house[i]);
//     }
// }

void break_all_house_bedrock(){
    rep(i, K) break_bedrock(house[i]);
}

void break_all_water_bedrock(){
    rep(i, W) break_bedrock(water[i]);
}

void dfs_make_path(Excavator exca){
    // cout<< "# dfs_make_path " << exca <<endl;
    path_list.push_back({exca.pos, exca.prepos});
    // break_known_bedrock(exca.pos, 15);
    // break_known_bedrock(exca.prepos, 15);
    if(exca.par<W){
        if(exca.prepos==water[exca.par]) return;
    }else{
        if(exca.prepos==house[exca.par-W]) return;
    }
    if(!(exca.prepos==exca_map[exca.prepos][0].pos)){
        path_list.push_back({exca.prepos, exca_map[exca.prepos][0].pos});
        // break_known_bedrock(exca.prepos, 15);
        // break_known_bedrock(exca_map[exca.prepos][0].pos, 15);
    }
    dfs_make_path(exca_map[exca.prepos][0]);
}

void set_exca_map(Excavator exca){
    // cout<< "set_exca_map " << exca <<endl;
    int y1=max(0, exca.pos.y-EXCA_WIDTH);
    int y2=min(199, exca.pos.y+EXCA_WIDTH+1); // 隙間をなくすため下に1つずらす
    int x1=max(0, exca.pos.x-EXCA_WIDTH);
    int x2=min(199, exca.pos.x+EXCA_WIDTH);
    // cout<< y1 SP << y2 SP << x1 SP << x2 <<endl;
    for(int i=y1;i<=y2;i++){
        for(int j=x1;j<=x2;j++){
            Pos npos(i, j);
            if(exca.pos.manhattan(npos)<EXCA_WIDTH || (exca.pos.manhattan(npos)==EXCA_WIDTH && exca.pos.y<i)){
                if(exca_map[npos].size()){
                    Excavator target=exca_map[npos][0];
                    // cout<< "match exca_map " << target <<endl;
                    int native_root=uf.root(target.par);
                    int visitor_root=uf.root(exca.par);
                    if(native_root==HYPER_V_IDX && visitor_root==HYPER_V_IDX) continue; // 両方の親に水源がいるならそもそもくっつける必要がない
                    if(native_root==visitor_root){
                        continue; // 既にくっついているもの同士が出会ったときはくっつける必要がない
                        // cout<< "same par: " << exca.par <<endl;
                        // assert(target.par!=exca.par);
                    }
                    // cout<< "# native_id: " << target.par <<endl;
                    // cout<< "# native_root: " << native_root <<endl;
                    // cout<< "# visitor_id: " << exca.par <<endl;
                    // cout<< "# visitore_root: " << visitor_root <<endl;

                    // パスを作る必要があるのは今までどこかとくっついたことがない水源家の方、両方かもしれないし両方違ううかもしれない4通り
                    // 道のりを逆順にたどってパスをつくる
                    if(1 || !united[target.par]){
                        // cout<< "# native dfs" <<endl;
                        dfs_make_path(target);
                        united[target.par]=true;
                    }
                    // 道のりを逆順にたどってパスをつくる
                    if(1 || !united[exca.par]){
                        // cout<< "# visitor dfs" <<endl;
                        dfs_make_path(exca);
                        united[exca.par]=true;
                    }
                    // 先端の点同士を結ぶpathも必要
                    // cout<< "# direct connect " << exca.pos SP << target.pos <<endl;
                    if(!(exca.pos==target.pos)) path_list.push_back({exca.pos, target.pos});
                    // break_known_bedrock(exca.pos, 15);
                    // break_known_bedrock(target.pos, 15);
                    uf.unite(target.par, exca.par);
                    int cnt=0;
                    rep(i, K){
                        if(uf.root(W+i)==HYPER_V_IDX){
                            does_get_water[i]=true;
                            cnt++;
                        }
                    }
                    if(cnt==K){
                        complete_make_path=true;
                        // return true;
                    }
                }else{
                    exca_map[npos].emplace_back(exca);
                    // break_bedrock(npos);
                }
            }
        }
    }
    // return false;
}

void gen_exavator(Excavator exca){
    // cout<< "gen_exavator " << exca <<endl;
    rep(i, 8){
        Pos npos=exca.pos+d8[i]*EXCA_WIDTH;
        if(npos.is_out_of_bounce()) continue;
        if(!exca_map[npos].empty()){
            Excavator native=exca_map[npos][0];
            // 自分が既に行った場所には2度いかない
            if(native.par==exca.par) continue;
            // 自分と親が同じ掘削機が既に行った場所には2度いかない
            if(uf.root(native.par)==uf.root(exca.par)){
                continue;
                // if(native.pos.manhattan(npos)<EXCA_WIDTH/2) continue;
            }
        }
        // is_broken[npos.y][npos.x]=1;
        // 行った先に家水源が居なさそうなら行かない
        // int ikanai=1;
        // rep(i, W){
        //     if(exca.par==i) continue;
        //     if(uf.root(exca.par)==uf.root(i)) continue;
        //     ikanai*=(water[i].manhattan(npos)-water[i].manhattan(exca.pos)<0);
        // }
        // rep(i, K){
        //     if(exca.par==i+W) continue;
        //     if(uf.root(exca.par)==uf.root(i+W)) continue;
        //     ikanai*=(house[i].manhattan(npos)-house[i].manhattan(exca.pos)<0);
        // }
        Excavator nexca(npos, exca.prio, exca.power, exca.par, exca.pos);
        // Excavator nexca(npos, exca.prio*(1+ikanai*3), exca.power, exca.par, exca.pos);
        excavatores.push(nexca);
        set_exca_map(nexca);
    }
}

void gen_all_excavator(){
    int base=GEN_EXCA_BASE+C/GEN_EXCA_DIV+log2(C)*GEN_EXCA_LOG;
    rep(i, W){
        // int nedpow=+need_power[water[i].y][water[i].x];
        gen_exavator({water[i], double(base)*GEN_EXCA_DIV_TIMES, base*GEN_EXCA_BASE_TIMES, i, water[i]});
    }
    rep(i, K){
        gen_exavator({house[i], double(base)*GEN_EXCA_DIV_TIMES, base*GEN_EXCA_BASE_TIMES, W+i, house[i]});
    }
}

void giveup_smart(){
    vector<Edge> edges;
    vector<Excavator> vex;
    set<Pos> st;
    rep(i, W){
        vex.push_back({water[i], 0, 0, i, water[i]});
    }
    rep(i, K){
        vex.push_back({house[i], 0, 0, i+W, house[i]});
    }
    rep(i, 200){
        rep(j, 200){
            if(!exca_map[{i, j}].empty()){
                if(st.find(exca_map[{i, j}][0].pos)==st.end()){
                    vex.push_back(exca_map[{i, j}][0]);
                    st.insert(exca_map[{i, j}][0].pos);
                }
            }
        }
    }
    rep(i, vex.size()){
        rep3(j, vex.size(), i+1){
            Excavator exca1=vex[i];
            Excavator exca2=vex[j];
            edges.push_back({exca1, exca2, exca1.pos.manhattan(exca2.pos)});
        }
    }
    sort(all(edges));
    rep(i, edges.size()){
        if(uf.root(edges[i].from.par)!=uf.root(edges[i].to.par)){
            uf.unite(edges[i].from.par, edges[i].to.par);
            path_list.push_back({edges[i].from.pos, edges[i].to.pos});
            dfs_make_path(edges[i].from);
            dfs_make_path(edges[i].to);
        }
    }
}

void exec_exca(){
    // cout<< "exec excavator" <<endl;
    while(!excavatores.empty()){
        if(step_sum>=giveup_lim){
            giveup_smart();
            break;
        }
        Excavator exca=excavatores.top();
        excavatores.pop();
        if(complete_make_path) break;
        // cout<< exca <<endl;
        if(exca.par>=W && uf.root(exca.par)==HYPER_V_IDX) continue;
        if(is_broken[exca.pos.y][exca.pos.x]) continue;
        if(excavation(exca.pos, exca.power, need_power[exca.pos.y][exca.pos.x])==1){
            gen_exavator({exca.pos, exca.prio*IF_PRIO_TIMES+IF_PRIO_ADD, exca.power*IF_POWER_TIMES+IF_POWER_ADD, exca.par, exca.prepos});
        }else{
            excavatores.push({exca.pos, exca.prio*ELSE_PRIO_TIMES+ELSE_PRIO_ADD, exca.power*ELSE_POWER_TIMES+ELSE_POWER_ADD, exca.par, exca.prepos});
            // excavation(exca.pos, 5000); //
        }
    }
    // cout<< "failed exec excavator." <<endl;
}

void exec_path_excavation(){
    rep(i, path_list.size()){
        assert(!path_list[i].first.is_out_of_bounce());
        assert(!path_list[i].second.is_out_of_bounce());
        // straight_connect(path_list[i].first, path_list[i].second);
        binary_connect(path_list[i].first, path_list[i].second);
    }
}

void set_lim(){
    min_power=(int(log2(C)+2))*MIN_POWER;
    min_power=max(min_power, 3);
    max_power=C*MAX_POWER;
    max_power=min(max_power, 5000);
    giveup_lim=GIVEUP_BASE+128/C*GIVEUP_DIV+log2(C)*GIVE_UP_LOG;
}

void set_exca_width(){
    EXCA_WIDTH=EXCA_WIDTH_BASE+log2(C)*EXCA_WIDTH_TIMES;
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
    set_lim();
    set_exca_width();
}

void get_argv(int argc, char* argv[]){
    vector<double> args;
    rep3(i, argc, 1){
        string tmp;
        tmp.assign(argv[i]);
        args.push_back(stof(tmp));
        // cout<< args[i-1] <<endl;
    }
    MIN_POWER=args[0];
    MAX_POWER=args[1];
    BREAK_BEDROCK_POWER=args[2];
    KNOWN_BREAK_BASE=args[3];
    KNOWN_BREAK_TIMES=args[4];
    KNOWN_BREAK_POWER=args[5];
    ELSE_DIV=args[6];
    ELSE_TIMES=args[7];
    BINARY_BASE=args[8];
    BINARY_POWER_DIV=args[9];
    DIST_DEL=args[10];
    GEN_EXCA_BASE=args[11];
    GEN_EXCA_DIV=args[12];
    GEN_EXCA_LOG=args[13];
    GEN_EXCA_DIV_TIMES=args[14];
    GEN_EXCA_BASE_TIMES=args[15];
    IF_PRIO_TIMES=args[16];
    IF_PRIO_ADD=args[17];
    IF_POWER_TIMES=args[18];
    IF_POWER_ADD=args[19];
    ELSE_PRIO_TIMES=args[20];
    ELSE_PRIO_ADD=args[21];
    ELSE_POWER_TIMES=args[22];
    ELSE_POWER_ADD=args[23];
    GIVEUP_BASE=args[24];
    GIVEUP_DIV=args[25];
    GIVE_UP_LOG=args[26];
    EXCA_WIDTH_BASE=args[27];
    EXCA_WIDTH_TIMES=args[28];
}

int main(int argc, char* argv[]){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    init();
    get_argv(argc, argv);

    break_all_house_bedrock();
    break_all_water_bedrock();
    gen_all_excavator();
    exec_exca();
    exec_path_excavation();

    return 0;
}

