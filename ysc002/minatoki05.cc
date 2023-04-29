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
double end_temp=1.0;

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
    void fix_oob(){
        x=max(0, min(1000, x));
        y=max(0, min(1000, y));
    }
    int euclid(Pos p){
        int rtn=0;
        if(abs(p.x-x)>1000){
            cout<< x SP << p.x <<endl;
            // exit(0);
        }
        assert(abs(p.x-x)<1000);
        assert(abs(p.y-y)<1000);
        rtn+=(p.x-x)*(p.x-x);
        rtn+=(p.y-y)*(p.y-y);
        assert(rtn>=0);
        return rtn;
        // return (p.x-x)*(p.x-x)+(p.y-y)*(p.y-y);
    }
    double angle(Pos p){
        return atan2(y-p.y, x-p.x);
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
        assert(dis>=0);
        if(t==1) dis*=ALPHA;
        if(wp.t==1) dis*=ALPHA;
        assert(dis>=0);
        return dis;
    }
};

struct Travel{
    vector<WayPoint> wp;
    vector<int> tour;
    vector<int> sta_route;
    vector<vector<pair<double, int>>> cluster;

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

    void reset_cluster(){
        // cout<< "reset_cluster" <<endl;
        cluster.clear();
        cluster.resize(M_SIZE);
        rep3(i, N_SIZE, 1){
            int idx;
            int mi=imax;
            rep3(j, N_SIZE+M_SIZE, N_SIZE){
                int dis=wp[j].pos.euclid(wp[i].pos);
                if(dis<mi){
                    mi=dis;
                    idx=j;
                }
            }
            cluster[idx-N_SIZE].push_back({wp[i].pos.angle(wp[idx].pos), i});
        }
        rep(i, M_SIZE) sort(all(cluster[i]));
    }
    void reset_sta_route(){
        // cout<< "reset_sta_route" <<endl;
        vector<pair<double, int>> pai;
        Pos cent={500, 500};
        rep3(i, N_SIZE+M_SIZE, N_SIZE) pai.push_back({wp[i].pos.angle(cent), i-N_SIZE});
        sort(all(pai));
        int idx;
        rep(i, M_SIZE){
            if(pai[i].second==0){
                idx=i;
                break;
            }
        }
        sta_route.clear();
        rep(i, M_SIZE){
            sta_route.push_back(pai[(i+idx)%M_SIZE].second);
            // cout<< sta_route[i] <<endl;
        }
    }
    void reset_pla_route(){
        // cout<< "reset_pla_route" <<endl;
        tour.clear();
        tour.push_back(0);
        rep(i, M_SIZE){
            // cout<< "i: " << sta_route[i] <<endl;
            tour.push_back(sta_route[i]+N_SIZE);
            rep(j, cluster[sta_route[i]].size()){
                // cout<< "j: " << j <<endl;
                tour.push_back(cluster[sta_route[i]][j].second);
                tour.push_back(sta_route[i]+N_SIZE);
            }
        }
        tour.push_back(0);
    }
    void cut_route(){
        rep(i, tour.size()-2){
            if(tour[i]<N_SIZE && tour[i+1]>=N_SIZE && tour[i+2]<N_SIZE){
                int bef=wp[tour[i]].dist(wp[tour[i+1]])+wp[tour[i+2]].dist(wp[tour[i+1]]);
                int aft=wp[tour[i]].dist(wp[tour[i+2]]);
                assert(bef>=0);
                assert(aft>=0);
                if(aft<bef){
                    // cout<< bef SP <<aft <<endl;
                    auto itr=tour.begin()+i+1;
                    tour.erase(itr);
                }
            }
        }
    }
    void move_station(){
        // cout<< "move_station" <<endl;
        int idx=mt()%M_SIZE+N_SIZE;
        wp[idx].pos+={int(mt()%21-10), int(mt()%21-10)};
        wp[idx].pos.fix_oob();
        assert(!wp[idx].pos.is_oob());
        reset_cluster();
        reset_sta_route();
        reset_pla_route();
        cut_route();
    }
    void zatsu_ans(){
        rep(i, N_SIZE) tour.push_back(i);
        tour.push_back(0);
    }
};

//入力など
int n, m;
Pos planets[N_SIZE];
Pos initial_pos[M_SIZE]={{167, 167}, {500, 167}, {834, 167}, {334, 500}, {667, 500}, {167, 834}, {500, 834}, {834, 834}};

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
    rep(i, M_SIZE) base.wp.push_back({2, initial_pos[i]});

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
        travel.move_station();

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // temp=10;
        // 遷移確率関数(最大化の場合)
        double prob = exp((travel.score()-best.score())/temp);
        // cout<< travel.score() <<endl;
        // cout<< best.score() <<endl;

        if (prob > (mt()%imax)/(double)imax) { // 確率probで遷移する
            // if(lp%100==0){
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