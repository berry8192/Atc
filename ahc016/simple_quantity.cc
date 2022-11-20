// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

#define QUESTIONS 100

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
// int liner={4,}

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp;
double end_temp=0.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

//入力
int m, eps;
string in_eps;

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

struct Query{
    string h;
    int ans;
};

// 構造体
struct Data{
    bitset<4950> b_set;
    vector<int> v_quantity;
    vector<double> graph_variance;
    // string str;
    // vector<vector<int>> board;
};

struct Graphs{
    int n, vertex, diff, turn_fig;
    double min_min_edit_distance;
	vector<Data> data;
    vector<double> min_edit_distance;
    // vector<vector<double>> graph_edit_distance;

	void init(int in_n=-1){
        if(in_n==-1) n=calc_v_annealing_size();
        else n=in_n;
        vertex=n*(n-1)/2;
        turn_fig=m*vertex/1500+1;
        // cout<< "n: " << n <<endl;
        // cout<< "vertex: " << vertex <<endl;
        data.resize(m);
        rep(i, m) data[i].graph_variance.resize(n);
        min_edit_distance.resize(m, 99999999);
        // graph_edit_distance.resize(m, vector<double>(m, -1));
        start_temp=0.0;
        
        // とりあえず初期解をつくる
        simple_create_graph();
        rep(i, m) init_v_quantity(i);
        calc_all_distances();
        calc_sum_min_edit_distance();
        // print_graph_info(); //
        // cout<< min_min_edit_distance <<endl;
    }

    int calc_v_simple_size(){
        // int tmp=int(m*(1.0+eps*0.01)*(1.0+eps*0.01)*2);
        int tmp=mt()%97+4;
        // cout<< "calc_v_simple_size: " << tmp <<endl;
        return min(100, max(4, tmp));
    }
    int calc_v_annealing_size(){
        int tmp=6+sqrt(m)*1/*+(m*m)*0.001*/+(eps*eps)*0.05+m*eps*0.03; // とりあえず適当な感じにしておく
        if(eps<=8) tmp=tmp*pow(0.95, 9-eps+m*0.01);
        if(eps==0) tmp-=1;
        if(tmp>=120) tmp=4;
        // cout<< "calc_v_size: " << tmp <<endl;
        return min(100, max(4, tmp));
    }

    void simple_create_graph(){
        // cout<< "simple_create_graph: " << diff <<endl;
        rep(i, m){
            int bit_quantity=round(vertex*i/(m-1));
            // bit_quantity=(bit_quantity*bit_quantity)/vertex;
            rep(j, min(vertex, bit_quantity)){
                data[i].b_set.set(j);
            }
            // rep(j, vertex) cout<< data[i].b_set[j];
            // cout<< endl;
            // graph_variance[i]=(bit_quantity*(100-eps)+(vertex-bit_quantity)*eps)/100.0;
            bit_quantity+=diff;
        }
    }
    void init_v_quantity(int index){
        int lp=0;
        data[index].v_quantity=vector<int>(n);
        rep(i, n-1){
            rep3(j, n, i+1){
                if(data[index].b_set.test(lp)){
                    // cout<< index SP << i SP << j <<endl;
                    data[index].v_quantity[i]++;
                    data[index].v_quantity[j]++;
                }
                lp++;
            }
        }
        sort(all(data[index].v_quantity));
        rep(i, n){
            data[index].graph_variance[i]=(data[index].v_quantity[i]*(100-eps)+(n-1-data[index].v_quantity[i])*eps)/100.0;
        }
    }
    vector<int> clac_v_quantity_from_string(string s){
        int lp=0;
        vector<int> rtn(n);
        rep(i, n-1){
            rep3(j, n, i+1){
                if(s[lp]=='1'){
                    // cout<< index SP << i SP << j <<endl;
                    rtn[i]++;
                    rtn[j]++;
                }
                lp++;
            }
        }
        sort(all(rtn));
        return rtn;
    }
    double calc_edit_distance(int index1, int index2){
        double rtn=0;
        rep(i, n){
            double tmp=abs(data[index1].graph_variance[i]-data[index2].graph_variance[i]);
            rtn+=tmp*tmp;
        }
        // rep(i, n) rtn+=abs(data[index1].v_quantity[i]-data[index2].v_quantity[i]);
        return rtn;
    }
    double calc_edit_distance_string(int index1, vector<int> v){
        double rtn=0;
        rep(i, n){
            double tmp=abs(data[index1].graph_variance[i]-v[i]);
            rtn+=tmp*tmp;
        }
        return rtn;
    }
    void calc_all_distances(){
        rep(i, m) min_edit_distance[i]=99999999;
        rep(i, m){
            rep3(j, m, i+1){
                double distance=calc_edit_distance(i, j);
                min_edit_distance[i]=min(min_edit_distance[i], distance);
                min_edit_distance[j]=min(min_edit_distance[j], distance);
                // graph_edit_distance[i][j]=distance;
                // graph_edit_distance[j][i]=distance;
            }
        }
    }
    void calc_sum_min_edit_distance(bool near_limit=false){
        double su=0.0;
        // near_limit=false;
        // if(near_limit){
        //     su=20000;
        //     rep(i, m){
        //         su=min(su, min_edit_distance[i])+10000;
        //         // su+=sqrt(min_edit_distance[i]);
        //         // su+=min_edit_distance[i];
        //     }
        // }
        rep(i, m){
            su+=log2(min_edit_distance[i]+0.1);
            // su+=sqrt(min_edit_distance[i]);
            // su+=min_edit_distance[i];
        }
        // cout<< su <<endl;
        min_min_edit_distance=su;
    }

