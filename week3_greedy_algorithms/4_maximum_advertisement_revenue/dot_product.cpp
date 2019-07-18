#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

void sort_vector(vector<int>& vectosort){
  int size = vectosort.size();
  vector<int> temparray(size);
	vector<int> indexarr(size);
  indexarr[0] = -1;

  // Get maximum
	for (int ex=0; ex<size; ex++){
		int max = -1e6;
		for (int i=0; i<size; i++){
				bool condition = true;
				for (int looper=1; looper < ex+1; looper++){
					condition = condition && (i != indexarr[ex-looper]);
				}
				if (condition && (vectosort[i] > max)){
						max = vectosort[i];
						indexarr[ex] = i;
				}
		}
		temparray[ex] = max;
	}

  for(int i=0; i<size; i++){
    vectosort[i] = temparray[i];
    //std::cout << vectosort[i] << " " << indexarr[i] << std::endl;
  }
}


long long max_dot_product(vector<int> a, vector<int> b) {

  sort_vector(a);
  sort_vector(b);

  long long result = 0;
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }

  assert((a.size() == b.size()) && (a.size() == n));

  std::cout << max_dot_product(a, b) << std::endl;
}
