#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

LLi gcdi(LLi a, LLi b) {
	if(a<0) a=b;
	if(b<0) b=a;
    if (b == 0) return a;
    return gcdi(b, a%b);
}

LLi lcmi(LLi a, LLi b) {
    return a/gcdi(a, b)*b;
}

int main(){

	LLi t, n, ax, bx, ay, by, first_match, ans=0;

	cin>> t;

	rep(i, t){
		cin >> ax >> bx >> ay >> by;
		
		if(ay==by){
			if(ax==bx) cout<< n <<endl;
			else cout<< 0 <<endl;
			continue;
		}

		//ax>bxになる
		if(ax<bx){
			swap(ax, bx);
			swap(ay, by);
		}

		//first_matchをもとめる
		if(ax==bx) first_match=0;
		if(ay<by){
			cout<< 0 <<endl;
			continue;
		}
		if(ay>by) first_match=(ax-bx)*lcmi(ay, by);
		if(by==1){
			first_match=ay*((ax-by)/(ay-1));
			if((ax-bx)%(ay-1)==0){
				if(first_match<=n){
					cout<< 2 <<endl;
				}else if(first_match+1<=n){
					cout<< 1 <<endl;
				}else{
					cout<< 0 <<endl;
				}
			}else{
				if(first_match<=n){
					cout<< 1 <<endl;
				}else{
					cout<< 0 <<endl;
				}
			}
			continue;
		}else{
			LLi tmp=(n+1-first_match)/ay*(by+(by-(n+1-first_match)/ay)/2);
			tmp+=min(n+1-(first_match+(n+1-first_match)/ay*ay), by-(n+1-first_match)/ay);
			tmp+=(first_match)/ay*(by+(by-(first_match)/ay)/2);
			tmp+=min(n+1-(first_match-(first_match)/ay*ay), by-(first_match)/ay);
			cout<< tmp <<endl;
		}

	}
 
	return 0;
}