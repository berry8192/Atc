#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int a, b, k, c;

	cin>> a >> b >> k;

	for(int i=100;0<i;i--){
		if((a/i)*i==a && (b/i)*i==b){
			k--;
			if(k==0){
				cout<< i << endl;
				i=0;
			}
		}
	}


}
