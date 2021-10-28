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

vector< vector<int> > v;
map<vector<int>, int> mp;
queue< vector<int> > q;

template <class T> void PV(T pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

void bfs(vector<int> x){
	//PV(x);
	vector<int> z(8);
	int em=36;
	for(int i=0;i<8;i++){
		em-=x[i];
	}
	//cout<< "emptyPlace=" << em <<endl;
	for(int i=0;i<9;i++){
		if(v[em][i]==0) continue;
		//cout<< "replaceToEmpty" << i;
		for(int j=0;j<8;j++) z[j]=x[j];
		for(int j=0;j<8;j++){
			if(z[j]==i){
				z[j]=em;
				break;
			}
		}
		mp[z]++;
		if(mp[z]==1){
			mp[z]=mp[x]+1;
			q.push(z);
			//cout<< "new=" << mp[z] <<endl;
			//PV(z);
		}else if(mp[z]>=10000 && mp[z]-1>mp[x]+1){
			//mp[z]=mp[x]+1
			mp[z]=mp[x]+1;
			q.push(z);
			//cout<< "renew=" << mp[z] <<endl;
			//PV(z);
		}else{
			mp[z]--;
		}
		//cout<< "mpz=" << mp[z] <<endl;
	}
	//cout<<endl;
}

int main(){

	int n, a, b, flag=0;
	vector<int> p(8);

	cin>> n;
	v.resize(9);
	rep(i, 9) v[i].resize(9);

	rep(i, n){
		cin >> a >> b;
		a--;
		b--;
		v[a][b]=1;
		v[b][a]=1;
	}
	rep(i, 8){
		cin>> p[i];
		p[i]--;
		//w[i]=i;
	}

	mp[p]=10000;
	q.push(p);

	while(!q.empty()){
		bfs(q.front());
		q.pop();
	}
	// for (auto p : mp) {
  	// 	auto key = p.first;
  	// 	auto value = p.second;
  	// 	// key, valueを使う
	// 	PV(key);
	// 	cout<< value <<endl;
	// }

	if(mp[{0, 1, 2, 3, 4, 5, 6, 7}]>=10000) cout<< mp[{0, 1, 2, 3, 4, 5, 6, 7}]-10000 <<endl;
	else cout<< -1 << endl;
 
	return 0;
}