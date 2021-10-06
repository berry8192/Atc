#include <iostream>
#include <random>

int main()
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  for (int i = 0; i < 5; ++i) {
    int result = engine();
	result=abs(result);
    std::cout << result << std::endl;
  }
}