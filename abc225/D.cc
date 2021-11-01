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
vector<int> fr, ba, f, b, ans, tmpf;

//int型vectorを出力
template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	// rep(i, pvv.size()-1) cout << pvv[i] SP;
	// cout<< pvv[pvv.size()-1] <<endl;
}

void dfsf(int x){
	if(fr[x]!=-1){
		f.push_back(fr[x]);
		dfsf(fr[x]);
	}
}

void dfsb(int x){
	if(ba[x]!=-1){
		b.push_back(ba[x]);
		dfsb(ba[x]);
	}
}

int main(){

	int n, q, ty, x, y;

	cin>> n >> q;
	fr.resize(n+1, -1);
	ba.resize(n+1, -1);

	rep(i, q) {
		cin>> ty;
		if(ty==1){
			cin>> x >> y;
			ba[x]=y;
			fr[y]=x;
		}else if(ty==2){
			cin>> x >> y;
			ba[x]=-1;
			fr[y]=-1;
		}else{
			cin>> x;
			f.clear();
			b.clear();
			ans.clear();
			tmpf.clear();
			dfsf(x);
			dfsb(x);

			//cout<< f <<endl;
			repr(j, f.size()) tmpf.push_back(f[j]);
			//cout<< tmpf <<endl;

			cout<< b.size()+f.size()+1 SP;
			// ans+=tmpf+to_string(x)+b;

			if(f.size()) PV(tmpf);
			if(b.size()) cout<< x SP;
			else cout<< x <<endl;
			if(b.size()){
				rep(j, b.size()-1) cout<< b[j] SP;
				cout<< b[b.size()-1] <<endl;
			}
			// PV(ans);
		}
	}

	return 0;
}