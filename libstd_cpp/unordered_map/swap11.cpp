// unordered_map::swap
#include <iostream>
#include <string>
#include "unordered_map.h"

int main ()
{
  Hx::unordered_map<std::string,std::string>
     first = {{"Star Wars","G. Lucas"},{"Alien","R. Scott"},{"Terminator","J. Cameron"}},
     second  = {{"Inception","C. Nolan"},{"Donnie Darko","R. Kelly"}};

  first.swap(second);

  std::cout << "first: ";
  for (auto& x: first) std::cout << x.first << " (" << x.second << "), ";
  std::cout << std::endl;

  std::cout << "second: ";
  for (auto& x: second) std::cout << x.first << " (" << x.second << "), ";
  std::cout << std::endl;

  return 0;
} 


/*
Possible output:

first: Inception (C. Nolan), Donnie Darko (R. Kelly),
second: Alien (R. Scott), Terminator (J. Cameron), Star Wars (G. Lucas),
*/ 


