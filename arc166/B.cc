#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define rep3r(i, n, m) for (int i = n-1; i >= m; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint998244353;
// ll mod=998244353;
// ll mod=1000000007;

template <class T> ll gcdv(vector<T> gv){
	assert(gv.size()>0);
	ll tmp=gv[0];
	for(int i=1;i<(int)gv.size();i++) tmp=gcdi(tmp, gv[i]);
	return tmp;
}
long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}
/*  lcm (a, b) : 2整数版
    入力：整数 a, b
    出力：aとbの最小公倍数
*/
long long lcm(long long a, long long b) {
    long long d = gcd(a, b);
    return a / d * b;
}
template <class T> ll lcmv(vector<T> gv){
	assert(gv.size()>0);
	ll tmp=gv[0];
	for(ll i=1;i<(int)gv.size();i++) tmp=lcm(tmp, gv[i]);
	return tmp;
}

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

template <class T> void PS(T ps) {
    // cout<< "{";
	for(auto s : ps) cout<< s SP;
	// cout<< "}";
	cout<<endl;
}

template <class T> void PM(T pm) {
    // cout<< "{";
	for(auto m : pm){
		cout<< "(" << m.first << "->" << m.second << "), ";
	}
	// cout<< "}";
	cout<<endl;
}

struct edge{
	int to;
	int co;

	bool operator<(const edge &in) const{
		return co!=in.co ? co<in.co : to<in.to;
	};
};
// クラスカル法とかやりたいときに使う
struct s_edge{
	int to;
	int from;
	int co;

	bool operator<(const s_edge &in) const{
		return co!=in.co ? co<in.co : to<in.to ? to<in.to : from<in.from;
	};
};
struct Graph{
	int n, m;
	vector<vector<edge>> g;
	vector<s_edge> edges;

	void init(int nn, int mm, bool weight=false, bool directed=false){
		n=nn;
		m=mm;
		// n頂点、m辺、重み有無、有向無向
		int uu, vv, ww;
		g.resize(nn);

		for(int i=0;i<mm;i++){
			cin>> uu >> vv;
			uu--;
			vv--;
			if(weight) cin>> ww;
			else ww=1;

			g[uu].push_back({vv, ww});
			edges.push_back({uu, vv, ww}); // edges
			if(!directed){
				g[vv].push_back({uu, ww});
				edges.push_back({vv, uu, ww}); // edges
			}
		}
	}
	void board_init(vector<string> &bb){
		// #.形式のboardを想定
		// 頂点番号は2重forの順に0から
		int hei=bb.size();
		int wid=bb[0].size();
		g.resize(hei*wid);

		for(int i=0;i<hei-1;i++){
			for(int j=0;j<wid-1;j++){
				if(bb[i][j]=='.' && bb[i+1][j]=='.'){
					int ww=1;
					g[i*wid+j].push_back({(i+1)*wid+j, ww});
					g[(i+1)*wid+j].push_back({i*wid+j, ww});
					// edges.push_back({i*wid+j, (i+1)*wid+j, 1}); // edges
					// edges.push_back({(i+1)*wid+j, i*wid+j, 1}); // edges
				}
			}
		}
	}

	vector<int> bfs(int x){
		vector<int> rtn(n, imax);
		rtn[x]=0;
		queue<int> que;
		que.push(x);
		while(!que.empty()){
			int y=que.front();
			int d=rtn[x];
			que.pop();
			for(int i=0;i<g[y].size();i++){
				int to_x=g[y][i].to;
				if(d+g[y][i].co<rtn[to_x]){
					rtn[to_x]=d+g[y][i].co;
					que.push(to_x);
				}
			}
		}
		return rtn;
	}
};

// 長い文字列を数列として解釈してmodで抑えた整数にする
ll stollmod(string ss, ll MOD){
	ll rtn=0;
	ll base=1;
	repr(i, ss.size()){
		int d=int(ss[i]-'0');
		rtn+=base*d;
		rtn%=MOD;
		base*=10;
		base%=MOD;
	}
	return rtn;
}

// 配列中の総和
template <class T> ll SM(vector<T> smv) {
	ll tmp=0;
	rep(i, (int)smv.size()) tmp+=smv[i];

	return tmp;
}

