// unique_ptr::operator[]
#include <iostream>
#include <memory>

int main () {
  std::unique_ptr<int[]> foo (new int[5]);

  for (int i=0; i<5; ++i) foo[i] = i;

  for (int i=0; i<5; ++i) std::cout << foo[i] << ' ';
  std::cout << '\n';

  return 0;
}

