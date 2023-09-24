#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;

double TIME_LIMIT=1950.0;

// 乱数の準備
// auto seed=(unsigned)time(NULL);
int seed=1;
mt19937 mt(seed);

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
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

struct Pos;

int n=50, m=100;
vector<vector<int>> c(n, vector<int>(n));
vector<set<int>> relation(m+1);
set<int> around_list;

struct Pos{
	int h, w;

	Pos(){}
	Pos(int hh, int ww){
		h=hh;
		w=ww;
	}

	bool is_oob(){
		// assert(0<=h);
		// assert(h<n);
		// assert(0<=w);
		// assert(w<=h);
		return !(0<=h && h<n && 0<=w && w<n);
	}
	void print(){
		cout<< "(" << h << ", " << w << ")" <<endl;
	}

	Pos operator+(const Pos pos){
        Pos rtn;
        rtn.h=h+pos.h;
        rtn.w=w+pos.w;
        return rtn;
    }
};
Pos dir4[4]={{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // 下右上左
Pos dir8[8]={{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}; // 下右上左

void calc_relation(vector<vector<int>> &cc, vector<set<int>> &rtn){
	// cout<< "calc_relation" <<endl;
	rep(i, n-1){
		rep(j, n){
			int ncc=cc[i][j];
			if(ncc==0) continue;
			if(ncc!=cc[i+1][j] && cc[i+1][j]!=0) rtn[ncc].insert(cc[i+1][j]);
		}
	}
	rep(i, n){
		rep(j, n-1){
			int ncc=cc[i][j];
			if(ncc==0) continue;
			if(ncc!=cc[i][j+1] && cc[i][j+1]!=0) rtn[ncc].insert(cc[i][j+1]);
		}
	}
	rep(i, n){
		// rtn[0].insert(cc[0][i]);
		// rtn[0].insert(cc[n-1][i]);
		// rtn[0].insert(cc[i][0]);
		// rtn[0].insert(cc[i][n-1]);
	}
}

struct City{
	vector<vector<int>> d;
	
	void init(){
		// cout<< "init" <<endl;
		d=c;
	}
	void plane(){
		Pos pos, npos;
		int color, ncolor;
		rep(i, n){
			rep(j, n){
				pos={i, j};
				map<int, int> mp;
				color=d[i][j];
				rep(k, 4){
					npos=pos+dir4[k];
					if(npos.is_oob()) continue;
					ncolor=d[npos.h][npos.w];
					if(color!=ncolor) mp[ncolor]++;
				}
				if(mp.size()==1 && mp[ncolor]==3){
					// cout<< i SP << j SP << ncolor <<endl;
					d[i][j]=ncolor;
				}else if(mp.size()==2){
					int tmp;
					int su=0;
					for(auto m : mp){
						su+=m.first;
						if(m.second==2) tmp=m.first;
					}
					if(su==3) d[i][j]=tmp;
				}
			}
		}
	}
	void delete_around(){
		// set<int> around_around;
		// for(auto re : relation[0]){
		// 	for(auto a : relation[re]){
		// 		around_around.insert(a);
		// 	}
		// }
		// for(auto re : relation[0]){
		// 	around_around.erase(re);
		// }
		rep(i, n){
			rep(j, n){
				if(relation[0].find(d[i][j])!=relation[0].end()){
					int flg=1;
					int color=d[i][j];
					Pos pos={i, j};
					rep(k, 8){
						Pos npos=pos+dir8[k];
						if(npos.is_oob()) continue;
						int val=d[npos.h][npos.w];
						if(val!=color && val!=0 && relation[0].find(val)==relation[0].end()){
							flg=0;
							break;
						}
					}
					if(flg) d[i][j]=0;
				}
			}
		}
	}
	void bfs(vector<vector<int>> &dd, Pos pos, int color){
		queue<Pos> q;
		q.push(pos);
		while(!q.empty()){
			Pos npos=q.front();
			dd[npos.h][npos.w]=0;
			q.pop();
			rep(i, 4){
				Pos cpos=npos+dir4[i];
				if(cpos.is_oob()) continue;
				if(dd[cpos.h][cpos.w]!=color) continue;
				q.push(cpos);
			}
		}
	}
	bool connected(vector<vector<int>> dd){
		// cout<< "connected" <<endl;
		bitset<101> checked;
		rep(i, n){
			rep(j, n){
				int col=dd[i][j];
				if(col==0) continue;
				bfs(dd, {i, j}, col);
				if(checked[col]){
					// cout<< "sepa: " << dd[i][j] <<endl;
					return false;
				}
				checked.set(col);
			}
		}
		return true;
	}
	void cut(int ch=-1, int cw=-1){
		// cout<< "cut: " << ch SP << cw <<endl;
		// ch=0なら列0を消滅させる 0<=ch<=49
		vector<vector<int>> cut_d=d;
		if(cw==-1){
			rep(i, n){
				rep3(j, n-1, ch){
					cut_d[i][j]=cut_d[i][j+1];
				}
				cut_d[i][n-1]=0;
			}
		}else{
			rep3(i, n-1, cw){
				rep(j, n){
					cut_d[i][j]=cut_d[i+1][j];
				}
			}
			rep(i, n) cut_d[n-1][i]=0;
		}
		vector<set<int>> rela(m+1);
		calc_relation(cut_d, rela);
		
		if(rela==relation && connected(cut_d)) d=cut_d;
	}

	void print_ans(){
		// cout<< "print_ans" <<endl;
		PVV(d);
	}
};

void inpt(){
	cin>> n >> m;
	rep(i, n){
		rep(j, n){
			cin>> c[i][j];
		}
	}
}
void zatsu(){
	if(c[0][0]==c[1][0] && c[0][0]==c[0][1] && c[0][0]==c[1][1]) c[0][0]=0;
	if(c[0][49]==c[1][49] && c[0][49]==c[0][48] && c[0][49]==c[1][48]) c[0][49]=0;
	if(c[49][0]==c[48][0] && c[49][0]==c[49][1] && c[49][0]==c[48][1]) c[49][0]=0;
	if(c[49][49]==c[48][49] && c[49][49]==c[49][48] && c[49][49]==c[48][48]) c[49][49]=0;
	PVV(c);
	exit(0);
}

int main(){
    //開始時間の計測
    std::chrono::system_clock::time_point start, current;
    double delta;
    start = chrono::system_clock::now();

	inpt();
	// zatsu();
	calc_relation(c, relation);
	// rep(i, m+1) PS(relation[i]);

	City best;
	best.init();
	// best.plane();

	for(int i=n-2;i>0;i--) best.cut(i, -1);
	for(int i=n-2;i>0;i--) best.cut(-1, i);

	// best.delete_around();
	best.print_ans();
	return 0;

    int lp=0;
    while (true){
        lp++;
        current = chrono::system_clock::now(); // 現在時刻
        delta=chrono::duration_cast<chrono::milliseconds>(current - start).count();
        if(delta > TIME_LIMIT) break;

		City city;
		city.init();

	}
	// cout<< "lp: " << lp <<endl;
	best.print_ans();
 
	return 0;
}