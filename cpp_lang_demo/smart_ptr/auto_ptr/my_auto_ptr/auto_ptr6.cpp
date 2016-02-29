// Auto_ptr::operator-> example
#include <iostream>
#include <cstddef>
#include <memory>
#include "my_auto_ptr.h"

int main () {
  typedef std::pair<int*,std::ptrdiff_t> mypair;

  Auto_ptr<mypair> p (new mypair);

  *p = std::get_temporary_buffer<int>(5);

  if (p->second >= 5) {
    for (int i=0; i<5; i++)
      p->first[i]=i*5;

    for (int i=0; i<5; i++)
      std::cout << p->first[i] << " ";

    std::cout << '\n';
  }

  std::return_temporary_buffer (p->first);

  return 0;
}
