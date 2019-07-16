#include <iostream>
#include <assert.h>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {
  int greater = a;
  if (b > a)
    greater = b;
  for (long l = greater; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

// Greates common divisor implementation from previous problem.
int gcd_fast(int a, int b) {
  if (a == 0 || b == 0)
    return a+b;
  int bigger, smaller;
  if (a > b) {
    bigger = a;
    smaller = b;
  }
  else {
    bigger = b;
    smaller = a;
  }
  gcd_fast(smaller, bigger%smaller);	
}

long long lcm_faster(int a, int b) {
  int gdc = gcd_fast(a,b);

  return (long long) a * b / (long long) gdc;
}


void test_solution() {
  assert(lcm_faster(6,8) == 24);
  //assert(lcm_faster(761457,614573) == 467970912861);
  for (int i=0;i < 10; ++i){
        int a = std::rand() % 100000;
	int b = std::rand() % 100000;
	assert(lcm_naive(a,b) == lcm_faster(a,b));
  }
}

int main() {
  int a, b;
  //test_solution();
  //std::cout << "Passed the tests. Enter the two numbers." << std::endl;
  std::cin >> a >> b;
  std::cout << lcm_faster(a, b) << std::endl;
  return 0;
}
