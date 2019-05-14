#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){

	int x;
	int min=10000;
	string s, s3;

	cin>> s;

	for(int i=0;i<s.size()-2;i++){
		s3=s.substr(i, 3);
		x=atoi(s3.c_str());
		if(abs(753-x)<min) min=abs(753-x);
	}
	cout<< min << "\n";
}
