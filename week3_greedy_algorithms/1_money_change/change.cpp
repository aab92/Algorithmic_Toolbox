#include <iostream>

void sortdenom(int* denom, int size){
	int temarray[size] = {10,5,1};

	


	for (int i=0; i<size; i++){
		denom[i] = temarray[i];
		//std::cout << denom[i] << " " ;
	}
	//std::cout << std::endl;
}


int get_change(int m) {
	int denom[] = {1,5,10};
	sortdenom(denom, 3);
	int quanti[3] = {0}; 
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
