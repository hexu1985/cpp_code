#include <assert.h>
#include <iostream>
#include "stack.h"

using namespace Hx;
using namespace std;

int main()
{
	Stack<int> stack1(new int[100], 100);

	assert(stack1.empty());
	assert(!stack1.full());
	assert(stack1.size() == 0);
	assert(stack1.max_size() == 100);

	// 测试push
	for (int i = 0; i < 5; ++i)
		stack1.push(i);

	cout << "stack1.size(): " << stack1.size() << endl;
	cout << "stack1.max_size(): " << stack1.max_size() << endl;
	cout << "stack1.peek(): " << stack1.peek() << endl;

	assert(!stack1.empty());
	assert(!stack1.full());
	assert(stack1.size() == 5);
	assert(stack1.peek() == 4);

	// 测试pop
	while (!stack1.empty()) {
		cout << ' ' << stack1.pop();
	}
	cout << endl;

	// 异常测试
	// underflow
	try {
		stack1.pop();
		assert(false);
	} catch (const underflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	try {
		cout << stack1.peek() << endl;
		assert(false);
	} catch (const runtime_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	// overflow
	try {
		int i = 0;
		while (true) {
			stack1.push(++i);
		}
		assert(false);
	} catch (const overflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	cout << "stack1.size(): " << stack1.size() << endl;
	cout << "stack1.max_size(): " << stack1.max_size() << endl;
	cout << "stack1.peek(): " << stack1.peek() << endl;

	cout << "SUCCESS testing \"stack.h\"" << endl;
	return 0;
}
