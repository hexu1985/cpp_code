#include <iostream>
#include <cstdint>

using namespace std;

int64_t calculate_one(int max_addend)
{
    volatile int64_t sum = 0;
    for (volatile int i = 0; i < max_addend; i++) {
        sum += i;
    }
    return sum;
}

int64_t calculate_loops(int max_addend, int loops)
{
    volatile int64_t sum = 0;
    for (volatile int j = 0; j < loops; j++) {
        for (volatile int i = 0; i < max_addend; i++) {
            sum += i;
        }
    }
    return sum;
}

int64_t calculate_loops_func(int max_addend, int loops)
{
    volatile int64_t sum = 0;
    for (volatile int j = 0; j < loops; j++) {
        sum += calculate_one(max_addend);
    }
    return sum;
} 

int main()
{
	int64_t sum;
	sum = calculate_loops(100000, 10000);
	cout << "sum: " << sum << endl;
	sum = calculate_loops_func(100000, 10000);
	cout << "sum: " << sum << endl;
	return 0;
}
