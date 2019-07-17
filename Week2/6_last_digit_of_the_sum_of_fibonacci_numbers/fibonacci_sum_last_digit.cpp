#include <iostream>
#include <vector>

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}


int get_fibonacci_last_digit_fast(long long n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    return current;
}

long long get_fibonacci_mod_superfast(long long n, long long m){

        int period;
	
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
		modulos.push_back((modulos[count-2] + modulos[count-1]) % m);
		periodnewfirst = modulos[count-1];
		periodnewsecond = modulos[count];
		count ++;
	}	
	period = modulos.size()-2;

	long long newn = n % (long long)period;
	
	return modulos[newn];
}

int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_naive(n);
    int lastdig = get_fibonacci_mod_superfast(n+2,10) -1;
    if (lastdig == -1)
      lastdig = 9;
    std::cout << lastdig;
    return 0;
}
