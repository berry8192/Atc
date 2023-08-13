#include <bits/stdc++.h>
// #include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
// using namespace atcoder;

// std::ofstream outputFile("log.csv");

// template <class T> void PV(T pvv) {
// 	if(!pvv.size()) return;
// 	rep(i, pvv.size()-1) outputFile << pvv[i] SP;
// 	outputFile<< pvv[pvv.size()-1] <<endl;
// }
// template <class T>void PVV(T pvv) {
// 	rep(i, pvv.size()){
// 		rep(j, pvv[i].size()){
// 			outputFile << pvv[i][j] SP;
// 		}
// 		outputFile << endl;
// 	}
// }
// template <class T> void PM(T pm) {
//     // cout<< "{";
// 	for(auto m : pm){
// 		outputFile<< "(" << m.first << "->" << m.second << "), ";
// 	}
// 	// cout<< "}";
// 	outputFile<<endl;
// }

double normsdist[]={0.5, 0.496011, 0.492022, 0.488033, 0.484047, 0.480061, 0.476078, 0.472097, 0.468119, 0.464144, 0.460172, 0.456205, 0.452242, 0.448283, 0.44433, 0.440382, 0.436441, 0.432505, 0.428576, 0.424655, 0.42074, 0.416834, 0.412936, 0.409046, 0.405165, 0.401294, 0.397432, 0.39358, 0.389739, 0.385908, 0.382089, 0.378281, 0.374484, 0.3707, 0.366928, 0.363169, 0.359424, 0.355691, 0.351973, 0.348268, 0.344578, 0.340903, 0.337243, 0.333598, 0.329969, 0.326355, 0.322758, 0.319178, 0.315614, 0.312067, 0.308538, 0.305026, 0.301532, 0.298056, 0.294598, 0.29116, 0.28774, 0.284339, 0.280957, 0.277595, 0.274253, 0.270931, 0.267629, 0.264347, 0.261086, 0.257846, 0.254627, 0.251429, 0.248252, 0.245097, 0.241964, 0.238852, 0.235762, 0.232695, 0.22965, 0.226627, 0.223627, 0.22065, 0.217695, 0.214764, 0.211855, 0.20897, 0.206108, 0.203269, 0.200454, 0.197662, 0.194894, 0.19215, 0.18943, 0.186733, 0.18406, 0.181411, 0.178786, 0.176186, 0.173609, 0.171056, 0.168528, 0.166023, 0.163543, 0.161087, 0.158655, 0.156248, 0.153864, 0.151505, 0.14917, 0.146859, 0.144572, 0.14231, 0.140071, 0.137857, 0.135666, 0.1335, 0.131357, 0.129238, 0.127143, 0.125072, 0.123024, 0.121001, 0.119, 0.117023, 0.11507, 0.11314, 0.111233, 0.109349, 0.107488, 0.10565, 0.103835, 0.102042, 0.100273, 0.098525, 0.096801, 0.095098, 0.093418, 0.091759, 0.090123, 0.088508, 0.086915, 0.085344, 0.083793, 0.082264, 0.080757, 0.07927, 0.077804, 0.076359, 0.074934, 0.073529, 0.072145, 0.070781, 0.069437, 0.068112, 0.066807, 0.065522, 0.064256, 0.063008, 0.06178, 0.060571, 0.05938, 0.058208, 0.057053, 0.055917, 0.054799, 0.053699, 0.052616, 0.051551, 0.050503, 0.049471, 0.048457, 0.04746, 0.046479, 0.045514, 0.044565, 0.043633, 0.042716, 0.041815, 0.040929, 0.040059, 0.039204, 0.038364, 0.037538, 0.036727, 0.03593, 0.035148, 0.034379, 0.033625, 0.032884, 0.032157, 0.031443, 0.030742, 0.030054, 0.029379, 0.028716, 0.028067, 0.027429, 0.026803, 0.02619, 0.025588, 0.024998, 0.024419, 0.023852, 0.023295, 0.02275, 0.022216, 0.021692, 0.021178, 0.020675, 0.020182, 0.019699, 0.019226, 0.018763, 0.018309, 0.017864, 0.017429, 0.017003, 0.016586, 0.016177, 0.015778, 0.015386, 0.015003, 0.014629, 0.014262, 0.013903, 0.013553, 0.013209, 0.012874, 0.012545, 0.012224, 0.011911, 0.011604, 0.011304, 0.011011, 0.010724, 0.010444, 0.01017, 0.009903, 0.009642, 0.009387, 0.009137, 0.008894, 0.008656, 0.008424, 0.008198, 0.007976, 0.00776, 0.007549, 0.007344, 0.007143, 0.006947, 0.006756, 0.006569, 0.006387, 0.00621, 0.006037, 0.005868, 0.005703, 0.005543, 0.005386, 0.005234, 0.005085, 0.00494, 0.004799, 0.004661, 0.004527, 0.004397, 0.004269, 0.004145, 0.004025, 0.003907, 0.003793, 0.003681, 0.003573, 0.003467, 0.003364, 0.003264, 0.003167, 0.003072, 0.00298, 0.00289, 0.002803, 0.002718, 0.002635, 0.002555, 0.002477, 0.002401, 0.002327, 0.002256, 0.002186, 0.002118, 0.002052, 0.001988, 0.001926, 0.001866, 0.001807, 0.00175, 0.001695, 0.001641, 0.001589, 0.001538, 0.001489, 0.001441, 0.001395, 0.00135, 0.001306, 0.001264, 0.001223, 0.001183, 0.001144, 0.001107, 0.00107, 0.001035, 0.001001, 0.000968, 0.000936, 0.000904, 0.000874, 0.000845, 0.000816, 0.000789, 0.000762, 0.000736, 0.000711, 0.000687, 0.000664, 0.000641, 0.000619, 0.000598, 0.000577, 0.000557, 0.000538, 0.000519, 0.000501, 0.000483, 0.000467, 0.00045, 0.000434, 0.000419, 0.000404, 0.00039, 0.000376, 0.000362, 0.00035, 0.000337, 0.000325, 0.000313, 0.000302, 0.000291, 0.00028, 0.00027, 0.00026, 0.000251, 0.000242, 0.000233, 0.000224, 0.000216, 0.000208, 0.0002, 0.000193, 0.000185, 0.000179, 0.000172, 0.000165, 0.000159, 0.000153, 0.000147, 0.000142, 0.000136, 0.000131, 0.000126, 0.000121, 0.000117, 0.000112};

