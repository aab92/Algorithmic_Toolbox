#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(const int W, const vector<int> &w) {
  vector<vector<int>> weight_table(w.size() + 1,vector<int>(W + 1)); // table to store the max weight achievable for a knapsack of capacity cap using items 1,..., i

  //Now, for the item i, there is the possibility that it is included in the optimal
  //solution, or that it is not included.

  for(int i=0; i<=w.size(); ++i)
    weight_table[i][0] = 0;

  for(int i=0; i<=W; ++i)
    weight_table[0][i] = 0;

  //int globalmax = 0;
  for(int row =1; row <= w.size(); ++row){  // items
    for(int col =1; col <= W; ++col){ // capacities
      int max = weight_table[row-1][col];
      int included = weight_table[row-1][col-w[row-1]] + w[row-1];
      if (max < included && included <= col)
        max = included;

      weight_table[row][col] = max;
    //  if (max>globalmax)
    //    globalmax = max;
    }
  }
/*
  for(int row =0; row <= w.size(); ++row){
    for(int col =0; col <= W; ++col)
      std::cout << weight_table[row][col] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
*/
  return weight_table[w.size()][W];
  //return globalmax;
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
