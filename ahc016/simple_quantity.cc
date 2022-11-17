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

//焼きなましの定数
double TIME_LIMIT=4500;
double start_temp=50.0;
double end_temp=10.0;

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
    string str;
    vector<int> v_quantity;
    vector<vector<int>> board;
};

struct Graphs{
    int n, vertex, diff;
	vector<Data> data;
    vector<double> simple_variance;
    vector<int> min_edit_distance;
    vector<vector<int>> graph_edit_distance;

	void init(){
        n=calc_v_annealing_size();
        vertex=n*(n-1)/2;
        // cout<< "vertex: " << vertex <<endl;
        data.resize(m);
        simple_variance.resize(m);
        min_edit_distance.resize(m,9999);
        graph_edit_distance.resize(m, vector<int>(m, -1));
    }

    int calc_v_simple_size(){
        // int tmp=int(m*(1.0+eps*0.01)*(1.0+eps*0.01)*2);
        int tmp=mt()%97+4;
        // cout<< "calc_v_simple_size: " << tmp <<endl;
        return min(100, max(4, tmp));
    }
    int calc_v_annealing_size(){
        int tmp=m*(1.0+eps*0.01); // とりあえず適当な感じにしておく
        // cout<< "calc_v_size: " << tmp <<endl;
        return min(100, max(4, tmp));
    }

    void simple_create_graph(){
        diff=vertex/(m-1);
        int bit_quantity=0;
        rep(i, m){
            rep(j, bit_quantity){
                data[i].b_set.set(j);
            }
            simple_variance[i]=(bit_quantity*(100-eps)+(vertex-bit_quantity)*eps)/100.0;
            bit_quantity+=diff;
        }
    }
    void annealing_graph(){
        // oxの配置を焼きなまして編集距離がそれぞれ離れるようにグラフを構築する
        std::chrono::system_clock::time_point start, current;
        start = chrono::system_clock::now();

        // とりあえず初期解をつくる
        simple_create_graph();
        rep(i, m) init_v_quantity(i);
        rep(i, m){
            rep3(j, m, i+1){
                int distance=calc_edit_distance(i, j);
                min_edit_distance[i]=min(min_edit_distance[i], distance);
                min_edit_distance[j]=min(min_edit_distance[j], distance);
                // graph_edit_distance[i][j]=distance;
                // graph_edit_distance[j][i]=distance;
            }
        }
        output_graph();//

        while (true){
            current = chrono::system_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
            rep(i, m){
                int before_distance=min_edit_distance[i];
                int new_distance=9999;
                int turn_bit_index=mt()%vertex;
                data[i].b_set.flip(turn_bit_index);
                init_v_quantity(i);
                rep(j, m){
                    if(i==j) continue;
                    new_distance=min(new_distance, calc_edit_distance(i, j)+1);
                }
                if(min_edit_distance[i]<=new_distance){
                    //改善したので変更を受け入れる
                    min_edit_distance[i]=new_distance;
                }else{
                    // 改善しなかったら元に戻す
                    data[i].b_set.flip(turn_bit_index);
                    init_v_quantity(i);
                }
            }
        }
        output_graph();//
        rep(i, m) PV(data[i].v_quantity);//
        rep(i, m) cout<< min_edit_distance[i] <<endl;//
    }
    void init_v_quantity(int index){
        int lp=0;
        data[index].v_quantity=vector<int>(m);
        rep(i, m-1){
            rep3(j, m, i+1){
                if(data[index].b_set.test(lp)){
                    // cout<< index SP << i SP << j <<endl;
                    data[index].v_quantity[i]++;
                    data[index].v_quantity[j]++;
                }
                lp++;
            }
        }
        sort(all(data[index].v_quantity));
    }
    int calc_edit_distance(int index1, int index2){
        int rtn=0;
        rep(i, m) rtn+=abs(data[index1].v_quantity[i]-data[index2].v_quantity[i]);
        return rtn;
    }
    void output_graph(){
        rep(i, m){
            rep(j, vertex){
                cout<< data[i].b_set[j];
            }
            cout<<endl;
        }
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

    int guess(string s){
        // cout<< "guess()" <<endl;
        bitset<4950> h(s);
        int bit_quantity=h.count();
        // int ans=round(1.0*bit_quantity/diff);
        int ans=0;
        double diff=9999.0;
        rep(i, m){
            if(diff>abs(bit_quantity-simple_variance[i])){
                ans=i;
                diff=bit_quantity-simple_variance[i];
            }
        }
        return ans;
    }
};

void inpt(){
    //cout<< "inpt" <<endl;
    cin>> m;
    cin>> in_eps;
    eps=stoi(in_eps.substr(2));
    // cout<< eps <<endl;
}

void solve(){
    inpt();

    Graphs graphs;
    graphs.init();
    graphs.annealing_graph();
    return;
    graphs.simple_create_graph();

    cout<< graphs.n <<endl;
    rep(i, m){
        rep(j, graphs.vertex){
            cout<< graphs.data[i].b_set[j];
        }
        cout<<endl;
    }

    rep(i, QUESTIONS){
        string h;
        int ans;
        cin>> h;
        cout << graphs.guess(h) <<endl;
    }
}

void test(int lp){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    std::ofstream ofs("log.csv");
    if (!ofs){
        std::cout << "書き込み失敗" << std::endl;
        exit(1);
    }
    ofs<< "m, eps, err, n, score" <<endl;

    rep(i, lp){
        m=mt()%91+10;
        eps=mt()%41;
        // cout<< "m: " << m <<endl;
        // cout<< "eps: " << eps <<endl;
        int err=0;

        // inpt();

        Graphs graphs;
        graphs.init();
        // graphs.simple_create_graph();
        graphs.annealing_graph();
        graphs.output_graph();

        rep(i, QUESTIONS){
            string h;
            int ans;
            Query query=graphs.gen_query();
            h=query.h;
            ans=query.ans;
            int submit=graphs.guess(h);
            if(ans!=submit) err++;
        }
        // cout<< "err: " << err <<endl;
        ofs<< m << ", " << eps << ", " << err << ", " << graphs.n << ", " << round(1000000000.0*pow(0.9, err)/graphs.n) <<endl;
    }
}

int main(){
    solve();
    // test(10000);
}
