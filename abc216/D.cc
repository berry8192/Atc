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

	int n, m, k, tmp, rm=0;
	vector< vector<int> > v, w;
	vector<int> dig;
  	queue<int> q;
	map<int, int> mp;

	cin>> n >> m;
	v.resize(m+1);
	w.resize(n+1);
	dig.resize(m+1);
	rep(i, n) w[i+1].resize(4);

	rep(i, m){
		cin>> k;
		rep(j, k){
			cin>> tmp;
			v[i+1].push_back(tmp);
			if(w[tmp][0]){
				w[tmp][1]=i+1;
				w[tmp][3]=j+1;
			}else{
				w[tmp][0]=i+1;
				w[tmp][2]=j+1;
			}
		}
	}

	rep(i, m) q.push(i+1);

	while (!q.empty()) {
    	//cout << q.front() << endl;  // 先頭の値を出力
    	//q.pop();  // 先頭の値を削除
		//cout<< "q.front() " << q.front() <<endl;
		mp[v[q.front()][dig[q.front()]]]++;
		//cout<< "v[q.front()][dig[q.front()]] " << v[q.front()][dig[q.front()]] <<endl;
		if(mp[v[q.front()][dig[q.front()]]]==2){
			//cout<< "match" <<endl;
			//cout<< "w[v[q.front()][dig[q.front()]]][0] " << w[v[q.front()][dig[q.front()]]][0] <<endl;
			if(w[v[q.front()][dig[q.front()]]][0]==q.front()){
				tmp=1;
			}else{
				tmp=0;
			}
			//cout<< "tmp " << tmp <<endl;
			//cout<< "w[v[q.front()][dig[q.front()]]][tmp] " << w[v[q.front()][dig[q.front()]]][tmp] <<endl;
			dig[w[v[q.front()][dig[q.front()]]][tmp]]++;
			dig[q.front()]++;
			if(v[q.front()].size()>=dig[q.front()]) q.push(q.front());
			//cout<< "add dig " << q.front() SP << w[v[q.front()][dig[q.front()]]][tmp] <<endl;
			//cout<< v[w[v[q.front()][dig[q.front()]]][tmp]].size();
			if(v[w[v[q.front()][dig[q.front()]]][tmp]].size()>=dig[w[v[q.front()][dig[q.front()]]][tmp]]) q.push(w[v[q.front()][dig[q.front()]]][tmp]);
			rm++;
		}
		q.pop();
  	}
//cout<< rm <<endl;
	if(rm==n) cout<< "Yes" << endl;
	else cout<< "No" << endl;
 
	return 0;
}