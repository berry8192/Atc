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
		
		string ans;
		rep(i, n){
			ans=ori[i];
			cout<< ans <<endl;
			vector<int> us(n);
			us[i]=1;
			flag=0;
			rep(j, n-1){
				int cnt=0;
				int idx;
				rep(k, n){
					if(us[k]) continue;
					//cout<< "k=" << ori[k] <<endl;
					if(ans[ans.size()-1]==ori[k][0] && ori[k][0]==ori[k][ori[k].size()-1]){
						ans+=ori[k];
						us[k]=1;
						break;
					}
					if(ans[ans.size()-1]==ori[k][0] && ori[k][0]!=ori[k][ori[k].size()-1]){
						cnt++;
						idx=k;
						if(cnt>1) break;
					}
				}
				if(cnt==1){
					ans+=ori[idx];
					us[idx]=1;
				}else{
					flag=1;
					break;
				}
				cout<< ans <<endl;
			}
			if(flag==0){
				break;
			}
		}
		
		if(flag){
			cout<< "Case #" << lp+1 << ": " << "IMPOSSIBLE" <<endl;
			continue;
		}

		// string a3="";

		// rep(i, ans.size()){
		// 	if(ans[i]!=' ') a3+=ans[i];
		// }

		cout<< "Case #" << lp+1 << ": " << ans <<endl;
	}

	return 0;
}