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

struct num{
	int val;
	int d;

	bool operator<(const num &in) const{
		return val<in.val;
	};
};

int main(){

	int n, ai, bi, tmp, us=0, pos, flag;
	set<int> s;
  	queue<int> q;
	priority_queue<num> pq;
	vector<num> cnt;
	vector<int> seen;
	vector< map<int, int> > bo;
	cin>> n;
	seen.resize(400010, 0);
	cnt.resize(400010);
	bo.resize(400010);

	rep(i, n){
		cin>> ai >> bi;
		if(ai==bi){
			s.insert(ai);
			if(seen[ai]==0) q.push(ai);
			seen[ai]++;
			us++;
			//cout<< ai << "kaburi" <<endl;

		}else{
			bo[ai][bi]++;
			bo[bi][ai]++;
			cnt[ai].val++;
			cnt[bi].val++;
			cnt[ai].d=ai;
			cnt[bi].d=bi;
		}
	}

	sort(cnt.begin(), cnt.end());
	//cout<< "cnt" <<endl;
	rep(i, cnt.size()){
		//if(cnt[i].val) cout<< cnt[i].val << " " << cnt[i].d <<endl;
	}
	//cout<< "cnt" <<endl;
	//rep(i, 400010) sort(bo[i].begin(), bo[i].end());

	rep(i, cnt.size()){
		pos=i;
		if(cnt[i].val>2){
			break;
		}
		if(cnt[i].val==1){
			s.insert(cnt[i].d);
			if(seen[cnt[i].d]==0) q.push(cnt[i].d);
			seen[cnt[i].d]++;
			us++;
			//cout<< "single" << cnt[i].d <<endl;
		}
	}

	while(1){
	//cout<< us <<endl;
	if(q.empty()){
		flag=1;
		for(int i=pos;i<cnt.size();i++){
			pos=i;
			if(cnt[i].val>0 && seen[cnt[i].d]==0){
				if(seen[cnt[i].d]==0) q.push(cnt[i].d);
				seen[cnt[i].d]++;
				us++;
				//cout<< "emptycall" << cnt[i].d <<endl;
				flag=0;
				break;
			}
		}
		if(flag) break;
	}

	while (!q.empty()) {
    	tmp=q.front();  // 先頭の値を出力
		//cout<<"tmp" << tmp<<endl;
		//cout<< us <<endl;
    	q.pop();  // 先頭の値を削除
		for (auto p : bo[tmp]) {
  			auto key = p.first;
  			auto value = p.second;
  			// key, valueを使う
			//cout<< key << " " << value <<endl;
			s.insert(key);
			if(seen[key]==0) q.push(key);
			seen[key]++;
			cnt[tmp].val--;
			cnt[key].val--;
			us++;

			if(value==1){
				bo[tmp].erase(key);
			}else{
				bo[tmp][key]--;
			}
		}
  	}

	}

	cout<< s.size() <<endl;
 
	return 0;
}