// constructing threads
#include <iostream>       // std::cout
#include <boost/atomic.hpp>         // boost::atomic
#include <boost/thread.hpp>         // boost::thread
#include <boost/foreach.hpp>
#include <vector>         // std::vector

boost::atomic<int> global_counter (0);

void increase_global (int n) { for (int i=0; i<n; ++i) ++global_counter; }

void increase_reference (boost::atomic<int>& variable, int n) { for (int i=0; i<n; ++i) ++variable; }

struct C : boost::atomic<int> {
  C() : boost::atomic<int>(0) {}
  void increase_member (int n) { for (int i=0; i<n; ++i) fetch_add(1); }
};

int main ()
{
  std::vector<boost::thread *> threads;

  std::cout << "increase global counter with 10 threads...\n";
  for (int i=1; i<=10; ++i)
    threads.push_back(new boost::thread(increase_global,1000));

  std::cout << "increase counter (foo) with 10 threads using reference...\n";
  boost::atomic<int> foo(0);
  for (int i=1; i<=10; ++i)
    threads.push_back(new boost::thread(increase_reference,boost::ref(foo),1000));

  std::cout << "increase counter (bar) with 10 threads using member...\n";
  C bar;
  for (int i=1; i<=10; ++i)
    threads.push_back(new boost::thread(&C::increase_member,boost::ref(bar),1000));

  std::cout << "synchronizing all threads...\n";
  BOOST_FOREACH(boost::thread *th, threads) {
    th->join();
    delete th;
  }

  std::cout << "global_counter: " << global_counter << '\n';
  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';

  return 0;
}

