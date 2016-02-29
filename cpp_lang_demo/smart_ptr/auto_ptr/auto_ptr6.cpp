// auto_ptr::operator-> example
#include <iostream>
#include <cstddef>
#include <memory>

int main () {
  typedef std::pair<int*,std::ptrdiff_t> mypair;

  std::auto_ptr<mypair> p (new mypair);

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
