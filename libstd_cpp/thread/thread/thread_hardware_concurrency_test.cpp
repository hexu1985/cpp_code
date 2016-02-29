#include <iostream>
#include "thread.h"
 
int main() {
    unsigned int n = Hx::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}

/*
Possible output:

4 concurrent threads are supported.
*/
