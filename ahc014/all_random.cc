// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp=50.0;
double end_temp=10.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//入力
int n, m, s;
int x[350], y[350];

// 構造体
struct Pos{
    int x;
    int y;

    Pos(){};
    Pos(int xx, int yy){
        x=xx;
        y=yy;
    }
    int weight(){
        //cout<< "weight" <<endl;
        return (x-n/2)*(x-n/2)+(y-n/2)*(y-n/2)+1;
    }
    bool out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        return (x<0 || n-1<x || y<0 || n-1<y);
    }
    int manhattan(Pos a){
        //cout<< "manhattan" <<endl;
        if(a.out_of_bounce()){
            a.print();
            assert(!a.out_of_bounce());
        }
        if(out_of_bounce()){
            print();
            assert(!out_of_bounce());
        }
        return (abs(a.x-x)+abs(a.y-y));
    }

    void print(){
        cout<< "(" << x << ", " << y << ")";
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
    bool operator!=(const Pos &in) const{
		return x!=in.x && y!=in.y;
	};
};
Pos d8[]={{0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}};

struct Rect{
    Pos p1;
    Pos p2;
    Pos p3;
    Pos p4;

    Rect(){};
    Rect(Pos point1, Pos point2, Pos point3, Pos point4){
        //cout<< "Rect" <<endl;
        p1=point1;
        p2=point2;
        p3=point3;
        p4=point4;
    }

    void print(){
        cout<< p1.x SP << p1.y SP << p2.x SP << p2.y SP << p3.x SP << p3.y SP << p4.x SP << p4.y <<endl;
    }
    // void print(int idx){
    //     cout<< idx SP << p1.x SP << p1.y SP << p2.x SP << p2.y SP << p3.x SP << p3.y SP << p4.x SP << p4.y <<endl;
    // }
};

// struct ConeList{
//     Pos pos;
//     int dir, a, b, c, pos_wei;

//     ConeList(){};
//     ConeList(Pos in_pos, int in_dir, int in_a, int in_b, int in_c){
//         pos=in_pos;
//         dir=in_dir;
//         a=in_a;
//         b=in_b;
//         c=in_c;
//         pos_wei=pos.weight();
//     }

//     void print(){
//         pos.print();
//         cout<< dir SP << a SP << b SP << c SP << "weight: " << pos.weight() <<endl;
//     }

//     bool operator<(const ConeList &in) const{
// 		return pos_wei!=in.pos_wei ? pos_wei>in.pos_wei : pos!=in.pos ? pos<in.pos : dir<in.dir;
// 	};
// };

struct ConeList{
    int a, dir;

    ConeList(){};
    ConeList(int in_a, int in_dir){
        dir=in_dir;
        a=in_a;
    }

    void print(){
        cout<< "id: " << a SP << "dir: " << dir <<endl;
    }

    bool operator<(const ConeList &in) const{
		return a!=in.a ? a>in.a : dir<in.dir;
	};
};

struct Point{
    vector<int> par;
    Pos pos;
    int next_to[8]={-1, -1, -1, -1, -1, -1, -1, -1};
    //8bit分をintで持つ
    int connect=0;

    Point(){};
    Point(Pos position){
        pos=position;
    }

    void print(){
        cout<< "parent: ";
        rep(i, par.size()) cout<< par[i] SP;
        pos.print();
        cout<< " nextto: ";
        rep(i, 8) cout<< next_to[i] SP;
        cout<< endl;
    }
};

struct Paper{
    vector<vector<int>> inv_board;
    vector<Point> poi;
    int score=0;
    vector<ConeList> connectable_list;
    vector<Rect> rectangle;

