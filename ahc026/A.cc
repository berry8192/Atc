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

template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

std::ofstream outputFile("score.txt", ios::app);

int imax=2147483647;
long long int llimax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=1950.0;
// double TIME_LIMIT=190.0;
double start_temp=10000000.0;
double end_temp=10000.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

int n, m;
vector<vector<int>> b(10, vector<int>(20));

struct Soko{
    vector<vector<int>> yama;
    vector<pair<int, int>> ans;
    int score;

    void init(){
        yama=b;
        score=10000;
    }

    void simple_find_box(int &v, int &pos, int x){
        rep(i, m){
            rep(j, yama[i].size()){
                if(yama[i][j]==x){
                    v=i;
                    pos=j;
                    return;
                }
            }
        }
        cout<< "#simple_find failed." <<endl;
    }
    int simple_find_non_use_yama(int from_yama){
        // 山の中の最小値が一番大きい山のindexを返す
        int ma=-1, mai;
        rep(i, m){
            if(i==from_yama) continue;
            int tmp=300;
            rep(j, yama[i].size()) tmp=min(tmp, yama[i][j]);
            if(ma<tmp){
                ma=tmp;
                mai=i;
            }
        }
        return mai;
    }
    void simple_move_boxes(int from_yama, int pos, int to_yama){
        vector<int> tmp;
        int move_size=yama[from_yama].size()-pos-1;
        rep3(i, yama[from_yama].size(), pos+1) tmp.push_back(yama[from_yama][i]);
        rep(i, move_size) yama[from_yama].pop_back();
        rep(i, move_size) yama[to_yama].push_back(tmp[i]);
        // PV(yama[from_yama]);
        // cout<< "idx: " << pos+1 <<endl;
        // cout<< "s_move: " << yama[from_yama][pos+1] <<endl;
        ans.push_back({yama[from_yama][pos+1], to_yama});
        score-=move_size+1;
    }
    void double_move_boxes(int from_yama, int pos, int to_yama){
        // 移動したい塊の中にある小さい数字を上に持ってくる
        // ある数字xを上に持ってくるとして、今取り出そうとしている数字とxの差よりもxの上に積まれている数字の個数が多ければ持ってくる対象にする
        int max_effect=1;
        int max_pos;
        rep3(i, yama[from_yama].size()-1, pos+1){
            int dist=yama[from_yama][i]-yama[from_yama][pos];
            int div=mt()%3+1;
            div=2;
            dist/=div;
            int on_box=yama[from_yama].size()-i+1;
            int effect=on_box-dist;
            if(max_effect<effect){
                // cout<< "#effect: " << yama[from_yama][i] SP << yama[from_yama][pos] <<endl;
                max_effect=effect;
                max_pos=i;
            }
        }
        if(max_effect>=2){
            simple_move_boxes(from_yama, max_pos, to_yama);
            to_yama=simple_find_non_use_yama(from_yama);
        }
        simple_move_boxes(from_yama, pos, to_yama);
    }
    void simple_ans(){
        rep(i, n){
            int v, pos;
            simple_find_box(v, pos, i);
            if(yama[v].size()==pos+1){
                // 最上段にあるのでそのまま運び出せる
                ans.push_back({i, -1});
                yama[v].pop_back();
            }else{
                // 最上段にないので上のやつをどかす
                int dokasu=yama[v][pos+1];
                int to_yama=simple_find_non_use_yama(v);
                // cout<< "move" <<endl;
                // PVV(yama);
                // cout<< "moved " << v SP << to_yama <<endl;
                double_move_boxes(v, pos, to_yama);
                // PVV(yama);
                ans.push_back({i, -1});
                yama[v].pop_back();
            }
        }
    }
    void print_ans(){
        rep(i, ans.size()){
            cout<< ans[i].first+1 SP << ans[i].second+1 <<endl;
        }
    }
};

void inpt(){
    cin>> n >> m;
    rep(i, m){
        rep(j, n/m){
            cin>> b[i][j];
            b[i][j]--;
        }
    }
    // PVV(b);
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

    inpt();
    Soko best;
    best.init();
    best.simple_ans();

    int lp=0;
    while (true){
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if(delta > TIME_LIMIT) break;

        Soko soko;
        soko.init();
        soko.simple_ans();

        if(best.score<soko.score) best=soko;
    }

    // cout<< "lp: " << lp SP << "score: " << best.score <<endl;
    best.print_ans();
    outputFile<< best.score <<endl;

    return 0;
}
