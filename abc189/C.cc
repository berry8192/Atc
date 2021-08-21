#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;

//int型vectorを出力
void PV(vector<int> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

//LLi型vectorを出力
void PVL(vector<LLi> pvv) {
	rep(i, pvv.size()) cout << pvv[i] SP;
	cout << endl;
}

template< typename T >
int64_t largest_rectangle(vector< T > height)
{
  stack< int > st;
  height.push_back(0);
  vector< int > left(height.size());
  int64_t ret = 0;
  for(int i = 0; i < height.size(); i++) {
    while(!st.empty() && height[st.top()] >= height[i]) {
      ret = max(ret, (int64_t) (i - left[st.top()] - 1) * height[st.top()]);
      st.pop();
    }
    left[i] = st.empty() ? -1 : st.top();
    st.emplace(i);
  }
  return (ret);
}


int main(){

	int n, ans=0;
	vector<int> v;

	cin>> n;
	v.resize(n);

	rep(i, n) cin >> v[i];

	cout << largest_rectangle(v) << endl;
 
	return 0;
}