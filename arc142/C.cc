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

int main(){

	int n, tmp;
	vector<int> a, b, d;

	cin>> n;
	a.resize(n+1);
	b.resize(n+1);
	d.resize(n);

	rep3(i, n+1, 3){
		cout<< "? " << 1 SP << i <<endl;
		cin>> tmp;
		a[i]=tmp;
	}
	rep3(i, n+1, 3){
		cout<< "? " << 2 SP << i <<endl;
		cin>> tmp;
		b[i]=tmp;
	}

	rep3(i, n+1, 3){
		d[a[i]+b[i]]++;
	}

	if(d[3]==1){
		cout<< "! " << 1 <<endl;
	}else if(d[3]>=3){
		cout<< "! " << 0 <<endl;
	}else if(d[3]==2){
		int m1=-1, m2=-1;
		rep3(i, n+1, 3){
			if(a[i]==1 && b[i]==2) m1=i;
		}
		rep3(i, n+1, 3){
			if(b[i]==1 && a[i]==2) m2=i;
		}
		if(m1*m2<0){
			cout<< "! " << 1 <<endl;
		}else{
			cout<< "? " << m1 SP << m2 <<endl;
			cin>> tmp;
			if(tmp==1){
				cout<< "! " << 3 <<endl;
			}else if(tmp==3){
				cout<< "! " << 1 <<endl;
			}else{
				return 1;
			}
		}
	}else{
		rep3(i, n, 2){
			if(d[i]){
				cout<< "!" << i <<endl;
				break;
			}
		}
	}
 
	return 0;
}