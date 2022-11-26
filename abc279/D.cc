#include <iostream>
#include <cmath>

using namespace std;

int main(){
  long long a, b;
double g;

  cin>> a>>b;

  g=pow(2.0*(b-1)/a, 2.0/3);

double ans=a;
ans=min(ans, a/sqrt(floor(g)));
ans=min(ans, a/sqrt(ceil(g)));

  printf("%.12lf\n", ans);

  return 0;
}