//進数変換10->2 桁指定 10進->2進
string tob(ll n, int lng=0, string fil="0")
{
    string r, rtn="";
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
	while(lng>r.size()) r+=fil;
    return r;
}

void all_perm(vector<int> vv){
	vector<int> perm;
	rep(i, vv.size()) perm.push_back(i);
	do {
		PV(perm);
	} while (next_permutation(all(perm)));
}

// ランレングス圧縮、連長圧縮
// 文字列を何の文字が何連続というかたまりに分解する
void rle(string s, vector<pair<char, int>> &vec)
{
  int cnt = 1;
  for(int i = 1; i < (int)s.size(); i++){
    if(s[i] != s[i-1]){
      vec.push_back({s[i-1], cnt});
      cnt = 0;
    }
    cnt++;
  }
  vec.push_back({s.back(), cnt});
}

// 累積和
template <class T> vector<ll> ruiseki(T vv){
	vector<ll> xx;
  	xx.resize(vv.size()+1);
	xx[0]=0;
	for(int i=0;i<(int)vv.size();i++){
		xx[i+1]=xx[i]+vv[i];
		// xx[i+1]=xx[i+1]%mod;
	}
	return xx;
}

// いもす法1D, imos1D
vector<int> imos(vector<int> vv){
	rep3(i, vv.size(), 1) vv[i]+=vv[i-1];
	return vv;
}

template <class T> void addbit(vector<T> vv){
	int sz=vv.size();
	for (int bit = 0; bit < (1<<sz); ++bit) {
		//全ての桁に対する処理
        for (int i = 0; i < sz; ++i) {
			//探索対象となっているbitかどうかを判定
            if(bit & (1<<i)){
				// ここに処理を書く
			}
        }
    }
}

struct xxxx{
	ll val;
	int idx;

	bool operator<(const xxxx &in) const{
		return val!=in.val ? val<in.val : idx<in.idx;
	};
};

