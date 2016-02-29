// swap priority_queues
#include <iostream>       // std::cout
#include <queue>          // std::priority_queue, std::swap(priority_queue)

int main ()
{
  std::priority_queue<int> foo,bar;
  foo.push (15); foo.push(30); foo.push(10);
  bar.push (101); bar.push(202);

  swap(foo,bar);

  std::cout << "size of foo: " << foo.size() << '\n';
  std::cout << "size of bar: " << bar.size() << '\n';

  return 0;
}
