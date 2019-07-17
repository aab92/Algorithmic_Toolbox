#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

//#define DEBUG ;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
	long long sum = 0;

	long long current = 0;
	long long next  = 1;

	for (long long i = 0; i <= to; ++i) {
		if (i >= from) {
			sum += current;
		}

		long long new_current = next;
		next = next + current;
		current = new_current;
	}

	return sum % 10;
}

int getperiod(long long module, vector<int>& modulos){
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

int get_fibonacci_sum_last_superfast(const long long n,const int period, const vector<int>&  modulos){

	long long newn = (n+2) % (long long)period;

	int ans = modulos[newn] - 1;
	if (ans == -1)
          ans = 9;

	return ans;
}

int get_fibonacci_partial_sum_fast(long long from, long long to)
{
	vector<int> modulos;
	int period = getperiod(10, modulos); // module 10 to get last digit.
	int digto = get_fibonacci_sum_last_superfast(to, period, modulos); 
	int digfromprev = get_fibonacci_sum_last_superfast(from-1, period, modulos); 
	int ans;
	if (digto < digfromprev)
	digto += 10;
	ans = digto - digfromprev;
	if (ans == -1)
		ans = 9;
	return ans;
}

void test_solution()
{
	assert (get_fibonacci_partial_sum_naive(10, 10) == get_fibonacci_partial_sum_fast(10, 10));
	for (int i=0; i<100; i++)
	{
		long long from = rand() % 10;
		long long to = rand() % 100;
		assert (get_fibonacci_partial_sum_naive(from, to) == get_fibonacci_partial_sum_fast(from, to));
	}
}

int main() {
	long long from, to;
#ifdef DEBUG
	test_solution();
	std::cout << "Passed Tests, to run normal application comment DEBUG" << std::endl;
	return 0;
#endif
	std::cin >> from >> to;
	//std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';

	std::cout << get_fibonacci_partial_sum_fast(from, to) << std::endl ;
	return 0;
}
