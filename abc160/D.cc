#include <bits/stdc++.h>

using namespace std;

int main(){

	int n, x, y, tmp, nearx, neary;
	int d[2020];

	cin>> n >> x >> y;

	for (int i = 0;i < 2020;i++) d[i] = 0;

	for (int i = 1;i <= n - 1;i++) {
		for (int j = i + 1;j <= n;j++) {
			nearx = min(abs(x - i), abs(y - i));
			neary = min(abs(x - j), abs(y - j));
			tmp = min(j - i, nearx + neary + 1);
			d[tmp]++;
		}
	}

	for (int i = 1;i < n;i++) cout << d[i] << endl;;

	return 0;
}
