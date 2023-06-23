#include <bits/stdc++.h>
#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
using namespace atcoder;

int imax=2147483647;
long long int llimax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=6950.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int n, m, k;

// 構造体
struct Pos{
    int x;
    int y;

    Pos(){};
    Pos(int xx, int yy){
        x=xx;
        y=yy;
    }

    double euclid(Pos ipos){
        int rnd=mt()%21+100;
        rnd=100;
        return (rnd/100.0)*sqrt((x-ipos.x)*(x-ipos.x)+(y-ipos.y)*(y-ipos.y));
    }
    bool is_out_of_bounce(){
        //cout<< "out_of_bounce" <<endl;
        if(abs(x)>=10000 || abs(y)>=10000){
            // print();
            return true;
        }
        return false;
    }
    int get_id(int id){
        // print();
        return 100000*x+y;
    }
    void print(){
        cout<< "(" << x << ", " << y << ")" <<endl;
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
};

struct Town{

    void init(){
    }

    ll calc_score(){
    }
    void print_ans(){
    }
};

void inpt(){
    cin>> n >> m >> k;

    rep(i, n){
    }

    rep(i, m){
    }

    rep(i, k){
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Town best;
    best.init();
    ll best_score=best.calc_score();

    int lp=0;
    while (true){
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if(delta > TIME_LIMIT) break;

        Town town;
        town.init();
        ll score=town.calc_score();

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // double prob = exp((best_score-score)/temp); // 最小化
        double prob = exp((score-best_score)/temp); // 最大化

        if(prob>(mt()%imax)/(double)imax){
            cout<< "lp: " << lp <<endl;
            cout<< score <<endl;
            best=town;
            best_score=score;
        }
    }

    // cout<< "lp: " << lp <<endl;
    best.print_ans();

    return 0;
}
