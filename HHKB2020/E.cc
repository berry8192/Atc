#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
 
LLi modpow(LLi a, LLi n) {
    LLi res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main(){

	int a, b, s, p=0;
	LLi tmp, ans=0;
	cin>> a >> b;
	vector< vector<int> > board;
	vector< vector<int> > sco;
	char stmp;
	board.resize(a);
	sco.resize(a);
	//stmp.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);
	for(int i=0;i<a;i++) sco[i].resize(b);

	//for(int i=0;i<a;i++) cin>> stmp[i];

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> stmp;
			if(stmp=='.'){
				board[i][j]=1;
				sco[i][j]=-1;
				p++;
			}else{
				board[i][j]=0;
			}
		}
	}

	for(int i=0;i<a;i++){
		tmp=0;
		s=0;
		for(int j=0;j<b;j++){
			if(board[i][j]){
			//if(stmp[i][j]=='.'){
				tmp++;

			}else{
				for(int k=s;k<j;k++) sco[i][k]+=tmp;
				s=j+1;
				tmp=0;
			}
		}
		for(int k=s;k<b;k++) sco[i][k]+=tmp;
	}
	
	for(int i=0;i<b;i++){
		tmp=0;
		s=0;
		for(int j=0;j<a;j++){
			if(board[j][i]){
			//if(stmp[j][i]=='.'){
				tmp++;

			}else{
				for(int k=s;k<j;k++) sco[k][i]+=tmp;
				s=j+1;
				tmp=0;
			}
		}
		for(int k=s;k<a;k++) sco[k][i]+=tmp;
	}

	map<int, int> mp;

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(sco[i][j]!=0) mp[sco[i][j]]++;
		}
	}
	
	for (auto pp : mp) {
  		auto key = pp.first;
  		auto value = pp.second;
  		// key, valueを使う
		  //cout<< key SP << value <<endl;
		tmp=modpow(2, ((LLi)p-(LLi)(key)));
		tmp=tmp%mod;
		tmp*=modpow(2, (LLi)key)-1;
		tmp=tmp%mod;
		//cout<< tmp <<endl;
		ans+=(value*tmp)%mod;
		ans=ans%mod;
	}

	/*for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(sco[i][j]==0) continue;
			tmp=modpow(2, (LLi)(p-sco[i][j]));
			tmp*=modpow(2, (LLi)(sco[i][j]))-1;
			ans+=tmp%mod;
		}
	}*/

	cout<< ans << endl;
 
	return 0;
}