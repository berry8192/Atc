#pragma GCC target("avx")
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#include <experimental/filesystem>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
namespace fs = std::filesystem;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
int dir_h[]={0, -1, 0, 1}, dir_w[]={-1, 0, 1, 0};

//焼きなましの定数
double TIME_LIMIT=2980;
double start_temp=50.0;
double end_temp=10.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
//int seed=10;
mt19937 mt(seed);

// 構造体
struct UnionFind {
    vector<int> par; // par[i]:iの親の番号　(例) par[3] = 2 : 3の親が2
	vector<int> siz; // siz[i]:iの属する木に含まれる点の数

    void init(int N){ //最初は全てが根であるとして初期化
        par.resize(N);
        for(int i = 0; i < N; i++) par[i] = i;
		siz.resize(par.size(), 1); //最初は全てサイズ1
    }

    int root(int x) { // データxが属する木の根を再帰で得る：root(x) = {xの木の根}
        if (par[x] == x) return x;
        return par[x] = root(par[x]);
    }

	int tsize(int x){ // siz[x]の木の根を見に行き、サイズを返す
		return siz[root(x)];
	}

    void unite(int x, int y) { // xとyの木を併合
        int rx = root(x); //xの根をrx
        int ry = root(y); //yの根をry
        if (rx == ry) return; //xとyの根が同じ(=同じ木にある)時はそのまま
        if(siz[rx]<siz[ry]) swap(rx,ry);
        par[ry] = rx; //xとyの根が同じでない(=同じ木にない)時：xの根rxをyの根ryにつける
		siz[rx]+=siz[ry]; //根で管理
    }

    bool same(int x, int y){
        return root(x)==root(y);
    }
};

struct Pos{
    int h;
    int w;

    Pos(){};
    Pos(int x, int y){
        h=x;
        w=y;
    }
    void print(){
        cout<< "(" << h << ", " << w << ")";
    }
};

struct Num{
    int type;
    int idx;

    Num(){};
    Num(int x, int y){
        type=x;
        idx=y;
    }
    void print(){
        if(type>=0) printf("%02d", type);
        else cout<< type;
    }
};

struct Cpu{
    int fig;
    Pos pos;
    bool le=true, ri=true, up=true, dw=true;

    Cpu(){};
    Cpu(int x, Pos y){
        fig=x;
        pos=y;
    }
    void print(){
        cout<< fig SP;
        pos.print();
    }
};

//入力
int n, k;
vector<vector<Num>> c;
vector<Cpu> cpu;

struct Move{
    Pos from;
    Pos to;

    Move(){};
    Move(Pos x, Pos y){
        from=x;
        to=y;
    }
    void print(){
        from.print();
        cout<< "->";
        to.print();
    }
};

struct Cone{
    Pos from;
    Pos to;

    Cone(){};
    Cone(Pos x, Pos y){
        from=x;
        to=y;
    }
    void print(){
        from.print();
        cout<< "<->";
        to.print();
    }
};

struct Room{
    vector<vector<Num>> board;
    vector<Cpu> comp;
    vector<Move> mv;
    vector<Cone> co;
    UnionFind uf;
    vector<Pos> minus;
    int score=0;
    int mv_lim;
    int co_lim;
    int prf=0;

