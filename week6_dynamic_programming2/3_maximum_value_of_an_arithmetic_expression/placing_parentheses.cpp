#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;

long long eval(long long a, long long b, const string* op, int k) {
  if (op[k] == "*") {
    return a * b;
  } else if (op[k] == "+") {
    return a + b;
  } else if (op[k] == "-") {
    return a - b;
  } else {
    assert(0);
  }
}

void print_table(vector<vector<long long>>& table, const int num_digits){
  for (int i=0; i<num_digits; ++i){
    for (int j=0; j<num_digits; ++j){
      std::cout << table[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void get_table_entries_k(const int row,const int col, vector<int>& digits, const int k,
                        const string* operations,vector<vector<long long>>& min_table,
                        vector<vector<long long>>& max_table, long long* temp){
  //temp[0] stores the minimum and temp[1] stores the maximum.
  vector<long long> tempor(4);
  tempor[0] = eval(min_table[row][k], min_table[k+1][col], operations, k);
  tempor[1] = eval(min_table[row][k], max_table[k+1][col], operations, k);
  tempor[2] = eval(max_table[row][k], min_table[k+1][col], operations, k);
  tempor[3] = eval(max_table[row][k], max_table[k+1][col], operations, k);

/*  for(int i=0; i<tempor.size(); ++i)
    std::cout << tempor[i] << " ";
  std::cout << std::endl;*/

  long long minimum = tempor[0];
  long long maximum = tempor[0];

  for(int i=1; i< tempor.size(); ++i){
    if(tempor[i]< minimum)
      minimum = tempor[i];
    if(tempor[i]> maximum)
      maximum = tempor[i];
  }

  temp[0] = minimum;
  temp[1] = maximum;
}


long long get_maximum_value(const string &exp) {
  int num_operations = exp.size()/2;
  int num_digits = num_operations + 1;
  vector<vector<long long>> min_table(num_digits, vector<long long>(num_digits));
  vector<vector<long long>> max_table(num_digits, vector<long long>(num_digits));
  vector<int> digits(num_digits);
  string operations[num_operations];
  // get digits and operations from the string
  for (int i=0; i< exp.size(); ++i){
    static int count = 0;
    if (i%2 == 0){
      digits[i/2] = exp[i] - 48;
    }
    else{
      operations[count] = exp[i];
      //std::cout << operations[count] << " ";
      count ++;
    }
  }

  // Fill the diagonal of the tables
  for (int i=0; i<num_digits; ++i){
    min_table[i][i] = (long long)digits[i];
    max_table[i][i] = (long long)digits[i];
  }

  // Now complete the tables (upper part)
  for (int iter=0;iter < num_digits-1; ++iter){
    for (int inner=0; inner < num_digits-1-iter; ++inner){
      int row= inner;
      int col= iter + inner + 1;
      long long minimum = 1e15;
      long long maximum = -1e15;

      for(int k=row; k<col; ++k){
          long long temp[2];
          get_table_entries_k(row, col, digits, k, operations, min_table, max_table, temp);
          if(temp[0] < minimum){
            minimum = temp[0];
          }
          if(temp[1] > maximum){
            maximum = temp[1];
          }
      }

      min_table[row][col] = minimum;
      max_table[row][col] = maximum;
    }
  }

/*
  std::cout << std::endl;
  print_table(min_table, num_digits);
  print_table(max_table, num_digits);
*/
  return max_table[0][num_digits-1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
