#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, ans=1, tmp, mi;

	cin>> n;

	cin >> mi;

	for (int i = 1;i < n;i++) {
		cin >> tmp;
		if (tmp < mi) {
			mi = tmp;
			ans++;
		}
	}

	cout<< ans << endl;

}
