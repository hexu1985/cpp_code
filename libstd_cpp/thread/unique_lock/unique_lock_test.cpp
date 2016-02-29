#include <iostream>
#include <vector>
#include "thread.h"
#include "mutex.h"

using namespace Hx;

int counter = 0;
mutex counter_mutex;
#if __cplusplus >= 201103L
std::vector<thread> threads;
#else
std::vector<thread *> threads;
#endif

void worker_task(int id)
{
#if __cplusplus >= 201103L
	[&](int id) {
		unique_lock<mutex> lock(counter_mutex);
		++counter;
		std::cout << id << ", initial counter: " << counter << '\n';
		lock.unlock();
 
		// don't hold the lock while we simulate an expensive operation
		this_thread::sleep_for(Hx::chrono::seconds(1));
 
		lock.lock();
		++counter;
		std::cout << id << ", final counter: " << counter << '\n';
	}(id);
#else
	unique_lock<mutex> lock(counter_mutex);
	++counter;
	std::cout << id << ", initial counter: " << counter << '\n';
	lock.unlock();
 
	// don't hold the lock while we simulate an expensive operation
	this_thread::sleep_for(Hx::chrono::seconds(1));
 
	lock.lock();
	++counter;
	std::cout << id << ", final counter: " << counter << '\n';
#endif
}
 
int main()
{
#if __cplusplus >= 201103L
	for (int i = 0; i < 10; ++i) threads.emplace_back(worker_task, i);
 
	for (auto &thread : threads) 
		thread.join();
#else
	for (int i = 0; i < 10; ++i) 
		threads.push_back(new thread(worker_task, i));
 
	for (std::vector<thread *>::iterator iter = threads.begin();
		iter != threads.end(); ++iter) {
		(*iter)->join();
		delete *iter;
	}
#endif

	return 0;
}

/*
Possible output:

0, initial counter: 1
1, initial counter: 2
2, initial counter: 3
3, initial counter: 4
4, initial counter: 5
5, initial counter: 6
6, initial counter: 7
7, initial counter: 8
8, initial counter: 9
9, initial counter: 10
6, final counter: 11
3, final counter: 12
4, final counter: 13
2, final counter: 14
5, final counter: 15
0, final counter: 16
1, final counter: 17
7, final counter: 18
9, final counter: 19
8, final counter: 20
*/
