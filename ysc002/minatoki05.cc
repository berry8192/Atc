#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

#define N_SIZE 100
#define M_SIZE 8
#define ALPHA 5

using namespace std;

//定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=985;
double start_temp=100.0;
double end_temp=10.0;

//乱数の準備
// int seed=1;
auto seed=(unsigned)time(NULL);
mt19937_64 mt(seed);

struct Pos{
	int x;
    int y;

    Pos(){}
    Pos(int ix, int iy){
        x=ix;
        y=iy;
    }

	bool operator<(const Pos &in) const{
		return x!=in.x ? x<in.x : y<in.y;
	};
    bool is_oob(){
        return (x<0 || y<0 || 1000<x || 1000<y);
    }
    int euclid(Pos p){
        return (p.x-x)*(p.x-x)+(p.y-y)*(p.y-y);
    }
    void operator+=(const Pos pos){
        x+=pos.x;
        y+=pos.y;
    }
};

struct WayPoint{
    int t;
    Pos pos;

    WayPoint(){}
    WayPoint(int it, Pos ipos){
        t=it;
        pos=ipos;
    }

    int dist(WayPoint wp){
        int dis=pos.euclid(wp.pos);
        if(t==1) dis*=ALPHA;
        if(wp.t==1) dis*=ALPHA;
        return dis;
    }
};

struct Travel{
    Pos stations[M_SIZE];
    vector<WayPoint> wp;
    vector<int> tour;

    int score(){
        set<int> st;
        ll s=0;
        rep(i, tour.size()-1){
            s+=wp[tour[i]].dist(wp[tour[i+1]]);
            if(tour[i]<N_SIZE) st.insert(tour[i]);
        }
        if(st.size()!=N_SIZE) return -100000000;
        double base=1000000000.0;
        base/=1000+sqrt(s);
        base=round(base);
        return base;
    }
    void print(){
        rep3(i, N_SIZE+M_SIZE, N_SIZE) cout<< wp[i].pos.x SP << wp[i].pos.y <<endl;
        cout<< tour.size() <<endl;
        rep(i, tour.size()){
            cout<< wp[tour[i]].t SP;
            if(wp[tour[i]].t==1) cout<< tour[i]+1 <<endl;
            else cout<< tour[i]-N_SIZE+1 <<endl;
        }
    }

    void zatsu_ans(){
        rep(i, N_SIZE) tour.push_back(i);
        tour.push_back(0);
    }
};

//入力など
int n, m;
Pos planets[N_SIZE];

void inpt(){
    cin>> n >> m;
    rep(i, N_SIZE){
        cin>> planets[i].x >> planets[i].y;
        // a[i]=mt()%1001;
        // b[i]=mt()%1001;
        // cout<< a[i] SP << b[i] <<endl;
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    //入力
    inpt();

    Travel base;
    rep(i, N_SIZE) base.wp.push_back({1, planets[i]});
    rep(i, M_SIZE) base.wp.push_back({2, {int(mt()%1001), int(mt()%1001)}});

    Travel best=base;
    best.zatsu_ans();
    // cout<< base.score() <<endl;
    // base.print();
    // return 0;

    //焼きなまし
    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        //cout<< lp <<endl;
        // if(lp%100==0){
            current = chrono::system_clock::now(); // 現在時刻
            if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
        // }
        
        // if(lp==400000) break;

        Travel travel=best;
        int rp=mt()%1+1;
        int ng=0;
        rep(i, rp){
            int type=mt()%3+1;
            int idx, val;
            Pos mov;
            //cout<< "type:" << type <<endl;
            if(type==1){
                // 訪問追加
                idx=mt()%(travel.tour.size()-2)+1;
                val=mt()%travel.wp.size();
                auto itr=travel.tour.begin()+idx;
                travel.tour.insert(itr, val);
            }else if(type==2){
                // 訪問削除
                idx=mt()%(travel.tour.size()-2)+1;
                auto itr=travel.tour.begin()+idx;
                travel.tour.erase(itr);
            }else if(type==3){
                // ステーション挿入
                idx=mt()%M_SIZE+N_SIZE;
                mov={int(mt()%21-10), int(mt()%21-10)};
                travel.wp[idx].pos+=mov;
                if(travel.wp[idx].pos.is_oob()){
                    ng=1;
                    break;
                }
            }else{
                // ステーション削除
            }
        }
        if(ng) continue;

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // double temp=100;
        // 遷移確率関数(最大化の場合)
        double prob = exp((travel.score()-best.score())/temp);

        if (prob > (mt()%imax)/(double)imax) { // 確率probで遷移する
            // if(lp%1000==0){
            //     cout<< "lp:" << lp <<endl;
            //     cout<< best.score() <<endl;
            // }
            best=travel;
        }else{
            
        }
    }

    best.print();

	return 0;
}