// circular_buffer::push_back
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;
  int myint;

  std::cout << "Please enter some integers (enter 0 to end):\n";

  do {
    std::cin >> myint;
    mycircular_buffer.push_back (myint);
  } while (myint);

  std::cout << "mycircular_buffer stores " << int(mycircular_buffer.size()) << " numbers.\n";

  return 0;
}

