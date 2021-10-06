#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(){

	int a, b;
	int sum=0;

	cin>> a >> b;

	for(int i=a;i<=b;i++){
		if(i/10000==i%10 && (i/1000)%10==(i%100)/10) sum++;
	}

	cout<< sum << endl;


}
/*
struct xxxx{
	int x;
	int y;
	int num;

	bool operator<(const xxxx &in) const{
		return num<in.num;
	};
};
*/
