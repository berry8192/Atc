// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

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

// 定数周り
int INF=1000000000;
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=5900.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

int lp=0;

//入力
int n, m, d, k;
vector<int> u, v, w, x, y;
int leftmost_v_idx, left_max=1001;

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

void preview_edge(vector<int> vv){
    vector<int> pv(m, 1);
    rep(i, vv.size()) pv[vv[i]]=i+2;
    PV(pv);
}

// 構造体
typedef pair<int, int> P;
struct Edge{
    int id;
    int to;
    int cost;
    double rad; // -PI<rad<PI

    bool operator<(const Edge &in) const{
		return rad<in.rad;
	};
};

// 最初の出発辺が入ってしまうのでcost計算やパス一覧を見るときに呼ぶ側で無視する
struct Path{
    vector<int> forw, reve;
    vector<int> ford, revd;
    ll for_cost=0, rev_cost=0;

    void calc_cost_sum(){
        rep3(i, forw.size(), 1) for_cost+=w[forw[i]];
        rep3(i, reve.size(), 1) rev_cost+=w[reve[i]];
    }
};

struct Loss{
    int day, from, to;
    double loss;

    bool operator<(const Loss &in) const{
		return loss>in.loss;
	};
};

struct Day{
    int day;
    int has_edge;
    int ran;

    bool operator<(const Day &in) const{
		return has_edge!=in.has_edge ? has_edge<in.has_edge : ran<in.ran;
	};
};

struct City{
    vector<vector<int>> base_dist; // [n][n] 通行止めがない状態の2頂点間の距離
    vector<vector<vector<int>>> dist; // [d][n][n] d日目の2頂点間の距離計算用
    vector<vector<int>> edge_inv; // [n][n] 始点と終点から辺idを出す
    vector<vector<Edge>> graph; // [n][3~10] 辺をEdgeの隣接リストで持っている
    vector<int> ans, edge_priority; // [m] 辺が何日目に通行止めになるかの出力用、辺が何番目に多く使われているか
    vector<ll> edge_used_fig; // [m] 辺が全頂点対の最短距離として何回使われているか //頂点からの距離で割ってもいいかも
    vector<Path> path; // [m] 迂回ルートを保存
    vector<int> nglist; // [m][d bit] ダメな日を保存
    vector<vector<ll>> trouble; // [m][m] 辺iが通行止めのときに辺jが通行止めになると辺iがどの程度困るか
    vector<set<int>> ans_inv; // [d]{} i日目に所属している辺の集合を表す
    double best_score; // トラブル値の最小記録
    vector<int> best_ans; // トラブル値の最少記録を達成した時のans
    bitset<3000> is_outside_for; // [m] 辺のfor方向が外周の辺であるかどうか
    bitset<3000> is_outside_rev; // [m] 辺がrev方向が外周の辺であるかどうか

    vector<Loss> loss_list; // 正確な計算で伸びてしまった経路長を算出
    vector<Edge> edges;
    vector<bitset<3000>> straight_bonus;

    void init(){
        // cout<< "init" <<endl;
        base_dist.resize(n, vector<int>(n));
        dist.resize(d);
        rep(i, d) dist[i].resize(n);
        rep(i, d){
            rep(j, n){
                dist[i][j].resize(n);
            }
        }
        edge_inv.resize(n, vector<int>(n, -1));
        graph.resize(n);
        ans.resize(m, -1);
        ans_inv.resize(d);
        edge_used_fig.resize(m);
        path.resize(m);
        nglist.resize(m);
        trouble.resize(m, vector<ll>(m));
        rep(i, m){
            // ワーシャルフロイドの時は使う
            // dist[u[i]][v[i]]=w[i];
            // dist[v[i]][u[i]]=w[i];
            double rad=atan2(y[v[i]]-y[u[i]], x[v[i]]-x[u[i]]);
            double radr=atan2(y[u[i]]-y[v[i]], x[u[i]]-x[v[i]]);
            // cout<< rad SP << radr <<endl;
            graph[u[i]].push_back({i, v[i], w[i], rad});
            graph[v[i]].push_back({i, u[i], w[i], radr});
            if(rad<0) rad+=M_PI;
            edges.push_back({i, v[i], w[i], rad});
            edge_inv[u[i]][v[i]]=i;
            edge_inv[v[i]][u[i]]=-i;
        }
        rep(i, n) sort(all(graph[i]));
    }

