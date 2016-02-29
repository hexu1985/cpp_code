#include "queue.h"        // Dlist_queue
#include <iostream>       // std::cout
#include <boost/thread.hpp>

// 从队列里提取num个节点
void do_pop(Dlist_queue<int> &queue, int num)
{
	std::cout << "start do_pop ok!" << std::endl;

	if (queue.empty()) {
		std::cout << "queue is empty" << std::endl;
	}

	Dlist_queue<int>::node_type *node;
	for (int i = 0; i < num; i++) {
		while ((node = queue.try_pop()) == NULL) {
			std::cout << "queue.try_pop(): no data" << std::endl;
			boost::this_thread::sleep_for(boost::chrono::seconds(1));
		}
		assert(node->key == i);
		delete node;
	}
	std::cout << "push " << num << " nodes OK!" << std::endl;
}

// 往队列里插入num个节点
void do_push(Dlist_queue<int> &queue, int num)
{
	std::cout << "start do_push ok!" << std::endl;
	for (int i = 0; i < num; i++) {
		queue.push(new Dlist_queue<int>::node_type(i));
	}
	std::cout << "push " << num << " nodes OK!" << std::endl;
}

int main(int argc, char *argv[])
{
	Dlist_queue<int> queue;
	int num = 100000;

	std::cout << "before start thread" << std::endl;
	boost::thread pop_thread(do_pop, boost::ref(queue), num);

	boost::this_thread::sleep_for(boost::chrono::seconds(3));
	boost::thread push_thread(do_push, boost::ref(queue), num);

	push_thread.join();
	pop_thread.join();
	std::cout << "after join thread" << std::endl;

	return 0;
}

