// unique_ptr constructor example
#include <iostream>
#include "my_auto_ptr.h"

int main () {
  Default_delete<int> d;
  Auto_ptr<int> u1;
  Auto_ptr<int> u2 (0);
  Auto_ptr<int> u3 (new int);
  Auto_ptr<int> u4 (new int, d);
  Auto_ptr<int> u5 (new int, Default_delete<int>());

  std::cout << "u1: " << (u1?"not null":"null") << '\n';
  std::cout << "u2: " << (u2?"not null":"null") << '\n';
  std::cout << "u3: " << (u3?"not null":"null") << '\n';
  std::cout << "u4: " << (u4?"not null":"null") << '\n';
  std::cout << "u5: " << (u5?"not null":"null") << '\n';

  return 0;
}