    // dfs(どの頂点idから来たか、どのidの辺を使うか)
    void outside_dfs(int from, int edge_idx, vector<int>& path, vector<int>& pathd){
        int before_edge_id=graph[from][edge_idx].id; // 使った辺のid
        if(!path.empty() && abs(path[0])==before_edge_id) return; // 最初の辺に戻ってきたら終了
        path.push_back(before_edge_id);
        pathd.push_back(from==u[before_edge_id]); // for->1, rev->0
        int to=graph[from][edge_idx].to;
        int esz=graph[to].size();
        // cout<< "from edge of: " << before_edge_id <<endl;
        rep(i, esz){
            if(graph[to][i].id==before_edge_id){
                int use_idx=(i+1)%esz;
                Edge use_edge=graph[to][use_idx];
                // testv.push_back(use_edge.id);
                outside_dfs(to, use_idx, path, pathd);
                return;
            }
        }
    }
    void search_outside_edge(){
        // 一番左側の頂点の一番左下を向いた辺がスタート地点
        vector<int> tmp, tmp2;
        outside_dfs(leftmost_v_idx, 0, tmp, tmp2);
        int prv_v=leftmost_v_idx;
        rep(i, tmp.size()){
            tmp[i]=abs(tmp[i]);
            // cout<< prv_v SP << tmp[i] SP;
            // outside_edge.set(tmp[i]);
            if(prv_v==u[tmp[i]]){
                is_outside_for.set(tmp[i]);
                prv_v=v[tmp[i]];
                // cout<< "for" <<endl;
            }else{
                is_outside_rev.set(tmp[i]);
                prv_v=u[tmp[i]];
                // cout<< "rev" <<endl;
            }
        }
        // preview_edge(tmp);
    }
    void search_detour_route_all(){
        rep(i, m){
            int vertex_id;
            rep(j, graph[u[i]].size()){
                if(graph[u[i]][j].id==i){
                    vertex_id=j;
                    break;
                }
            }
            if(!is_outside_for[i]) outside_dfs(u[i], vertex_id, path[i].forw, path[i].ford);
            else path[i].for_cost=1000000000;
            
            rep(j, graph[v[i]].size()){
                if(graph[v[i]][j].id==i){
                    vertex_id=j;
                    break;
                }
            }
            if(!is_outside_rev[i]) outside_dfs(v[i], vertex_id, path[i].reve, path[i].revd);
            else path[i].rev_cost=1000000000;
            
            path[i].calc_cost_sum();
        }
    }
    void decide_close_day(int edge, int close_day){
        // ans[edge]=close_day;
        // if(path[edge].for_cost<path[edge].rev_cost){
        //     rep3(i, path[edge].forw.size(), 1){
        //         nglist[path[edge].forw[i]]+=(1<<close_day);
        //     }
        // }else{
        //     rep3(i, path[edge].reve.size(), 1){
        //         nglist[path[edge].reve[i]]+=(1<<close_day);
        //     }
        // }
    }
    void calc_NGlist(){
        // vector<int> days(d);
        // rep(i, m){
        //     int rot=mt()%d;
        //     rep(lp, 2*d){
        //         int j=(lp+rot)%d;
        //         // cout<< j << endl;
        //         if(days[j]==k) continue;
        //         if((nglist[i]&(1<<d)) && lp<d) continue;
        //         decide_close_day(i, j);
        //         days[j]++;
        //         break;
        //     }
        // }
    }
    void calc_trouble(){
        // ll ma=0, mi=10000000000;
        rep(i, m){
            ll weight=edge_used_fig[i]+150000*n/m;
            // ma=max(ma, weight);
            // mi=min(mi, weight);
            // weight=1;
            // ここで迂回ルートが短い方を選んでいるが、そうじゃない方がいいときがありそう
            // if(path[i].for_cost<path[i].rev_cost && !outside_edge[i]){
            //     rep3(j, path[i].forw.size(), 1){
            //         int stop_edge_id=path[i].forw[j];
            //         trouble[i][stop_edge_id]=weight*(path[stop_edge_id].rev_cost-w[stop_edge_id]);
            //     }
            // }else{
            //     rep3(j, path[i].reve.size(), 1){
            //         int stop_edge_id=path[i].reve[j];
            //         trouble[i][stop_edge_id]=weight*(path[stop_edge_id].for_cost-w[stop_edge_id]);
            //     }
            // }
            if(!is_outside_for[i]){
                int base_cost=path[i].for_cost+w[i];
                rep3(j, path[i].forw.size(), 1){
                    int stop_edge_id=path[i].forw[j];
                    if(base_cost!=path[stop_edge_id].for_cost+w[stop_edge_id]){
                        trouble[i][stop_edge_id]=weight*(path[stop_edge_id].rev_cost-w[stop_edge_id]);
                    }else{
                        trouble[i][stop_edge_id]=weight*(path[stop_edge_id].for_cost-w[stop_edge_id]);
                    }
                }
            }
            if(!is_outside_rev[i]){
                int base_cost=path[i].rev_cost+w[i];
                rep3(j, path[i].reve.size(), 1){
                    int stop_edge_id=path[i].reve[j];
                    if(base_cost!=path[stop_edge_id].rev_cost+w[stop_edge_id]){
                        trouble[i][stop_edge_id]=weight*(path[stop_edge_id].for_cost-w[stop_edge_id]);
                    }else{
                        trouble[i][stop_edge_id]=weight*(path[stop_edge_id].rev_cost-w[stop_edge_id]);
                    }
                }
            }
        }
        // cout<< mi SP << ma <<endl;
    }
    int is_separate(set<int> days){
        int rtn=0;
        for(auto itr=days.begin();itr!=days.end();itr++){
            // cout<< *itr <<endl;
            dsu ds(n);
            rep(i, m){
                if(ans[i]!=*itr) ds.merge(u[i], v[i]);
            }
            int tmp=max(ds.size(0), ds.size(1));
            // cout<< ds.size(0) SP << ds.size(1) <<endl;
            rtn+=n-tmp;
        }
        return rtn;
    }
    int over_day(){
        int rtn=0;
        rep(i, d){
            rtn+=max(0, int(k-ans_inv[i].size()));
        }
        return rtn;
    }
    // 辺id, 大本の辺の通行止め日、ルートの方向、残り迂回回数、迂回で増加した距離
    ll detour_increase_dist_dfs(int eid, int ban_day, int dir, int depth, vector<int>& tmp){
        // dir==1 ? forward_route : reverse_route
        if(ans[eid]!=ban_day){
            tmp.push_back(eid);
            return w[eid];
        }
        // rep(i, depth*2) cout SP;
        // cout<< eid SP << ban_day SP << dir SP << depth <<endl;
        if(depth==0){
            // cout<< "とどかない " << eid SP << ban_day SP << dir SP << depth <<endl;
            return INF;
        }

        // 迂回するときは自分を通らなくなるので引いておく
        ll rtn=-w[eid];
        if(dir==1 && !is_outside_for[eid]){
            rep3(i, path[eid].forw.size(), 1){
                int next_eid=path[eid].forw[i];
                if(path[eid].ford[i]){
                    rtn+=detour_increase_dist_dfs(next_eid, ban_day, 1, depth-1, tmp);
                }else{
                    rtn+=detour_increase_dist_dfs(next_eid, ban_day, 0, depth-1, tmp);
                }
            }
        }else if(dir==0 && !is_outside_rev[eid]){
            rep3(i, path[eid].reve.size(), 1){
                int next_eid=path[eid].reve[i];
                if(!path[eid].revd[i]){
                    rtn+=detour_increase_dist_dfs(next_eid, ban_day, 0, depth-1, tmp);
                }else{
                    rtn+=detour_increase_dist_dfs(next_eid, ban_day, 1, depth-1, tmp);
                }
            }
        }else{
            rtn=INF;
        }

        if(rtn<0){
            // 精度の問題で時空がゆがんでいる事があるので0にする
            rtn=0;
            // cout<< "lp: " << lp <<endl;
            // PV(path[eid].forw);
            // PV(path[eid].reve);
            // // cout<< testes SP << testes2 <<endl;
            // cout<< "rtn: " << rtn <<endl;
            // preview_edge(path[eid].forw);
            // preview_edge(path[eid].reve);
            // cout<< path[eid].for_cost SP << path[eid].rev_cost <<endl;
            // print_ans();
            // assert(0<=rtn);
        }
        return rtn;
    }
    double calc_trouble_score(){
        double rtn=0;
        rep(i, m){
            ll fpath_dist=lmax, rpath_dist=lmax;
            // double weight=w[i];
            // weight*=1000000-(x[u[i]]-500)*(x[u[i]]-500)-(x[v[i]]-500)*(x[v[i]]-500)-(y[u[i]]-500)*(y[u[i]]-500)-(y[v[i]]-500)*(y[v[i]]-500);
            // weight*=0.000001;
            // ll weight=edge_used_fig[i]+30000;
            // cout<< "i: " << i <<endl;
            vector<int> detuor_fpath, detuor_rpath;
            // int width=0;
            if(!is_outside_for[i]){
                fpath_dist=detour_increase_dist_dfs(i, ans[i], 1, 3, detuor_fpath);
                //rep(i, detuor_fpath.size()){

                    // int u0=u[detuor_fpath[i]];
                    // int u1=u[detuor_fpath[i+1]];
                    // int v0=v[detuor_fpath[i]];
                    // int v1=v[detuor_fpath[i+1]];
                    // if(edge_inv[u0][v0]!=0){
                    //     fpath_dist-=w[u0]+w[v0]-w[abs(edge_inv[u0][v0])];
                    // }else if(edge_inv[u0][v1]!=0){
                    //     fpath_dist-=w[u0]+w[v1]-w[abs(edge_inv[u0][v1])];
                    // }else if(edge_inv[u1][v0]!=0){
                    //     fpath_dist-=w[u1]+w[v0]-w[abs(edge_inv[u1][v0])];
                    // }else if(edge_inv[u1][v1]!=0){
                    //     fpath_dist-=w[u1]+w[v1]-w[abs(edge_inv[u1][v1])];
                    // }
                //}
                // cout<< shorter_path <<endl;
                // PV(detuor_rpath);
                // preview_edge(detuor_fpath);
            }
            if(!is_outside_rev[i]){
                rpath_dist=detour_increase_dist_dfs(i, ans[i], 0, 3, detuor_rpath);
                //rep(i, detuor_rpath.size()-1){
                    // int u0=u[detuor_rpath[i]];
                    // int u1=u[detuor_rpath[i+1]];
                    // int v0=v[detuor_rpath[i]];
                    // int v1=v[detuor_rpath[i+1]];
                    // if(edge_inv[u0][v0]!=0){
                    //     rpath_dist-=w[u0]+w[v0]-w[abs(edge_inv[u0][v0])];
                    // }else if(edge_inv[u0][v1]!=0){
                    //     rpath_dist-=w[u0]+w[v1]-w[abs(edge_inv[u0][v1])];
                    // }else if(edge_inv[u1][v0]!=0){
                    //     rpath_dist-=w[u1]+w[v0]-w[abs(edge_inv[u1][v0])];
                    // }else if(edge_inv[u1][v1]!=0){
                    //     rpath_dist-=w[u1]+w[v1]-w[abs(edge_inv[u1][v1])];
                    // }
                //}
                // cout<< shorter_path <<endl;
                // PV(detuor_rpath);
                // preview_edge(detuor_rpath);
            }
            // if(i==50){
            //     print_ans();
            //     exit(0);
            // }
            ll weight=edge_used_fig[i]+150000*n/m;
            // weight=1;
            rtn+=min(fpath_dist, rpath_dist)*weight;
        }
        // vector<bitset<3000>> bs(d);
        // rep(i, m) bs[ans[i]].set(i);
        // rep(i, d){
        //     rep(j, straight_bonus.size()){
        //         int tmp=straight_bonus[j].count();
        //         if(round(tmp*0.8)<=(bs[i]&straight_bonus[j]).count()){
        //             rtn*=pow(0.98, tmp);
        //         }
        //     }
        // }

        // }
        return rtn;
    }
    void move_ans(int e1, int day){
        int before_day=ans[e1];
        ans[e1]=day;
        ans_inv[before_day].erase(e1);
        ans_inv[day].insert(e1);
    }
    void swap_ans(int e1, int e2){
        int before_day1=ans[e1];
        int before_day2=ans[e2];
        swap(ans[e1], ans[e2]);
        // cout<< e1 SP << e2 SP << ans[e1] SP << ans[e2]<<endl;
        ans_inv[before_day1].erase(e1);
        ans_inv[before_day2].erase(e2);
        ans_inv[before_day1].insert(e2);
        ans_inv[before_day2].insert(e1);
        // PS(ans_inv[before_day1]);
        // PS(ans_inv[before_day2]);
    }
    void dijkstra(int start, int day, vector<int>& calc_dist, vector<int>& prev){
        // cout<< "dijkstra " << start <<endl;
        priority_queue< P, vector<P>, greater<P> > que;
        fill(all(calc_dist), INF);
        // fill(all(prev), -1);
        calc_dist[start] = 0;
        que.push(P(0, start));
        while(que.size()){
            int dd = que.top().first;
            int uu = que.top().second;
            que.pop();
            if(calc_dist[uu] != dd) continue;
            for(int i=0;i<graph[uu].size();++i){
                // ここはedge型に一旦移すと速いはず
                if(ans[graph[uu][i].id]==day) continue;
                int vv = graph[uu][i].to;
                int cost = graph[uu][i].cost;
                if(calc_dist[vv] > dd + cost){
                    calc_dist[vv] = dd + cost;
                    prev[vv] = uu;
                    que.push(P(calc_dist[vv], vv));
                }
            }
        }
    }
    vector<int> get_path(const vector<int> &prev, int t) {
        vector<int> rtn;
        for (int cur = t; prev[cur] != -1; cur = prev[cur]) {
            int tmp=abs(edge_inv[cur][prev[cur]]);
            rtn.push_back(tmp);
            // cout<< cur << "->" << prev[cur] SP << tmp SP;
            if(-1<tmp) edge_used_fig[tmp]++;
        }
        // cout<< endl;
        return rtn;
    }
    void dijkstra_base(){
        // cout<< "dijkstra_base" <<endl;
        rep(i, n){
            vector<int> prev(n, -1);
            dijkstra(i, -1, base_dist[i], prev);
            rep(j, n) get_path(prev, j);
            // PV(edge_used);
        }
        // cout<< "dijkstra_base_end" <<endl;
        // rep(i, m) edge_used_fig[i]*=-w[i];
        // edge_priority=v_inv(edge_used_fig);
    }
    void dijkstra_all(int day, vector<vector<int>>& calc_dist){
        rep(i, n){
            vector<int> prev(n, -1);
            dijkstra(i, day, calc_dist[i], prev);
        }
    }
    void calc_loss_all(){
        rep(i, d){
            rep(j, n){
                rep(l, n){
                    double loss=1.0*dist[i][j][l]/base_dist[j][l];
                    loss_list.push_back({i, j, l, loss});
                }
            }
        }
    }
    void preview_loss(){
        sort(all(loss_list));
        rep(i, 1){
            cout<< loss_list[i].day SP << loss_list[i].from SP << loss_list[i].to SP << loss_list[i].loss <<endl;
            vector<int> tmp(n), prev(n, -1);
            dijkstra(loss_list[i].from, loss_list[i].day, tmp, prev);
            vector<int> view=get_path(prev, loss_list[i].to);
            preview_edge(view);
            // PV(view);
            // rep(i, m){
            //     if(ans[i]==loss_list[i].day) view[i]=1;
            // }
            // PV(view);
        }
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
        // ランダムのやつ
        rep(i, m){
            int day=i%d;
            ans[i]=day;
            ans_inv[day].insert(i);
            // cout<< day <<endl;
        }
    }
    void init_outside_ans(){
        // rep(i, m){
        //     int day=i%(d-1)+1;
        //     ans[i]=day;
        //     ans_inv[day].insert(i);
        //     // cout<< day <<endl;
        // }
        rep(i, m){
            if(is_outside_for[i] || is_outside_rev[i]){
                move_ans(i, 0);
            }
        }
    }
    void straight_line_ans(){
        sort(all(edges));
        rep(i, m) cout<< edges[i].rad <<endl;
        int div=m/d, sur=m%d, loop=0;
        rep(i, d){
            rep(j, div+(i<sur)){
                ans[edges[loop].id]=i;
                loop++;
            }
        }
    }
    void make_straight_path_dfs(int edg, double radian, double tolerance_rad, set<int>& st, int depth){
        if(depth==0) return;
        // cout<< edg SP << radian SP << tolerance_rad <<endl;
        // PS(st);
        st.insert(edg);
        double rad=radian;
        if(radian<0) rad=edges[edg].rad;

        int uedge, vedge, nuid, nvid;
        double miu=5.0, miv=5.0;
        rep(i, graph[u[edg]].size()){
            double tmp=abs(graph[u[edg]][i].rad-rad);
            nuid=graph[u[edg]][i].id;
            // 誤差が最小、答えが決まっていない、現在計算中でもない、もと来た辺ではない
            if(tmp<miu && st.find(nuid)==st.end() && nuid!=edg){
                miu=tmp;
                uedge=nuid;
            }
        }
        if(miu<=tolerance_rad){
            make_straight_path_dfs(uedge, edges[uedge].rad, tolerance_rad, st, depth-1);
        }
        rep(i, graph[v[edg]].size()){
            double tmp=abs(graph[v[edg]][i].rad-rad);
            nvid=graph[v[edg]][i].id;
            // 誤差が最小、答えが決まっていない、現在計算中でもない、もと来た辺ではない
            if(tmp<miv && st.find(nvid)==st.end() && nvid!=edg){
                miv=tmp;
                vedge=nvid;
            }
        }
        if(miv<=tolerance_rad){
            make_straight_path_dfs(vedge, edges[vedge].rad, tolerance_rad, st, depth-1);
        }
    }
    int make_straight_path(double tolerance_rad){
        lp++;
        fill(all(ans), -1);
        vector<set<int>> lines;
        set<int> unsettled_edge;
        rep(i, m) unsettled_edge.insert(i);
        vector<int> shu(m);
        while(!unsettled_edge.empty()){
            auto itr=unsettled_edge.begin();
            set<int> tmp;
            make_straight_path_dfs(*itr, -1, tolerance_rad, tmp, 30);
            for(auto itr2=tmp.begin();itr2!=tmp.end();itr2++){
                unsettled_edge.erase(*itr2);
            }
            lines.push_back(tmp);
        }
        set<Day> days;
        rep(i, d) days.insert({i, 0, int(mt()%INF)});
        for(auto itr2=days.begin();itr2!=days.end();itr2++){
            Day tmp2=*itr2;
            // cout<< tmp2.day SP << tmp2.has_edge <<endl;
        }

        int used=0;
        rep(i, lines.size()){
            // PS(lines[i]);
            int sz=lines[i].size();
            used+=sz*sz*i;
            auto itr=days.begin();
            Day day=*itr;
            days.erase(itr);
            day.has_edge+=lines[i].size();
            days.insert(day);
            for(auto itr2=lines[i].begin();itr2!=lines[i].end();itr2++){
                ans[*itr2]=day.day;
            }
        }
        // rep(i, lines.size()){
        //     if(lines[i].size()<5) continue;
        //     bitset<3000> bs;
        //     for(auto itr2=lines[i].begin();itr2!=lines[i].end();itr2++){
        //         bs.set(*itr2);
        //     }
        //     straight_bonus.push_back(bs);
        // }
        // cout<< straight_bonus.size() <<endl;

        rep(i, d){
            dsu ds(n);
            int cnt=0;
            rep(j, m){
                if(ans[j]==i){
                    cnt++;
                    continue;
                }
                ds.merge(u[j], v[j]);
            }
            if(cnt>k) return cnt;
            if(ds.size(0)!=n) return n-ds.size(0);
        }
        return used-INF;
    }
    // ll calc_score(){
    //     // vector<vector<int>> block(d);
    //     // rep(i, m) block[ans[i]-1].push_back(i-1);
    //     ll complain_sum=0, base_sum=calc_dist_sum(base_dist);
    //     rep3(i, d){
    //         dijkstra_all(i, dist);
    //         // cout<< calc_dist_sum(dist) SP << base_sum <<endl;
    //         double day_complain=calc_dist_sum(dist)-base_sum;
    //         // day_complain/=n*(n-1);
    //         cout<< "day:" << i SP;
    //         printf("%.3lf\n", day_complain/n/(n-1));
    //         complain_sum+=day_complain;
    //     }
    //     return round(1000.0*complain_sum/(d*n*(n-1)));
    // }
    void print_ans(){
        rep(i, m) cout<< ans[i]+1 SP;
        cout<< endl;
    }
    void print_best_ans(){
        rep(i, m) cout<< best_ans[i]+1 SP;
        cout<< endl;
    }
    void debug_mode(){
        while(1){
            int tmp;
            cin>> tmp;
            if(0<tmp){
                preview_edge(path[tmp].forw);
                cout<< "for_cost: " << path[tmp].for_cost <<endl;
            }else{
                preview_edge(path[-tmp].reve);
                cout<< "rev_cost: " << path[-tmp].rev_cost <<endl;
            }
        }
    }
    ll ideal_score(){
        ll rtn=0;
        rep(i, m) rtn+=min(path[i].for_cost, path[i].rev_cost)-w[i];
        return rtn/(m);
    }
};


