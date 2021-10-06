#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

vector<int> itb(int x, int b){
	vector<int> tmp;
	tmp.resize(b);

	for(int i=b-1;i>=0;i--){
		if(x/(1<<i)>0){
			tmp[i]=1;
			x-=(1<<i);
		}
	}

	return tmp;
}

int bti(vector<int> x, int b){
	int tmp=0;
	for(int i=0;i<b;i++) tmp+=x[i]*(1<<i);
	return tmp;
}

int main(){

	int n, k, s, t, tmp, flag;
	LLi ans=0;
	vector<int> sb, tb, tmpv;
	vector< vector<int> > a, cs, ct;

	cin>> n >> k >> s >> t;

	cs.reisze(k+1);
	ct.reisze(k+1);
	rep(i, k+1) cs[i].reisze(262144);
	rep(i, k+1) ct[i].reisze(262144);
	sb=itb(s, 18);
	tb=itb(t, 18);

	//PV(sb);
	//PV(tb);
	rep(i, 18){
		if(sb[i]==1 && tb[i]==0){
			cout<< "0" <<endl;
			return 0;
		}
	}

	rep(i, n){
		cin >> tmp;
		tmpv=itb(tmp, 18);
		flag=1;
		rep(j, 18){
			if(tmpv[j]==0 && sb[j]==1){
				flag=0;
				break;
			}
			if(tmpv[j]==1 && tb[j]==0){
				flag=0;
				break;
			}
		}

		if(flag) a.push_back(tmpv);
	}

	cs[0][262143]=1;
	ct[0][0]=1;
	rep(i, a.size()){
		for(int j=k-1;j>=0;j--){
			rep(l, 262144){
				if(ct[j][l]>0){
					tmpv=itb(l);
					rep(m, 18){
						if(a[i][m]==1) tmpv[m]=1;
					}
					ct[j+1][bti(tmpv)]+=ct[j][i];
				}
			}
		}
	}

	rep(i, a.size()) {
		PV(a[i]);
	}

	return 0;
}