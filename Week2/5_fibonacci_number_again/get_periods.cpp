#include <iostream>
#include <vector>
#include <exception>
#include <fstream>

int main(){
	int periods[999];

	std::ofstream myfile;
	myfile.open ("periods.txt");
	
	for (int modu = 2; modu <= 1000; ++modu){
		const int periodfirst = 0;
		const int periodsecond = 1;
		std::vector<int> modulos;
		int periodnewfirst = 0;
		int periodnewsecond = 0;
		modulos.push_back(periodfirst);
		modulos.push_back(periodsecond);
		int count = 2;
		while (!(periodnewfirst == periodfirst && periodnewsecond == periodsecond))
		{
			modulos.push_back((modulos[count-2] + modulos[count-1]) % modu);
			periodnewfirst = modulos[count-1];
			periodnewsecond = modulos[count];
			count ++;
		}	
		periods[modu-2]=modulos.size()-2;
	
		myfile << periods[modu-2] << ", ";
	}

	myfile.close();
	return 0;
}
