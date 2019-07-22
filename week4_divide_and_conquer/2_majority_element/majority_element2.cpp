#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

//#define DEBUG ;

struct Ocurrences{
  int value;
  int numberapperances;
};

int get_majority_element(const vector<int> &a, int left, int right, vector<Ocurrences> &ocurrences,const int &thres) {
  bool newvalue = true;
  bool firstcomp = true;
  if (left == right) return 0;
  if (left + 1 == right) {
    newvalue = true;
    for (int i = 0; i< ocurrences.size(); ++i){
      if(a[left] == ocurrences[i].value){
        ocurrences[i].numberapperances++;
        if(ocurrences[i].numberapperances > thres)
          return 1;
        newvalue = false;
        break;
      }
    }
    if (newvalue && firstcomp){
        Ocurrences oc;
        oc.value = a[left];
        oc. numberapperances = 1;
        ocurrences.push_back(oc);
    }
    return 0;
  }

  int  midpoint = (left + right)/2;

  //std::cout << "did this1" << std::endl;
  int subans = get_majority_element(a, midpoint, right, ocurrences, thres);
  int subans2 = 0;
  firstcomp = false;
  if (subans)
    return 1;
  else
    subans2 = get_majority_element(a, left, midpoint, ocurrences, thres);
  //std::cout << "did this" << std::endl;
  return (subans || subans2);
}

int find_max(vector<Ocurrences>& ocurrences){
  return 0;
}

void test_solution(vector<Ocurrences>& ocurrences){
  int n=5;
  vector<int> a{2,3,9,2,2};
  //assert(get_majority_element(a, n, ocurrences)==0);
  get_majority_element(a, 0, a.size(), ocurrences, n/2);
}

int main() {
  vector<Ocurrences> ocurrences;
#ifdef DEBUG
  test_solution(ocurrences);
#else
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }

  int ans = get_majority_element(a, 0, a.size(), ocurrences, n/2);
/*  int ans = 0;
  for(int i=0; i<ocurrences.size(); ++i){
    //std::cout << ocurrences[i].value << std::endl;
    if (ocurrences[i].numberapperances > n/2)
      ans = 1;
  }*/

  std::cout << ans << '\n';
#endif
}