int main(){
	cout << fixed << setprecision(12);
	int n;
	cin>> n;
	ll a;
	cin>> a;
	ll b;
	cin>> b;
	ll c;
	cin>> c;
	ll labc=lcmv(vector<ll>({a, b, c}));
	ll lab=lcmv(vector<ll>({a, b}));
	ll lac=lcmv(vector<ll>({a, c}));
	ll lbc=lcmv(vector<ll>({b, c}));
	// cout<< labc SP << lab SP << lac SP << lbc <<endl;
	vector<ll> v(n);
	vector<xxxx> abc(n), ab(n), ac(n), bc(n), aa(n), bb(n), cc(n);
	rep(i, n){
		cin >> v[i];
		abc[i]={labc-v[i]%labc, i};
		ab[i]={lab-v[i]%lab, i};
		ac[i]={lac-v[i]%lac, i};
		bc[i]={lbc-v[i]%lbc, i};
		aa[i]={a-v[i]%a, i};
		bb[i]={b-v[i]%b, i};
		cc[i]={c-v[i]%c, i};
		if(v[i]%labc==0) abc[i]={0, i}; 
		if(v[i]%lab==0) ab[i]={0, i}; 
		if(v[i]%lac==0) ac[i]={0, i}; 
		if(v[i]%lbc==0) bc[i]={0, i}; 
		if(v[i]%a==0) aa[i]={0, i}; 
		if(v[i]%b==0) bb[i]={0, i}; 
		if(v[i]%c==0) cc[i]={0, i}; 		
	}
	sort(all(abc));
	sort(all(ab));
	sort(all(ac));
	sort(all(bc));
	sort(all(aa));
	sort(all(bb));
	sort(all(cc));

	ll ans=lmax, tmp=lmax;
	ans=min(ans, abc[0].val);
	// cout<< ans <<endl;

	if(ab[0].idx==cc[0].idx){
		if(1<n) tmp=min(ab[0].val+cc[1].val, ab[1].val+cc[0].val);
	}else{
		tmp=ab[0].val+cc[0].val;
	}
	ans=min(ans, tmp);
	if(ab[0].idx==ac[0].idx){
		if(1<n) tmp=min(ab[0].val+ac[1].val, ab[1].val+ac[0].val);
	}else{
		tmp=ab[0].val+ac[0].val;
	}
	ans=min(ans, tmp);
	if(ab[0].idx==bc[0].idx){
		if(1<n) tmp=min(ab[0].val+bc[1].val, ab[1].val+bc[0].val);
	}else{
		tmp=ab[0].val+bc[0].val;
	}
	ans=min(ans, tmp);

	if(ac[0].idx==bb[0].idx){
		if(1<n) tmp=min(ac[0].val+bb[1].val, ac[1].val+bb[0].val);
	}else{
		tmp=ac[0].val+bb[0].val;
	}
	ans=min(ans, tmp);
	if(ac[0].idx==ab[0].idx){
		if(1<n) tmp=min(ac[0].val+ab[1].val, ac[1].val+ab[0].val);
	}else{
		tmp=ac[0].val+ab[0].val;
	}
	ans=min(ans, tmp);
	if(ac[0].idx==bc[0].idx){
		if(1<n) tmp=min(ac[0].val+bc[1].val, ac[1].val+bc[0].val);
	}else{
		tmp=ac[0].val+bc[0].val;
	}
	ans=min(ans, tmp);

	if(bc[0].idx==aa[0].idx){
		if(1<n) tmp=min(bc[0].val+aa[1].val, bc[1].val+aa[0].val);
	}else{
		tmp=bc[0].val+aa[0].val;
	}
	ans=min(ans, tmp);
	if(bc[0].idx==ab[0].idx){
		if(1<n) tmp=min(bc[0].val+ab[1].val, bc[1].val+ab[0].val);
	}else{
		tmp=bc[0].val+ab[0].val;
	}
	ans=min(ans, tmp);
	if(bc[0].idx==ac[0].idx){
		if(1<n) tmp=min(bc[0].val+ac[1].val, bc[1].val+ac[0].val);
	}else{
		tmp=bc[0].val+ac[0].val;
	}
	ans=min(ans, tmp);

	if(aa[0].idx!=bb[0].idx && aa[0].idx!=cc[0].idx && bb[0].idx!=cc[0].idx){
		tmp=aa[0].val+bb[0].val+cc[0].val;
	}else if(aa[0].idx==bb[0].idx && aa[0].idx!=cc[0].idx && bb[0].idx!=cc[0].idx){
		if(1<n) tmp=min(aa[0].val+bb[1].val+cc[0].val, aa[1].val+bb[0].val+cc[0].val);
	}else if(aa[0].idx==cc[0].idx && aa[0].idx!=bb[0].idx && bb[0].idx!=cc[0].idx){
		if(1<n) tmp=min(aa[0].val+cc[1].val+bb[0].val, aa[1].val+cc[0].val+bb[0].val);
	}else if(cc[0].idx==bb[0].idx && aa[0].idx!=cc[0].idx && bb[0].idx!=aa[0].idx){
		if(1<n) tmp=min(cc[0].val+bb[1].val+aa[0].val, cc[1].val+bb[0].val+aa[0].val);
	}else{
		if(2<n){
			tmp=min(ans, aa[0].val+bb[1].val+cc[2].val);
			tmp=min(ans, aa[0].val+bb[2].val+cc[1].val);
			tmp=min(ans, aa[1].val+bb[0].val+cc[2].val);
			tmp=min(ans, aa[1].val+bb[2].val+cc[0].val);
			tmp=min(ans, aa[2].val+bb[0].val+cc[1].val);
			tmp=min(ans, aa[2].val+bb[1].val+cc[0].val);
		}
		if(1<n){
			if(bb[1].idx!=cc[1].idx) tmp=min(ans, aa[0].val+bb[1].val+cc[1].val);
			if(aa[1].idx!=cc[1].idx) tmp=min(ans, aa[1].val+bb[0].val+cc[1].val);
			if(bb[1].idx!=aa[1].idx) tmp=min(ans, aa[1].val+bb[1].val+cc[0].val);
		}
		if(1<n){
			if(bb[0].idx!=cc[0].idx) tmp=min(ans, aa[1].val+bb[0].val+cc[0].val);
			if(aa[0].idx!=cc[0].idx) tmp=min(ans, aa[0].val+bb[1].val+cc[0].val);
			if(bb[0].idx!=aa[0].idx) tmp=min(ans, aa[0].val+bb[0].val+cc[1].val);
		}
	}
	ans=min(ans, tmp);

	cout<< ans << endl;
 
	return 0;
}