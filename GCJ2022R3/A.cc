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

int main(){

	int t;
	cin>> t;
	rep(lp, t){
		int n, flag=0;
		cin>> n;
		vector<int> ng(26), v(26);
		vector<string> s(n), ori(n);
		vector<int> sa, di;
		// string ins;
		// cin>> ins;
		// ins+=' ';
		// string itm="";
		// rep(i, ins.size()){
		// 	cout<< ins[i] <<endl;
		// 	if(ins[i]==' '){
		// 		s.push_back(itm);
		// 		itm="";
		// 	}else{
		// 		itm+=ins[i];
		// 	}
		// }
		rep(i, n){
			cin>> s[i];
			ori[i]=s[i];
			s[i]+=" ";
			string sh="";
			rep(j, s[i].size()-1){
				if(s[i][j]!=s[i][j+1]) sh+=s[i][j];
			}
			s[i]=sh;
			cout<< s[i] <<endl;
			for(int j=1;j<s[i].size()-1;j++){
				// char tmc=s[i][0];
				// char tme=s[i][s[i].size()-1];
				// int cf=0;
				// int ce=0;
				// rep3(k, j+1, 1){
				// 	if(s[i][k]!=tmc) cf=1;
				// }
				// for(int k=s[i].size()-1;k>=j;k--){
				// 	if(s[i][k]!=tme) cf=1;
				// }
				// if(cf==0 || ce==0) continue;
				ng[int(s[i][j]-'A')]++;
				if(ng[int(s[i][j]-'A')]>1){
					flag=1;
					break;
				}
			}
		}
		rep(i, n){
			if(ng[int(s[i][0]-'A')]) flag=1;
			if(ng[int(s[i][s[i].size()]-'A')]) flag=1;
			// v[int(s[i][0]-'A')]++;
			// if(s[i][s[i].size()]>1) v[int(s[i][s[i].size()]-'A')]++;
		}
		if(flag){
			cout<< "Case #" << lp+1 << ": " << "IMPOSSIBLE" <<endl;
			continue;
		}
		
		string ans=" ";
		rep(i, n){
			if(s[i][0]==s[i][s[i].size()]){
				sa.push_back(i);
			}else{
				di.push_back(i);
			}
		}

		if(di.size()!=0){
			ans+=s[di.size()-1];
			di.pop_back();
		}else{
			ans+=s[sa.size()-1];
			sa.pop_back();
		}
		ans+=" ";
		rep(i, di.size()){
			int fl=1;
			rep(j, di.size()){
				if(di[j]==-1) continue;
				if(s[di[j]][0]==ans[ans.size()-2]){
					ans+=s[di[j]]+" ";
					fl=0;
					di[j]=-1;
					break;
				}
				if(s[di[j]][s[di[j]].size()-1]==ans[1]){
					ans=" "+s[di[j]]+ans;
					fl=0;
					di[j]=-1;
					break;
				}
			}
			ans+=s[di[i]]+" ";
		}

		rep(i, sa.size()){
			int fl=1;
			
			if(ans[1]==s[sa[i]][s[sa[i]].size()-1]){
				ans=" "+s[sa[i]]+ans;
				continue;
			}
			if(ans[ans.size()-2]==s[sa[i]][0]){
				ans+=s[sa[i]]+" ";
				continue;
			}
			rep(j, ans.size()-2){
				char tmp=s[sa[i]][0];
				string a2="";
				if(ans[j]==tmp && ans[j+1]==' ' && ans[j]==tmp){
					rep(l, j+2) a2+=ans[l];
					a2+=s[sa[i]];
					rep3(l, ans.size(), j+2) a2+=ans[l];
					fl=0;
					ans=a2;
					break;
				}
			}
			if(fl){
				flag=1;
				break;
			}
		}
		if(flag){
			cout<< "Case #" << lp+1 << ": " << "IMPOSSIBLE" <<endl;
			continue;
		}

		string a3="";

		rep(i, ans.size()){
			if(ans[i]!=' ') a3+=ans[i];
		}

		cout<< "Case #" << lp+1 << ": " << a3 <<endl;
	}

	return 0;
}