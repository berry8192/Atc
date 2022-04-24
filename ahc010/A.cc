#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

//定数周り
int imax=2147483647;
ll lmax=9223372036854775807;
vector<vector<int>> to = {
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};
vector<int> di = {0, -1, 0, 1}, dj = {-1, 0, 1, 0};
vector<vector<int>> rot = {
    {1, 3, -1, -1},
    {7, -1, -1, 1},
    {-1, -1, 1, 7},
    {-1, 5, 7, -1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {0, -1, 0, -1},
    {-1, 0, -1, 0},
};
vector<vector<int>> rota = {
    {1, 3, -1, -1},
    {3, -1, -1, 1},
    {-1, -1, 1, 3},
    {-1, 1, 3, -1},
    {1, 1, 1, 1},
    {1, 1, 1, 1},
    {0, -1, 0, -1},
    {-1, 0, -1, 0},
};

//焼きなましの定数
double TIME_LIMIT=1.9;
double start_temp=50.0;
double end_temp=10.0;

//入力など
char c;
int ans[30][30];
int sco1=0, sco2=0;
int t[30][30];
int u[30][30];
int ox, oy;

//スコアの計算
ll calc_score(int idx){
    ll rtn=0;

    return rtn;
}

bool dfs(int i, int j, int d, int dep){
    cout<< i SP << j SP << d SP << dep <<endl;
    //すでに使われている
    if(u[i][j]==3) return false;
    //移動する
    int d2=to[t[i][j]][d];
    if (d2 == -1) return false;
    int mi = i+di[d2];
    int mj = j+dj[d2];
    if (mi < 0 || mi >= 30 || mj < 0 || mj >= 30) return false;
    int md = (d2 + 2) % 4;

    if(mi==ox && mj==oy && dep){
        //戻ってきた（閉路完成）
        if(sco1==0) sco1=dep;
        else sco2=dep;
        return true;
    }
    if(dfs(mi, mj, md, dep+1)){
        return true;
    }else{
        cout<< "change " << i SP << j SP << d SP << dep <<endl;
        ans[i][j]=(ans[i][j]+rota[ans[i][j]][d])%4;
        d2=to[(t[i][j]+rot[ans[i][j]][d])%8][d];
        mi = i+di[d2];
        mj = j+dj[d2];
        if (mi < 0 || mi >= 30 || mj < 0 || mj >= 30) return false;
        int md = (d2 + 2) % 4;
        if(mi==ox && mj==oy && dep){
            //戻ってきた（閉路完成）
            if(sco1==0) sco1=dep;
            else sco2=dep;
            return true;
        }
        if(dfs(mi, mj, md, dep+1)){
            return true;
        }else{
            ans[i][j]=(ans[i][j]-rota[ans[i][j]][d]+4)%4;
            return false;
        }
    }
}

int main(){

    //開始時間の計測
    double start_time;

    //乱数の準備
    int seed=10000;
    mt19937 mt(seed);

    //入力
    rep(i, 30) rep(j, 30){
        cin>> c;
        t[i][j]=c-'0';
        u[i][j]=0;
        ans[i][j]=0;
    }

    //初期状態の計算（貪欲やらランダムやら）
    rep3(i, 30, 5){
        rep3(j, 30, 5){
            if(t[i][j]!=4 && t[i][j]!=5 && t[i][j]!=0 && u[i][j]!=3){
                ox=i;
                oy=j;
                if(to[t[i][j]][2]!=-1) dfs(i, j, 2, 0);
                else dfs(i, j, 3, 0);
            }
        }
    }
return 0;
    //焼きなまし
    while (true) { // 時間の許す限り回す
        double now_time; // 現在時刻
        if (now_time - start_time > TIME_LIMIT) break;

        
        int new_score = calc_score(2);
        int pre_score = calc_score(1);

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * (now_time-start_time) / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        double prob = exp((new_score-pre_score)/temp);

        if (prob > (mt()%lmax)/(double)lmax) { // 確率probで遷移する
            
        }
    }

    //答え出力
    rep(i, 200){
        cout <<endl;
    }

	return 0;
}