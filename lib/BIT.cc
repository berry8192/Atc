#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
long long int llmax=9223372036854775807;
ll mod=1000000007;
//ll mod=998244353;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//ll型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

//数列a(a[0],a[1],…,a[n-1])についての区間和と点更新を扱う
//区間和,点更新,二分探索はO(log{n})で動作する
class BIT {
public:
    //データの長さ
    ll n;
    //データの格納先
    vector<ll> a;
    //コンストラクタ
    BIT(ll n):n(n),a(n+1,0){}

    //a[i]にxを加算する
    void add(ll i,ll x){
        i++;
        if(i==0) return;
        for(ll k=i;k<=n;k+=(k & -k)){
            a[k]+=x;
        }
    }

    //a[i]+a[i+1]+…+a[j]を求める
    ll sum(ll i,ll j){
        return sum_sub(j)-sum_sub(i-1);
    }

    //a[0]+a[1]+…+a[i]を求める
    ll sum_sub(ll i){
        i++;
        ll s=0;
        if(i==0) return s;
        for(ll k=i;k>0;k-=(k & -k)){
            s+=a[k];
        }
        return s;
    }

    //a[0]+a[1]+…+a[i]>=xとなる最小のiを求める(任意のkでa[k]>=0が必要)
    ll lower_bound(ll x){
        if(x<=0){
            //xが0以下の場合は該当するものなし→0を返す
            return 0;
        }else{
            ll i=0;ll r=1;
            //最大としてありうる区間の長さを取得する
            //n以下の最小の二乗のべき(BITで管理する数列の区間で最大のもの)を求める
            while(r<n) r=r<<1;
            //区間の長さは調べるごとに半分になる
            for(int len=r;len>0;len=len>>1) {
                //その区間を採用する場合
                if(i+len<n && a[i+len]<x){
                    x-=a[i+len];
                    i+=len;
                }
            }
            return i;
        }
    }
};

int main(){

	int n, m;
	ll ans=0;
	vector<int> l, r;

	cin>> n >> m;
	l.resize(m);
	r.resize(m);

	BIT bo=BIT(n);

	rep(i, m) cin>> l[i] >> r[i];

	while(1){
		int a, b, c;
		cin>> a >> b >> c;
		bo.add(a, 1);
		cout<< bo.sum(b, c) <<endl;
	}

	rep(i, m){
		bo.add(l[i]+1, 1);
		bo.add(r[i], -1);
		ans+=bo.sum(l[i], r[i]-1);
		cout<< ans << endl;
	}

	cout<< ans << endl;
 
	return 0;
}