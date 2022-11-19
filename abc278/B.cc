#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define ll long long

using namespace std;

int imax=2147483647;
ll llimax=9223372036854775807;
ll mod=1000000007;

int main(){

	int a;
	cin>> a;
	int b;
	cin>> b;
	int t=a*60+b;
	// cout<< t<<endl;

	while(1){
		// cout<< t<<endl;
		int h=t/60;
		int m=t%60;
		string s;
		if(h<10) s+='0';
		s+=to_string(h);
		if(m<10) s+='0';
		s+=to_string(m);
		// cout<< s <<endl;
		// string hh=to_string(s[0])+to_string(s[2]);
		// string mm=to_string(s[1])+to_string(s[3]);
		// rep(i, 4) cout<< s[i] <<endl;
		string hh;
		string mm;
		hh+=s[0];
		hh+=s[2];
		mm+=s[1];
		mm+=s[3];
		// cout<< hh SP << mm <<endl; 
		h=stoi(hh);
		m=stoi(mm);
		// cout<< h SP << m <<endl; 
		if(h<=23 && m<=59){
			cout<< s[0] << s[1] SP << s[2] << s[3] <<endl;
			return 0;
		}

		t++;
		if(t==1440) t=0;
	}
 
	return 0;
}