// circular_buffer::insert
#include <iostream>
#include "circular_buffer.h"

int main ()
{
  int myarray[3] = { 11, 22, 33 };
  Hx::circular_buffer<int> myvec;
  Hx::circular_buffer<int>::iterator it;

  it = myvec.insert ( myvec.begin(), 10 );      // 10
                                                //  ^  <- it
  it = myvec.insert ( it, 2, 20 );              // 20 20 10
                                                //  ^
  it = myvec.insert ( it, myarray, myarray+3 ); // 11 22 33 20 20 10
                                                //  ^
  it = myvec.end();                             //                 ^
#if __cplusplus >= 201103L
  it = myvec.insert ( it, {1,2,3} );            // 11 22 33 20 20 10 1 2 3 
                                                //                   ^
#else
  it = myvec.insert ( it, (int []) {1,2,3} );   // 11 22 33 20 20 10 1 2 3 
                                                //                   ^
#endif

  std::cout << "myvec contains:";
#if __cplusplus >= 201103L
  for (int& x: myvec) std::cout << ' ' << x;
#else
  for (size_t i = 0; i < myvec.size(); ++i) std::cout << ' ' << myvec[i];
#endif
  std::cout << '\n';
  return 0;
}

/*
Output:

myvec contains: 11 22 33 20 20 10 1 2 3 
*/

