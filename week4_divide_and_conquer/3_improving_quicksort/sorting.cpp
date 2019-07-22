#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>

using std::vector;
using std::swap;

#define DEBUG ;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

int partition3(vector<int> &a, int l, int r, int & counteq) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      if (a[i] == x )
        counteq++;
      j++;
      swap(a[i], a[j]);
      if(a[j] < x){
        swap(a[j], a[j-counteq]);
      }
    }
  }
  swap(a[l], a[j-counteq]);
  return j-counteq;
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int counteq = 0;
  int m = partition3(a, l, r, counteq);

  std::cout << k << std::endl;
  std::cout << m << std::endl;
  std::cout << counteq << std::endl;

  for(int i=l; i<=r; ++i)
    std::cout << a[i] << " ";
  std::cout << std::endl;

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + counteq, r);

  for(int i=l; i<=r; ++i)
    std::cout << a[i] << " ";
  std::cout << std::endl;
}

void test_solution(){
  int n = 20;
  vector<int> a{1,1,2,2,2,3,1,2,3,4,5,9,1,2,3,4,5,5,5,6};
  randomized_quick_sort(a, 0, a.size() - 1);
  vector<int> result{1,1,1,1,2,2,2,2,2,3,3,3,4,4,5,5,5,5,6,9};
/*
  int n = 6;
  vector<int> a{1,1,2,4,2,1};
  randomized_quick_sort(a, 0, a.size() - 1);
  vector<int> result{1,1,1,2,2,4};*/

  assert(a == result);
}

int main() {
#ifdef DEBUG
  test_solution();
#else
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
#endif
}
