#include <iostream>
#include <csignal>
#include "chrono.h"
#include "thread.h"
#include "shared_mutex.h"
#include "mutex.h"

#define READER_COUNT 10
#define WRITER_COUNT 10

sig_atomic_t ready = false;

Hx::shared_mutex rwlock;

void reader(int i)
{
	while (!ready) {             // wait until main() sets ready...
		Hx::this_thread::yield();
	}

	Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1));
	Hx::shared_lock<Hx::shared_mutex> rdlock(rwlock);

	//doing sth...
	for (int j = 0; j < 3; j++) {
		std::cout << "reader " << i << " work\n";
		Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1));
	}
}
 
void writer(int i)
{
	while (!ready) {             // wait until main() sets ready...
		Hx::this_thread::yield();
	}
	 
	Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1));
	Hx::unique_lock<Hx::shared_mutex> wrlock(rwlock);

	//doing sth...
	for (int j = 0; j < 3; j++) {
		std::cout << "writer " << i << " work\n";
		Hx::this_thread::sleep_for(Hx::chrono::milliseconds(1));
	}
}
 
int main()
{
	Hx::thread *thr_readers[READER_COUNT];
	Hx::thread *thr_writers[WRITER_COUNT];

	for(int i = 0 ; i< READER_COUNT; i++) {
		thr_readers[i] = new Hx::thread(reader, i+1);
		std::cout << "create reader " << i+1 << "\n";
	}
	for(int i = 0 ; i< WRITER_COUNT; i++) {
		thr_writers[i] = new Hx::thread(writer, i+1);
		std::cout << "create writer " << i+1 << "\n";
	}

	ready = true;               // go!

	for(int i = 0 ; i< READER_COUNT; i++) {
		thr_readers[i]->join();
		delete thr_readers[i];
	}
	for(int i = 0 ; i< WRITER_COUNT; i++) {
		thr_writers[i]->join();
		delete thr_writers[i];
	}

	return 0;
}

