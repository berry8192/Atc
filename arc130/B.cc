#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

template <class T> void PV(T pvv) {
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	int h, w, c, q, hd=0, wd=0;
	vector<int> tv, nv, cv;
	map<int, int> seh, sew;
	vector<LLi> bo;
	cin>> h >> w >> c >> q;

	bo.resize(c+1);
	tv.resize(q);
	nv.resize(q);
	cv.resize(q);

	rep(i, q){
		cin>> tv[i] >> nv[i] >> cv[i];
	}

	repr(i, q){
		//cout<< tv[i] << nv[i] << cv[i] <<endl;
		if(tv[i]==1){
			seh[nv[i]]++;
			if(seh[nv[i]]>1) continue;
			bo[cv[i]]+=w-wd;
			hd++;
		}else{
			sew[nv[i]]++;
			if(sew[nv[i]]>1) continue;
			bo[cv[i]]+=h-hd;
			wd++;
		}
	}

	rep(i, c-1){
		cout<< bo[i+1] << " ";
	}
	cout<< bo[c] <<endl;
 
	return 0;
}