    void output_graph(){
        rep(i, m){
            rep(j, vertex){
                cout<< data[i].b_set[j];
            }
            cout<<endl;
        }
    }
    void print_graph_info(){
        // cout<< "-------v_quantity---------" <<endl;
        // rep(i, m) PV(data[i].v_quantity);//
        // cout<< "-------graph_variance---------" <<endl;
        // rep(i, m) PV(data[i].graph_variance);//
        double mi=99999999.0, ma=-1.0;
        double ave=0;
        // cout<< "-------min_edit_distance--------" <<endl;
        rep(i, m){
            // cout<< min_edit_distance[i] <<endl;//
            mi=min(mi, min_edit_distance[i]);
            ma=max(ma, min_edit_distance[i]);
            ave+=min_edit_distance[i];
        }
        // cout<< "(min, max, ave)=(" << mi << ", " << ma << ", " << ave/m << ")" <<endl;
    }

    int guess(string s){
        // cout<< "guess()" <<endl;
        vector<int> h=clac_v_quantity_from_string(s);
        int ans=0;
        double diff=99999999.0;
        rep(i, m){
            double tmp=calc_edit_distance_string(i, h);
            if(diff>tmp){
                ans=i;
                diff=tmp;
            }
        }
        return ans;
    }

    Query gen_query(){
        // cout<< "gen_query()" <<endl;
        Query rtn;
        rtn.ans=mt()%m;
        bitset<4950> tmp=data[rtn.ans].b_set;
        rep(i, vertex){
            if(eps>mt()%100) tmp.flip(i);

            if(tmp[i]) rtn.h+='1';
            else rtn.h+='0';
        }
        return rtn;
    }
};

void inpt(){
    //cout<< "inpt" <<endl;
    cin>> m;
    cin>> in_eps;
    eps=stoi(in_eps.substr(2));
    // cout<< eps <<endl;
}

Graphs annealing_graph(int in_n=-1){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    Graphs best;
    if(in_n==-1) best.init();
    else best.init(in_n);

    //焼きなまし
    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        //cout<< lp <<endl;
        current = chrono::system_clock::now(); // 現在時刻
        double d_time=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if (d_time > TIME_LIMIT) break;

        Graphs now=best;
        // int stop_streak=0, stop_flag=0;
        int index=mt()%(m-2)+1;

        vector<int> turn_bit_index;
        rep(j, round(now.turn_fig*(TIME_LIMIT-d_time)/TIME_LIMIT)+1) turn_bit_index.push_back(mt()%now.vertex);
        rep(j, turn_bit_index.size()) now.data[index].b_set.flip(turn_bit_index[j]);
        // cout<< turn_bit_index.size() <<endl;
        now.init_v_quantity(index);
        now.calc_all_distances();
        now.calc_sum_min_edit_distance(TIME_LIMIT-d_time<100);

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * d_time / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        // cout<< now.min_min_edit_distance SP << best.min_min_edit_distance <<endl;
        double prob = exp((now.min_min_edit_distance-best.min_min_edit_distance)/temp);

        if (prob > (mt()%imax)/(double)imax){
            //改善したので変更を受け入れる
            best=now;
            // stop_flag=1;
        }
        // stop_streak++;
        // if(stop_flag) stop_streak=0;
        // if(stop_streak>10000) break;
    }
    // cout<< "lp: " << lp <<endl; //
    // output_graph();//
    // rep(i, m) PV(data[i].v_quantity);//
    // double mi_dis=9999.0;
    // rep(i, m) mi_dis=min(mi_dis, best.min_edit_distance[i]);
    // cout<< "mi_dis: " << mi_dis <<endl;
    // rep(i, m) cout<< min_edit_distance[i] <<endl;//
    return best;
}

