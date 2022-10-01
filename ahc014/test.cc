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

string getDatetimeStr() {
    time_t t = time(nullptr);
    const tm* localTime = localtime(&t);
    std::stringstream s;
    s << localTime->tm_year + 1900;
    // setw(),setfill()で0詰め
    s << setw(2) << setfill('0') << localTime->tm_mon + 1;
    s << setw(2) << setfill('0') << localTime->tm_mday;
    s << setw(2) << setfill('0') << localTime->tm_hour;
    s << setw(2) << setfill('0') << localTime->tm_min;
    s << setw(2) << setfill('0') << localTime->tm_sec;
    // std::stringにして値を返す
    return s.str();
}

std::ofstream gofs("testcases/"+getDatetimeStr());

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4970;

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
        // if(a.out_of_bounce()){
        //     a.print();
        //     assert(!a.out_of_bounce());
        // }
        // if(out_of_bounce()){
        //     print();
        //     assert(!out_of_bounce());
        // }
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

struct Point{
    Pos pos;
    int next_to[8]={-1, -1, -1, -1, -1, -1, -1, -1};
    //8bit分をintで持つ
    int connect=0;

    Point(){};
    Point(Pos position){
        pos=position;
    }

    void print(){
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
        rep(i, permutation.size()) search_connect(permutation[i], true);
    }
    void search_connect(int index, bool execute, int direction=-1){
        //cout<< "search_connect" <<endl;
        if(direction!=-1){
            search_connect_direction(index, direction, execute);
        }else{
            int random_dir=mt()%8;
            rep(dir, 8){
                search_connect_direction(index, (random_dir+dir)%8, execute);
            }
        }
    }
    void search_connect_direction(int c, int j, bool execute){
        int a=poi[c].next_to[j];
        int b=poi[c].next_to[(j+2)%8];
        //出発点から伸びる2辺を確認
        if(a>=0 && b>=0){
            //出発点から伸びた2点を確認
            if(poi[a].next_to[(j+4)%8]<-1 || poi[b].next_to[(j+6)%8]<-1) return;
            if(poi[a].next_to[(j+2)%8]<-1 || poi[b].next_to[j]<-1) return;
            
            //cにベクトルcaとcbを作用させると目的地が出る
            Pos pos=poi[c].pos+poi[a].pos-poi[c].pos+poi[b].pos-poi[c].pos;
            //方眼紙の領域外なら中断
            if(pos.out_of_bounce()) return;
            //置きたい場所にすでに点があったら中断
            if(inv_board[pos.x][pos.y]!=-1) return;
            //置きたい点と既存の点との間に点があったら中断
            int a_next_index=poi[a].next_to[(j+2)%8];
            int b_next_index=poi[b].next_to[(j)%8];
            //-1なら隣接点なしなのでOK
            bool a_line=(a_next_index==-1);
            bool b_line=(b_next_index==-1);
            if(!a_line) a_line=(poi[a].pos.manhattan(pos)<poi[a].pos.manhattan(poi[a_next_index].pos));
            if(!b_line) b_line=(poi[b].pos.manhattan(pos)<poi[b].pos.manhattan(poi[b_next_index].pos));
            //つなぐ
            if(a_line && b_line && execute){
                rectangle.emplace_back(Rect(pos, poi[a].pos, poi[c].pos, poi[b].pos));
                add_point(pos);
                reconnect_line(j);
                delete_next_to(j, a, b, c);
                search_connect(poi.size()-1, false);
            }
        }
    }
    void add_point(Pos position){
        //position.print();
        //cout<< " add_point" <<endl;
        // idを振るための採番をしている
        // assert(0<=position.x && position.x<=n-1);
        // assert(0<=position.y && position.y<=n-1);
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
                        //reconnects.emplace_back(next_to_index);
                    }
                    search_connect(next_to_index, false);
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
    void print_out(){
        cout<< rectangle.size() <<endl;
        rep(i, rectangle.size()) rectangle[i].print();
    }
};

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

        Paper new_paper=base;

        // new_paper.search_connect((lp/8)%m, true, lp%8);
        new_paper.random_search_amap();

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
    //cout<< "lp:" << lp <<endl;
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

    gofs<< "TIME_LIMIT: " << TIME_LIMIT <<endl;
    // gofs<< "start_temp: " << start_temp <<endl;
    // gofs<< "end_temp: " << end_temp <<endl;
    gofs<< "seed: " << seed <<endl;
    gofs<< "TEST_CASES: " << TEST_CASE <<endl;
    gofs<< "score sum: " << score_sum <<endl;
    gofs<< "average: " << 1.0*score_sum/TEST_CASE <<endl;
}
// todo
//得点計算を実装して焼けるようにする
//最悪ビームサーチでいい