    Room(){
    }
    void init(){
        board=c;
        comp=cpu;
        uf.init(k*100);
        mv_lim=mt()%80+10;
        co_lim=mt()%6+95;
        mv.reserve(500);
        co.reserve(500);
        // rep(i, n){
        //     rep(j, n){
        //         if(board[i][j].type>0) cout<< board[i][j].idx SP;
        //     }
        //     cout<< endl;
        // }
    }
    int hand(){
        return mv.size()+co.size();
    }
    void add_mv(int x1, int y1, int x2, int y2, char di){
        int comp_idx=board[x1][y1].idx;
        // cout<< x1 SP << y1 SP << x2 SP << y2 <<endl;
        // comp[comp_idx].print();
        // cout<< endl;
        // 動かない場合を排除
        assert(!(x1==x2 && y1==y2));
        // 直線でない位置にいないか確認
        assert(!(x1!=x2 && y1!=y2));

        if(di=='D'){
            for(int i=x1;i<x2;i++){
                mv.emplace_back(Move{{i, y1}, {i+1, y1}});
                if(comp[comp_idx].up){
                    board[i][y1].type=-comp[comp_idx].fig;
                    minus.emplace_back(Pos{i, y1});
                }else board[i][y1].type=0;
            }
            comp[comp_idx].up=false;
            comp[comp_idx].dw=false;
        }else if(di=='U'){
            for(int i=x1;i>x2;i--){
                mv.emplace_back(Move{{i, y1}, {i-1, y1}});
                if(comp[comp_idx].dw){
                    board[i][y1].type=-comp[comp_idx].fig;
                    minus.emplace_back(Pos{i, y1});
                }else board[i][y1].type=0;
            }
            comp[comp_idx].up=false;
            comp[comp_idx].dw=false;
        }else if(di=='R'){
            for(int i=y1;i<y2;i++){
                mv.emplace_back(Move{{x1, i}, {x1, i+1}});
                if(comp[comp_idx].le){
                    board[x1][i].type=-comp[comp_idx].fig;
                    minus.emplace_back(Pos{x1, i});
                }else board[x1][i].type=0;
            }
            comp[comp_idx].le=false;
            comp[comp_idx].ri=false;
        }else{
            for(int i=y1;i>y2;i--){
                mv.emplace_back(Move{{x1, i}, {x1, i-1}});
                if(comp[comp_idx].ri){
                    board[x1][i].type=-comp[comp_idx].fig;
                    minus.emplace_back(Pos{x1, i});
                }else board[x1][i].type=0;
            }
            comp[comp_idx].le=false;
            comp[comp_idx].ri=false;
        }
        board[x2][y2]={comp[comp_idx].fig, comp_idx};
        comp[comp_idx].pos={x2, y2};
        
        //print_board();
    }
    void add_co(int x1, int y1, int x2, int y2){
        // if(x1==16 && y1==9 && x2==20 && y2==9){
        //     cout<< "!" <<endl;
        //     print_board();
        // }
        if(hand()>=k*co_lim) return;
        // cout<< x1 SP << y1 SP << x2 SP << y2 <<endl;
        int from=board[x1][y1].type;
        int to=board[x2][y2].type;
        //if(from!=to) return;
        // for文のために右か下方向に伸ばすようにする
        if(x1>x2) swap(x1, x2);
        if(y1>y2) swap(y1, y2);
        // 別の種類のコンピュータを繋ごうとしていないか確認
        //assert(from==to);
        // 同一コンピュータを繋ごうとしていないか確認
        //assert(!(x1==x2 && y1==y2));
        // 直線で結べない位置にいないか確認
        //assert(!(x1!=x2 && y1!=y2));
        // 間に負の値でケーブルをつなぐ
        if(x1!=x2){
            // 間をケーブルが通っていないか確認
            // rep3(i, x2, x1+1){
            //     assert(board[i][y1].type==0);
            // }
            rep3(i, x2, x1+1){
                board[i][y1].type=-from;
                minus.emplace_back(Pos{i, y1});
            }
            comp[board[x1][y1].idx].le=false;
            comp[board[x1][y1].idx].ri=false;
            comp[board[x2][y2].idx].le=false;
            comp[board[x2][y2].idx].ri=false;
        }else{
            // 間をケーブルが通っていないか確認
            // rep3(i, y2, y1+1){
            //     assert(board[x1][i].type==0);
            // }
            rep3(i, y2, y1+1){
                board[x1][i].type=-from;
                minus.emplace_back(Pos{x1, i});
            }
            comp[board[x1][y1].idx].up=false;
            comp[board[x1][y1].idx].dw=false;
            comp[board[x2][y2].idx].up=false;
            comp[board[x2][y2].idx].dw=false;
            // cout<< "banned lr " << x1 SP << y1 <<endl;
            // cout<< "banned lr " << x2 SP << y2 <<endl;
        }
        // coに追加
        co.emplace_back(Cone{{x1, y1}, {x2, y2}});
        uf.unite(board[x1][y1].idx, board[x2][y2].idx);
    }
    bool between_zero(int x1, int y1, int x2, int y2){
        if(x1!=x2){
            rep3(i, x2, x1+1){
                if(board[i][y1].type!=0) return false;
            }
        }else{
            rep3(i, y2, y1+1){
                if(board[x1][i].type!=0) return false;
            }
        }
        return true;
    }
    void nomove_connect(int num, int length){
        vector<int> perm3(k*100);
        rep(i, k*100) perm3[i]=i;
        shuffle(all(perm3), mt);

        rep(lp, k*100){
            // cout<< num << " nomove lp " << lp <<endl;
            int i=comp[perm3[lp]].pos.h;
            int j=comp[perm3[lp]].pos.w;
            int tmp=board[i][j].type;
            if(tmp!=num) continue;
            // if(tmp>1) continue;
            rep3(l, min(i+1+length, n), i+1){
                if(board[l][j].type==0){
                    continue;
                }else if(board[l][j].type==tmp){
                    if(!uf.same(board[i][j].idx, board[l][j].idx) && between_zero(i, j, l, j)){
                        add_co(i, j, l, j);
                    }
                    break;
                }else{
                    break;
                }
            }
            rep3(l, min(j+1+length, n), j+1){
                if(board[i][l].type==0){
                    continue;
                }else if(board[i][l].type==tmp){
                    if(!uf.same(board[i][j].idx, board[i][l].idx) && between_zero(i, j, i, l)){
                        add_co(i, j, i, l);
                    }
                    break;
                }else{
                    break;
                }
            }
        }
        //cout<< "end nomove" <<endl;
    }
    void nomove_connect_hw(int num, int length, char ty){
        vector<int> perm3(k*100);
        rep(i, k*100) perm3[i]=i;
        shuffle(all(perm3), mt);

        rep(lp, k*100){
            // cout<< num << " nomove lp " << lp <<endl;
            int i=comp[perm3[lp]].pos.h;
            int j=comp[perm3[lp]].pos.w;
            int tmp=board[i][j].type;
            if(tmp!=num) continue;
            // if(tmp>1) continue;
            if(ty=='D'){
                rep3(l, min(i+1+length, n), i+1){
                    if(board[l][j].type==0){
                        continue;
                    }else if(board[l][j].type==tmp){
                        if(!uf.same(board[i][j].idx, board[l][j].idx) && between_zero(i, j, l, j)){
                            add_co(i, j, l, j);
                        }
                        break;
                    }else{
                        break;
                    }
                }
            }else{
                rep3(l, min(j+1+length, n), j+1){
                    if(board[i][l].type==0){
                        continue;
                    }else if(board[i][l].type==tmp){
                        if(!uf.same(board[i][j].idx, board[i][l].idx) && between_zero(i, j, i, l)){
                            add_co(i, j, i, l);
                        }
                        break;
                    }else{
                        break;
                    }
                }
            }
        }
        //cout<< "end nomove" <<endl;
    }
    int cpu_slide(int num, int length, int dep){
        vector<int> perm2(k*100);
        rep(i, k*100) perm2[i]=i;
        shuffle(all(perm2), mt);
        int rdc=mv.size();

        rep(lp, k*100){
            int i=perm2[lp];
            if(comp[i].fig!=num) continue;
            if(mv.size()>=k*mv_lim) return 0;
            Pos pos=comp[i].pos;
        // pos.print();
        // cout<< endl;
            int flag=0;
            vector<int> perm;
            if(comp[i].le) perm.emplace_back(0);
            if(comp[i].up) perm.emplace_back(1);
            if(comp[i].ri) perm.emplace_back(2);
            if(comp[i].dw) perm.emplace_back(3);
            shuffle(all(perm), mt);
            rep(j, perm.size()){
                if(perm[j]==0){
                    // 左へ移動
                    for(int l=pos.w-1;l>=max(0, pos.w-length);l--){
                        if(board[pos.h][l].type==0 || board[pos.h][l].type==-comp[i].fig){
                            // 上側サーチ
                            for(int d=pos.h-1;d>=max(0, pos.h-dep);d--){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[d][l].type==comp[i].fig){
                                    if(!uf.same(i, board[d][l].idx)){
                                        add_mv(pos.h, pos.w, pos.h, l, 'L');
                                        //add_co(pos.h, l, d, l);
                                        flag=1;
                                        break;
                                    }
                                }else if(board[d][l].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                            // 下側サーチ
                            for(int d=pos.h+1;d<min(n, pos.h+dep);d++){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[d][l].type==comp[i].fig){
                                    if(!uf.same(i, board[d][l].idx)){
                                        add_mv(pos.h, pos.w, pos.h, l, 'L');
                                        //add_co(pos.h, l, d, l);
                                        flag=1;
                                        break;
                                    }
                                }else if(board[d][l].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                        }else{
                            break;
                        }
                    }
                    if(flag) break;
                }else if(perm[j]==1){
                    // 上へ移動
                    for(int l=pos.h-1;l>=max(0, pos.h-length);l--){
                        if(board[l][pos.w].type==0 || board[l][pos.w].type==-comp[i].fig){
                            // 左側サーチ
                            for(int d=pos.w-1;d>=max(0, pos.w-dep);d--){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[l][d].type==comp[i].fig){
                                    if(!uf.same(i, board[l][d].idx)){
                                        add_mv(pos.h, pos.w, l, pos.w, 'U');
                                        flag=1;
                                        break;
                                    }
                                }else if(board[l][d].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                            // 下側サーチ
                            for(int d=pos.w+1;d<min(n, pos.w+dep);d++){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[l][d].type==comp[i].fig){
                                    if(!uf.same(i, board[l][d].idx)){
                                        add_mv(pos.h, pos.w, l, pos.w, 'U');
                                        flag=1;
                                        break;
                                    }
                                }else if(board[l][d].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                        }else{
                            break;
                        }
                    }
                    if(flag) break;
                }else if(perm[j]==2){
                    // 右へ移動
                    for(int l=pos.w+1;l<min(n, pos.w+length);l++){
                        if(board[pos.h][l].type==0 || board[pos.h][l].type==-comp[i].fig){
                            // 上側サーチ
                            for(int d=pos.h-1;d>=max(0, pos.h-dep);d--){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[d][l].type==comp[i].fig){
                                    if(!uf.same(i, board[d][l].idx)){
                                        add_mv(pos.h, pos.w, pos.h, l, 'R');
                                        //add_co(pos.h, l, d, l);
                                        flag=1;
                                        break;
                                    }
                                }else if(board[d][l].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                            // 下側サーチ
                            for(int d=pos.h+1;d<min(n, pos.h+dep);d++){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[d][l].type==comp[i].fig){
                                    if(!uf.same(i, board[d][l].idx)){
                                        add_mv(pos.h, pos.w, pos.h, l, 'R');
                                        //add_co(pos.h, l, d, l);
                                        flag=1;
                                        break;
                                    }
                                }else if(board[d][l].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                        }else{
                            break;
                        }
                    }
                    if(flag) break;
                }else{
                    // 下へ移動
                    for(int l=pos.h+1;l<min(n, pos.h+length);l++){
                        if(board[l][pos.w].type==0 || board[l][pos.w].type==-comp[i].fig){
                            // 左側サーチ
                            for(int d=pos.w-1;d>=max(0, pos.w-dep);d--){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[l][d].type==comp[i].fig){
                                    if(!uf.same(i, board[l][d].idx)){
                                        add_mv(pos.h, pos.w, l, pos.w, 'D');
                                        flag=1;
                                        break;
                                    }
                                }else if(board[l][d].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                            // 下側サーチ
                            for(int d=pos.w+1;d<min(n, pos.w+dep);d++){
                                    //cout<< i SP << d SP << l <<endl;
                                if(board[l][d].type==comp[i].fig){
                                    if(!uf.same(i, board[l][d].idx)){
                                        add_mv(pos.h, pos.w, l, pos.w, 'D');
                                        flag=1;
                                        break;
                                    }
                                }else if(board[l][d].type!=0){
                                    break;
                                }
                            }
                            if(flag) break;
                        }else{
                            break;
                        }
                    }
                }
                    if(flag) break;
            }
        }
        return rdc-mv.size();
    }
    void easy_score(){
        // マイナス点が発生しない前提の得点計算
        vector<int> cnt(k*100);
        rep(i, k*100){
            cnt[uf.root(i)]++;
        }
        int rtn=0;
        rep(i, k*100) rtn+=cnt[i]*(cnt[i]-1)/2;
        score+=rtn;
    }
    int move_other(int num){
        int rdc=0;
        rep(i, k*100){
            if(comp[i].fig==num) continue;
            vector<int> di={0, 0, 0, 0};
            int ch=comp[i].pos.h;
            int cw=comp[i].pos.w;
            rep(j, 4){
                int l=1;
                while(0<=ch+dir_h[j]*l && ch+dir_h[j]*l<n && 0<=cw+dir_w[j]*l && ch+dir_w[j]*l<n){
                    if(board[ch+dir_h[j]*l][cw+dir_w[j]*l].type==num){
                        di[j]=1;
                        break;
                    }else if(board[ch+dir_h[j]*l][cw+dir_w[j]*l].type!=0) break;
                    l++;
                }
            }
            int okd=0;
            string dd="LURD";
            rep(j, 4){
                if(di[j]==1) okd++;
            }
            if(okd>=2){
                rep(j, 4){
                    if(di[j]==0 && 0<=ch+dir_h[j] && ch+dir_h[j]<n && 0<=cw+dir_w[j] && cw+dir_w[j]<n && board[ch+dir_h[j]][cw+dir_w[j]].type==0){
                        add_mv(ch, cw, ch+dir_h[j], cw+dir_w[j], dd[j]);
                        //cout<< ch SP << cw SP << ch+dir_h[j] SP << cw+dir_w[j] SP << dd[j] <<endl;
                        rdc++;
                        break;
                    }
                }
            }
        }
        return rdc;
    }
    void random_mv(int rnd){
        string dd="RDLU";
        int rn=mt()%(n*n);
        while(board[rn/n][rn%n].type!=0) rn=(rn+1)%(n*n);

        int rh=rn/n;
        int rw=rn%n;
        int prd=-1;
        rep(i, rnd){
            rep(j, 4){
                if(j==prd) continue;
                if(0<=rh+dir_h[j] && rh+dir_h[j]<n && 0<=rw+dir_w[j] && rw+dir_w[j]<n){
                    if(board[rh+dir_h[j]][rw+dir_w[j]].type>0){
                        add_mv(rh+dir_h[j], rw+dir_w[j], rh, rw, dd[j]);
                        rh+=dir_h[j];
                        rw+=dir_w[j];
                        prd=j;
                        break;
                    }
                }
            }
        }
    }
    void bridge(int notouch_sz, int nocon_sz, int mi_sco, vector<int> perm){
        int rdc=0;
        //vector<Bridge> di;
        rep(i, k*100){
            // ある程度でかい塊に所属しているCPUはノータッチ
            if(uf.siz[uf.root(i)]>=notouch_sz) continue;
            int ch=comp[i].pos.h;
            int cw=comp[i].pos.w;
            int con=0;
            rep(lp, k){
                int j=perm[lp];
                // cout<< "j=" << j <<endl;
                if(hand()>k*100-2) return;
                if(comp[i].fig==j) continue;
                // int ma=0;
                int pre_r=-1, psh, psw, psz;
                rep(di, 4){
                    int l=1;
                    int sh, sw;
                    while(0<=ch+dir_h[di]*l && ch+dir_h[di]*l<n && 0<=cw+dir_w[di]*l && cw+dir_w[di]*l<n){
                        sh=ch+dir_h[di]*l;
                        sw=cw+dir_w[di]*l;
                        if(board[sh][sw].type==0){
                            l++;
                            continue;
                        }else if(board[sh][sw].type==j){
                            int rt=uf.root(board[sh][sw].idx);
                            if(uf.siz[rt]>=nocon_sz) break;
                            if(pre_r==-1){
                                pre_r=rt;
                                psh=sh;
                                psw=sw;
                                psz=uf.siz[rt];
                            }else{
                                if(rt==pre_r) break;
                                int del=(psz+uf.siz[rt])*(psz+uf.siz[rt]-1)/2-psz*(psz-1)/2+uf.siz[rt]*(uf.siz[rt]-1)/2-uf.siz[uf.root(i)]*(uf.siz[uf.root(i)]-1)/2-uf.siz[uf.root(i)]*(psz+uf.siz[rt]);
                                //if(del>0) cout<< del <<endl;
                                if(del<mi_sco) break;
                                add_co(ch, cw, sh, sw);
                                add_co(ch, cw, psh, psw);
                                board[ch][cw].type=mt()%imax;
                                con=1;
                                score+=del;
                                prf+=del;
                            }
                            break;
                        }else{
                            break;
                        }
                    }
                    if(con) break;
                }
                if(con) break;
            }
        }
    }
    void lar(int p1, int p2, int itv){
        //int aim1=1;
        int aim2=2+itv/5;
        int rr, ph, pw;
        rep(i, k*100){
            ph=comp[i].pos.h;
            pw=comp[i].pos.w;
            rr=ph%itv;
            if(comp[i].fig==p1){
                if(rr==4){
                    if(ph<n-1 && board[ph+1][pw].type==0){
                        add_mv(ph, pw, ph+1, pw, 'D');
                    }
                }else if(rr==3){
                    if(0<ph && board[ph-1][pw].type==0){
                        add_mv(ph, pw, ph-1, pw, 'U');
                    }
                }
                if(rr==0 || rr==4){
                    if(ph<n-1 && board[ph+1][pw].type==0){
                        add_mv(ph, pw, ph+1, pw, 'D');
                    }
                }else if(rr==2 || rr==3){
                    if(0<ph && board[ph-1][pw].type==0){
                        add_mv(ph, pw, ph-1, pw, 'U');
                    }
                }
            }else if(comp[i].fig==p2){
                if(aim2==2){
                    if(rr==1){
                        if(ph<n-1 && board[ph+1][pw].type==0){
                            add_mv(ph, pw, ph+1, pw, 'D');
                        }
                    }else if(rr==0){
                        if(0<ph && board[ph-1][pw].type==0){
                            add_mv(ph, pw, ph-1, pw, 'U');
                        }
                    }
                }else{
                    if(rr==1 || rr==2){
                        if(ph<n-1 && board[ph+1][pw].type==0){
                            add_mv(ph, pw, ph+1, pw, 'D');
                        }
                    }else if(rr==0 || rr==4){
                        if(0<ph && board[ph-1][pw].type==0){
                            add_mv(ph, pw, ph-1, pw, 'U');
                        }
                    }
                    if(rr==1){
                        if(ph<n-1 && board[ph+1][pw].type==0){
                            add_mv(ph, pw, ph+1, pw, 'D');
                        }
                    }else if(rr==0){
                        if(0<ph && board[ph-1][pw].type==0){
                            add_mv(ph, pw, ph-1, pw, 'U');
                        }
                    }
                }
            }else{
                if(rr==1 || rr==aim2){
                    if(0<ph && board[ph-1][pw].type==0){
                        add_mv(ph, pw, ph-1, pw, 'U');
                    }
                    if(ph<n-1 && board[ph+1][pw].type==0){
                        add_mv(ph, pw, ph+1, pw, 'D');
                    }
                }
            }
        }
    }

    void print_board(){
        rep(i, n){
            rep(j, n){
                if(board[i][j].type<0) cout<< 0;
                else cout<< board[i][j].type;
            }
            cout<< endl;
        }
    }
    void print_out(){
        cout<< mv.size() <<endl;
        rep(i, mv.size()) cout<< mv[i].from.h SP << mv[i].from.w SP << mv[i].to.h SP << mv[i].to.w <<endl;
        cout<< co.size() <<endl;
        rep(i, co.size()) cout<< co[i].from.h SP << co[i].from.w SP << co[i].to.h SP << co[i].to.w <<endl;
    }
};

void inpt(){
    cin>> n >> k;
    c.resize(n);
    rep(i, n) c[i].resize(n);
    cpu.resize(k*100);
    int cnt=0;

    rep(i, n){
        string tmp;
        cin>> tmp;
        rep(j, n){
            int fig=int(tmp[j]-'0');
            c[i][j]=Num(fig, cnt);
            if(fig){
                cpu[cnt]={fig, {i, j}};
                cnt++;
            }
        }
    }
    // rep(i, k*100){
    //     comp[i].print();
    //     cout<< endl;
    // }
}

int score(Room room){
    int rtn=0;
    Room tes;
    //cout<< "init tes" <<endl;
    tes.init();
    //cout<< "calc score" <<endl;
    assert(room.hand()<=k*100);
    //cout<< "mv" <<endl;
    rep(i, room.mv.size()){
        int th=room.mv[i].to.h;
        int tw=room.mv[i].to.w;
        int fh=room.mv[i].from.h;
        int fw=room.mv[i].from.w;
        assert(abs(th-fh)+abs(tw-fw)==1);
        assert(tes.board[th][tw].type==0);
        assert(tes.board[fh][fw].type>0);
        // cout<< tes.board[th][tw].type SP << tes.board[fh][fw].type <<endl;
        //tes.comp[tes.board[th][tw].idx].pos={th, tw};
        swap(tes.board[th][tw], tes.board[fh][fw]);
    }
    rep(i, room.co.size()){
        int th=room.co[i].to.h;
        int tw=room.co[i].to.w;
        int fh=room.co[i].from.h;
        int fw=room.co[i].from.w;
        assert((th==fh && tw!=fw) || (th!=fh && tw==fw));
        assert(tes.board[fh][fw].type>0);
        assert(tes.board[th][tw].type>0);
        //assert(tes.board[fh][fw].type==tes.board[th][tw].type);
    }
    // cout<< "co" <<endl;
    // rep(i, room.co.size()){
    //     int th=room.co[i].to.h;
    //     int tw=room.co[i].to.w;
    //     int fh=room.co[i].from.h;
    //     int fw=room.co[i].from.w;
    //     assert(!tes.uf.same(tes.board[th][tw].idx, tes.board[fh][fw].idx));
    //     tes.uf.unite(tes.board[th][tw].idx, tes.board[fh][fw].idx);
    // }
    // cout<< "calc" <<endl;
    // rep(i, k*100){
    //     rep3(j, k*100, i+1){
    //         if(tes.uf.same(i, j)){
    //             if(tes.comp[i].fig==tes.comp[j].fig) rtn++;
    //             else rtn--;
    //         }
    //     }
    // }
    // cout<< "mv" <<endl;
    return rtn;
}

int main(){
    int point=0;
    string path = "testcases/";
    vector<string> file_in_paths;
    vector<string> file_out_paths;
    rep(i, 100){
        int no=i+10000;
        string tmp="testcases/"+to_string(no).substr(1, 4)+".txt";
        file_in_paths.push_back(tmp);
        file_out_paths.push_back(tmp.substr(0, 15)+"out");
    }
    sort(all(file_in_paths));
    //rep(i, 100) cout<< file_in_paths[i] <<endl;
    sort(all(file_out_paths));
    rep(testcase, file_in_paths.size()){
        std::ifstream ifs(file_in_paths[testcase]);
        if (!ifs)
        {
            std::cout << file_in_paths[testcase] << " 読み込み失敗" << std::endl;
            continue;
        }
        cout<< "opened " << file_in_paths[testcase] <<endl;

        // ~~~~~~~~~~~~~~~main~~~~~~~~~~~~~~~~~~


        //開始時間の計測
        std::chrono::system_clock::time_point start, current;
        start = chrono::system_clock::now();
        // posting inpt here
        // replace cin -> ifs
        // add c&cpu clear
        c.clear();
        cpu.clear();
        ifs>> n >> k;
        c.resize(n);
        rep(i, n) c[i].resize(n);
        cpu.resize(k*100);
        int cnt=0;

        rep(i, n){
            string tmp;
            ifs>> tmp;
            rep(j, n){
                int fig=int(tmp[j]-'0');
                c[i][j]=Num(fig, cnt);
                if(fig){
                    cpu[cnt]={fig, {i, j}};
                    cnt++;
                }
            }
        }
        // inpt end

        Room best;

        int lp=0;
        while (true) { // 時間の許す限り回す
            lp++;
            current = chrono::system_clock::now(); // 現在時刻
            if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
            //cout<< lp <<endl;

            Room cur;
            cur.init();

            int rnd=max(0, (k*10000/(n*n)-80))*k*10;
            if(rnd){
                rnd=mt()%rnd;
                cur.random_mv(rnd);
            }

            vector<int> perm(k);
            rep(i, k) perm[i]=i+1;
            shuffle(all(perm), mt);

        if(n*n>(k*300)){
            rnd=mt()%100;
            if(rnd==3 || rnd==5){
                cur.lar(perm[0], perm[1], rnd);
                cur.nomove_connect_hw(perm[0], n, 'R');
                cur.nomove_connect_hw(perm[1], n, 'R');
            }
        }

        //cur.co_lim=100;
            rep(i, k){
                // perm[i]番の数字を構築する
                // rep3(j, n, 1){
                //     //cout<< "nomove " << perm[i] <<endl;
                //     cur.nomove_connect(perm[i], j);
                // }
                cur.nomove_connect(perm[i], 3);
                cur.nomove_connect(perm[i], 6);
                cur.nomove_connect(perm[i], n);
                //cout<< "cpu_slide " << perm[i] <<endl;
                //cout<< "nomove2 " << i+1 <<endl;
                int rdc=1, mc=0;
                while(i==0 && rdc!=0 && mc<5){
                rdc+=cur.cpu_slide(perm[i], mt()%(n/2)+1, mt()%(n/2)+1);
                    rep(j, cur.minus.size()){
                        int mh=cur.minus[j].h;
                        int mw=cur.minus[j].w;
                        if(cur.board[mh][mw].type<0) cur.board[mh][mw].type=0;
                    }
                    cur.minus.clear();
                    cur.uf.init(k*100);
                    cur.co.clear();

                    cur.nomove_connect(perm[i], n);
                
                    rdc=cur.move_other(perm[i]);

                    cur.nomove_connect(perm[i], n);

                    mc++;
                }
                rep3(j, mt()%(n-2)+2, 1) cur.nomove_connect(perm[i], j);
            }
            // 優先度1番以外の1点しか取れない
            //cur.shrot_erase(perm[0]);
            //cout<< "end connect" <<endl;
            rep(i, k){
                //rep3(j, n, 1) cur.nomove_connect(perm[i], j);
                cur.nomove_connect(perm[i], n);
            }
            cur.co_lim=100;
            cur.bridge(20, 3, 100, perm);
            cur.bridge(10, 6, 25, perm);
            //score(cur);
            cur.easy_score();
            //cout<< cur.score <<endl;
            if(best.score<cur.score) best=cur;
        }

        score(best);
        std::ofstream ofs(file_out_paths[testcase]);
        if (!ofs){
            std::cout << file_out_paths[testcase] << " 書き込み失敗" << std::endl;
            continue;
        }
        //cout << "opened " << file_out_paths[testcase] <<endl;

        ofs<< best.mv.size() <<endl;
        rep(i, best.mv.size()) ofs<< best.mv[i].from.h SP << best.mv[i].from.w SP << best.mv[i].to.h SP << best.mv[i].to.w <<endl;
        ofs<< best.co.size() <<endl;
        rep(i, best.co.size()) ofs<< best.co[i].from.h SP << best.co[i].from.w SP << best.co[i].to.h SP << best.co[i].to.w <<endl;

        int sco=best.score;;
        cout<< "(n, k, sco, lp)=" << n SP << k SP << sco SP << lp SP << best.prf <<endl;
        point+=sco;


        // ~~~~~~~~~~~~main~~~~~~~~~~~~
    }

    cout<< "score sum:" << point <<endl;
	return 0;
}

// uf木セット
