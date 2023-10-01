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

template <class T>vector<vector<T>> vv_rotate(vector<vector<T>> vv){
	assert(vv.size()>0);
	int row=vv.size();
	int column=vv[0].size();
	vector<vector<T>> rtn(column, vector<T>(row));
	rep(i, row){
		rep(j, column){
			rtn[j][row-i-1]=vv[i][j];
		}
	}
	return rtn;
}

int main(){

	vector<vector<vector<char>>> p(3, vector<vector<char>>(4, vector<char>(4)));

	int cnt=0;
	rep(i, 3){
		rep(j, 4){
			rep(k, 4){
				cin>> p[i][j][k];
				if(p[i][j][k]=='#') cnt++;
			}
		}
	}
	if(cnt!=16){
		cout<< "No" <<endl;
		return 0;
	}
	rep(r1, 4){
		p[0]=vv_rotate(p[0]);
		rep3(i1, 4, -3){
			rep3(j1, 4, -3){
				rep(r2, 4){
					p[1]=vv_rotate(p[1]);
					rep3(i2, 4, -3){
						rep3(j2, 4, -3){
							rep(r3, 4){
								p[2]=vv_rotate(p[2]);
								rep3(i3, 4, -3){
									rep3(j3, 4, -3){
										vector<vector<char>> tmp(4, vector<char>(4, '.'));
										rep(i, 4){
											if(i1+i<0 || i1+i>=4) continue;
											rep(j, 4){
												if(j1+j<0 || j1+j>=4) continue;
												if(p[0][i][j]=='#'){
													tmp[i1+i][j1+j]='#';
												}
											}
										}
										rep(i, 4){
											if(i2+i<0 || i2+i>=4) continue;
											rep(j, 4){
												if(j2+j<0 || j2+j>=4) continue;
												if(p[1][i][j]=='#'){
													tmp[i2+i][j2+j]='#';
												}
											}
										}
										rep(i, 4){
											if(i3+i<0 || i3+i>=4) continue;
											rep(j, 4){
												if(j3+j<0 || j3+j>=4) continue;
												if(p[2][i][j]=='#'){
													tmp[i3+i][j3+j]='#';
												}
											}
										}
										int flg=1;
										rep(i, 4){
											rep(j, 4){
												if(tmp[i][j]=='.') flg=0;
											}
										}
										if(flg){
											cout<< "Yes" <<endl;
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout<< "No" << endl;
 
	return 0;
}