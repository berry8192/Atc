#include <bits/stdc++.h>

using namespace std;

int main(){

	int a, b, c;

	cin>> a >> b;

	if(a<b){
		c=b;
		b--;
	}else{
		c=a;
		a--;
	}

	if(a<b){
		c+=b;
	}else{
		c+=a;
	}

	cout<< c << endl;


}
