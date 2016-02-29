// constructing threads
#include <iostream>       // std::cout
#if __cplusplus >= 201103L
#include <atomic>         // std::atomic
#include <functional>
#else
#include <csignal>
#include <tr1/functional>
#endif
#include "thread.h"         // std::thread
#include <vector>         // std::vector

#if __cplusplus >= 201103L
std::atomic<int> global_counter (0);

void increase_global (int n) { for (int i=0; i<n; ++i) ++global_counter; }

void increase_reference (std::atomic<int>& variable, int n) { for (int i=0; i<n; ++i) ++variable; }

struct C : std::atomic<int> {
  C() : std::atomic<int>(0) {}
  void increase_member (int n) { for (int i=0; i<n; ++i) fetch_add(1); }
};
#else
sig_atomic_t global_counter (0);

void increase_global (int n) { for (int i=0; i<n; ++i) ++global_counter; }

void increase_reference (sig_atomic_t &variable, int n) { for (int i=0; i<n; ++i) ++variable; }

struct C {
  C(): value(0) {}

  void increase_member(int n) { for (int i=0; i<n; ++i) ++value; }

  sig_atomic_t value;
};

std::ostream &operator <<(std::ostream &out, const struct C &c)
{
	out << c.value;
	return out;
}
#endif

int main ()
{
#if __cplusplus >= 201103L
  std::vector<Hx::thread> threads;
#else
  std::vector<Hx::thread *> threads;
#endif

  std::cout << "increase global counter with 10 threads...\n";
  for (int i=1; i<=10; ++i)
#if __cplusplus >= 201103L
    threads.push_back(Hx::thread(increase_global,1000));
#else
    threads.push_back(new Hx::thread(increase_global,1000));
#endif

  std::cout << "increase counter (foo) with 10 threads using reference...\n";
#if __cplusplus >= 201103L
  std::atomic<int> foo;
#else
  sig_atomic_t foo = 0;
#endif
  for (int i=1; i<=10; ++i)
#if __cplusplus >= 201103L
    threads.push_back(Hx::thread(increase_reference,std::ref(foo),1000));
#else
    threads.push_back(new Hx::thread(increase_reference,std::tr1::ref(foo),1000));
#endif

  std::cout << "increase counter (bar) with 10 threads using member...\n";
  C bar;
  for (int i=1; i<=10; ++i)
#if __cplusplus >= 201103L
    threads.push_back(Hx::thread(&C::increase_member,std::ref(bar),1000));
#else
    threads.push_back(new Hx::thread(&C::increase_member,std::tr1::ref(bar),1000));
#endif

  std::cout << "synchronizing all threads...\n";
#if __cplusplus >= 201103L
  for (auto& th : threads) th.join();
#else
  for (size_t i = 0; i < threads.size(); ++i) {
	threads[i]->join();
	delete threads[i];
  }
#endif

  std::cout << "global_counter: " << global_counter << '\n';
  std::cout << "foo: " << foo << '\n';
  std::cout << "bar: " << bar << '\n';

  return 0;
}


/*
Output:

increase global counter using 10 threads...
increase counter (foo) with 10 threads using reference...
increase counter (bar) with 10 threads using member...
synchronizing all threads...
global_counter: 10000
foo: 10000
bar: 10000
*/

