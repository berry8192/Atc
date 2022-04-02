#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep3(i, n, m) for (int i = m; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)
#define all(v) v.begin(), v.end()
#define SP << " " 
#define LLi long long int

using namespace std;

int imax=2147483647;
long long int llimax=9223372036854775807;
LLi mod=1000000007;
//LLi mod=998244353;

LLi n, tmp, ans=llimax, rtn;

//int型vectorを出力
template <class T> void PV(T pvv) {
	if(!pvv.size()) return;
	rep(i, pvv.size()-1) cout << pvv[i] SP;
	cout<< pvv[pvv.size()-1] <<endl;
}

//LLi型vectorを出力
template <class T>void PVV(T pvv) {
	rep(i, pvv.size()){
		rep(j, pvv[i].size()){
			cout << pvv[i][j] SP;
		}
		cout << endl;
	}
}

template<typename T>
auto SolveCubicEquation(const T p, const T q){
    //p/3
    const auto p_d3 = p / T(3.0);
    //q/2
    const auto q_half = q / T(2.0);
    //D = (q/2)^2 + (p/3)^3
    const auto D = q_half*q_half + p_d3*p_d3*p_d3;
    
    T x1{};
    std::complex<T> x2{}, x3{};
    
    if(std::fabs(D) < 1.0E-8) {
        // D == 0 重解
        
        auto tmp = std::cbrt(q_half);
        x1 = T(-2.0) * tmp;
        x2 = x3 = tmp;
    }
    else if(0.0 < D) {
        // 0 < D １つの実数解と二つの共役な複素数解
        
        //√D
        const auto D_root = std::sqrt(D);
        //u = v = ∛(-q/2 ± √D)
        const auto u = std::cbrt(-q_half + D_root);
        const auto v = std::cbrt(-q_half - D_root);
        
        x1 = u + v;
        //-(u + v)/2
        const auto real = T(-0.5)*x1;
        //√3
        constexpr T root3 = T(1.7320508075688772935274463415059);
        //√3(u - v)/2
        const auto imag  = root3 * (u - v) * T(0.5);
        
        x2 = {real,  imag};
        x3 = {real, -imag};
    }
    else {
        // D < 0 異なる３つの実数解
        
        //2√(-p/3)
        const auto sqrt_p_d3 = T(2.0) * std::sqrt(-p_d3);
        //θ/3
        const auto arg = std::arg(std::complex<T>{ -q_half, std::sqrt(-D) }) / T(3.0);
        //2π/3
        constexpr T pi2d3 = T(2.0 * 3.1415926535897932384626433832795 / 3.0);
        
        x1 = sqrt_p_d3*std::cos(arg);
        x2 = sqrt_p_d3*std::cos(arg + pi2d3);
        x3 = sqrt_p_d3*std::cos(arg + pi2d3 + pi2d3);
    }
    
    return std::make_tuple(x1, x2, x3);
}

template<typename T>
auto SolveCubicEquation(const T A, const T B, const T C){
    //A/3
    auto A_div3 = A / T(3.0);
    
    const T p = B - A_div3*A;
    
    //A^3/27
    auto q_t = A_div3 * A_div3 * A_div3;
    //2A^3/27
    q_t += q_t;
    
    const T q = q_t - A_div3*B + C;
    
    auto [x1, x2, x3] = SolveCubicEquation(p, q);
    
    //xn = yn - A/3
    return std::make_tuple(x1 - A_div3, x2 - A_div3, x3 - A_div3);
}

template<typename T>
auto SolveQuadraticEquation(const T a, const T b, const T c){
    const auto D = b*b - T(4.0)*a*c;
    
    std::complex<T> x1{}, x2{};
    if(std::fabs(D) < 1.0E-6) {
        x1 = x2 = -b / (a + a);
    }
    else if(D < 0.0) {
        const auto a2 = a + a;
        const auto real = -b / a2;
        const auto imag = std::sqrt(D) / a2;
        x1 = {real,  imag};
        x2 = {real, -imag};
    }
    else {
        //-b - √D
        const auto tmp = -b - std::sqrt(D);
        //2c/(-b - √D)
        x1 = (c + c) / tmp;
        //(-b - √D)/2a
        x2 = tmp / (a + a);
    }
    
    return std::make_tuple(T(0.0), x1, x2);
}

template<typename T>
auto SolveCubicEquation(const T a, const T b, const T c, const T d){
    if(a != 0.0) {
        return SolveCubicEquation(b/a, c/a, d/a);
    }
    else if(b != 0.0) {
        //bx^2 + cx + d = 0
        //x = (-b ± √(b^2 - 4ac))/2a
        return SolveQuadraticEquation(b, c, d);
    }
    else {
        constexpr std::complex<T> z = T(0.0);
        //cx + d = 0
        //x = -d / c
        return std::make_tuple(-d/c, z, z);
    }
}

void cal(LLi a, LLi b){
	LLi tmp=a*a*a+a*a*b+a*b*b+b*b*b;
	if(tmp>=n) ans=min(ans, tmp);
}

int main(){

	cin>> n;

	rep3(i, 1000001, 0){
		double tmp=i;
		auto [x1, x2, x3] = SolveCubicEquation(1.0, tmp, tmp*tmp, tmp*tmp*tmp-n);
		//std::cout << x1 << "," << x2  << "," << x3 << std::endl;
		if(x1<0.0) break;
		LLi b=round(x1);
		if(b-1>=0) cal(i, b-1);
		cal(i, b);
		cal(i, b+1);
	}

	cout<< ans <<endl;
 
	return 0;
}