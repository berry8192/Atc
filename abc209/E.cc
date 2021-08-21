#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

int n, ans=0;
vector<vector<vector<vector<int>>>> sta, fin;
vector<int> win, seen;
vector<string> v;

vector<int> conv_s(int x){
	vector<int> id(3);
	for(int j=0;j<3;j++){
		char c=v[x][j];
		if('A'<=c && c<='Z'){
			id[j]=(int)(c-'A')+26;
		}else{
			id[j]=(int)(c-'a');
		}
	}
	return id;
}

vector<int> conv_f(int x){
	vector<int> id(3);
	for(int j=0;j<3;j++){
		char c=v[x][v[x].size()-1-j];
		if('A'<=c && c<='Z'){
			id[j]=(int)(c-'A')+26;
		}else{
			id[j]=(int)(c-'a');
		}
	}
	return id;
}

int dfs(int x){
	if(seen[x]){
		win[x]=max(2, win[x]);
		return max(2, win[x]);
	}
	seen[x]=1;

	if(win[x]!=0) return win[x];
	int tmp=999;

	vector<int> id=conv_s(x);

	if(sta[id[0]][id[1]][id[2]].size()==0) return 3;

	vector<int> res(sta[id[0]][id[1]][id[2]].size());
	rep(i, sta[id[0]][id[1]][id[2]].size()){
		res[i]=dfs(sta[id[0]][id[1]][id[2]][i]);
		tmp=min(tmp, res[i]);
	}
	return 4-tmp;
}

int main(){

	vector<int> id(3);

	cin>> n;
	v.resize(n);
	win.resize(n);
	seen.resize(n);

	rep(i, n) cin >> v[i];

	rep(i, n) {
		id=conv_s(i);
		sta[id[0]][id[1]][id[2]].push_back(i);
		id=conv_f(i);
		fin[id[0]][id[1]][id[2]].push_back(i);
	}

	rep(i, n){
		dfs(i);
	}

	vector<string> S={"", "Aoki", "Draw", "Takahashi"};
	rep(i, n){
		cout<< S[win[i]] <<endl;
	}
 
	return 0;
}