#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define SP << " " 

using namespace std;

void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

int main(){

	long long int n, k, nw=1, sen=0;
	vector<int> v, seen, p(1);

	cin>> n >> k;
	v.resize(n+1);
	seen.resize(n+1, 0);

	rep(i, n) cin >> v[i+1];

	seen[1]=1;
	p[0]=1;
	while(1){
		if(k==sen) break;

		nw=v[nw];
		sen++;
		if(seen[nw]){
			int po;
			rep(i, p.size()){
				if(p[i]==nw){
					po=i;
					break;
				}
			}

			nw=p[(k-sen)%(sen-po)+po];
			break;
		}else{
			seen[nw]=1;
			p.push_back(nw);
		}
	}

	//PV(p);
	cout<< nw << endl;
 
	return 0;
}