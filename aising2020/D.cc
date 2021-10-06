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

int main(){

	int n, ans, def1=0, tmp;
	vector<int> v, d1, d2, d3, sc, cnt;
	char iv;
	LLi ds1=0, ds3=0;

	cin>> n;
	v.resize(n);
	d1.resize(n);
	//d2.resize(n);
	d3.resize(n);
	sc.resize(n);
	cnt.resize(n);
	
	rep(i, n){
		cin >> iv;
		v[i]=(int)(iv-'0');
		if(v[i]==1) def1++;
	}
	reverse(v.begin(), v.end());

	if(def1>0){
		tmp=1;
		for(int i=0;i<n;i++){
			if(def1==1) break;
			tmp=tmp%(def1-1);
			d1[i]=tmp;
			if(v[i]==1){
				ds1+=tmp;
				ds1=ds1%(def1-1);
			}
			tmp*=2;
			//cout<< d1[i] <<endl;
		}
	}else{
		rep(i, n) cout<< 1 <<endl;
		return 0;
	}

	tmp=1;
	for(int i=0;i<n;i++){
		tmp=tmp%(def1+1);
		d3[i]=tmp;
		if(v[i]==1){
			ds3+=tmp;
			ds3=ds3%(def1+1);
		}
		tmp*=2;
		//cout<< d3[i] <<endl;
	}
	//cout<< ds1 <<endl;
	//cout<< ds3 <<endl;

	rep(i, n){
		if(def1==1 && v[i]==1){
			cnt[i]=-1;
			continue;
		}
		if(v[i]==1){
			//cout<< "in1" <<endl;//
			sc[i]=ds1-d1[i]+def1-1;
			sc[i]=sc[i]%(def1-1);
		}else{
			//cout<< "in0" <<endl;//
			sc[i]=ds3+d3[i];
			sc[i]=sc[i]%(def1+1);
		}
	}

	//rep(i, n) cout<< sc[i] <<endl;

	rep(i, n){
		if(cnt[i]==-1){
			cnt[i]=0;
			continue;
		}
		ans=1;
		while(sc[i]!=0){
			int mod=__builtin_popcount(sc[i]);
			//cout<< sc[i] << "#" << mod << endl;
			sc[i]=sc[i]%mod;
			ans++;
		}
		cnt[i]=ans;
	}

	reverse(cnt.begin(), cnt.end());
	rep(i, n) cout<< cnt[i] <<endl;
 
	return 0;
}
