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
int n, cone, detected_cycle, land=-1;
vector<int> dh={0, -1, 0, 1}, dw={-1, 0, 1, 0};
string ds="LURD";
vector< vector<int> > seen, bo, fbo;
const double TIME_LIMIT = 2900.0;

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

void dfs(int h, int w, int pai, int pdir){
	if(seen[h][w]) return;
	//cout<< "dfs " << h SP << w <<endl;
	seen[h][w]=pai;
	cone++;
	rep(i, 4){
		if(0<=pdir && pdir==(i+2)%4) continue;
		if(h+dh[i]<0 || n<=h+dh[i] || w+dw[i]<0 || n<=w+dw[i]) continue;
		
		int fr=(bo[h][w]>>i);
		int to=((bo[h+dh[i]][w+dw[i]])>>((i+2)%4));
		//cout<< "dir=" << i SP;
		//cout<< "fr=" << fr SP;
		//cout<< "to=" << to SP;
		//cout<< "goto " << bo[h+dh[i]][w+dw[i]] <<endl;
		if(fr%2 && to%2){
			if(seen[h+dh[i]][w+dw[i]]==pai){
				detected_cycle=1;
				//cout<< "detected_cycle" <<endl;
			}
			dfs(h+dh[i], w+dw[i], pai, i);
		}
	}
}

int score(){
	int ma=0;
	rep(i, n) rep(j, n) seen[i][j]=0;
	rep(i, n){
		rep(j, n){
			cone=0;
			detected_cycle=0;
			if(!seen[i][j]){
				//cout<< "dfs start " << i SP << j <<endl;
				dfs(i, j, i*n+j+1, -10);
			}
			if(!detected_cycle && ma<=cone){
				ma=cone;
				land=seen[i][j];
			}
		}
	}
	//PVV(seen);
	return ma;
}

int main(){
	std::chrono::system_clock::time_point start, current;
    start = chrono::system_clock::now();

	int t, fh, fw, h, w, pdir, sco, msco=0, cnt=0;
	char tmp;
	string ans, mans;
	
    //乱数の準備
    int seed=100003;
    mt19937 mt(seed);

	cin>> n >> t;
	bo.resize(n);
	fbo.resize(n);
	seen.resize(n);
	rep(i, n) bo[i].resize(n);
	rep(i, n) fbo[i].resize(n);
	rep(i, n) seen[i].resize(n);

	rep(i, n){
		rep(j, n){
			cin>> tmp;
			if('a'<=tmp) tmp=tmp-39;
			tmp=tmp-48;
			//cout<< int(tmp) SP;
			fbo[i][j]=int(tmp);
			if(int(tmp)==0){
				fh=i;
				fw=j;
			}
		}
		//cout<< endl;
	}
	//cout<< "h=" << h << " w=" << w <<endl;
	
	sco=score();

	while (true) {
		cnt++;
        current = chrono::system_clock::now();
        if (chrono::duration_cast<chrono::milliseconds>(current - start).count() > TIME_LIMIT) {
            break;
        }

		rep(i, n) rep(j, n) bo[i][j]=fbo[i][j];
		pdir=mt()%4;
		ans="";
		h=fh;
		w=fw;
		//cout<< "first score=" << sco <<endl;
		rep(i, t){
			//cout<< "turn: " << i <<endl;
			int d[4];
			rep(j, 4) d[j]=j;
			d[(pdir+2)%4]=-1;
			rep(j, 4){
				if(h+dh[j]<0 || n<=h+dh[j] || w+dw[j]<0 || n<=w+dw[j]) d[j]=-1;
			}
			vector<int> nd;
			rep(j, 4){
				if(d[j]!=-1){
					nd.push_back(d[j]);
				}
			}
			//cout<< "nd=";
			//PV(nd);
			while(1){
				// TODO、連続部分がすくないものを選ぶようにする
				int idx=mt()%nd.size();
				pdir=nd[idx];
				swap(bo[h][w], bo[h+dh[pdir]][w+dw[pdir]]);
				int tmp, flag=0;
				rep(j, 4){
					if(h+dh[j]<0 || n<=h+dh[j] || w+dw[j]<0 || n<=w+dw[j]) continue;
					if(seen[h+dh[j]][w+dw[j]]==land) flag=1;
				}
				rep(j, 4){
					if(h+dh[pdir]+dh[j]<0 || n<=h+dh[pdir]+dh[j] || w+dw[pdir]+dw[j]<0 || n<=w+dw[pdir]+dw[j]) continue;
					if(seen[h+dh[pdir]+dh[j]][w+dw[pdir]+dw[j]]==land) flag=1;
				}
				if(flag) tmp=score();
				else tmp=sco;
				if(sco<=tmp || nd.size()==1){
					h+=dh[pdir];
					w+=dw[pdir];
					sco=tmp;
					//cout<< "score=" << sco <<endl;
					ans+=ds[pdir];
					if(msco<sco){
						mans=ans;
						msco=sco;
					}
					break;
				}else{
					swap(bo[h][w], bo[h+dh[pdir]][w+dw[pdir]]);
					nd.erase(nd.begin()+idx);
				}
			}
		}
    }

	//cout<< cnt <<endl;
	cout<< mans << endl;
 
	return 0;
}