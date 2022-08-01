#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

#define HEIGHT 
#define WIDTH 
#define TEAMS 
#define LOW_SCORE_STREAK_LIMIT 100000
#define MAX_ROTATE 4

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=3000;
double start_temp=1000.0;
double end_temp=10.0;

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=10;
mt19937 mt(seed);

vector<int> PEOPLE={};
int people_sum=0;
vector<string> SEAT={
};
int ans[HEIGHT][WIDTH];
vector<int> h_usable_seat, w_usable_seat; // 座れる席の逆引き用配列
int best_score=imax, new_score;

void init(){
    vector<int> team_num;
    rep(i, TEAMS){
        rep(j, PEOPLE[i]){
            team_num.push_back(i);
        }
    }
    people_sum=team_num.size();
    rep(i, HEIGHT){
        rep(j, WIDTH){
            if(SEAT[i][j]=='#'){
                ans[i][j]=-1;
            }else{
                int idx=mt()%team_num.size();
                ans[i][j]=team_num[idx];
                team_num.erase(team_num.begin()+idx);

                h_usable_seat.push_back(i);
                w_usable_seat.push_back(j);
            }
        }
    }
}

int calc_two_seat_score(int h1, int w1, int h2, int w2){
    int two_seat_score=0;
    two_seat_score+=abs(h1-h2)*2;
    two_seat_score+=abs((w1+1)/2-(w2+1)/2)*10;
    two_seat_score+=abs(w1-w2)*2;
    // two_seat_score+=(h1-h2)*(h1-h2);
    // two_seat_score+=((w1+1)/2-(w2+1)/2)*((w1+1)/2-(w2+1)/2)*10;
    // two_seat_score+=(w1-w2)*(w1-w2);
    return two_seat_score;
}

int calc_score(){
    int score=0;
    rep(i, HEIGHT*WIDTH){
        rep3(j, HEIGHT*WIDTH, i+1){
            int h1=i/WIDTH, w1=i%WIDTH, h2=j/WIDTH, w2=j%WIDTH;
            assert(0<=h1 && h1<HEIGHT);
            assert(0<=w1 && w1<WIDTH);
            assert(0<=h2 && h2<HEIGHT);
            assert(0<=w2 && w2<WIDTH);
            if(ans[h1][w1]==ans[h2][w2]) score+=calc_two_seat_score(h1, w1, h2, w2);
        }
    }
    return score;
}

void print_ans(){
    rep(i, HEIGHT){
        rep(j, WIDTH){
            assert(-1<=ans[i][j] && ans[i][j]<TEAMS);
            cout<< ans[i][j]+1;
        }
        cout<< endl;
    }
}

int main(){

    // 開始時間の計測
    std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

    // 初期状態を作成
    init();
    print_ans();
    // 初期状態のスコアを計算
    best_score=calc_score();

    int loop=0;
    // int low_score_streak=0;
    vector<int> accept_rotate(MAX_ROTATE+1);
    while (true) {
        loop++;
        current = chrono::system_clock::now(); // 現在時刻
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) break;

        int type=mt()%1+1;
        int rotate=mt()%(MAX_ROTATE-1)+2; // (2<=rotate<=MAX_ROTATE)
        vector<int> h_idx, w_idx;
        if(type==1){
            // ランダムにrotate個の座席を入れ替える（indexを1ずつずらす）
            // 同じ席が選ばれることもあるけど許す
            rep(i, rotate){
                int idx=mt()%people_sum;
                h_idx.push_back(h_usable_seat[idx]);
                w_idx.push_back(w_usable_seat[idx]);
            }
            rep(i, rotate) assert(0<=ans[h_idx[i]][w_idx[i]] && ans[h_idx[i]][w_idx[i]]<TEAMS);
            rep(i, rotate-1) swap(ans[h_idx[0]][w_idx[0]], ans[h_idx[i+1]][w_idx[i+1]]);
        }else{
            assert(false);
        }
        
        new_score=calc_score();

        // 温度関数
        double temp = start_temp + (end_temp - start_temp) * chrono::duration_cast<chrono::milliseconds>(current - start).count() / TIME_LIMIT;
        // 遷移確率関数
        double prob = exp((best_score-new_score)/temp);

        if(prob > (mt()%imax)/(double)imax){ // 確率probで遷移する
        //if(best_score>new_score){
            // low_score_streak=0;
            best_score=new_score;
            cout<< "loop:" << loop <<endl;
            cout<< "new_score:" << new_score <<endl;
            print_ans();
            accept_rotate[rotate]++;
        }else{
            if(type==1){
                repr(i, rotate-1) swap(ans[h_idx[0]][w_idx[0]], ans[h_idx[i+1]][w_idx[i+1]]);
            }
            // low_score_streak++;
            // if(low_score_streak==LOW_SCORE_STREAK_LIMIT) break;
        }
    }

    rep3(i, MAX_ROTATE+1, 2) cout<< i << " rotate:" << accept_rotate[i] << " times" <<endl;
    print_ans();

	return 0;
}