#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

int main(){

	int a, b, n, ssr, ssc;
	int sl=0, sr=0, su=0, sd=0, tl=0, tr=0, tu=0, td=0;
	int l, r, u, d, x, y, flag=0;
	//vector< vector<int> > board;
	string s, t;

	cin>> a >> b >> n;
	cin>> ssr >> ssc;
	cin>> s;
	cin>> t;

	/*board.resize(a);
	for(int i=0;i<a;i++) board[i].resize(b);

	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			cin>> board[i][j];
		}
	}*/

	l=ssc-1;
	r=b-ssc;
	u=ssr-1;
	d=a-ssr;

	//cout<< l << " " << r << " " << u << " " << d << endl;

	for(int i=0;i<n;i++){
		if(s[i]=='L') sl++;
		if(s[i]=='R') sr++;
		if(s[i]=='U') su++;
		if(s[i]=='D') sd++;

		if(l<sl-tr){
			flag=1;
			//cout<< i << endl;
			break;
		}
		if(r<sr-tl){
			flag=1;
			//cout<< i << endl;
			break;
		}
		if(u<su-td){
			flag=1;
			//cout<< i << endl;
			break;
		}
		if(d<sd-tu){
			flag=1;
			//cout<< i << endl;
			break;
		}

		if(t[i]=='L' && tl+1-sr<=l) tl++;
		if(t[i]=='R' && tr+1-sl<=r) tr++;
		if(t[i]=='U' && tu+1-sd<=u) tu++;
		if(t[i]=='D' && td+1-su<=d) td++;

	}

	if(flag==1){
		cout<< "NO" << endl;
	}else{
		cout<< "YES" << endl;
	}

}
