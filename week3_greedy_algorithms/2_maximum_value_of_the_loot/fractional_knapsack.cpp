#include <iostream>
#include <vector>

using std::vector;

void sort_value_weight(vector<int>& weights, vector<int>& values, vector<double>& value_weight, vector<int>& indexarr){
  int size = weights.size();
  vector<double> temparray(size);
	indexarr[0] = -1;

  for(int i=0; i<size; i++)
    value_weight[i] = (double)values[i]/weights[i];

  // Get maximum
	for (int ex=0; ex<size; ex++){
		double max = 0.0;
		for (int i=0; i<size; i++){
				bool condition = true;
				for (int looper=1; looper < ex+1; looper++){
					condition = condition && (i != indexarr[ex-looper]);
				}
				if (condition && (value_weight[i] > max)){
						max = value_weight[i];
						indexarr[ex] = i;
				}
		}
		temparray[ex] = max;
	}

  for(int i=0; i<size; i++){
    value_weight[i] = temparray[i];
    //std::cout << value_weight[i] << " " << indexarr[i] << std::endl;
  }
}


double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;
  int size = weights.size();
  vector<int> quant_per_itm(size,0);
  vector<double> value_weight(size); // contains the sorted values per unit of weight
  vector<int> value_weight_index(size, 0); // the indexes for the sorted values per unit of weight
  sort_value_weight(weights, values, value_weight, value_weight_index);

  int count = 0;
  while (capacity > 0){
    int index = value_weight_index[count];
    quant_per_itm[count] += (capacity > weights[index]) ? weights[index] : capacity;
    capacity = capacity - quant_per_itm[count];
    if(quant_per_itm[count] == weights[index])
      count++;
  }

  for (int i=0; i< size; i++)
    value += (double)value_weight[i]*quant_per_itm[i];
  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
