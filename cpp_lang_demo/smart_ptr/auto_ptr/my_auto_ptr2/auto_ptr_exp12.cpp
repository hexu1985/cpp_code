// unique_ptr::operator[]
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Auto_ptr<int[]> foo (new int[5]);

  for (int i=0; i<5; ++i) foo[i] = i;

  for (int i=0; i<5; ++i) std::cout << foo[i] << ' ';
  std::cout << '\n';

  return 0;
}

