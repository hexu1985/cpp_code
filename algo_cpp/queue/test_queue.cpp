#include <assert.h>
#include <iostream>
#include "queue.h"

using namespace Hx;
using namespace std;

int main()
{
	Queue<int> queue1(new int[100], 100);

	assert(queue1.empty());
	assert(!queue1.full());
	assert(queue1.size() == 0);
	assert(queue1.max_size() == 99);

	// 测试enqueue
	for (int i = 0; i < 5; ++i)
		queue1.enqueue(i);

	cout << "queue1.size(): " << queue1.size() << endl;
	cout << "queue1.max_size(): " << queue1.max_size() << endl;
	cout << "queue1.peek(): " << queue1.peek() << endl;

	assert(!queue1.empty());
	assert(!queue1.full());
	assert(queue1.size() == 5);
	assert(queue1.peek() == 0);

	// 测试dequeue
	while (!queue1.empty()) {
		cout << ' ' << queue1.dequeue();
	}
	cout << endl;

	// 异常测试
	// underflow
	try {
		queue1.dequeue();
		assert(false);
	} catch (const underflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	try {
		cout << queue1.peek() << endl;
		assert(false);
	} catch (const runtime_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	// overflow
	try {
		int i = 0;
		while (true) {
			queue1.enqueue(++i);
		}
		assert(false);
	} catch (const overflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	cout << "queue1.size(): " << queue1.size() << endl;
	cout << "queue1.max_size(): " << queue1.max_size() << endl;
	cout << "queue1.peek(): " << queue1.peek() << endl;

	cout << "SUCCESS testing \"queue.h\"" << endl;
	return 0;
}

