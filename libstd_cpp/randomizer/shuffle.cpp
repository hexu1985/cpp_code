// shuffle algorithm example
#include <iostream>
#include <ctime>
#include <vector>
#include "randomizer.h"

using namespace Hx;

int main () {
  int foo[] = {1, 2, 3, 4, 5};

  // obtain a time-based seed:
  unsigned seed = (unsigned) time(0);
  Randomizer random(seed);

  random.shuffle(foo, 5);

  std::cout << "shuffled elements:";
  for (int i = 0; i < 5; i++) std::cout << ' ' << foo[i];
  std::cout << '\n';

  for (int i = 0; i < 5; i++) foo[i] = i+1;
  random.srand(seed);
  random.shuffle(foo, foo+5);
  std::cout << "shuffled elements:";
  for (int i = 0; i < 5; i++) std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::vector<int> foo2;
  for (int i = 0; i < 5; i++) foo2.push_back(i+1);
  random.srand(seed);
  random.shuffle(foo2);
  std::cout << "shuffled elements:";
  for (int i = 0; i < 5; i++) std::cout << ' ' << foo2[i];
  std::cout << '\n';

  return 0;
}

/*
Possible output:

shuffled elements: 3 1 4 2 5
shuffled elements: 3 1 4 2 5
shuffled elements: 3 1 4 2 5
*/

