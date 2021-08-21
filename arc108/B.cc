#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
LLi llimax=9223372036854775807;
LLi mod=1000000007;

void ac(string s){
	cout<< s <<endl;
	exit(0);
}

int main(){

	int n, tmp=0;
	cin>> n;
	string s;
	cin>> s;
	n=s.size();
	//cout<< n <<endl;
	//cout<< s <<endl;

  	stack<int> v;
	v.push(0);

	rep(i, n){
		//cout<< s[i] SP << v.top() <<endl;
		if(s[i]=='f'){
			if(i<n-1 && s[i+1]=='o'){
				if(i<n-2 && s[i+2]=='x'){
					//v.push(3);
					tmp++;
					i+=2;
					//cout<<"fox"<<endl;
				}else{
					v.push(2);
					i++;
					//cout<<"fo?"<<endl;
					if(i<n-2 && s[i+2]!='f') v.push(0);
				}
			}else{
				v.push(1);
				//cout<<"f?"<<endl;
				if(i<n-1 && s[i+1]!='f') v.push(0);
			}
		}else{
			if(s[i]=='o'){
				if(i<n-1 && s[i+1]=='x'){
					if(v.top()==1){
						tmp++;
						i++;
						v.pop();
					//cout<<"f+ox"<<endl;
					}else{
						v.push(0);
					//cout<<"?+ox"<<endl;
					}
				}else{
					v.push(0);
					//cout<<"+o?"<<endl;
				}
			}else{
				if(s[i]=='x'){
					if(v.top()==2){
						tmp++;
						v.pop();
						//cout<<"fo+x"<<endl;
					}else{
						v.push(0);
						//cout<<"?+x"<<endl;
					}
				}else{
					v.push(0);
					//cout<< "?" <<endl;
				}
			}
		}
	}

	cout<< n-3*tmp <<endl;
 
	return 0;
}