// unique_ptr destructor example
#include <iostream>
#include <memory>

int main () {
  auto deleter = [](int*p){
    delete p;
    std::cout << "[deleter called]\n";
  };

  std::unique_ptr<int,decltype(deleter)> foo (new int,deleter);

  std::cout << "foo " << (foo?"is not":"is") << " empty\n";

  return 0;                        // [deleter called]
}
