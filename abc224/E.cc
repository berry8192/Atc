#include <bits/stdc++.h>
using namespace std;

long long imax=2147483647;

struct poi{
	long long r, c;
	long long a;

	bool operator<(const poi &in) const{
		return a!=in.a ? a>in.a : c!=in.c ? c<in.c : r<in.r;
	};
};

long long a, b, n, ans=0;
vector< vector<poi> > hv, wv;
vector<long long> hs, wss;
queue<poi> q;
map<poi, long long> dis;
long long cnt=0;

void bfs(poi x){
	//cout<< x.r << " " << x.c << " " << x.a <<endl;
	cnt++;
	if(cnt>100) return;
	//移動してきた時の処理
	// if(dis[x]>dep) dis[x]=dep;

	//移動する処理
	for(int i=0;i<hv[x.r].size();i++){
		poi y=hv[x.r][i];
		if(hs[x.r]!=imax){
			dis[y]=dis[x]+hs[x.r];
			break;
		}

		if(dis[y]==0){
			dis.erase(y);
			continue;
		}
		if(dis[y]>dis[x] || (y.a)>=x.a) continue;
		
		q.push(y);
		dis[y]=dis[x]+1;
	}
	//移動する処理
	for(int i=0;i<wv[x.c].size();i++){
		poi y=wv[x.c][i];
		if(wss[x.c]!=imax){
			dis[y]=max(dis[y], dis[x]+wss[x.c]);
			break;
		}

		if(dis[y]==0){
			dis.erase(y);
			continue;
		}
		if(dis[y]>dis[x] || (y.a)>=x.a) continue;
		q.push(y);
		dis[y]=dis[x]+1;
	}
}

int main(){
	poi tmp;
	vector<poi> rca;

	cin>> a >> b >> n;
	hv.resize(a);
	wv.resize(b);
	hs.resize(a, imax);
	wss.resize(b, imax);
	rca.resize(n);

	for (int i=0;i<n;i++){
		cin>> tmp.r >> tmp.c >> tmp.a;
		tmp.r--;
		tmp.c--;
		rca[i]=tmp;
		dis[tmp]=imax;
		hv[tmp.r].push_back(tmp);
		wv[tmp.c].push_back(tmp);
		//cout<< tmp.r << tmp.c << tmp.a <<endl;
	}

	// Keyの値が小さい順にループ
	auto begin=dis.begin(), end=dis.end();
	for (auto itr=begin;itr!=end;itr++) {
  		auto key = itr->first;
  		auto value = itr->second;
  		// key, valueを使う
		cout<< key.r << " " << key.c << " " << key.a << " " << value <<endl;
	
		q.push(itr->first);
		while (!q.empty()) {
			tmp=q.front();
			bfs(tmp);
			q.pop();
		}
		hs[tmp.r]=max(dis[tmp], hs[tmp.r]);
		wss[tmp.c]=max(dis[tmp], wss[tmp.c]);
		cout<< dis[tmp] <<endl;
	}

	//dis表示
	// for (auto itr=begin;itr!=end;itr++) {
	// 	auto key = itr->first;
  	// 	auto value = itr->second;
	// 	cout<< key.r << " " << key.c << " " << key.a << " " << value <<endl;
	// }

	for(int i=0;i<n;i++) cout<< dis[rca[i]]-imax <<endl;

	return 0;
}