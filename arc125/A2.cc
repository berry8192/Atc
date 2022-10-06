#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

void rle(string s, vector<pair<char, int>> &vec)
{
  int cnt = 1;
  for(int i = 1; i < (int)s.size(); i++){
    if(s[i] != s[i-1]){
      vec.push_back({s[i-1], cnt});
      cnt = 0;
    }
    cnt++;
  }
  vec.push_back({s.back(), cnt});
}

int main(){

	int n, m;
	vector<int> d={-1, -1};
	vector<int> s, t;
	string turn;
	vector<pair<char, int>> svec;

	cin>> n >> m;
	s.resize(n);
	t.resize(m);

	rep(i, n) cin >> s[i];
	rep(i, m){
		cin >> t[i];
		turn+=to_string(t[i]);
	}

	rep(i, n){
		if(s[i]==0 || s[(n-i)%n]==0){
			d[0]=i;
			break;
		}
	}
	rep(i, n){
		if(s[i]==1 || s[(n-i)%n]==1){
			d[1]=i;
			break;
		}
	}

	rle(turn, svec);
	// cout<< "d[0] " SP << d[0] <<endl;
	// cout<< "d[1] " SP << d[1] <<endl;
	int ans=0;
	rep(i, svec.size()){
		// cout<< svec[i].first SP << svec[i].second <<endl;
		if(i==0) ans+=d[t[0]];
		else ans++;

		// cout<< "svec[i].first " << svec[i].first <<endl;
		// cout<< "d[svec[i].first] " << d[svec[i].first] <<endl;
		if(d[int(svec[i].first-'0')]==-1){
			cout<< -1 <<endl;
			return 0;
		}
	}

	cout<< ans+m <<endl;
 
	return 0;
}