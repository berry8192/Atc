#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

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

int main(){

	LLi n, m, d;
	LLi ans=0, tmp=0;
	vector<LLi> r, s, sec;
	map<LLi, LLi> mp;

	cin>> n >> m >> d;
	r.resize(m+1);
	s.resize(m+1);
	sec.resize(d);

	rep(i, m+1) cin >> r[i];
	rep(i, m) cin >> s[i];
	s[m]=0;

	//-∞から+∞に1ずつ矢をスライドさせたときの点数の上下イベントを記録
	for(int i=1;i<m+1;i++) {
		mp[r[i]]=s[i]-s[i-1];
		mp[-r[i]-1]=s[i-1]-s[i];
	}

	//初期位置は中央の矢がど真ん中想定
	//矢が偶数の場合は余りを左端につける
	//初期位置でのスコアを計算
	tmp=s[0];
	for(LLi i=1;i<n/2+1;i++){
		auto lb = lower_bound(all(r), d*i);
		int sco=lb-r.begin();
		tmp+=s[sco-1]*2;
		if(n%2==0 && i==n/2) tmp-=s[sco-1]; //偶数の時の処理
		//cout<< tmp <<endl;
	}
	//cout<< tmp <<endl;

	LLi le=-n/2*d, ri=(n-1)/2*d; //存在する矢の左端と右端
	//cout<< le SP << ri <<endl;
	
	// 全ての増減イベントを見る
	for (auto p : mp) {
  		auto key = p.first;
  		auto value = p.second;
  		// key, valueを使う
		if(key<le || ri<key-d) continue; //矢が増減イベントを通らない場合
		//cout<< key << " " << value SP << key-le SP << (key-le+d)%d <<endl;
		sec[(key-le+d)%d]+=value; //矢を動かして何回目に増減イベントを踏むか
	}
	//PV(sec);

	ans=tmp;
	for(int i=0;i<=d/2;i++){
		tmp+=sec[i];
		ans=max(ans, tmp); //最大になったスコアを記録
		//cout<< tmp <<endl;
	}

	cout<< ans <<endl;
 
	return 0;
}
