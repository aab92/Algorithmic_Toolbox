#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {

  size_t first_str_size = str1.size();
  size_t second_str_size = str2.size();
  vector<vector<int>> distance_table(first_str_size +1 ,vector<int>(second_str_size + 1));
  vector<int> prevdist(3);

  // fill table first column
  for(int i=0; i<=first_str_size; ++i)
    distance_table[i][0] = i;
  // fill table first row
  for(int i=0; i<=second_str_size; ++i)
    distance_table[0][i] = i;


  for(int row=1; row <= first_str_size; ++row){
    for(int col=1; col <= second_str_size; ++col){
        int mindis = 200;
        prevdist[0] = distance_table[row][col-1] + 1;
        prevdist[1] = distance_table[row-1][col] + 1;
        int diff = (str1[row-1]==str2[col-1]) ? 0 : 1 ;
        prevdist[2] = distance_table[row-1][col-1] + diff;
        for (int i=0; i<3; i++){
          if (prevdist[i] < mindis)
            mindis = prevdist[i];
        }
        distance_table[row][col] = mindis;
    }
  }

  return distance_table[first_str_size][second_str_size];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;

  return 0;
}
