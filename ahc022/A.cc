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
Pos dm[]={{0, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 0}, {1, 1}, {-1, 1}, {1, -1}, {1, 1}, {0, 2}, {-2, 0}, {0, -2}, {2, 0}, {0, 3}, {-3, 0}, {0, -3}, {3, 0}, {2, 1}, {-2, 1}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {1, -2}, {1, 2}};

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
    int p[110][110]; // システムに渡す配置
    vector<Compare> compare; // 計測結果保存用かつ並べ替え用
    int e[110]; // 出力するE
    vector<int> allowable_cell; // セルに設定できる値のリスト
    int acsz; // セルから得られる情報量
    vector<vector<int>> cells_setting; // セルの各地点にどの値を設定しているか、allowable_cellの添え字にすると欲しい値になる
    map<ll, int> setting_e_cells_map;

    void init(){
        rep(i, n) e_cells[i]=exit_cells[i];
        compare.resize(n);
        for(int i=0;i<=1000;i+=8*s) allowable_cell.push_back(i);
        if(allowable_cell.size()==1) allowable_cell.push_back(1000);
        acsz=allowable_cell.size();
        cells_setting.resize(n);
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
        normalize_placement();
        print_placement();
    }
    void placement(){
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
                    if(p_val==1000){
                        cells_setting[j].push_back(1);
                        set_val=1;
                    }else{
                        cells_setting[j].push_back(p_val/(8*s));
                        set_val=p_val/(8*s);
                    }
                }
                current_cells_setting[j]+=base*set_val;
                setting_map[current_cells_setting[j]]=j;
            }
            if(setting_map.size()==n){
                setting_e_cells_map=setting_map;
                print_placement();
                break;
            }
            base*=acsz;
        }
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
                int lp=(s*4+999)/1000;
                // int lp=9500/(n*cells_setting[i].size());
                if(lp%2==0) lp++;
                while(lp*n*cells_setting[i].size()>10000) lp-=2;
                int tmp=multi_query(i, dm[j], lp);
                if(tmp==-1) exit(0);
                // outputFile<< "tmp: " << tmp <<endl;
                int idx=round(1.0*tmp/(8*s));
                setting+=base*idx;
                base*=acsz;
            }
            // outputFile<< setting <<endl;
            // PM(setting_e_cells_map);
            if(setting_e_cells_map.find(setting)!=setting_e_cells_map.end()){
                e[i]=setting_e_cells_map[setting];
            }else{
                // 算出したsettingが見当たらないときはとりあえず0と答える
                e[i]=0;
            }
        }
    }

    void normalize_placement(){
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
    int multi_query(int i, Pos pos, int lp){
        map<int, int> mp;
        rep(j, lp){
            int tmp=query(i, pos);
            tmp=round(1.0*tmp/(8*s));
            mp[tmp]++;
        }
        int ma=0;
        int mai;
        for(auto m : mp){
            if(ma<m.second){
                mai=m.first;
                ma=m.second;
            }
        }

        return allowable_cell[mai];
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
                if(p[i][j]==-1) cout<< 0 SP;
                else cout<< p[i][j] SP;
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
    space.placement();
    space.measurement();

    space.print_ans();

    return 0;
}

// 1つのセルが何個の情報を持てるか決める
  // Sのみに依存
    // 一旦4σを完全に信頼する方針で行く
    // あとで2000ケースから何回間違えているかを調べる
      // 0から8Sずつ置いていけばいい
// 配置
  // どの相対座標たちを使うかを決める
    // 最初はマンハッタンが近い点から取る（25個用意した）
    // 一旦先頭から必ず使うようにしていく
      // allowable_cellsの長さをacszとしてacsz進数の数字として管理
      // それらがN個のセルで被らないようにすればOK 
// 計測
// N回に1回までなら間違えてもいい
  // 被った二つを戦わせられるため
  // N回に2回以上被ってもなんとかなる可能性はあるが、
  // N回に2回以上被る事象が3000回に0.5回未満であればOK

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