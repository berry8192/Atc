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
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
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

	int tmp, flag=1, cnt=0;
	string s, t, aa="", ab="";
	vector<int> a(10), b(10), nine(10), ansa, ansb;
	vector< vector<int> > ten(10);
	rep(i, 10) ten[i].resize(10);

	cin>> s >> t;

	rep(i, s.size()){
		a[int(s[i]-'0')]++;
	}
	rep(i, t.size()){
		b[int(t[i]-'0')]++;
	}

	// PV(a);
	// PV(b);
	
	// //9つくる
	// for(int i=1;i<9;i++){
	// 	tmp=min(a[i], b[9-i]);
	// 	nine[i]=tmp;
	// 	a[i]-=tmp;
	// 	b[9-i]-=tmp;
	// }

	for(int i=9;i<19;i++){
		//iが桁の和 9~18
		for(int j=1;j<10;j++){
			//jがaから使う数字
			if(i-j<1 || 9<i-j) continue;
			tmp=min(a[j], b[i-j]);
			a[j]-=tmp;
			b[i-j]-=tmp;
			if(i==9 && tmp) cnt+=tmp;
			if(i>9 && tmp){
				flag=0;
			}
			ten[j][i-j]+=tmp;
		}
	}
	//PVV(ten);

	for(int i=10;i<19;i++){
		for(int j=1;j<10;j++){
			if(i-j<1 || 9<i-j) continue;
			while(ten[j][i-j]){
				ansa.push_back(j);
				ansb.push_back(i-j);
				ten[j][i-j]--;
			}
		}
	}

	for(int j=1;j<9;j++){
		while(ten[j][9-j]){
			ansa.push_back(j);
			ansb.push_back(9-j);
			ten[j][9-j]--;
		}
	}

	for(int j=9;j>0;j--){
		while(a[j]){
			ansa.push_back(j);
			a[j]--;
		}
		while(b[j]){
			ansb.push_back(j);
			b[j]--;
		}
	}

	if(cnt==min(s.size(), t.size())){
		// ansb[10000000];
		// return 1;
		if(s.size()>t.size()){
			repr(i, ansa.size()){
				if(ansa[i]+ansb[0]>9){
					swap(ansa[i], ansa[0]);
					break;
				}
			}
		}else{
			repr(i, ansb.size()){
				if(ansb[i]+ansa[0]>9){
					swap(ansb[i], ansb[0]);
					break;
				}
			}
		}
	}

	repr(i, ansa.size()) aa+=to_string(ansa[i]);
	repr(i, ansb.size()) ab+=to_string(ansb[i]);

	cout<< aa <<endl;
	cout<< ab <<endl;

	return 0;
}