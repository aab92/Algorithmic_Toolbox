#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);

  // Get number of inversions
  for(int i=left; i < ave; ++i){
    for(int j=ave; j<right; ++j){
      if(a[i]>a[j]){
        number_of_inversions++;
      }
      else
          break;
    }
  }
  //Merge
  int i = left;
  int bind = left;
  int j = ave;
  while(bind<right){
    if(a[i]<a[j]){
      b[bind] = a[i];
      i++;
      bind++;
    }
    else{
      b[bind] = a[j];
      j++;
      bind++;
    }
    if(j==right)
      while(i < ave){
        b[bind] = a[i];
        i++;
        bind++;
      }
    if(i==ave)
      while(j < right){
        b[bind] = a[j];
        j++;
        bind++;
      }
  }
  for(int i=left; i< right; ++i){
    a[i] = b[i];
    //std::cout << a[i] << " ";
  }
  //std::cout << std::endl;

  return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
