// #pragma GCC target("avx")
// #pragma GCC optimize("O3")

#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

// 定数周り
int imax=2147483647;
ll lmax=9223372036854775807;

//焼きなましの定数
double TIME_LIMIT=4900;
double start_temp;
double end_temp=0.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

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

template <typename T>
class SafeVector : public std::vector<T>
{
    public:
    // int 型の引数を1つ取るコンストラクタ
    SafeVector(int idx = 0)
    {
        this->resize(idx);
    }

    // 添え字演算子をオーバーロード
    T& operator[](int idx)
    {
        // 配列外参照の場合は、異常終了する
        if (idx < 0 || idx >= this->size())
        {
            cout<< "index limit: " << this->size() <<endl;
            cout<< "given index: " << idx <<endl;
        throw std::out_of_range("配列外参照してます");
        }

        return std::vector<T>::operator[](idx);
    }
};

//入力
int n, m, d, k;
SafeVector<int> u, v, w;

// 構造体


void inpt(){
    //cout<< "inpt" <<endl;
    cin>> n >> m >> d >> k;
    u.resize(m);
    v.resize(m);
    w.resize(m);
    rep(i, m) cin>> u[i] >> v[i] >> w[i];
}

int main(){
    inpt();
    return 0;
}
