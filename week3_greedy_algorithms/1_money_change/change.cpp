#include <iostream>

void sortdenom_naive(int* denom, int size){
	int temarray[size] = {0};

	int indexarr[size] = {0};
	indexarr[0] = -1;
	// Get maximum
	
	for (int ex=0; ex<size; ex++){
		int max = 0;
		for (int i=0; i<size; i++){
			switch (ex){
				case 0:
					if (denom[i] > max){
						max = denom[i];
						indexarr[ex] = i;	
					}
				case 1:
					if ((i != indexarr[ex-1]) && (denom[i] > max)){
						max = denom[i];
						indexarr[ex] = i;
					}
				case 2:	
					if ((i != indexarr[ex-1]) && (i != indexarr[ex-2]) && (denom[i] > max)){
						max = denom[i];
						indexarr[ex] = i;
					}
			}	
		}
		temarray[ex] = max;
	}


	for (int i=0; i<size; i++){
		denom[i] = temarray[i];
		std::cout << denom[i] << " " ;
	}
	std::cout << std::endl;
}


int get_change(int m) {
	int denom[] = {1,5,10};
	int denom_size = 3;
	sortdenom_naive(denom, denom_size);
	int quanti[denom_size] = {0}; 
	int counter=0;
	while ( m > 0)
	{
		quanti[counter] += m/denom[counter];
		m = m%denom[counter];
		counter++;			
	}
	
	return quanti[0] + quanti[1] + quanti[2] ;
}

int main() {
	int m;
	std::cin >> m;
	std::cout << get_change(m) << '\n';
}
