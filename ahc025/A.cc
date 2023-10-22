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

int imax=2147483647;
ll lmax=9223372036854775807;

chrono::system_clock::time_point start, current;
double TIME_LIMIT=1900.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

std::ofstream outputFile("log.txt");
//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) outputFile << pvv[i] SP;
	outputFile<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			outputFile << pvv[i][j] SP;
		}
		outputFile << endl;
	}
}

int n, d, q;
// vector<int> answer_weight;

// struct Interval{
//     int l;
//     int r;

//     Interval(){};
//     Interval(int il, int ir){
//         l=il;
//         r=ir;
//     };

//     void is_valid(){
//         assert(l<=r);
//     }
//     int get_middle(){
//         assert(l==r);
//         return l;
//     }
// };

// struct Item{
//     Interval order;
//     vector<int> index;

//     Item(){};
//     Item(Interval iorder, vector<int> iindex){
//         order=iorder;
//         index=iindex;
//     };

//     int get_order(){
//         return order.get_middle();
//     }
// };

// struct Item{
//     int order;
//     vector<int> index;

//     Item(){};
//     Item(int iorder, vector<int> iindex){
//         order=iorder;
//         index=iindex;
//     };
// };

// void show_weight_answer(vector<vector<int>> items){
//     // outputFile<< "#show_weight_answer" <<endl;
//     rep(i, items.size()){
//         int tmp=0;
//         rep(j, items[i].size()) tmp+=answer_weight[items[i][j]];

//         // outputFile<< tmp SP;
//         // rep(j, items[i].size()) outputFile<< answer_weight[items[i][j]] SP;
//         // outputFile<< endl;
//     }
// }

bool query(vector<int> l, vector<int> r){
    // rep(i, l.size()){
    //     rep(j, r.size()){
    //         assert(l[i]!=r[j]);
    //     }
    // }
    cout<< l.size() SP << r.size() SP;
    rep(i, l.size()) cout<< l[i] SP;
    rep(i, r.size()) cout<< r[i] SP;
    cout<< endl;

    if(0){
        // int le=0;
        // int ri=0;
        // rep(i, l.size()) le+=answer_weight[l[i]];
        // rep(i, r.size()) ri+=answer_weight[r[i]];
        // return le<ri;
    }else{
        char tmp;
        cin>> tmp;
        return (tmp=='<');
    }
}

struct Goods{
    int remain_query; // 残りクエリ可能回数
    vector<vector<int>> items; // 挿入ソート済みアイテム
    vector<vector<int>> item_list; // 未ソートアイテム
    vector<int> ans; // 回答
    vector<int> weight_sum; // items=nのときのみ、0~xまでの重さの和がidxの重さをギリギリ超えない
    vector<int> weight; // items[i]の相対的な重さ

