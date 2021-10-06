#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

vector< vector<string> > d={{"#.#", "#.#", "#.#"}, {"##.", ".#.", ".#."}, {"..#", "###", "#.."}, {"..#", "###", "..#"}, {"#.#", "###", "..#"}, {"#..", "###", "..#"}, {"#..", "###", "#.#"}, {"..#", "..#", "..#"}, {"#.#", "###", "#.#"}, {"#.#", "###", "..#"}};

void jdg(vector<string> v, int x){
	int flag;
	rep(i, 10){
		flag=1;
		rep(j, 3){
			//if(i>7) cout<< i << " " << v[j] << " " << d[i][j] <<endl;
			if(v[j]!=d[i][j]) flag=0;
		}
		if(flag){
			if(i==4 && x==9) i=9;
			cout<< i;
			return;
		}
	}
}

void PV(vector<string> pvv) {
	rep(i, (int)pvv.size()) cout << pvv[i] <<endl;
	cout <<endl;
}

int main(){

	int n, x;
	vector<string> v, tmp;

	cin>> n;
	v.resize(5);
	tmp.resize(3);

	rep(i, 5) cin >> v[i];

	rep(i, n) {
		if(v[0][4*i+2]=='#') x=9;
		else x=4;
		rep(j, 3){
			tmp[j]=v[j+1].substr(4*i+1, 3);
			//cout<< tmp[j] <<endl;
		}
		//PV(tmp);
		jdg(tmp, x);
	}

	return 0;
}