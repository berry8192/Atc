#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(){

	int n, tmp;
	long long int ans = 0;
	int board[10][10];

	cin>> n;

	if (n <= 10) {
		cout << n << endl;
		return 0;
	}

	for (int i = 1;i < 10;i++) {
		for (int j = 1;j < 10;j++) {
			tmp = 0;
			if(i==j) tmp++;

			if (i * 10 + j <= n) tmp++;

			if (i * 100 + j <= n) {
				if (n < (i + 1) * 100) {
					tmp += ((n / 10) % 10);
					if (j <= n % 10) tmp++;
				}
				else {
					tmp += 10;
				}
			}

			if (i * 1000 + j <= n) {
				if (n < (i + 1) * 1000) {
					tmp += ((n / 10) % 100);
					if (j <= n % 10) tmp++;
				}
				else {
					tmp += 100;
				}
			}

			if (i * 10000 + j <= n) {
				if (n < (i + 1) * 10000) {
					tmp += ((n / 10) % 1000);
					if (j <= n % 10) tmp++;
				}
				else {
					tmp += 1000;
				}
			}

			if (i * 100000 + j <= n) {
				if (n < (i + 1) * 100000) {
					tmp += ((n / 10) % 10000);
					if (j <= n % 10) tmp++;
				}
				else {
					tmp += 10000;
				}
			}

			if (i * 1000000 + j <= n) {
				if (n < (i + 1) * 1000000) {
					tmp += ((n / 10) % 100000);
					if (j <= n % 10) tmp++;
				}
				else {
					tmp += 100000;
				}
			}
			board[i][j] = tmp;
		}
	}

	for (int i = 1;i < 10;i++) {
		for (int j = 1;j < 10;j++) {
			ans += board[i][j] * board[j][i];
		}
	}

	cout<< ans << endl;


}
