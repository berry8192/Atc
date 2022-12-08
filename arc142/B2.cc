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

const double TIME_LIMIT = 1900.0;
int dh8[]={-1, -1, -1, 0, 0, 1, 1, 1, 0};
int dw8[]={-1, 0, 1, -1, 1, -1, 0, 1, 0};

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

//乱数の準備
int seed=(unsigned)time(NULL), cnt, scnt, lp=0;
mt19937 mt(seed);

struct poi{
	int h;
	int w;

	bool operator<(const poi &in) const{
		return h*1000+w<in.h*1000+in.w;
	};
};

int main(){
	std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	int n;
	vector<vector<int>> v;
	vector<int> shu;
	set<poi> st;
	cin>> n;
	v.resize(n);
	shu.resize(n*n);
	rep(i, n) v[i].resize(n);

	rep(i, n*n) shu[i]=i+1;
	shuffle(all(shu), mt);

	rep(i, n){
		rep(j, n){
			v[i][j]=shu[i*n+j];
		}
	}

	rep3(i, n-1, 1){
		rep3(j, n-1, 1){
			cnt=0;
			rep(k, 8){
				if(v[i][j]<v[i+dh8[k]][j+dw8[k]]) cnt++;
			}
			if(cnt==4){
				poi tmp;
				tmp.h=i;
				tmp.w=j;
				st.insert(tmp);
			}
		}
	}

	while (!st.empty()) {
		// PVV(v);
		if(st.empty()) break;
		lp++;
		if(lp%100==0){
			//cout<< st.size() <<endl;
			current = chrono::system_clock::now();
			if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) {
				break;
			}
		}
        
		poi p1=*st.begin();
		poi p2;
		st.erase(st.begin());
		if(st.size()<2){
			p2.h=mt()%n;
			p2.w=mt()%n;
		}else{
			auto itr=st.end();
			itr--;
			p2=*itr;
			st.erase(itr);
		}
		// cout<< v[p1.h][p1.w] SP << v[p2.h][p2.w] <<endl;
		swap(v[p1.h][p1.w], v[p2.h][p2.w]);
		scnt=0;
		vector<int> ah, aw;
		int ddh, ddw;
		rep(i, 9){
			cnt=0;
			int dh=p1.h+dh8[i], dw=p1.w+dw8[i];
			if(dh==0 || dh==n-1 || dw==0 || dw==n-1) continue;
			if(st.find(poi({dh, dw}))!=st.end()) scnt--;
			rep(j, 8){
				ddh=dh+dh8[j];
				ddw=dw+dw8[j];
				if(dh<0 || dh>n-1 || dw<0 || dw>n-1) continue;
				if(v[dh][dw]<v[ddh][ddw]) cnt++;
			}
			if(cnt==4){
				scnt++;
				ah.push_back(dh);
				aw.push_back(dw);
			}
		}
		rep(i, 9){
			cnt=0;
			int dh=p2.h+dh8[i], dw=p2.w+dw8[i];
			if(dh==0 || dh==n-1 || dw==0 || dw==n-1) continue;
			if(st.find(poi({dh, dw}))!=st.end()) scnt--;
			rep(j, 8){
				ddh=dh+dh8[j];
				ddw=dw+dw8[j];
				if(dh<0 || dh>n-1 || dw<0 || dw>n-1) continue;
				if(v[dh][dw]<v[ddh][ddw]) cnt++;
			}
			if(cnt==4){
				scnt++;
				ah.push_back(dh);
				aw.push_back(dw);
			}
		}
		if(scnt>0){
			swap(v[p1.h][p1.w], v[p2.h][p2.w]);
		}else{
			rep(i, ah.size()){
				poi tmp;
				tmp.h=ah[i];
				tmp.w=aw[i];
				st.insert(tmp);
			}
		}
	}
	
	// cout<< st.size() <<endl;
	// rep3(i, n-1, 1){
	// 	rep3(j, n-1, 1){
	// 		cnt=0;
	// 		rep(k, 8){
	// 			if(v[i][j]<v[i+dh8[k]][j+dw8[k]]) cnt++;
	// 		}
	// 		if(cnt==4){
	// 			poi tmp;
	// 			tmp.h=i;
	// 			tmp.w=j;
	// 			st.insert(tmp);
	// 		}
	// 	}
	// }
	// cout<< st.size() <<endl;
	
	PVV(v);

	return 0;
}