    Paper(){
    }
    void init(){
        //cout<< "init" <<endl;
        inv_board.resize(n, vector<int>(n, -1));
        rep(i, m){
            add_point(Pos(x[i], y[i]));
        }
        search_line();
    }
    void search_line(){
        //cout<< "search_line" <<endl;
        //左から右
        rep(i, n){
            int prev=-1;
            rep(j, n){
                int inv_idx=inv_board[i][j];
                if(inv_idx!=-1){
                    if(prev!=-1){
                        poi[inv_idx].next_to[4]=prev;
                        poi[prev].next_to[0]=inv_idx;
                    }
                    prev=inv_idx;
                }
            }
        }
        //上から下
        rep(i, n){
            int prev=-1;
            rep(j, n){
                int inv_idx=inv_board[j][i];
                if(inv_idx!=-1){
                    if(prev!=-1){
                        poi[inv_idx].next_to[2]=prev;
                        poi[prev].next_to[6]=inv_idx;
                    }
                    prev=inv_idx;
                }
            }
        }
        //左上から
        rep(i, n){
            int prev1=-1;
            int prev2=-1;
            rep(j, n-i){
                int inv_idx=inv_board[i+j][j];
                if(inv_idx!=-1){
                    if(prev1!=-1){
                        poi[inv_idx].next_to[3]=prev1;
                        poi[prev1].next_to[7]=inv_idx;
                    }
                    prev1=inv_idx;
                }
            }
            if(i==0) continue;
            rep(j, n-i){
                int inv_idx=inv_board[j][i+j];
                if(inv_idx!=-1){
                    if(prev2!=-1){
                        poi[inv_idx].next_to[3]=prev2;
                        poi[prev2].next_to[7]=inv_idx;
                    }
                    prev2=inv_idx;
                }
            }
        }
        //左下から
        rep(i, n){
            int prev1=-1;
            int prev2=-1;
            rep(j, n-i){
                int inv_idx=inv_board[n-1-(i+j)][j];
                if(inv_idx!=-1){
                    if(prev1!=-1){
                        poi[inv_idx].next_to[5]=prev1;
                        poi[prev1].next_to[1]=inv_idx;
                    }
                    prev1=inv_idx;
                }
            }
            if(i==0) continue;
            rep(j, n-i){
                int inv_idx=inv_board[n-1-j][i+j];
                if(inv_idx!=-1){
                    if(prev2!=-1){
                        poi[inv_idx].next_to[5]=prev2;
                        poi[prev2].next_to[1]=inv_idx;
                    }
                    prev2=inv_idx;
                }
            }
        }
    }
    void random_search_amap(){
        int prev_score;
        do{
            prev_score=score;
            search_connect_all(true);
        }while(prev_score<score);
    }
    void search_connect_all(bool execute){
        vector<int> permutation(poi.size());
        rep(i, poi.size()) permutation[i]=i;
        shuffle(all(permutation), mt);
        rep(i, permutation.size()) search_connect(permutation[i], execute);
    }
    void edge_search_all(int distance_limit, bool execute){
        rep(i, poi.size()){
            if(abs(poi[i].pos.x-n/2)>=distance_limit || abs(poi[i].pos.y-n/2)>=distance_limit){
                search_connect(i, execute);
            }
        }
    }
    void search_connect(int index, bool execute, int direction=-1){
        //cout<< "search_connect" <<endl;
        if(direction!=-1){
            search_connect_direction(index, execute, direction);
        }else{
            int random_dir=mt()%8;
            rep(dir, 8){
                search_connect_direction(index, execute, (random_dir+dir)%8);
            }
        }
    }
    void search_connect_direction(int c, bool execute, int j){
        int a_index=poi[c].next_to[j];
        int b_index=poi[c].next_to[(j+2)%8];
        //出発点から伸びる2辺を確認
        if(a_index>=0 && b_index>=0){
            //出発点から伸びた2点を確認
            if(poi[a_index].next_to[(j+4)%8]<-1 || poi[b_index].next_to[(j+6)%8]<-1) return;
            if(poi[a_index].next_to[(j+2)%8]<-1 || poi[b_index].next_to[j]<-1) return;
            if(!(a_index<poi.size())){
                cout<< a_index SP << poi.size() <<endl;
                assert(a_index<int(poi.size()));
            }
            if(!(b_index<poi.size())){
                cout<< b_index SP << poi.size() <<endl;
                assert(b_index<int(poi.size()));
            }
            point_can_be_add(a_index, b_index, c, j, execute);
        }
    }
    void point_can_be_add(int a, int b, int c, int dir, bool execute){
        //cout<< "point_can_be_add" <<endl;
        //cにベクトルcaとcbを作用させると目的地が出る
        Pos pos=poi[c].pos+poi[a].pos-poi[c].pos+poi[b].pos-poi[c].pos;
        //方眼紙の領域外なら中断
        if(pos.out_of_bounce()) return;
        //置きたい場所にすでに点があったら中断
        if(inv_board[pos.x][pos.y]!=-1) return;
        //置きたい点と既存の点との間に点があったら中断
        int a_next_index=poi[a].next_to[(dir+2)%8];
        int b_next_index=poi[b].next_to[(dir)%8];
        if(!(a_next_index<int(poi.size()))){
            cout<< a_next_index SP << poi.size() <<endl;
            assert(a_next_index<int(poi.size()));
        }
        if(!(b_next_index<int(poi.size()))){
            cout<< b_next_index SP << poi.size() <<endl;
            assert(b_next_index<int(poi.size()));
        }
        //-1なら隣接点なしなのでOK
        bool a_line=(a_next_index==-1);
        bool b_line=(b_next_index==-1);
        if(!a_line) a_line=(poi[a].pos.manhattan(pos)<poi[a].pos.manhattan(poi[a_next_index].pos));
        if(!b_line) b_line=(poi[b].pos.manhattan(pos)<poi[b].pos.manhattan(poi[b_next_index].pos));
        //つなぐ
        if(a_line && b_line){
            if(execute){
                execute_connect(pos, dir, a, b, c);
            }else{
                //ConeList(pos, dir, a, b, c).print();
                //connectable_list.emplace_back(ConeList(pos, dir, a, b, c));
                connectable_list.emplace_back(c, dir);
            }
        }
    }
    void execute_connect(Pos pos, int dir, int a, int b, int c){
        rectangle.emplace_back(Rect(pos, poi[a].pos, poi[c].pos, poi[b].pos));
        add_point(pos);
        reconnect_line(dir);
        delete_next_to(dir, a, b, c);
        search_connect(poi.size()-1, false);
    }
    void add_point(Pos position){
        //position.print();
        //cout<< " add_point" <<endl;
        // idを振るための採番をしている
        assert(0<=position.x && position.x<=n-1);
        assert(0<=position.y && position.y<=n-1);
        inv_board[position.x][position.y]=poi.size();
        poi.emplace_back(Point(position));
        score+=position.weight();
    }
    void reconnect_line(int dir){
        //cout<< "reconnect_line" <<endl;
        dir=(dir+4)%8;
        int add_index=poi.size()-1;
        //vector<int> reconnects;
        rep(i, 8){
            if(i==dir || i==(dir+2)%8) continue;
            Pos pos=poi[add_index].pos+d8[i];
            while(!pos.out_of_bounce()){
                int next_to_index=inv_board[pos.x][pos.y];
                if(next_to_index!=-1){
                    if(poi[next_to_index].next_to[(i+4)%8]<-1){
                        poi[add_index].next_to[i]-=10000;
                    }else{
                        poi[next_to_index].next_to[(i+4)%8]=add_index;
                        poi[add_index].next_to[i]=next_to_index;
                        // search_connect_direction(next_to_index, false, (i+2)%8);
                        // search_connect_direction(next_to_index, false, (i+4)%8);
                        search_connect(next_to_index, false);
                        //reconnects.emplace_back(next_to_index);
                    }
                    break;
                }
                pos+=d8[i];
            }
        }
        // rep(i, reconnects.size()) search_connect(reconnects[i], false);
    }
    void delete_next_to(int dir, int a, int b, int c){
        //cout<< "delete_next_to" <<endl;
        poi[c].next_to[dir]-=10000;
        poi[a].next_to[(dir+4)%8]-=10000;
        poi[a].next_to[(dir+2)%8]-=10000;
        //新規追加の点は一番最後にいる
        poi[poi.size()-1].next_to[(dir+6)%8]-=10000;
        poi[poi.size()-1].next_to[(dir+4)%8]-=10000;
        poi[b].next_to[dir]-=10000;
        poi[b].next_to[(dir+6)%8]-=10000;
        poi[c].next_to[(dir+2)%8]-=10000;
    }

