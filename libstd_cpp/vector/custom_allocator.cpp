// custom allocator example
#include <cstddef>
#include <iostream>
#include <memory>
#include "vector.h"

template <class T>
struct custom_allocator {
  typedef T value_type;
  custom_allocator() noexcept {}
  template <class U> custom_allocator (const custom_allocator<U>&) noexcept {}
  T* allocate (std::size_t n) { return static_cast<T*>(::operator new (n*sizeof(T))); }
  void deallocate (T* p, std::size_t n) { ::delete(p); }
};

template <class T, class U>
constexpr bool operator== (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{return true;}

template <class T, class U>
constexpr bool operator!= (const custom_allocator<T>&, const custom_allocator<U>&) noexcept
{return false;}

int main () {
  Hx::vector<int,custom_allocator<int> > foo = {10,20,30};
  for (auto x: foo) std::cout << x << " ";
  std::cout << '\n';
  return 0;
}


/*
Possible output:

10 20 30 
*/
