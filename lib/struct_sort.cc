#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

struct xxxx{
	int value;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};

int main(){

	int n;
	vector<xxxx> v;

	cin>> n;
	v.resize(n);

	for(int i=0;i<n;i++){
		cin>> v[i].value;
		v[i].num=i;
	}

	sort(v.begin(), v.end());//構造体xxxxのvalueをnumでソートする

	for(int i=0;i<v.size();i++) cout<< v[i].num << " " << v[i].value << endl;

}
