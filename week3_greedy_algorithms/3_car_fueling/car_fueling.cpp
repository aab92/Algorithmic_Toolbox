#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    if (tank > dist) return 0;

    int num_refill = 0;
    int current_station = 0;
    vector<int> station_refill_index;
    auto iter = stops.begin();
    iter =  stops.insert(iter, 0);
    stops.push_back(dist);

    for (int i=0; i<stops.size(); ++i){
      if(stops[i+1]-stops[i] > tank)
        return -1;
      if(stops[i]-stops[current_station] > tank){
              current_station = i-1;
              num_refill ++;
              station_refill_index.push_back(current_station);
      }
    }

    return num_refill;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
