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

//焼きなましの定数
double TIME_LIMIT=985;
double start_temp=400000.0;
double end_temp=1000.0;

//入力など
int n, m;
int a[100], b[100];

// 変数
int alp=5, sz=0, mv=10;
vector<int> c(8), d(8);
vector<int> r(99);
vector<vector<int>> s(100);
ll b_sco, n_sco;

//乱数の準備
// int seed=1;
auto seed=(unsigned)time(NULL);
mt19937_64 mt(seed);

struct poi{
	double th;
	int idx;

	bool operator<(const poi &in) const{
		return th!=in.th ? th<in.th : idx<in.idx;
	};
};

void inpt(){
    cin>> n >> m;
    rep(i, 100){
        //cin>> a[i] >> b[i];
        a[i]=mt()%1001;
        b[i]=mt()%1001;
        // cout<< a[i] SP << b[i] <<endl;
    }
}

void init(){
    vector<poi> ang(99);
    rep(i, r.size()){
        ang[i].th=atan2(b[i+1], a[i+1]);
        ang[i].idx=i+2;
    }
    sort(all(ang));
    rep(i, r.size()) r[i]=ang[i].idx;
    r.push_back(1);
    // rep(i, 8){
    //     c[i]=mt()%1001;
    //     d[i]=mt()%1001;
    // }
    c={167, 500, 834, 334, 667, 167, 500, 834};
    d={167, 167, 167, 500, 500, 834, 834, 834};
}

ll score(){
    ll sco=0;
    int px=a[0], py=b[0];
    int nx, ny;
    int tmp;
    rep(i, 100){
        tmp=alp*alp;
        rep(j, s[i].size()){
            nx=c[s[i][j]-1];
            ny=d[s[i][j]-1];
            tmp=1;
            if(j==0 || j==s[i].size()-1) tmp=alp;
            sco+=tmp*((px-nx)*(px-nx)+(py-ny)*(py-ny));
            px=nx;
            py=ny;
        }
        nx=a[r[i]-1];
        ny=b[r[i]-1];
        sco+=tmp*((px-nx)*(px-nx)+(py-ny)*(py-ny));
        px=nx;
        py=ny;
    }
    return sco;
}

void print_ans(){
    rep(i, m) cout<< c[i] SP << d[i] <<endl;
    cout<< r.size()+sz+1 <<endl;
    cout<< 1 SP << 1 <<endl;
    rep(i, r.size()){
        rep(j, s[i].size()) cout<< 2 SP << s[i][j] <<endl;
        cout<< 1 SP << r[i] <<endl;
    }
}

int main(){

    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    //入力
    inpt();
    //初期状態の計算
    init();
    // print_ans();
    b_sco=score();

    //焼きなまし
    int lp=0;
    while (true) { // 時間の許す限り回す
        lp++;
        //cout<< lp <<endl;
        if(lp%1000==0){
            current = chrono::system_clock::now(); // 現在時刻
            if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;
        }
        
        //if(lp==20000) break;

        int type=mt()%4+1;
        int idx1, idx2, dx, dy;
        int no_sco=0;
        vector<int> pre_s;
        //cout<< "type:" << type <<endl;
        if(type==1){
            // 惑星訪問の順番入れ替え
            idx1=mt()%99;
            while(1){
                idx2=(idx1+mt()%99)%100;
                if(idx2!=99) break;
            }
            swap(r[idx1], r[idx2]);
        }else if(type==2){
            // ステーション移動
            idx1=mt()%m;
            while(1){
                dx=mt()%(mv*2+1)-mv;
                dy=mt()%(mv*2+1)-mv;
                if(0<=c[idx1]+dx && c[idx1]+dx<=1000 && 0<=d[idx1]+dy && d[idx1]+dy<=1000) break;
            }
            c[idx1]+=dx;
            d[idx1]+=dy;
        }else if(type==3){
            // ステーション挿入
            idx1=mt()%m+1;
            idx2=mt()%99;
            pre_s=s[idx2];
            int flag=1;
            rep(i, s[idx2].size()){
                if(s[idx2][i]==idx1){
                    flag=0;
                    no_sco=1;
                    break;
                }
            }
            if(flag){
                int ins=0;
                if(s[idx2].size()>0) ins=mt()%s[idx2].size();
                s[idx2].insert(s[idx2].begin()+ins, idx1);
                sz++;
            }
        }else{
            // ステーション削除
            idx2=mt()%99;
            pre_s=s[idx2];
            if(s[idx2].size()>0){
                idx1=mt()%s[idx2].size();
                s[idx2].erase(s[idx2].begin()+idx1);
                sz--;
            }else{
                no_sco=1;
            }
        }
        if(no_sco) continue;
        n_sco=score();
        //cout<< n_sco <<endl;

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // 遷移確率関数(最大化の場合)
        double prob = exp((b_sco-n_sco)/temp);

        if (prob > (mt()%imax)/(double)imax) { // 確率probで遷移する
        //if (nsco<psco) {
            b_sco=n_sco;
            // cout<< "lp:" << lp <<endl;
            //cout<< n_sco <<endl;
        }else{
            if(type==1){
                swap(r[idx1], r[idx2]);
            }else if(type==2){
                c[idx1]-=dx;
                d[idx1]-=dy;
            }else if(type==3){
                s[idx2]=pre_s;
                sz--;
            }else{
                s[idx2]=pre_s;
                sz++;
            }
        }
    }

    print_ans();
    cout<< b_sco <<endl;
    // cout<< chrono::duration_cast<chrono::milliseconds>(current - start).count() <<endl;

	return 0;
}