#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
	int n, tmp;
	set<int> st;

  cin>> n;
  
  for(int i=0;i<n;i++){
  	cin>> tmp;
  	st.insert(tmp);
  	}
  	auto itr=st.rbegin();
  	itr++;

  cout<< *itr <<endl;

  return 0;
}
