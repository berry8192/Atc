#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int r, g, b, n, cnt=0;

	cin>> r >> g >> b >> n;

	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(i*r+j*g<=n && (n-(i*r+j*g))%b==0){
				cnt++;
				//cout<< r << " " << g << " " << b << "  " << i << " " << j << endl;
				//break;
			}
		}
	}

	cout<< cnt << endl;


}
