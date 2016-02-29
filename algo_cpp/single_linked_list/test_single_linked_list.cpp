#include <assert.h>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include "test_single_linked_list.h"

using namespace std;

void printList(const std::string title, const List<int> &l)
{
	cout << title;
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

int main()
{
	List<int> list1, list2;

	assert(list1.empty() == true);
	assert(list2.empty() == true);

	// 测试push
	for (int i = 1; i <= 6; i++) {
		list1.push_front(i);
	}
	for (int i = 6; i >= 1; i--) {
		list2.insert_after(list2.before_begin(), i);
	}
	printList("list1: ", list1);
	printList("list2: ", list2);

	assert(list1.size() == 6);
	assert(list1.front() == 6);
	assert(list1.empty() == false);

	assert(list2.size() == 6);
	assert(list2.front() == 1);
	assert(list2.empty() == false);

	// 测试pop
	for (int i = 1; i <= 6; i++) {
		list1.pop_front();
		list2.erase_after(list2.before_begin());
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
	}
	for (int i = 6; i >= 1; i--) {
		list2.insert_after(list2.before_begin(), i);
	}
	printList("list1: ", list1);
	printList("list2: ", list2);

	cout << "list1.splice_after(list1.before_begin(), list2)\n";
	list1.splice_after(list1.before_begin(), list2);
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
	list1.erase_after(iter);	
	printList("after erase, list1: ", list1);

	// 测试remove
	list1.remove(5);
	printList("after remove(5), list1: ", list1);

	// 测试nofound
	iter = list1.find(5);
	assert(iter == list1.end());
	if (iter == list1.end()) {
		cout << "5 is not in list1" << endl;
	} else {
		cout << "5 is in list1" << endl;
	}

	// 测试swap
	list1.swap(list2);
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
		list1.insert_after(list1.before_begin(), i);
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

	cout << "SUCCESS testing \"single_linked_list.h\"" << endl;

	return 0;
}
