// condition_variable::notify_one
#include <iostream>           // std::cout
#include "thread.h"             // std::thread
#include "mutex.h"              // std::mutex, std::unique_lock
#include "condition_variable.h" // std::condition_variable

Hx::mutex mtx;
Hx::condition_variable cv;

int cargo = 0;     // shared value by producers and consumers

void consumer () {
  Hx::unique_lock<Hx::mutex> lck(mtx);
  while (cargo==0) cv.wait(lck);
  std::cout << cargo << '\n';
  cargo=0;
}

void producer (int id) {
  Hx::unique_lock<Hx::mutex> lck(mtx);
  cargo = id;
  cv.notify_one();
}

int main ()
{
#if __cplusplus >= 201103L
  Hx::thread consumers[10],producers[10];
#else
  Hx::thread *consumers[10], *producers[10];
#endif

  // spawn 10 consumers and 10 producers:
#if __cplusplus >= 201103L
  for (int i=0; i<10; ++i) {
    consumers[i] = Hx::thread(consumer);
    producers[i] = Hx::thread(producer,i+1);
  }
#else
  for (int i=0; i<10; ++i) {
    consumers[i] = new Hx::thread(consumer);
    producers[i] = new Hx::thread(producer,i+1);
  }
#endif

  // join them back:
  for (int i=0; i<10; ++i) {
#if __cplusplus >= 201103L
    producers[i].join();
    consumers[i].join();
#else
    producers[i]->join();
    consumers[i]->join();
    delete producers[i];
    delete consumers[i];
#endif
  }

  return 0;
} 

/*
Possible output (order of consumed cargoes may vary):
 




1
2
3
4
5
6
7
8
9
10
*/ 

