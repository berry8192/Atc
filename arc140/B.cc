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
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

int main(){

	int n, cnt=0, ans=0;
	cin>> n;
	string s;
	cin>> s;

	vector<int> p;
	multiset<int> st;

	rep(i, n-2){
		if(s[i]=='A' && s[i+1]=='R' && s[i+2]=='C'){
			p.push_back(i);
		}
	}
	//PV(p);

	rep(i, p.size()){
		int l=0, r=0, lp=0;
		while(1){
			lp--;
			if(p[i]+lp<0 || s[p[i]+lp]!='A') break;
			l++;
		}
		lp=2;
		while(1){
			lp++;
			if(p[i]+lp>=n || s[p[i]+lp]!='C') break;
			r++;
		}
		if(min(l, r)>0) st.insert(min(l, r));
		else cnt++;
		//cout<< min(l, r) SP;
	}
	//cout<< endl;
	//cout<< cnt <<endl;

	rep(i, 300000){
		if(i%2==0){
			if(st.empty()){
				ans+=cnt;
				break;
			}
			int tmp=*st.begin();
			st.erase(st.begin());
			//cout<< "tmp=" << tmp <<endl;
			if(tmp==1){
				cnt++;
			}else{
				st.insert(tmp-1);
			}
		}else{
			if(cnt==0){
				if(!st.empty()){
					st.erase(st.begin());
				}else{
					break;
				}
			}else{
				cnt--;
				//cout<< "cnt=" << cnt <<endl;
			}
		}
		ans++;
	}

	cout<< ans <<endl;
 
	return 0;
}