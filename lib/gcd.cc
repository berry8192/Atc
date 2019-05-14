#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
//
if(a<0) a=b;
if(b<0) b=a;
//
    if (b == 0) return a;
    return gcd(b, a%b);
}

int lcm(int a, int b) {
    return a*b/gcd(a, b);
}
