#include <bits/stdc++.h>
//#include <atcoder/all>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;
//using namespace atcoder;

int imax=2147483647;
ll lmax=9223372036854775807;
//using mint = modint1000000007;
//using mint = modint=998244353;

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

// 乱数の準備
auto seed=(unsigned)time(NULL);
// int seed=1;
mt19937 mt(seed);

struct Pair {
    int value;
    int index;
};

bool compare(const Pair& a, const Pair& b) {
    return a.value != b.value ? a.value > b.value : a.index < b.index;
}

std::vector<int> rank_array(const std::vector<int>& arr) {
    int n = arr.size();
    std::vector<Pair> pairs(n);
    for (int i = 0; i < n; i++) {
        pairs[i] = { arr[i], i };
    }
    std::sort(pairs.begin(), pairs.end(), compare);
    std::vector<int> ranks(n);
    for (int i = 0; i < n; i++) {
        ranks[pairs[i].index] = i + 1;
    }
    return ranks;
}

int main(){
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

	int n, su=0;
	vector<int> v, w;
	vector<vector<int>> ans;

	int imi=imax, ima=0;
	cin>> n;
	v.resize(n);
	w.resize(n);
	iota(all(w), 1);

	rep(i, n){
		cin >> v[i];
		su+=v[i];
		imi=min(imi, v[i]);
		ima=max(ima, v[i]);
	}
	
	if(imi==ima){
		cout<< "Yes" << endl;
		cout<< ans.size() <<endl;
		PVV(ans);
		exit(0);
	}
	if(su%n!=0){
		cout<< "No" <<endl;
		return 0;
	}
	return 1;
	
    while (true){
		current = chrono::system_clock::now(); // 現在時刻
		delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
		if(delta > 1950) break;
		
		ans.clear();
		int befo=mt()%6;
		rep(lp, befo){
			shuffle(all(w), mt);
			int mi=imax, ma=0;
			rep(i, n){
				v[i]+=w[i];
				mi=min(mi, v[i]);
				ma=max(ma, v[i]);
			}
			ans.push_back(w);
			if(mi==ma){
				cout<< "Yes" << endl;
				cout<< ans.size() <<endl;
				PVV(ans);
				exit(0);
			}
		}
		rep(lp, 10000-befo){
			vector<int> z=rank_array(v);
			// PV(z);
			// exit(0);
			int mi=imax, ma=0;
			rep(i, n){
				v[i]+=z[i];
				mi=min(mi, v[i]);
				ma=max(ma, v[i]);
			}
			ans.push_back(z);
			if(mi==ma){
				cout<< "Yes" << endl;
				cout<< ans.size() <<endl;
				PVV(ans);
				exit(0);
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}