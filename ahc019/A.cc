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
ll lb32=2147483648;
ll lmax=9223372036854775807;
int icos[]={1, 0, -1, 0};
int isin[]={0, 1, 0, -1};

//焼きなましの定数
double TIME_LIMIT=5900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

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

//入力
int D;
vector<vector<vector<int>>> f, r;

void inpt(){
    // cout<< "inpt" <<endl;
    cin>> D;

    f.resize(2);
    rep(i, 2) f[i].resize(D);
    rep(i, 2) rep(j, D) f[i][j].resize(D);
    r.resize(2);
    rep(i, 2) r[i].resize(D);
    rep(i, 2) rep(j, D) r[i][j].resize(D);

    string s;
    rep(i, 2){
        rep(j, D){
            cin>> s;
            rep(k, D){
                f[i][j][k]=int(s[k]-'0');
            }
        }
        rep(j, D){
            cin>> s;
            rep(k, D){
                r[i][j][k]=int(s[k]-'0');
            }
        }
    }
}

// 構造体
struct Pos{
    int x;
    int y;
    int z;

    Pos(){};
    Pos(int xx, int yy, int zz){
        x=xx;
        y=yy;
        z=zz;
    }

    bool is_out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        if(x<0 || D<=x || y<0 || D<=y || z<0 || D<=z){
            // print();
            return true;
        }
        return false;
    }
    int get_id(int id){
        // print();
        return 3375*id+225*x+15*y+z;
    }
    void print(){
        cout<< "(" << x << ", " << y << ", " << z << ")" <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.x=x+pos.x;
        rtn.y=y+pos.y;
        rtn.z=z+pos.z;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.x=x-pos.x;
        rtn.y=y-pos.y;
        rtn.z=z-pos.z;
        return rtn;
    }
};
Pos d6[]={{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};

struct Space{
    ll prio;
    Pos pos;
    int bid;

    Space(){}
    Space(Pos ipos, int ibid=-1){
        prio=mt();
        // cout<< prio <<endl;
        pos=ipos;
        bid=ibid;
    }

    bool operator<(const Space &in) const{
		return prio!=in.prio ? prio<in.prio : bid<in.bid;
	};
};

struct matrix {
    vector<vector<int>> data;

    matrix(){}
    matrix(vector<vector<int>> mat){
        data=mat;
    }

    matrix operator*(const matrix &in) const {
        matrix res(vector<vector<int>>(3, vector<int>(3)));
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                for (int k=0;k<3;k++){
                    res.data[i][j]+=data[i][k]*in.data[k][j];
                }
            }
        }
        return res;
    }
    Pos operator*(const Pos &in) const {
        int x=data[0][0]*in.x+data[0][1]*in.y+data[0][2]*in.z;
        int y=data[1][0]*in.x+data[1][1]*in.y+data[1][2]*in.z;
        int z=data[2][0]*in.x+data[2][1]*in.y+data[2][2]*in.z;
        return {x, y, z};
    }
    void print(){
        rep(i, 3){
            rep(j, 3){
                cout<< data[i][j] SP;
            }
            cout<< endl;
        }
    }
};