    int correct_score(){
        double ans=1000000.0;
        ans*=n*n;
        ans/=m;
        ans*=score;
        ans/=s;
        return round(ans);
    }
    void print_board(){
        rep(i, n){
            rep(j, n){
                if(inv_board[i][j]==-1) cout<< -1 SP;
                else printf("%02d ", inv_board[i][j]);
            }
            cout<< endl;
        }
    }
    void print_point(){
        rep(i, poi.size()){
            poi[i].print();
        }
    }
    void print_out(){
        cout<< rectangle.size() <<endl;
        rep(i, rectangle.size()) rectangle[i].print();
    }
};

int output_validation(Paper paper){
    int rtn=0;
    vector<vector<int>> test_board(n, vector<int>(n));
    return rtn;
}

void inpt(){
    //cout<< "inpt" <<endl;
    s=0;
    cin>> n >> m;
    rep(i, m) cin>> x[i] >> y[i];
    rep(i, n){
        rep(j, n){
            s+=Pos(i, j).weight();
        }
    }
}

void solve(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    Paper base;
    base.init();
    // base.search_connect_all(false);
    // cout<< base.connectable_list.size() <<endl;
    // rep(i, base.connectable_list.size()){
    //     base.connectable_list[i].print();
    // }
    Paper best=base;

    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;

        Paper new_paper=base;
        // while(1){
        //     int sz=new_paper.connectable_list.size();
        //     //cout<< sz <<endl;
        //     if(sz==0) break;
        //     int index=mt()%sz;
        //     auto itr=new_paper.connectable_list.begin()+index;
        //     new_paper.connectable_list.erase(itr);
        //     new_paper.search_connect_direction(new_paper.connectable_list[index].a, true, new_paper.connectable_list[index].dir);
        // }
        // new_paper.print_out();
        // cout<< "score: " << new_paper.correct_score() <<endl;
        new_paper.random_search_amap();

        if(best.score<new_paper.score){
            best=new_paper;
        }
    }

    best.print_out();
    // cout<< "lp:" << lp <<endl;
    // cout<< best.score SP << best.correct_score() <<endl;
}

int main(){
    solve();
}
// todo
//得点計算を実装して焼けるようにする
//最悪ビームサーチでいい
//新たに追加された頂点を探索するようにするDFSっぽく
//ある頂点から伸びる辺を全削除
//ある頂点と接続している頂点につながっていた頂点から伸びる辺を全削除？
//頑張れば既存頂点から達成できるポイントを全網羅できるかと思ったけど頂点がふえていくので怪しい
//なるべく壁に近い頂点を生成できる操作を優先する？
//どこかが結ばれると結べなくなる点があるので注意

//頂点削除にも転用できそう