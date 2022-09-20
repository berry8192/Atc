// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

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

int TEST_CASE=100;
int testcase=0;
string path = "testcases/";
vector<string> file_in_paths;
vector<string> file_out_paths;

void setup_input(){
    rep(i, TEST_CASE){
        int no=i+10000;
        string tmp="testcases/"+to_string(no).substr(1, 4)+".txt";
        file_in_paths.push_back(tmp);
        file_out_paths.push_back(tmp.substr(0, 15)+"out");
    }
    sort(all(file_in_paths));
    sort(all(file_out_paths));
}

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

//入力
int n, m, s;
int x[350], y[350];

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp=50.0;
double end_temp=10.0;

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
        assert(!a.out_of_bounce());
        assert(!out_of_bounce());
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
    void operator+=(const Pos pos){
        x+=pos.x;
        y+=pos.y;
    }
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

struct Point{
    vector<int> par;
    Pos pos;
    int next_to[8]={-1, -1, -1, -1, -1, -1, -1, -1};
    //8bit分をintで持つ
    int connectable=0;

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
    set<int> connectable;
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
    void search_connect(int index){
        //cout<< "search_connect" <<endl;
        int i=index;
        int random_dir=mt()%8;
        rep(dir, 8){
            int j=(random_dir+dir)%8;
            int a_index=poi[i].next_to[j];
            int b_index=poi[i].next_to[(j+2)%8];
            //出発点から伸びる2辺を確認
            if(a_index>=0 && b_index>=0){
                assert(a_index<poi.size());
                assert(b_index<poi.size());
                //出発点から伸びた2点を確認
                if(poi[a_index].next_to[(j+4)%8]<-1 || poi[b_index].next_to[(j+6)%8]<-1) continue;
                if(poi[a_index].next_to[(j+2)%8]<-1 || poi[b_index].next_to[j]<-1) continue;
                if(point_can_be_add(a_index, b_index, i, j)){
                    // poi[i].connectable+=(1<<j);
                    // connectable.insert(i);
                }
            }
        }
    }
    bool point_can_be_add(int a, int b, int c, int dir){
        //cout<< "point_can_be_add" <<endl;
        // if(c>70){
        //     cout<< "70over" <<endl;
        // }
        double x=(poi[a].pos.x+poi[b].pos.x)/2.0;
        double y=(poi[a].pos.y+poi[b].pos.y)/2.0;
        x+=x-poi[c].pos.x;
        y+=y-poi[c].pos.y;
        Pos pos=Pos(round(x), round(y));
        //方眼紙の領域外なら中断
        if(pos.out_of_bounce()) return false;
        //置きたい場所にすでに点があったら中断
        assert(0<=pos.x);
        assert(0<=pos.y);
        assert(pos.x<=n-1);
        assert(pos.y<=n-1);
        if(inv_board[pos.x][pos.y]!=-1) return false;
        //置きたい点と既存の点との間に点があったら中断
        int a_next_index=poi[a].next_to[(dir+2)%8];
        int b_next_index=poi[b].next_to[(dir)%8];
        assert(a_next_index<int(poi.size()));
        assert(b_next_index<int(poi.size()));
        //-1なら隣接点なしなのでOK
        bool a_line=(a_next_index==-1);
        bool b_line=(b_next_index==-1);
        if(!a_line) a_line=(poi[a].pos.manhattan(pos)<poi[a].pos.manhattan(poi[a_next_index].pos));
        if(!b_line) b_line=(poi[b].pos.manhattan(pos)<poi[b].pos.manhattan(poi[b_next_index].pos));
        //つなぐ
        if(a_line && b_line){
            rectangle.emplace_back(Rect(pos, poi[a].pos, poi[c].pos, poi[b].pos));
            add_point(pos);
// cout<< poi.size()-1 SP << a SP << c SP << b <<endl;
// poi[poi.size()-1].print();
// poi[a].print();
// poi[c].print();
// poi[b].print();
            reconnect_line(dir);
// poi[poi.size()-1].print();
// poi[a].print();
// poi[c].print();
// poi[b].print();
            delete_next_to(dir, a, b, c);
// poi[poi.size()-1].print();
// poi[a].print();
// poi[c].print();
// poi[b].print();
// rectangle[rectangle.size()-1].print(c);
// print_board();
        }

        return true;
    }
    void reconnect_line(int dir){
        //cout<< "reconnect_line" <<endl;
        dir=(dir+4)%8;
        int add_index=poi.size()-1;
        rep(i, 8){
            if(i==dir || i==(dir+2)%8) continue;
            Pos pos=poi[add_index].pos+d8[i];
            while(!pos.out_of_bounce()){
                int next_to_index=inv_board[pos.x][pos.y];
                if(next_to_index!=-1){
                    if(poi[next_to_index].next_to[(i+4)%8]<-1){
                        poi[add_index].next_to[i]-=10000;
                        break;
                    }else if(poi[next_to_index].next_to[(i+4)%8]>=0){
                        poi[next_to_index].next_to[(i+4)%8]=add_index;
                        poi[add_index].next_to[i]=next_to_index;
                        break;
                    }
                    //assert(poi[next_to_index].next_to[(i+4)%8]=-1);
                    poi[next_to_index].next_to[(i+4)%8]=add_index;
                    poi[add_index].next_to[i]=next_to_index;
                    break;
                }
                pos+=d8[i];
            }
        }
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
    void search_connect_all(){
        vector<int> permutation(poi.size());
        rep(i, poi.size()) permutation[i]=i;
        shuffle(all(permutation), mt);
        rep(i, permutation.size()) search_connect(permutation[i]);
    }
    void random_search(){
        int prev_score;
        do{
            prev_score=score;
            search_connect_all();
        }while(prev_score<score);
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
    std::ifstream ifs(file_in_paths[testcase]);
    if (!ifs){
        std::cout << file_in_paths[testcase] << " 読み込み失敗" << std::endl;
        exit(1);
    }
    cout<< "opened " << file_in_paths[testcase] <<endl;

    s=0;
    ifs>> n >> m;
    rep(i, m) ifs>> x[i] >> y[i];
    rep(i, n){
        rep(j, n){
            s+=Pos(i, j).weight();
        }
    }
}

int solve(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    Paper base;
    base.init();
    Paper best=base;

    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
        //cout<< poi_size SP << best.poi.size() <<endl;
        //poi_size=best.poi.size();
        Paper new_paper=base;
        new_paper.random_search();
        if(best.score<new_paper.score){
            best=new_paper;
        }
    }

    std::ofstream ofs(file_out_paths[testcase]);
    if (!ofs){
        std::cout << file_out_paths[testcase] << " 書き込み失敗" << std::endl;
        return -imax;
    }

    //best.print_out();
    ofs<< best.rectangle.size() <<endl;
    rep(i, best.rectangle.size()){
        ofs<< best.rectangle[i].p1.x SP;
        ofs<< best.rectangle[i].p1.y SP;
        ofs<< best.rectangle[i].p2.x SP;
        ofs<< best.rectangle[i].p2.y SP;
        ofs<< best.rectangle[i].p3.x SP;
        ofs<< best.rectangle[i].p3.y SP;
        ofs<< best.rectangle[i].p4.x SP;
        ofs<< best.rectangle[i].p4.y <<endl;
    }
    cout<< "lp:" << lp <<endl;
    cout<< best.score SP << best.correct_score() <<endl;
    return best.correct_score();
}

ll test(){
    ll point=0;
    
    rep(i, TEST_CASE){
        point+=solve();
        testcase++;
    }

    return point;
}

int main(){
    setup_input();
    ll score_sum=test();
    cout<< "score sum:" << score_sum <<endl;
}
// todo
//得点計算を実装して焼けるようにする
//最悪ビームサーチでいい