matrix get_rot(int rx, int ry, int rz){
    matrix rtn({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
    matrix matx({{1, 0, 0}, {0, icos[rx], -isin[rx]}, {0, isin[rx], icos[rx]}});
    matrix maty({{icos[ry], 0, isin[ry]}, {0, 1, 0}, {-isin[ry], 0, icos[ry]}});
    matrix matz({{icos[rz], -isin[rz], 0}, {isin[rz], icos[rz], 0}, {0, 0, 1}});
    return rtn*matx*maty*matz;
}

struct Blocks{
    int id;
    int type;
    matrix rot;
    // matrix rotinv;
    Pos pos;
    vector<Pos> cubes;

    Blocks(){}
    Blocks(int iid, int ftype, Pos ipos){
        id=iid;
        type=ftype;
        pos=ipos;
        cubes.push_back({0, 0, 0});
        if(type==2){
            int rx=mt()%4, ry=mt()%4, rz=mt()%4;
            rot=get_rot(rx, ry, rz);
            rx=(4-rx)%4;
            ry=(4-ry)%4;
            rz=(4-rz)%4;
            // rotinv=get_rot(rx, ry, rz);
        }else{
            // rot=get_rot(0, 0, 0);
            // rotinv=rot;
        }
    }

    bool operator<(const Blocks &in) const{
		return id<in.id;
	};
};

// struct LeftBlock{
//     ll prio;
//     int bid;

//     LeftBlock(){}
//     LeftBlock(int ibid=-1){
//         prio=mt();
//         bid=ibid;
//     }

//     bool operator<(const LeftBlock &in) const{
// 		return prio!=in.prio ? prio<in.prio : bid<in.bid;
// 	};
// };

struct Field{
    int type;
    vector<vector<vector<int>>> val; //-1のときNG、0のとき空、それ以外block
    map<int, Blocks> blocks;
    set<Space> spaces;
    set<Space> extends;
    set<int> dup_ext;
    vector<vector<int>> front_count, right_count;
    int front_remain=0, right_remain=0;
    // set<LeftBlock> left_blocks;

    Field(){}
    Field(int ftype, vector<vector<int>> sif, vector<vector<int>> sir){
        type=ftype;
        // cout<< type <<endl;
        val.resize(D);
        rep(i, D) val[i].resize(D);
        rep(i, D) rep(j, D) val[i][j].resize(D);
        front_count.resize(D);
        rep(i, D) front_count[i].resize(D);
        right_count.resize(D);
        rep(i, D) right_count[i].resize(D);

        rep(i, D){
            rep(j, D){
                if(sif[i][j]==0){
                    rep(k, D) val[j][k][i]=-1;
                }else{
                    front_remain++;
                }
                if(sir[i][j]==0){
                    rep(k, D) val[k][j][i]=-1;
                }else{
                    right_remain++;
                }
            }
        }
        
        rep(i, D){
            rep(j, D){
                rep(k, D){
                    if(val[i][j][k]==0) spaces.insert({{i, j, k}});
                    // cout<< val[i][j][k] SP;
                }
            }
        }
    }
    // Field vector<vector<int>> front_count, right_count を作り、シルエットに対応しているブロックが何個存在するか(0~D)をメモしておく。
    // Field front_remain, right_remainで埋めたいけど埋められていないシルエット数を求める
    // fは[x][y][z]=[z][x], rは[x][y][z]=[z][y]
    void set_val(Pos pos, int value){
        // cout<< type SP << "set_val: " << value <<endl;
        // cout<< "pos: ";
        // pos.print();
        assert(!pos.is_out_of_bounce());
        // 変化がないのはおかしい
        // cout<< val[pos.x][pos.y][pos.z] SP << value <<endl;
        assert(val[pos.x][pos.y][pos.z]!=value);
        int effect=1;
        if(value==0) effect=-1;
        val[pos.x][pos.y][pos.z]=value;

        front_count[pos.z][pos.x]+=effect;
        int tmpf=front_count[pos.z][pos.x];
        assert(tmpf>=0);
        assert(tmpf<=D);
        if(tmpf==0) front_remain++;
        else if(tmpf==1 && value) front_remain--;
        assert(front_remain>=0);

        right_count[pos.z][pos.y]+=effect;
        int tmpr=right_count[pos.z][pos.y];
        assert(tmpr>=0);
        assert(tmpr<=D);
        if(tmpr==0) right_remain++;
        else if(tmpr==1 && value) right_remain--;
        assert(right_remain>=0);
        // cout<< "end set_val" <<endl;
    }
    bool random_set(int id){
        rep(i, D*D*D*10){
            int x=mt()%D;
            int y=mt()%D;
            int z=mt()%D;
            if(val[x][y][z]==0){
                // cout<< lp <<endl;
                int dup1=0, dup2=0, dup;
                rep(i, D){
                    if(val[i][y][z]>0) dup1=1;
                    if(val[x][i][z]>0) dup2=1;
                }
                dup=dup1+dup2;
                if(dup*D*D*D>i) continue;
                val[x][y][z]=id;
                blocks[id]={id, type, {x, y, z}};
                return true;
            }
        }
        return false;
    }
    // 絶対位置を受け取る
    void f1_add_ext(int block_id, Pos pos, bool direct=false){
        // cout<< "f1_add_ext" <<endl;
        assert(type==1);
        rep(i, 6){
            Pos npos;
            if(direct) npos=pos;
            else npos=pos+d6[i];
            if(npos.is_out_of_bounce()) continue;
            int ext_id=npos.get_id(block_id);
            if(dup_ext.find(ext_id)!=dup_ext.end()) continue;
            dup_ext.insert(ext_id);
            if(val[npos.x][npos.y][npos.z]==0){
                // blockの相対位置をつめる
                extends.insert({npos-blocks[block_id].pos, block_id});
                if(direct) return;
                // cout<< "gen: " << block_id <<endl;
            }
        }
    }
    bool shuffle_set(int id){
        // cout<< type SP << "shuffle_set" <<endl;
        // if(spaces.empty()) return false;
        vector<set<Space>::iterator> itrs;
        bool found=false;
        for(auto itr=spaces.begin();itr!=spaces.end();itr++){
            Space spa=*itr;
            Pos pos=spa.pos;
            // assert(!pos.is_out_of_bounce());
            if(front_count[pos.z][pos.x] && right_count[pos.z][pos.y]) continue;
            if(val[pos.x][pos.y][pos.z]!=0){
                itr=spaces.erase(itr);
                if(spaces.empty()) break;
                continue;
            }
            // pos.print();
            itrs.push_back(itr);
            if(itrs.size()>=5) break;
        }
        int min_dup=9;
        // cout<< "itrs:" << itrs.size() <<endl;
        set<Space>::iterator min_itr;
        rep(i, itrs.size()){
            int dup1=0, dup2=0;
            Space spa=*itrs[i];
            int x=spa.pos.x;
            int y=spa.pos.y;
            int z=spa.pos.z;
            rep(i, D){
                if(val[i][y][z]>0) dup1=1;
                if(val[x][i][z]>0) dup2=1;
                if(dup1+dup2==2) break;
            }
            if(dup1+dup2<min_dup){
                min_dup=dup1+dup2;
                min_itr=itrs[i];
                found=true;
            }
        }
        // cout<< "#1" <<endl;
        if(found){
            Space spa=*min_itr;
            Pos pos=spa.pos;
            spaces.erase(min_itr);
            set_val(pos, id);
            blocks[id]=Blocks({id, type, pos});
            // cout<< type SP << "blocks.size() " << blocks.size() <<endl;
            if(type==1){
                // cout<< id SP << "set f1: ";
                // pos.print();
                // auto block_itr=blocks.find({block_id, 0, {0, 0, 0}});
                f1_add_ext(id, pos);
            }
            // cout<< "extend: " << id <<endl;
            return true;
        }
        return false;
    }
    Space f1_fetch_extend(){
        // cout<< "f1_fetch_extend" <<endl;
        assert(type==1);
        while(!extends.empty()){
            Space space=*extends.begin();
            Pos abpos=space.pos+blocks[space.bid].pos;
            // abpos.print();
            extends.erase(extends.begin());
            if(val[abpos.x][abpos.y][abpos.z]==0) return space;
        }
        return {{-9999, 0, 0}};
    }
    Pos f1_fetch_space(int block_id){
        /*assert(0<=block_id);
        assert(block_id<blocks.size());
        int lp=0;
        rep(i, 100){
            int cube_id=mt()%blocks[block_id].cubes.size();
            lp++;
            Pos pos=blocks[block_id].pos+blocks[block_id].cubes[cube_id];
            if(pos.is_out_of_bounce()){
                pos.print();
                continue;
                assert(!pos.is_out_of_bounce());
            }
            assert(val[pos.x][pos.y][pos.z]==blocks[block_id].id);
            vector<int> shu(6);
            rep(i, 6) shu[i]=i;
            shuffle(all(shu), mt);
            rep(lp, 6){
                int i=shu[lp];
                Pos npos=pos+d6[i];
                if(npos.is_out_of_bounce()) continue;
                // cout<< "not Oob" <<endl;
                if(val[npos.x][npos.y][npos.z]==0) return npos-blocks[block_id].pos;
            }
        }*/
        return {-9999, 0, 0};
    }
    bool f2_is_usable_space(int block_id, Pos ivec){
        // cout<< "f2_is_usable_space" <<endl;
        assert(type==2);
        Pos pos=blocks[block_id].pos;
        Pos vec;
        if(type==2) vec=blocks[block_id].rot*ivec;
        else vec=ivec;
        Pos npos=pos+vec;
        // npos.print();
        if(npos.is_out_of_bounce()) return false;
        if(val[npos.x][npos.y][npos.z]==0){
            set_val(npos, block_id);
            blocks[block_id].cubes.push_back(vec);
            return true;
        }
        return false;
    }
    void f1_add_cube(int block_id, Pos vec){
        // cout<< "f1_add_cube" <<endl;
        blocks[block_id].cubes.push_back(vec);
        Pos npos=blocks[block_id].pos+vec;
        // cout<< block_id SP << "extend f1: ";
        // npos.print();
        assert(val[npos.x][npos.y][npos.z]==0);
        set_val(npos, block_id);
        f1_add_ext(block_id, npos);
    }
    void del_block(int block_id){
        // cout<< "type" << type SP << "del_block" <<endl;
        vector<Pos> cubes=blocks[block_id].cubes;
        Pos base=blocks[block_id].pos;
        // cout<< "cube size: " << cubes.size() <<endl;
        rep(i, cubes.size()){
            Pos pos=cubes[i]+base;
            // init val
            // assert(val[pos.x][pos.y][pos.z]==block_id);
            set_val(pos, 0);
            // add space
            spaces.insert(pos);
        }
        if(type==2) return;
        rep(i, cubes.size()){
            Pos pos=cubes[i]+base;
            rep(j, 6){
                Pos npos=pos+d6[j];
                if(npos.is_out_of_bounce()) continue;
                int value=val[npos.x][npos.y][npos.z];
                if(value>0){
                    f1_add_ext(value, pos, true);
                }
            }
        }
    }
    int fail_fill(int &id){
        int cnt=0;
        // rep(i, D){
        //     rep(j, D){
        //         if(f[type-1][i][j]==1){
        //             int flag=1;
        //             rep(k, D){
        //                 if(val[j][k][i]>0){
        //                     flag=0;
        //                     break;
        //                 }
        //             }
        //             if(flag){
        //                 rep(k, D){
        //                     if(val[j][k][i]==0 && r[type-1][i][j]==1){
        //                         id++;
        //                         val[j][k][i]=id;
        //                         cnt++;
        //                         break;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        // rep(i, D){
        //     rep(j, D){
        //         if(r[type-1][i][j]==0){
        //             int flag=1;
        //             rep(k, D){
        //                 if(val[k][j][i]>0){
        //                     flag=0;
        //                     break;
        //                 }
        //             }
        //             if(flag){
        //                 rep(k, D){
        //                     if(val[k][j][i]==0 && f[type-1][i][j]==1){
        //                         id++;
        //                         val[k][j][i]=id;
        //                         cnt++;
        //                         break;
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }
        return cnt;
    }
    void print_val(int dif){
        rep(i, D) rep(j, D) rep(k, D){
            if(val[i][j][k]<=0) cout<< "0 ";
            else cout<< val[i][j][k] SP;
        }
        cout<<endl;
    }
};

struct Puzzle{
    Field f1=Field(1, f[0], r[0]), f2=Field(2, f[1], r[1]);
    int idx=0;
    int pena=0;

    bool random_set(){
        // cout<< "random_set" <<endl;
        idx++;
        return (f1.random_set(idx) && f2.random_set(idx));
    }
    bool shuffle_set(){
        // cout<< "shuffle_set" <<endl;
        idx++;
        bool b1=f1.shuffle_set(idx);
        bool b2=f2.shuffle_set(idx);
        // cout<< "b1b2: " << b1 << b2 <<endl;
        return (b1 && b2);
    }
    bool random_extend(){
        // cout<< "random_extend" <<endl;
        /*rep(i, 10*D*D*D){
            int block_id=mt()%f1.blocks.size();
            Pos vec1=f1.f1_fetch_space(block_id);
            // vec1.print();
            if(vec1.x==-9999) continue;
            // cout<< "f1" <<endl;
            if(!f2.f2_is_usable_space(block_id, vec1)) continue;
            f1.f1_add_cube(block_id, vec1);
            // cout<< "extend!" <<endl;
            return true;
        }*/
        return false;
    }
    bool shuffle_extend(){
        // cout<< "shuffle_extend" <<endl;
        while(1){
            Space space=f1.f1_fetch_extend();
            if(space.pos.x==-9999) return false; // extendsの在庫切れ
            int block_id=space.bid;
            // cout<< block_id <<endl;
            Pos vec1=space.pos;
            if(!f2.f2_is_usable_space(block_id, vec1)) continue;
            f1.f1_add_cube(block_id, vec1);
            break;
        }
        // cout<< "extend!" <<endl;
        return true;
    }
    void del_block(){
        int id=(*f1.blocks.begin()).first;
        // cout<< "!delete: " << id <<endl;
        f1.del_block(id);
        f2.del_block(id);
        f1.blocks.erase(id);
        f2.blocks.erase(id);
    }
    void fail_fill(){
        pena=f1.fail_fill(idx)+f2.fail_fill(idx);
        // cout<< pena <<endl;
    }
    bool check_complete(){
        // cout<< f1.front_remain SP << f1.right_remain SP << f2.front_remain SP << f2.right_remain <<endl;
        return (!f1.front_remain && !f1.right_remain && !f2.front_remain && !f2.right_remain);
    }
    bool simple_check_complete(){
        rep(i, D){
            rep(j, D){
                if(f[0][i][j]==0){
                    rep(k, D){
                        if(f1.val[j][k][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f1.val[j][k][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(f[1][i][j]==0){
                    rep(k, D){
                        if(f2.val[j][k][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f2.val[j][k][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(r[0][i][j]==0){
                    rep(k, D){
                        if(f1.val[k][j][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f1.val[k][j][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        rep(i, D){
            rep(j, D){
                if(r[1][i][j]==0){
                    rep(k, D){
                        if(f2.val[k][j][i]>0) return false;
                    }
                }else{
                    int flag=1;
                    rep(k, D){
                        if(f2.val[k][j][i]>0){
                            flag=0;
                            break;
                        }
                    }
                    if(flag) return false;
                }
            }
        }
        return true;
    }
    void init_best(){
        rep3(i, 3000, 1){
            random_set();
            if(simple_check_complete()) return;
        }
    }
    ll calc_score(){
        double base=1000000000.0;
        double sig=0.0;
        // cout<< f1.blocks.size() <<endl;
        for(auto itr=f1.blocks.begin();itr!=f1.blocks.end();itr++){
            // cout<< (*itr).first SP;
            sig+=1.0/(*itr).second.cubes.size();
        }
        // cout<< endl;
        ll rtn=round(base*sig)+pena;
        return rtn;
    }
    void print_ans(){
        int mi=999;
        rep(i, D) rep(j, D) rep(k, D){
            if(f1.val[i][j][k]>0){
                mi=min(mi, f1.val[i][j][k]);
            }
        }
        cout<< idx <<endl;
        // cout<< idx-mi <<endl;
        f1.print_val(mi);
        f2.print_val(mi);
    }
};

// グローバル
// vector<vector<vector<matrix>>> rot;

void init(){
    inpt();
}

void get_argv(int argc, char* argv[]){
    vector<double> args;
    rep3(i, argc, 1){
        string tmp;
        tmp.assign(argv[i]);
        args.push_back(stof(tmp));
        // cout<< args[i-1] <<endl;
    }
}

int main(int argc, char* argv[]){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    init();
    // get_argv(argc, argv);
    ll best_score=lmax;
    int lp=0;

    Puzzle puzzle, best;
    puzzle.shuffle_set();
    best.init_best();
    int mul=sqrt(mt()%50)/3*D+1;
    int mib=1000;
    bool no_shuffle=false;

    while (true){
        lp++;
        // if(lp>1) break;
        // if(lp%1==0) cout<< "lp: " << lp <<endl;
        current = chrono::system_clock::now(); // 現在時刻
        double delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if (delta > TIME_LIMIT) break;
 
        Puzzle puzzle;
        puzzle.shuffle_set();
        int mul=sqrt(mt()%50)/3*D+1;
        int mib=1000;
        bool no_shuffle=false;
        rep3(i, 1000, 1){
            // cout<< "i: " << i <<endl;
            if(no_shuffle || mt()%mul==0){
                if(mib<puzzle.f1.blocks.size()) break;
                if(!puzzle.shuffle_set()){
                    // puzzle.del_block();
                    break;
                }
                no_shuffle=false;
            }else{
                if(!puzzle.shuffle_extend()) no_shuffle=true;
            }
 
            if(puzzle.check_complete()){
                // puzzle.print_ans();
                while(puzzle.shuffle_extend()){}
                ll score=puzzle.calc_score();
                // cout<< "lp: " << lp SP << score <<endl;
                if(score<best_score){
                    mib=min(mib, int(puzzle.f1.blocks.size()));
                    best_score=score;
                    best=puzzle;
                    // cout<< "lp: " << lp SP << best_score <<endl;
                    // puzzle.print_ans();
                }
                // break;
            }
        }
    }

    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}