int imax=2147483647;
long long llimax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=3900.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

struct Compare;
struct Space;

int l, n, s;

double normal_distribution_p(int delta){
    // sはグローバルから
    return exp(-1.0*delta*delta/(2*s*s))/(s*2.506628274631);
}

void normalize(double &a, double &b) {
    double magnitude = (a+b);
    a /= magnitude;
    b /= magnitude;
}

// 構造体
struct Pos{
    int y;
    int x;

    Pos(){};
    Pos(int yy, int xx){
        y=yy;
        x=xx;
    }

    void bounce(){
        y=(y+l)%l;
        x=(x+l)%l;
    }
    void print(){
        cout<< "(" << y << ", " << x << ")" <<endl;
    }
    Pos operator+(const Pos pos){
        Pos rtn;
        rtn.y=y+pos.y;
        rtn.x=x+pos.x;
        return rtn;
    }
    Pos operator-(const Pos pos){
        Pos rtn;
        rtn.y=y-pos.y;
        rtn.x=x-pos.x;
        return rtn;
    }
};

Pos d4[]={{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
Pos dm[]={{0, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {0, 2}, {-2, 0}, {0, -2}, {2, 0}, {0, 3}, {-3, 0}, {0, -3}, {3, 0}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

Pos exit_cells[110];

struct Compare{
	int idx;
	int val;

	bool operator<(const Compare &in) const{
		return val!=in.val ? val<in.val : idx<in.idx;
	};
};

struct Space{
    Pos e_cells[110]; // 入力をコピーしてくる
    vector<vector<int>> p; // システムに渡す配置
    vector<Compare> compare; // 計測結果保存用かつ並べ替え用
    int e[110]; // 出力するE
    vector<int> allowable_cell; // セルに設定できる値のリスト
    int acsz; // セルから得られる情報量
    vector<vector<int>> cells_setting; // セルの各地点にどの値を設定しているか、allowable_cellの添え字にすると欲しい値になる
    map<ll, int> setting_e_cells_map;

    void init(){
        rep(i, n) e_cells[i]=exit_cells[i];
        compare.resize(n);
        if(s==1) setting_allowable_zero();
        else setting_allowable();
        p.resize(l, vector<int>(l));
    }

    void sample_placement(){
        rep(i, l){
            rep(j, l){
                p[i][j]=-1;
            }
        }
        rep(i, n){
            p[e_cells[i].y][e_cells[i].x]=i*10;
        }
        half_normalize_placement();
        print_placement();
    }
    void random_placement(){
        vector<vector<int>> shortest_cells_setting, shortest_p;
        map<ll, int> shortest_setting_e_cells_map;
        int min_cs_length=26;
        rep(lp, 100){
            int cs_length=placement();
            if(cs_length<min_cs_length){
                shortest_cells_setting=cells_setting;
                shortest_p=p;
                shortest_setting_e_cells_map=setting_e_cells_map;
                min_cs_length=cs_length;
            }
        }
        cells_setting=shortest_cells_setting;
        p=shortest_p;
        setting_e_cells_map=shortest_setting_e_cells_map;
        // PVV(cells_setting);
        // PM(setting_e_cells_map);
        normalize_placement();
        print_placement();
    }
    int placement(){
        cells_setting.clear();
        cells_setting.resize(n);
        setting_e_cells_map.clear();
        rep(i, l){
            rep(j, l){
                p[i][j]=-1;
            }
        }
        vector<ll> current_cells_setting(n);
        ll base=1;
        rep(i, 25){
            // マンハッタン距離3以内のセルは25個ある
            map<ll, int> setting_map;
            rep(j, n){
                Pos npos=e_cells[j]+dm[i];
                npos.bounce();
                int p_val=p[npos.y][npos.x];
                int set_val;
                if(p_val==-1){
                    // 値が入っていなければ自由に設定する
                    int idx;
                    if(n<(1<<i)){
                        // なかなか決まらないときはランダムにする
                        idx=mt()%acsz;
                    }else{
                        idx=j/(1<<i)%acsz;
                    }
                    p[npos.y][npos.x]=allowable_cell[idx];
                    cells_setting[j].push_back(idx);
                    set_val=idx;
                }else{
                    // 値が入っている場合はその値を反映させる
                    // if(p_val==1000){
                    //     cells_setting[j].push_back(1);
                    //     set_val=1;
                    // }else{
                    //     cells_setting[j].push_back(p_val/(8*s));
                    //     set_val=p_val/(8*s);
                    // }
                    rep(k, allowable_cell.size()){
                        if(p_val==allowable_cell[k]){
                            cells_setting[j].push_back(k);
                            set_val=k;
                            break;
                        }
                    }
                }
                current_cells_setting[j]+=base*set_val;
                setting_map[current_cells_setting[j]]=j;
            }
            if(setting_map.size()==n){
                setting_e_cells_map=setting_map;
                break;
            }
            base*=acsz;
        }
        return cells_setting[0].size();
    }
    void sample_measurement(){
        int s_try=int(sqrt(s))*2+1;
        rep(i, n){
            int tmp=0;
            rep(j, s_try){
                tmp+=query(i, {0, 0});
            }
            compare[i]={i, tmp/s_try};
        }
        // sort_guess();
        sample_guess();
    }
    void measurement(){
        // PM(setting_e_cells_map);
        // outputFile<< cells_setting[0].size() <<endl;
        rep(i, n){
            ll base=1;
            ll setting=0;
            rep(j, cells_setting[i].size()){
                // int lp=(s*8+999)/1000;
                // // int lp=9500/(n*cells_setting[i].size());
                // while(lp*n*cells_setting[i].size()>10000) lp--;
                int idx;
                if(s<125){
                    idx=single_query(i, dm[j]);
                }else if(s<333){
                    idx=over_query(i, dm[j]);
                }else{
                    // idx=binary_query(i, dm[j]); // TODO
                    int lp=(s*8+999)/1000;
                    while(lp*n*cells_setting[i].size()>10000) lp--;
                    idx=multi_query(i, dm[j], lp);
                }
                setting+=base*idx;
                base*=acsz;
            }
            // outputFile<< setting <<endl;
            // PM(setting_e_cells_map);
            if(setting_e_cells_map.find(setting)!=setting_e_cells_map.end()){
                e[i]=setting_e_cells_map[setting];
            }else{
                e[i]=-1;
            }
        }
    }

    void fill_ans(){
        set<int> remain;
        rep(i, n) remain.insert(i);
        rep(i, n){
            if(e[i]!=-1) remain.erase(e[i]);
        }
        rep(i, n){
            if(e[i]==-1){
                e[i]=*remain.begin();
                remain.erase(remain.begin());
            }
        }
    }
    void setting_allowable_zero(){
        allowable_cell={493, 500, 507};
        acsz=allowable_cell.size();
    }
    void setting_allowable(){
        // いったん4σの間隔をとる、これで99.99%確保
        int sigma_width=4;
        int l=max(0, 500-sigma_width*s);
        int r=min(1000, 500+sigma_width*s);
        allowable_cell={l, r};
        acsz=allowable_cell.size();
        // outputFile<< "allowable_cell: " << l SP << r <<endl;
        // outputFile<< "acsz: " << acsz <<endl;
    }
    void normalize_placement(){
        vector<Pos> emp;
        rep(i, l){
            rep(j, l){
                if(p[i][j]==-1) emp.push_back({i, j});
            }
        }
        // cout<< "normalize_placement: " << emp.size() <<endl;
        rep(lp, 100){
            rep(i, emp.size()){
                normalize4(emp[i]);
            }
            repr(i, emp.size()){
                normalize4(emp[i]);
            }
        }
    }
    void normalize4(Pos pos){
        int su=0;
        int div=0;
        rep(j, 4){
            Pos npos=pos+d4[j];
            npos.bounce();
            if(p[npos.y][npos.x]!=-1){
                su+=p[npos.y][npos.x];
                div++;
            }
        }
        // outputFile<< su SP << div <<endl;
        if(div) p[pos.y][pos.x]=su/div;
    }
    void half_normalize_placement(){
        rep(i, n){
            rep(j, 4){
                Pos npos=e_cells[i]+d4[j];
                npos.bounce();
                if(p[npos.y][npos.x]==-1) p[npos.y][npos.x]=i*5;
            }
        }
    }
    void sort_guess(){
        sort(all(compare));
        rep(i, n) e[i]=compare[i].idx;
    }
    void sample_guess(){
        rep(i, n){
            e[i]=round(compare[i].val/10.0);
            e[i]=max(0, min(n-1, e[i]));
        }
    }
    int over_query(int i, Pos pos){
        while(1){
            int tmp=query(i, pos);
            if(tmp<=allowable_cell[0]) return 0;
            if(tmp>=allowable_cell[1]) return 1;
        }
    }
    int binary_query(int i, Pos pos){
        // outputFile<< "i: " << i <<endl;
        // allowable_cellとsも使う
        double bias=0.0; // l側にどれだけ寄っているかをbiasで持つ
        while(abs(bias)<0.9999){
            // lである確率からrである確率を引いてbiasに足していく
            int tmp=query(i, pos);
            double l_prob=normal_distribution_p(allowable_cell[0]-tmp);
            double r_prob=normal_distribution_p(allowable_cell[1]-tmp);
            normalize(l_prob, r_prob);
            // outputFile<< "nor: " << l_prob <<endl;
            // outputFile<< "nor: " << r_prob <<endl;
            bias+=l_prob-r_prob;

            // outputFile<< "bias: " << bias <<endl;
        }
        if(bias<0) return 0;
        else return 1;
    }
    int multi_query(int i, Pos pos, int lp){
        // 0か1000の場合
        int vote[]={0, 0};
        rep(j, lp){
            int tmp=query(i, pos);
            if(tmp==0) vote[0]+=5000000;
            if(tmp==1000) vote[1]+=5000000;
            vote[0]+=(1000-tmp)*(1000-tmp);
            vote[1]+=tmp*tmp;
        }
        if(vote[0]<vote[1]) return 1;
        else return 0;
    }
    int single_query(int i, Pos pos){
        int tmp=query(i, pos);
        int best=imax;
        int besti;
        rep(k, allowable_cell.size()){
            int delta=abs(allowable_cell[k]-tmp);
            if(delta<best){
                best=delta;
                besti=k;
            }
        }
        // outputFile<< "tmp, besti: " << tmp SP << besti <<endl;
        return besti;
    }
    int query(int i, Pos pos){
        cout<< i SP << pos.y SP << pos.x <<endl;
        int tmp;
        cin>> tmp;
        return tmp;
    }

    void print_placement(){
        rep(i, l){
            rep(j, l){
                if(p[i][j]==-1) cout<< 500 SP;
                else cout<< p[i][j] SP;
                // cout<< p[i][j] SP;
            }
            cout<< endl;
        }
    }
    void print_ans(){
        cout<< "-1 -1 -1" <<endl;
        rep(i, n) cout<< e[i] <<endl;
    }
};

void inpt(){
    cin>> l >> n >> s;

    rep(i, n){
        cin>> exit_cells[i].y >> exit_cells[i].x;
    }
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Space space;
    space.init();
    space.random_placement();
    space.measurement();
    space.fill_ans();

    space.print_ans();

    return 0;
}

// 1つのセルが何個の情報を持てるか決める
  // Sのみに依存
    // 一旦4σを完全に信頼する方針で行く
    // あとで2000ケースから何回間違えているかを調べる
      // 全然100%に近づかない
    // 0から8Sずつ置いていけばいい
      // 0 1 2 3 4 5 6 7、7個差で置けばよさそう
      //* 0からじゃなくて500を中心にやった方がよさそう
        // 500中心で間隔をSに比例した何かにするとよさそう、4Sで99.99%くらい
// 配置
  // どの相対座標たちを使うかを決める
    // 最初はマンハッタンが近い点から取る（25個用意した）
    // 一旦先頭から必ず使うようにしていく
      // allowable_cellsの長さをacszとしてacsz進数の数字として管理
      // それらがN個のセルで被らないようにすればOK
  //* 焼けそう
    // 乱択でもよさそう
      // 設置コストと調べる数を減らす
  //* 木構造みたいにできないか？
    // ユニークな形になったらそれ以上判定要素を追加しないようにすればよさそう
// 計測
// N回に1回までなら間違えてもいい
  //* 被った二つを戦わせられるため
    // 被らなくても分からなかったものをもう一度やれば良い、10000回を超えないように
  // N回に2回以上被ってもなんとかなる可能性はあるが、
  // N回に2回以上被る事象が3000回に0.5回未満であればOK
  //* 動的に推測する、lとrを設定してどちらの山かを推定する方法
    // 確率の差が100%になったらokにしよう（1回で決着をつけたいやつもいるから99.99とかでもいいかも）
    // あとは正規分布の式から出せそう
  //* 全セルを幅優先探索っぽく見ていき、最大10000回かけて確度を上げていく
  // 1セルにかける探索回数をへらすことはできるか？むずそう
  // つくる木の密集度をあえて下げてgraphoreanみたいに2乗誤差から一番近い形を想像するやつ
  // はじめから何個か捨てて他に集中する？ただし10個捨てるとスコアが10分の1
// 盤面をクソデカの単一模様にして計測するときに頑張るか
  // これは厳しそう、N^2計測が必要なため

// 信頼区間メモ
// 　σ　0.682689492137086
// ２σ　0.954499736103641
// ３σ　0.997300203936740
// ４σ　0.999936657516326
// ５σ　0.999999426696856
// ６σ　0.999999998026825
// ７σ　0.999999999997440
// ８σ　0.999999999999999
// ９σ　1.000000000000000

// ２σを3回で4σになる
// sが125以下なら一発で判定可能
// 250以下なら50%で判定可能、これを一般化したい

// パラメータチューニング
  // L, Nによる密度から、1セルあたりの情報量を2にするかそれ以上にするか決める
  // 信頼区間をどこまで求めるか