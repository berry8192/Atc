#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

	int a, b, c, d, e;
	int sum=0;
	cin>> a >> b >> c >> d >> e;

	int min=a;

	if((b+9)%10<=(min+9)%10) min=b;
	if((c+9)%10<=(min+9)%10) min=c;
	if((d+9)%10<=(min+9)%10) min=d;
	if((e+9)%10<=(min+9)%10) min=e;

	sum+=(a/10+1)*10;
	sum+=(b/10+1)*10;
	sum+=(c/10+1)*10;
	sum+=(d/10+1)*10;
	sum+=(e/10+1)*10;

	if(min%10!=0) sum+=min%10-10;

	if(a%10==0) sum-=10;
	if(b%10==0) sum-=10;
	if(c%10==0) sum-=10;
	if(d%10==0) sum-=10;
	if(e%10==0) sum-=10;

	cout<< sum << endl;


}
