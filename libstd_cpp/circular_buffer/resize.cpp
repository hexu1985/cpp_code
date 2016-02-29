// resizing circular_buffer
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  Hx::circular_buffer<int> mycircular_buffer;
  Hx::circular_buffer<int>::iterator it;

  // set some initial content:
  for (int i=1; i<10; ++i) mycircular_buffer.push_back(i);

  mycircular_buffer.resize(5);
  mycircular_buffer.resize(8,100);
  mycircular_buffer.resize(12);

  std::cout << "mycircular_buffer contains:";
  for (Hx::circular_buffer<int>::iterator it = mycircular_buffer.begin(); it != mycircular_buffer.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}


/*
The code sets a sequence of 9 numbers as the initial content for mycircular_buffer. It then uses resize first to set the container size to 5, then to extend its size to 8 with values of 100 for its new elements, and finally it extends its size to 12 with their default values (for int elements this is zero). Output:

mycircular_buffer contains: 1 2 3 4 5 100 100 100 0 0 0 0
*/
