#include <iostream>

int get_change(int m) {
  int denominations[] = {1, 3, 4};
  int numdem = 3;
  int highestdenom = 4;
  int prev_opt[highestdenom]={1,2,1,1};

  if (m<=highestdenom)
    return prev_opt[m-1];

  for (int i=highestdenom+1; i<= m; ++i){  //1
    int min = 1e3+1;
    for(int j=0; j< numdem; ++j){
      if(prev_opt[highestdenom-denominations[j]] + 1 < min){
        min = prev_opt[highestdenom-denominations[j]] + 1 ;
      }
    }
    for(int inde=0; inde<highestdenom-1; ++inde){
      prev_opt[inde] = prev_opt[inde+1];
    }
    prev_opt[highestdenom-1] = min;
    //std::cout << min << std::endl;
  }


  return  prev_opt[highestdenom-1];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
