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

	int d, mans=-imax, ans;
	vector<int> c, t, ld, at, us;
	vector< vector<int> >s;

	cin>> d;

	c.resize(26);
	rep(i, 26) cin>> c[i];
	s.resize(d);
	rep(i, d){
		s[i].resize(26);
		rep(j, 26) cin>> s[i][j];
	}
	t.resize(d);
	at.resize(d);
	ld.resize(26);
	rep(i, d){
		int tmp=1, su, ma=-imax;
		rep(j, 26){
			su=s[i][j];
			rep(k, 26){
				if(j==k) continue;
				ans-=(i-ld[k]+1)*c[k];
			}

			if(ma<=su){
				tmp=j;
				ma=su;
			}
		}
		ld[tmp]=i+1;
		at[i]=tmp+1;
		//cout<< ma <<endl;
	}

	rep(i, d){
		cout<< at[i] <<endl;
	}
return 0;
	us.resize(26);
	
  	std::random_device seed_gen;
  	std::mt19937 engine(seed_gen());

	int ti = clock();
    while (clock() - ti < 185 * CLOCKS_PER_SEC / 100){
	
		rep(i, 26) us[i]=0;

    	rep(i, d){
			int rs=engine();
			rs=abs(rs)%26;
			while(us[rs]>(i+0)/26) rs=(rs+1)%26;
			us[rs]++;
			t[i]=rs;
			//PV(us);
		}
		ans=0;
		rep(i, 26) ld[i]=0;

		rep(i, d){
			ans+=s[i][t[i]];
			ld[t[i]]=i+1;
			rep(j, 26) ans-=(i-ld[j]+1)*c[j];
		}

		if(mans<ans){
			rep(i, d) at[i]=t[i]+1;
			mans=ans;
			//cout<< mans <<endl;
		}
	}

	rep(i, d) cout<< at[i] <<endl;
 
	return 0;
}