    void init(){
        remain_query=q;
        int tmp=calc_allow_sort_count();
        // cout<< "items: " << tmp <<endl;
        make_item(tmp);
        ans.resize(n);
        weight_sum.resize(n);
        weight.resize(n);
    }
    // Qの数からソート可能なNの上限を求める、制約から解Xは(N/2<=X<=N)、N=30で21, N=100で51
    int calc_allow_sort_count(){
        int rtn=n;
        int tmp=0;
        rep3(i, n+1, 2){
            int divi=i;
            while(divi>=2){
                divi=(divi+1)/2;
                tmp++;
            }
            if(q<tmp){
                rtn=i-1;
                break;
            }
        }
        return rtn;
    }
    void make_item(int item_count){
        item_list.resize(item_count);
        rep(i, n) item_list[i%item_count].push_back(i);
    }
    bool is_less_than_item(int target_id, int self_id){
        // outputFile<< "#is_less_than_item" <<endl;
        vector<int> right=items[target_id];
        vector<int> left=item_list[self_id];
        assert(remain_query);
        remain_query--;
        return query(left, right);
    }
    void insert_sort(){
        // outputFile<< "#insert_sort" <<endl;
        rep(i, item_list.size()){
            int le=0;
            int ri=items.size();
            // outputFile<< "i: " << i SP << remain_query <<endl;
            while(le!=ri){
                assert(le<=ri);
                // outputFile<< le SP << ri <<endl;
                int mid=(le+ri)/2;
                if(is_less_than_item(mid, i)){
                    ri=mid;
                    // outputFile<< "small" <<endl;
                }else{
                    le=mid+1;
                    // outputFile<< "large" <<endl;
                }
            }
            // outputFile<< "index: " << le <<endl;
            items.insert(items.begin()+le, item_list[i]);
            // show_weight_answer(items);
        }
        reverse(all(items));
    }
    void make_snake_ans(){
        // outputFile<< "make_snake_ans" <<endl;
        int flg=0;
        int lp=0;
        rep(dir, 1000){
            if(dir%2){
                rep(i, d){
                    rep(j, items[lp].size()){
                        ans[items[lp][j]]=i;
                    }
                    lp++;
                    if(lp==items.size()){
                        flg=1;
                        break;
                    }
                }
            }else{
                repr(i, d){
                    rep(j, items[lp].size()){
                        ans[items[lp][j]]=i;
                    }
                    lp++;
                    if(lp==items.size()){
                        flg=1;
                        break;
                    }
                }
            }
            if(flg) break;
        }
    }
    void random_swap(){
        int swap1=mt()%d;
        int swap2=(swap1+(mt()%(d-1)+1))%d;
        assert(swap1!=swap2);
        vector<int> v1, v2;
        rep(i, n){
            if(ans[i]==swap1) v1.push_back(i);
            if(ans[i]==swap2) v2.push_back(i);
        }
        // outputFile<< "remain: " << remain_query <<endl;
        // PV(v1);
        // PV(v2);
        if(query(v1, v2)){
            if(v2.size()>1){
                int move_id=mt()%v2.size();
                ans[v2[move_id]]=swap1;
            }
        }else{
            if(v1.size()>1){
                int move_id=mt()%v1.size();
                ans[v1[move_id]]=swap2;
            }
        }
        remain_query--;
    }
    void use_remain_query(){
        // outputFile<< "use_remain_query: " << remain_query <<endl;
        rep(i, remain_query) query({0}, {1});
        // outputFile<< "use_remain_query end" <<endl;
    }
    void remain_random_swap(){
        while(remain_query){
            random_swap();
            // PV(ans);
        }
    }
    // 0からriの重さの総和が、item_idxの重さをギリギリ超えない
    bool measure_weight(){
        // outputFile<< "#measure_weight" <<endl;
        // まず一番デカいやつを求める
        int le=0;
        int ri=n-1;
        // leだとΣ<item、riだとitem<Σとなってほしい
        while(ri-le>1){
            int mid=(le+ri)/2;
            vector<int> tmp;
            rep(i, mid) tmp.push_back(items[n-1-i][0]);
            if(query(items[0], tmp)){
                ri=mid;
            }else{
                le=mid;
            }
            remain_query--;
            if(remain_query==0) return false;
        }
        weight_sum[0]=le-1;
        // outputFile<< 0 SP << "wei: " << weight_sum[0] <<endl;
        rep3(i, n-1-weight_sum[0], 1){
            // 手前のやつより区間を一つ短くして、オーバーしたら元の区間が正
            int pos=weight_sum[i-1];
            while(1){
                vector<int> tmp;
                rep(j, pos) tmp.push_back(items[n-1-j][0]);
                // outputFile<< "q" <<endl;
                bool reached=!query(items[i], tmp);
                remain_query--;
                if(remain_query==0) return false;
                if(reached) break;
                pos--;
            }
            weight_sum[i]=pos;
            // outputFile<< i SP << "wei: " << weight_sum[i] <<endl;
        }
        return true;
    }
    void liner_predict(){
        rep(i, n){
            if(weight_sum[i]) weight[i]=weight_sum[i]*(weight_sum[i]+1)/2;
            else weight[i]=n-i;
            weight[i]*=2250;
        }
        // repr(i, n) outputFile<< weight[i] <<endl;
    }
    void get_mima(ll &mii, ll &mai, vector<vector<ll>> &clusters){
        // outputFile<< "#get_mima" <<endl;
        vector<ll> value(d);
        ll mi=lmax;
        ll ma=-1;
        rep(i, d){
            rep(j, clusters[i].size()){
                // value[i]+=weight[items[clusters[i][j]][0]];
                value[i]+=weight[clusters[i][j]];
            }
            // outputFile<< value[i] <<endl;
            if(value[i]<mi){
                mi=value[i];
                mii=i;
            }
            if(value[i]>ma){
                ma=value[i];
                mai=i;
            }
        }
    }
    ll calc_S(vector<vector<ll>> &clusters){
        // outputFile<< "#calc_S" <<endl;
        vector<ll> value(d);
        double rtn=0.0;
        double ave=0.0;
        rep(i, d){
            rep(j, clusters[i].size()){
                // value[i]+=weight[items[clusters[i][j]][0]];
                // ave+=weight[items[clusters[i][j]][0]];
                value[i]+=weight[clusters[i][j]];
                ave+=weight[clusters[i][j]];
            }
            // outputFile<< value[i] <<endl;
        }
        ave/=d;
        // outputFile<< "ave: " << ave <<endl;
        rep(i, d){
            rtn+=(value[i]-ave)*(value[i]-ave);
            // outputFile<< (value[i]-ave)*(value[i]-ave) <<endl;
        }
        return sqrt(rtn/d);
    }
    void save_ans(vector<vector<ll>> &clusters){
        rep(i, d){
            rep(j, clusters[i].size()){
                ans[items[clusters[i][j]][0]]=i;
            }
        }
        // PV(ans);
    }
    // 焼きなまし
    void annealing(){
        // outputFile<< "#annealing!" <<endl;
        vector<vector<ll>> clusters(d); // それぞれの袋にitems[x]が入る
        rep(i, n) clusters[i%d].push_back(i);

        ll mini_score=lmax;

        int lp=0;
        while(1){
            lp++;
                // if(lp>5) break;
            current = chrono::system_clock::now(); // 現在時刻
            double delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
            if(delta > TIME_LIMIT) break;

            int type=mt()%100;
            int fromd, fromidx, tod;
            ll mii, mai;
            get_mima(mii, mai, clusters);
            // PVV(clusters);
            // 一番大きいクラスタから適当に移動する
            if(type<0){
                fromd=mai;
                tod=(fromd+mt()%(d-1)+1)%d;
                fromidx=mt()%clusters[fromd].size();
                if(clusters[fromd].size()==0) continue;
                clusters[tod].push_back(clusters[fromd][fromidx]);
                clusters[fromd].erase(clusters[fromd].begin()+fromidx);
            // 一番小さいクラスタから適当に移動する
            }else if(type<0){
                tod=mii;
                fromd=(tod+mt()%(d-1)+1)%d;
                fromidx=mt()%clusters[fromd].size();
                if(clusters[fromd].size()==0) continue;
                clusters[tod].push_back(clusters[fromd][fromidx]);
                clusters[fromd].erase(clusters[fromd].begin()+fromidx);
            // 適当に移動する
            }else if(type<0){
                fromd=mt()%d;
                tod=(fromd+mt()%(d-1)+1)%d;
                fromidx=mt()%clusters[fromd].size();
                if(clusters[fromd].size()==0) continue;
                clusters[tod].push_back(clusters[fromd][fromidx]);
                clusters[fromd].erase(clusters[fromd].begin()+fromidx);
            // 一番大きいクラスタから一番小さいクラスタに移動する
            }else{
                fromd=mai;
                tod=mii;
                fromidx=mt()%clusters[fromd].size();
                if(clusters[fromd].size()==0) continue;
                clusters[tod].push_back(clusters[fromd][fromidx]);
                clusters[fromd].erase(clusters[fromd].begin()+fromidx);
            }

            ll score=calc_S(clusters);
            if(score<=mini_score){
            // outputFile<< "mii,mai: " << mii SP << mai <<endl;
                save_ans(clusters);
                // outputFile<< "lp: " << lp SP << score <<endl;
                // PV(ans);
                mini_score=score;
            }else{
                clusters[fromd].push_back(clusters[tod][clusters[tod].size()-1]);
                clusters[tod].pop_back();
                // outputFile<< "revert" <<endl;
                // PVV(clusters);
            }
        }
        // outputFile<< "annealing end" <<endl;
    }

    void print_ans(){
        rep(i, n) cout<< ans[i] SP;
        cout<< endl;
    }
};

void inpt(){
    cin>> n >> d >> q;
    // outputFile<< n SP << d SP << q <<endl;
    // rep(i, q) query({0}, {1});
    // rep(i, n) cout<< 0 SP;
    // cout<< endl;
    // answer_weight.resize(n);
    // rep(i, n){
    //     // outputFile<< "i: " << i <<endl;
    //     cin>> answer_weight[i];
    //     // outputFile<< answer_weight[i] <<endl;
    // }
}

int main(){
    start = chrono::system_clock::now();
    // outputFile<< "#main" <<endl;
    inpt();
    Goods goods;

    goods.init();
    goods.insert_sort();
    // PVV(goods.items);
    // show_weight_answer(goods.items);
    // cout<< goods.remain_query <<endl;
    goods.make_snake_ans();
    if(goods.items.size()==n){
        if(goods.measure_weight()){
            goods.liner_predict();
            // rep(i, n) outputFile<< goods.items[i][0] SP;
            // outputFile<< endl;
            // PV(goods.weight);
            goods.annealing();
        }
        goods.use_remain_query();
    }else{
        goods.use_remain_query();
    }
    goods.print_ans();

    return 0;
}
