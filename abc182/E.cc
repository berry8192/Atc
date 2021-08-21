#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	int h, w, n, m, a, b, prv, ans=0;
	bool lt;
	vector< vector<int> > v;
	set<int> st;

	cin>> h >> w >> n >> m;
	v.resize(h+1);
	rep(i, h){
		v[i].resize(w+1);
		v[i][w]=-1;
	}
	v[h].resize(w+1, -1);

	rep(i, n){
		cin >> a >> b;
		v[a-1][b-1]=1;
	}
	rep(i, m){
		cin >> a >> b;
		v[a-1][b-1]=-1;
	}

	//rep(i, h+1) PV(v[i]);
	//cout<< endl;

	rep(i, h){
		prv=0;
		lt=false;
		rep(j, w+1){
			if(v[i][j]==1){
				lt=true;
			}
			if(v[i][j]==-1){
				if(lt){
					for(int k=prv;k<j;k++){
						if(v[i][k]!=1) v[i][k]=2;
					}
				}
				lt=false;
				prv=j+1;
			}
		}
	}

	//rep(i, h+1) PV(v[i]);
	//cout<< endl;

	rep(i, w){
		prv=0;
		lt=false;
		rep(j, h+1){
			//cout<< j << " " << i << " " << v[j][i] << " " << lt <<endl;
			if(v[j][i]==1){
				lt=true;
			}
			if(v[j][i]==-1){
				if(lt){
					for(int k=prv;k<j;k++){
						if(v[k][i]!=1) v[k][i]=2;
					}
				}
				lt=false;
				prv=j+1;
			}
		}
	}

	//rep(i, h+1) PV(v[i]);

	rep(i, h){
		rep(j, w){
			if(v[i][j]>0) ans++;
		}
	}

	cout<< ans <<endl;
 
	return 0;
}