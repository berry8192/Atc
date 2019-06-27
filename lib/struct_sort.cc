#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

//by num sort
struct xxxx{
	int value;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};

//2 factor sort
struct xxxx{
	int x1;
	int x2;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2<in.x2;
	};
};

//3 factor sort
struct xxxx{
	int x1;
	int x2;
	int x3;

	bool operator<(const xxxx &in) const{
		return x1!=in.x1 ? x1<in.x1 : x2!=in.x2 ? x2<in.x2 : x3<in.x3;
	};
};

int main(){

	int n;
	vector<xxxx> v;

	cin>> n;
	v.resize(n);

	for(int i=0;i<n;i++){
		cin>> v[i].x1 >> v[i].x2 >> v[i].x3;
	}

	sort(v.begin(), v.end());

	for(int i=0;i<v.size();i++) cout<< v[i].x1 << " " << v[i].x2 << " " << v[i].x3 << endl;

}
