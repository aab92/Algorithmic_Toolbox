#include <iostream>
#include <vector>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int getperiod(long long module, std::vector<int>& modulos){
	int period;	
	const int periodfirst = 0;
	const int periodsecond = 1;
	int periodnewfirst = 0;
	int periodnewsecond = 0;
        modulos.push_back(periodfirst);
	modulos.push_back(periodsecond);
	int count = 2;
	while (!(periodnewfirst == periodfirst && periodnewsecond == periodsecond))
	{
		modulos.push_back((modulos[count-2] + modulos[count-1]) % module);
		periodnewfirst = modulos[count-1];
		periodnewsecond = modulos[count];
		count ++;
	}	
	return period = modulos.size()-2;
}

int get_fibonacci_last_dig(const long long n,const int period, const std::vector<int>&  modulos){
	long long newn = n % (long long)period;
	return modulos[newn];
}

// The sum of the squares of the n Fibonacci numbers is the product of the n and n+1 Fibonacci numbers
int fibonacci_sum_squares_fast (const long long n) {
	std::vector<int> modulos;
	int period = getperiod(10, modulos); // module 10 to get last digit.
	int ans = get_fibonacci_last_dig(n, period, modulos) * get_fibonacci_last_dig(n+1, period, modulos); 
	return ans % 10;
}

int main() {
	long long n = 0;
	std::cin >> n;
	//std::cout << fibonacci_sum_squares_naive(n) << std::endl;
	std::cout << fibonacci_sum_squares_fast(n) << std::endl;
}
