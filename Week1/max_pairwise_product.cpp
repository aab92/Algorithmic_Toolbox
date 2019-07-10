#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

long long MaxPairwiseProduct(const std::vector<long long>& numbers) {
    long long max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    }

    return max_product;
}

long long MaxPairwiseProductFast(const std::vector<long long>& numbers){
    long long max_product = 0;
    int n = numbers.size();

    int in_max1 = 0;
    long long max2 = 0;
    for (int i = 0; i < n-1; i++)
        if (numbers[in_max1] < numbers[i+1] )
            in_max1 = i+1;
    for (int i = 0; i < n; i++)
        if ( (i != in_max1) && (max2 < numbers[i]) )
            max2 = numbers[i];

    return numbers[in_max1]*max2;
}

int main() {

/* Stress Testing
  while(true){
    int nsamples = rand() % 1000 + 2;
    std::vector<long long> nnumbers(nsamples);
    std::cout << nsamples << std::endl;
    for (int i = 0; i < nsamples; ++i) {
        nnumbers[i] = rand() % 10000;
        std::cout << nnumbers[i] << " " ;
    }
    std::cout << std::endl;

    long long res1 = MaxPairwiseProduct(nnumbers);
    long long res2 = MaxPairwiseProductFast(nnumbers);
    std::cout << res1 << " " << res2 << std::endl;

    if (res1 != res2){
      std::cout << "Wrong answer!" << std::endl;
      break;
    }
}
//  -- / Stress Testing  */
    int n;
    std::cin >> n;
    std::vector<long long> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    //std::cout << MaxPairwiseProduct(numbers) << "\n";
    std::cout << MaxPairwiseProductFast(numbers) << "\n";
    return 0;
}
