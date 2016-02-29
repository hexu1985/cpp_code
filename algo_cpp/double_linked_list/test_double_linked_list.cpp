#include "test_double_linked_list.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

using namespace std;

void printList(const std::string title, const List<int> &l)
{
	cout << title;
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void test_list_int()
{
	cout << "-------------" << __func__ << "-------------" << endl;
	List<int> list1, list2;

	assert(list1.empty() == true);
	assert(list2.empty() == true);

	// 测试push
	for (int i = 1; i <= 6; i++) {
		list1.push_front(i);
		list2.push_back(i);
	}
	printList("list1: ", list1);
	printList("list2: ", list2);

	assert(list1.size() == 6);
	assert(list1.front() == 6);
	assert(list1.back() == 1);
	assert(list1.empty() == false);

	assert(list2.size() == 6);
	assert(list2.front() == 1);
	assert(list2.back() == 6);
	assert(list2.empty() == false);

	// 测试pop
	for (int i = 1; i <= 6; i++) {
		list1.pop_front();
		list2.pop_back();
	}
	printList("list1: ", list1);
	printList("list2: ", list2);

	assert(list1.empty() == true);
	assert(list1.size() == 0);

	assert(list2.empty() == true);
	assert(list1.size() == 0);

	// 测试splice
	for (int i = 1; i <= 6; i++) {
		list1.push_front(i);
		list2.push_back(i);
	}
	printList("list1: ", list1);
	printList("list2: ", list2);

	cout << "list1.splice(list1.end(), list2)\n";
	list1.splice(list1.end(), list2);
	printList("list1: ", list1);
	printList("list2: ", list2);

	// 测试find
	List<int>::iterator iter = list1.find(5);
	if (iter == list1.end()) {
		cout << "5 is not in list1" << endl;
	} else {
		cout << "5 is in list1" << endl;
	}
	assert(iter != list1.end());
	assert(*iter == 5);

	// 测试erase
	printList("before erase, list1: ", list1);
	list1.erase(iter);	
	printList("after erase, list1: ", list1);

	// 测试nofound
	iter = list1.find(1024);
	assert(iter == list1.end());
	if (iter == list1.end()) {
		cout << "1024 is not in list1" << endl;
	} else {
		cout << "1024 is in list1" << endl;
	}

	// 测试swap
	cout << "before swap\n";
	printList("list1: ", list1);
	printList("list2: ", list2);
	list1.swap(list2);
	cout << "after swap\n";
	printList("list1: ", list1);
	printList("list2: ", list2);

	assert(list1.empty());
	assert(!list2.empty());

	// 测试clear
	cout << "clear list1, list2\n";
	list1.clear();
	list2.clear();
	printList("list1: ", list1);
	printList("list2: ", list2);

	assert(list1.empty());
	assert(list2.empty());

	// 测试insert和reverse
	for (int i = 1; i < 6; i++) {
		list1.insert(list1.end(), i);
	}
	printList("before reverse, list1: ", list1);

	list1.reverse();
	printList("after reverse list1: ", list1);

	List<int> empty_list;
	// 测试异常
	try {
		empty_list.front();
		assert(false);
	} catch (const runtime_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	try {
		empty_list.pop_front();
		assert(false);
	} catch (const underflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	try {
		empty_list.back();
		assert(false);
	} catch (const runtime_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	try {
		empty_list.pop_back();
		assert(false);
	} catch (const underflow_error &e) {
		assert(true);
		cout << e.what() << endl;
	}

	cout << "-------------" << __func__ << "-------------" << endl;
}

int main()
{
	test_list_int();
	cout << "SUCCESS testing \"double_linked_list.h\"" << endl;
	return 0;
}
