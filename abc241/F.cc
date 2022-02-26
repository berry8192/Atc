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

	int h, w, n, sh, sw, gh, gw, ix, iy, ph, pw, pd, ans=imax;
	bool bu, bd, bl, br;
	map<int, set<int> > x, y;
	queue<int> qh, qw, qd;
	set< pair<int, int> > seen;

	cin>> h >> w >> n;
	cin>> sh >> sw;
	cin>> gh >> gw;

	rep(i, n){
		cin >> ix >> iy;
		x[ix].insert(iy);
		y[iy].insert(ix);
	}

	qh.push(sh);
	qw.push(sw);
	qd.push(0);
	seen.insert({sh, sw});
  	while (!qh.empty()) {
    	ph=qh.front();
		pw=qw.front();
		pd=qd.front();
		//cout<< "h=" << ph << " w=" << pw << " dep=" << pd <<endl;
    	qh.pop();
    	qw.pop();
    	qd.pop();
		if(ph==gh && pw==gw){
			ans=min(ans, pd);
			continue;
		}

		bu=false;
		bd=false;
		bl=false;
		br=false;

		auto dr=x[ph].upper_bound(pw);
		if(dr!=x[ph].end()) br=true;
		auto dl=dr;
		if(dr!=x[ph].begin()){
			dl--;
			bl=true;
		}

		auto dd=y[pw].upper_bound(ph);
		if(dd!=y[pw].end()) bd=true;
		auto du=dd;
		if(dd!=y[pw].begin()){
			du--;
			bu=true;
		}

		// if(bu) cout<< "up={" << *du+1 << ", " << pw << "}\n";
		// if(bd) cout<< "dw={" << *dd-1 << ", " << pw << "}\n";
		// if(bl) cout<< "le={" << ph << ", " << *dl+1 << "}\n";
		// if(br) cout<< "ri={" << ph << ", " << *dr-1 << "}\n";

		if(bl && seen.find({ph, *dl+1})==seen.end()){
			//cout<< "le={" << ph << ", " << *dl+1 << "}\n";
			qh.push(ph);
			qw.push(*dl+1);
			qd.push(pd+1);
			seen.insert({ph, *dl+1});
		}
		if(br && seen.find({ph, *dr-1})==seen.end()){
			//cout<< "ri={" << ph << ", " << *dr-1 << "}\n";
			qh.push(ph);
			qw.push(*dr-1);
			qd.push(pd+1);
			seen.insert({ph, *dr-1});
		}
		if(bu && seen.find({*du+1, pw})==seen.end()){
			//cout<< "up={" << *du+1 << ", " << pw << "}\n";
			qh.push(*du+1);
			qw.push(pw);
			qd.push(pd+1);
			seen.insert({*du+1, pw});
		}
		if(bd && seen.find({*dd-1, pw})==seen.end()){
			//cout<< "dw={" << *dd-1 << ", " << pw << "}\n";
			qh.push(*dd-1);
			qw.push(pw);
			qd.push(pd+1);
			seen.insert({*dd-1, pw});
		}
  	}

	if(ans!=imax) cout<< ans << endl;
	else cout<< -1 <<endl;
 
	return 0;
}