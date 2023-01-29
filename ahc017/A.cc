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
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp;
double end_temp=0.0;

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
int n, m, d, k;
vector<int> u, v, w;

// 構造体
typedef pair<int, int> P;
struct edge{int id; int to; int cost;};

struct City{
    vector<vector<int>> base_dist, dist;
    vector<vector<edge>> graph;
    vector<int> ans;
    double complain;

    void init(){
        // cout<< "init" <<endl;
        base_dist.resize(n);
        dist.resize(n);
        graph.resize(n);
        ans.resize(m);
        rep(i, n) base_dist[i].resize(n);
        rep(i, n) dist[i].resize(n);
        rep(i, m){
            // ワーシャルフロイドの時は使う
            // dist[u[i]][v[i]]=w[i];
            // dist[v[i]][u[i]]=w[i];
            graph[u[i]].push_back({i, v[i], w[i]});
            graph[v[i]].push_back({i, u[i], w[i]});
        }
    }

    void floyd_warshall() {
        for (int k=0;k<n;k++){
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    void dijkstra(int start, int day, vector<int>& calc_dist){
        // cout<< "dijkstra " << start <<endl;
        priority_queue< P, vector<P>, greater<P> > que;
        fill(all(calc_dist), INF);
        calc_dist[start] = 0;
        que.push(P(0, start));
        while(que.size()){
            int dd = que.top().first;
            int uu = que.top().second;
            que.pop();
            if(calc_dist[uu] < dd) continue;
            for(int i=0;i<graph[uu].size();++i){
                if(ans[graph[uu][i].id]==day) continue;
                int vv = graph[uu][i].to;
                int cost = graph[uu][i].cost;
                if(calc_dist[vv] > dd + cost){
                    calc_dist[vv] = dd + cost;
                    que.push(P(calc_dist[vv], vv));
                }
            }
        }
    }
    void dijkstra_all(int day, vector<vector<int>>& calc_dist){
        rep(i, n) dijkstra(i, day, calc_dist[i]);
    }
    ll calc_dist_sum(vector<vector<int>>& calc_dist){
        ll dist_sum=0;
        rep(i, n){
            rep3(j, n, i+1){
                dist_sum+=calc_dist[i][j];
            }
        }
        dist_sum*=2;
        return dist_sum;
    }
    void init_ans(){
        int lp=0;
        while(lp<m){
            ans[lp]=lp%d+1;
            lp++;
        }
    }
    ll calc_score(){
        // vector<vector<int>> block(d);
        // rep(i, m) block[ans[i]-1].push_back(i-1);
        ll complain_sum=0, base_sum=calc_dist_sum(base_dist);
        rep3(i, d+1, 1){
            dijkstra_all(i, dist);
            // cout<< calc_dist_sum(dist) SP << base_sum <<endl;
            double day_complain=calc_dist_sum(dist)-base_sum;
            // day_complain/=n*(n-1);
            cout<< "day:" << i SP;
            printf("%.3lf\n", day_complain);
            complain_sum+=day_complain;
        }
        return round(1000.0*complain_sum/(d*n*(n-1)));
    }
    void print_ans(){
        rep(i, m) cout<< ans[i] SP;
        cout<< endl;
    }
};


void inpt(){
    // cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
}

int main(){
    // cout<< "main" <<endl;
    inpt();
    City city;
    city.init();
    // city.floyd_warshall();
    // cout<< city.dist_sum <<endl;
    city.init_ans();
    city.print_ans();
    city.dijkstra_all(0, city.base_dist);
    cout<< city.calc_score() <<endl;

    return 0;
}
