#include <iostream>
#include <string>

using namespace std;
int main(){

	string s;
	int y, m;

	cin>> s;

	y = std::stoi(s.substr(0, 4));
	m = std::stoi(s.substr(5, 2));

	//cout<< y << " " << m << "\n";

	if(2019<=y){
		if(5<=m){
			cout<< "TBD" << "\n";
		}else{
			cout<< "Heisei" << "\n";
		}
	}else{
		cout<< "Heisei" << "\n";
	}

}
