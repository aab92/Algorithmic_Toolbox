#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

//#define DEBUG ;


vector<int> optimal_number_operations(int n) {
  int poss_operations = 3;
  std::vector<int> sequence;
  std::vector<int> optimal_numOp(n,1e5);
  std::vector<int> prev_opt(poss_operations);

  for (int i=1; i<=n; ++i) {
    if (i % 3 == 0) {
      prev_opt[0] = i/3;
    }
    else
      prev_opt[0] = 1e5;
    if (i % 2 == 0) {
      prev_opt[1] = i/2;
    }
    else
      prev_opt[1] = 1e5;
    if (i-1>=1)
      prev_opt[2] = i-1;
    else{
      prev_opt[2] = 1e5;
    }
    // Find the optimal alternative
    int min = 1e5;
    for (int k=0; k<poss_operations; ++k){
      if(prev_opt[k]!= 1e5 && optimal_numOp[prev_opt[k]-1] < min)
        min = optimal_numOp[prev_opt[k]-1];
    }
    if (min == 1e5){
      optimal_numOp[i-1] = 0;
      continue;
    }
    optimal_numOp[i-1] = min + 1;
  }

/*  for(int i=0; i<n; ++i)
    std::cout << optimal_numOp[i] << " ";
  std::cout << std::endl;
*/
  return optimal_numOp;
}

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  std::vector<int> op_num_op = optimal_number_operations(n);  // vector contains the optimal number of operations for all numbers from 1 to n
  int poss_operations = 3;
  std::vector<int> prev_opt(poss_operations); // previous optimus

  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      prev_opt[0] = n / 3;
    }
    else
      prev_opt[0] = 1e5;
    if (n % 2 == 0) {
      prev_opt[1] = n / 2;
    }
    else
      prev_opt[1] = 1e5;
    if(n-1>=1){
      prev_opt[2] = n - 1;
    }
    else
      prev_opt[2] = 1e5;
    // Find the optimal alternative
    int min = 1e5;
    int minindex;
    for (int k=0; k<poss_operations; ++k){
      if(prev_opt[k]!= 1e5 && op_num_op[prev_opt[k]-1] < min){
        min = op_num_op[prev_opt[k]-1];
        minindex = k;
      }
    }
    if (min == 1e5)
      break;

    n = prev_opt[minindex];
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}


int main() {
  int n;
  std::cin >> n;

#ifdef DEBUG
//  std::cout << optimal_number_operations(n) << std::endl;
#else
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }

#endif
}