void inpt(){
    // cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    x.resize(n);
    y.resize(n);
    rep(i, m){
        cin>> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
    rep(i, n){
        cin>> x[i] >> y[i];
        // 最も左にある点を取得
        if(x[i]<left_max){
            left_max=x[i];
            leftmost_v_idx=i;
        }
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    inpt();
    City city;
    city.init();
    if(1.0*m/n>2.4){
        int best_tmp=INF;
        vector<int> best_ans;
        rep(i, 500){
            double rd=(mt()%600)/1000.0+0.2;
            int tmp=city.make_straight_path(rd);
            if(tmp<best_tmp){
                best_tmp=tmp;
                best_ans=city.ans;
                // city.print_ans();
                // return 0;
            }
            // cout<< tmp <<endl;
            current = chrono::system_clock::now(); // 現在時刻
            double delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
            if (delta > 2000){
                assert(delta<6000);
                if(best_tmp>0) break;
                rep(i, m) cout<< best_ans[i]+1 SP;
                cout<< endl;
                return 0;
            }
        }
    }
    // city.init_ans();
    // city.print_ans();

    city.init_ans();
    city.dijkstra_base();
    city.search_outside_edge();
    city.search_detour_route_all();
    // city.calc_trouble();
    city.best_score=1e100;

    // cout<< "min_score: " << city.ideal_score() <<endl;

    bool use_outside=false;
    while (true) { // 時間の許す限り回す
        lp++;
        // if(lp%2000==0) cout<< "lp: " << lp << " score: " << city.best_score <<endl;
        // if(lp==2) break;
        current = chrono::system_clock::now(); // 現在時刻
        double delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if (delta > TIME_LIMIT) break;
        if(delta > TIME_LIMIT>2000 && !use_outside){
            city.best_score=1e100;
            city.init_outside_ans();
            use_outside=true;
        }

        int type=mt()%100, mass=max(1.0, (TIME_LIMIT-delta-500)/200), day=mt()%d;
        int e1=mt()%m;
        int move_from=city.ans[e1];
        bool movable=true;
        // vector<int> e1(mass);
        vector<int> e2(mass);
        set<int> move_days;
        if(type<50){
            rep(i, mass){
                // e1[i]=mt()%m;
                e2[i]=(e1+mt()%(m-1))%m;
                move_days.insert(city.ans[e1]);
                move_days.insert(city.ans[e2[i]]);
            }
            rep(i, mass) city.swap_ans(e1, e2[i]);
        }else{
            // rep(i, mass){
            //     e1[i]=mt()%m;
            //     e2[i]=(e1[i]+mt()%(m-1))%m;
            //     move_days.insert(city.ans[e1[i]]);
            //     move_days.insert(city.ans[e2[i]]);
            // }
            if(city.ans_inv[day].size()==k){
                movable=false;
                continue;
            }
            city.move_ans(e1, day);
        }
        
        int iso=city.is_separate(move_days);
        int ove=city.over_day();
        // city.print_ans();
        double new_score=city.calc_trouble_score();
        // assert(0.0<new_score);
        // cout<< new_score SP << iso <<endl;
        if(iso) new_score*=iso*iso*1e10;
        if(ove) new_score*=ove*1e10;
        // if(lp%1000==0){
        //     cout<< new_score SP << iso <<endl;
        //     city.print_ans();
        // }

        // 温度関数
        double d_time=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        double temp = start_temp + (end_temp - start_temp) * d_time / TIME_LIMIT;
        double prob = exp((city.best_score-new_score)/temp);
        if (prob > (mt()%imax)/(double)imax) { // 確率probで遷移する
            city.best_ans=city.ans;
            city.best_score=new_score;
        }else{
            if(type<50){
                repr(i, mass) city.swap_ans(e1, e2[i]);
            }else{
                if(movable) city.move_ans(e1, move_from);
            }
        }
    }

    // cout<< "lp: " << lp <<endl;
    city.print_ans();
    return 0;
    
    rep(i, d) city.dijkstra_all(i, city.dist[i]);
    city.calc_loss_all();
    city.preview_loss();

    return 0;
}
