#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

//#define DEBUG ;

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size();
  if (right == 1){
    if (a[left] == x){
      return left;
    }
    else{
      return -1;
    }
  }

  int midpoint = (left + right)/2;

  if (a[midpoint] == x)
    return midpoint;
  else if (x < a[midpoint]){
    vector<int>::const_iterator first = a.begin();
    vector<int>::const_iterator last = a.begin() + midpoint; // a[midpoint] not included
    vector<int> subvec(first,last);
    return binary_search(subvec, x);
  }
  else{
    if ((int)a.size()==2)
      return -1;
    vector<int>::const_iterator first = a.begin() + midpoint +1;
    vector<int>::const_iterator last = a.end();
    vector<int> subvec(first, last);
    return binary_search(subvec, x);
  }
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void test_solution(){
  int n = 5;
  vector<int> a{1,5,8,12,13};
  int m = 5;
  vector<int> b{8,1,23,1,11};
  for (int i=0; i < 5; ++i)
    assert(linear_search(a,b[i]) == binary_search(a,b[i]));
    //std::cout << binary_search(a,b[i]) << std::endl;
  //std::cout << "Completed Test." << std::endl;
}

int main() {
#ifdef DEBUG
  test_solution();
#else
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << linear_search(a, b[i]) << ' ';
  }
#endif
}