void solve(){
    inpt();

    Graphs graphs=annealing_graph();

    cout<< graphs.n <<endl;
    graphs.output_graph();

    rep(i, QUESTIONS){
        string h;
        int ans;
        cin>> h;
        cout << graphs.guess(h) <<endl;
    }
}

void test(int lp){
    std::ofstream ofs("log.csv");
    if (!ofs){
        std::cout << "書き込み失敗" << std::endl;
        exit(1);
    }
    // ofs<< "m, eps, err, n, score" <<endl;

    double sco=0.0;
    rep(i, lp){
        m=mt()%91+10;
        eps=mt()%41;
        // m=10+10*i;
        // eps=i*4;
        m=50;
        eps=40;
        int in_n=4;

        // cout<< "m: " << m <<endl;
        // cout<< "eps: " << eps <<endl;
        if(eps<10) ofs<< m SP << "0.0" << eps <<endl;
        else ofs<< m SP << "0." << eps <<endl;
        int err=0;

        // inpt();

        Graphs graphs=annealing_graph(in_n);
        // cout<< graphs.n <<endl;
        // graphs.output_graph();
        // graphs.print_graph_info(); //
        // return; //

        rep(i, QUESTIONS){
            string h;
            int ans;
            Query query=graphs.gen_query();
            h=query.h;
            ans=query.ans;
            ofs<< ans <<endl; //
            // cout<< h <<endl; //
            int submit=graphs.guess(h);
            // cout<< submit <<endl; //
            if(ans!=submit) err++;
        }
        ofs<< "1" <<endl; // seed
        // cout<< "err: " << err <<endl;
        cout<< m << ", " << eps << ", " << err << ", " << graphs.n << ", " << round(1000000000.0*pow(0.9, err)/graphs.n) <<endl;
        sco+=round(1000000000.0*pow(0.9, err)/graphs.n);
    }
    cout<< sco/lp <<endl;
}

void ex(){
    std::ofstream ofs("log.csv");
    if (!ofs){
        std::cout << "書き込み失敗" << std::endl;
        exit(1);
    }

    for(int i=10;i<101;i+=5){
        rep3(j, 41, 0){
            int err=0;
            m=i;
            eps=j;
            Graphs graphs=annealing_graph();
            // cout<< graphs.n <<endl; //
            // graphs.output_graph(); //

            rep(i, QUESTIONS){
                string h;
                int ans;
                Query query=graphs.gen_query();
                h=query.h;
                ans=query.ans;
                // ofs<< ans <<endl; //
                // cout<< h <<endl; //
                int submit=graphs.guess(h);
                // cout<< submit <<endl; //
                if(ans!=submit) err++;
            }
            int tmp=round(1000000000.0*pow(0.9, err)/graphs.n);
        }
    }
}

void ex2(){
    std::ofstream ofs("log.csv");
    if (!ofs){
        std::cout << "書き込み失敗" << std::endl;
        exit(1);
    }

    inpt();

    rep3(k, 101, 4){
        cout<< "(m eps n) = (" << m SP << eps SP << k << ")" SP;
        int err=0;
        Graphs graphs=annealing_graph();
        // cout<< graphs.n <<endl; //
        // graphs.output_graph(); //

        rep(i, QUESTIONS){
            string h;
            int ans;
            Query query=graphs.gen_query();
            h=query.h;
            ans=query.ans;
            // ofs<< ans <<endl; //
            // cout<< h <<endl; //
            int submit=graphs.guess(h);
            // cout<< submit <<endl; //
            if(ans!=submit) err++;
        }
        int tmp=round(1000000000.0*pow(0.9, err)/graphs.n);
        cout<< err SP <<tmp <<endl;
    }
}

void ex3(){
    std::ofstream ofs("log.csv");
    if (!ofs){
        std::cout << "書き込み失敗" << std::endl;
        exit(1);
    }

    Graphs graphs;

    for(int i=0;i<41;i+=1){
        eps=i;
        for(int j=10;j<101;j+=5){
            m=j;
            int tmp=graphs.calc_v_annealing_size();
            if(j!=100) ofs<< tmp << ", ";
            else ofs<< tmp <<endl;
        }
    }
}

int main(){
    solve();
    // test(10);
    // ex();
    // ex2();
    // ex3();
}
