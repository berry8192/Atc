#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int nc[100010];

struct shi{
	int p;
	int y;
	int num;

	bool operator<(const shi &in) const{
		return y<in.y;
	};
};

struct ids{
	int ida;
	int idb;
	int num;

	bool operator<(const ids &in) const{
		return num<in.num;
	};
};

int main(){

	vector<shi> s;
	vector<ids> ii;
	int n, m;

	for(int i=0;i<100010;i++) nc[i]=1;

	cin>> n >> m;

	s.resize(m);
	ii.resize(m);

	for(int i=0;i<m;i++){
		cin>> s[i].p >> s[i].y;
		s[i].num=i;
	}

	sort(s.begin(), s.end());

	for(int i=0;i<m;i++){
		ii[i].ida=s[i].p;
		ii[i].idb=nc[s[i].p];
		nc[s[i].p]++;
		ii[i].num=s[i].num;
	}

	sort(ii.begin(), ii.end());

	for(int i=0;i<m;i++) printf("%06d%06d\n",ii[i].ida ,ii[i].idb);

}
