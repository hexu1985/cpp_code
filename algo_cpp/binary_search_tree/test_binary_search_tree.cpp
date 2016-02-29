#include "test_binary_search_tree.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

using namespace std;

void printSet(const std::string title, const Set<int> &l)
{
	cout << title;
	copy(l.begin(), l.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void test_set_int()
{
	cout << "-------------" << __func__ << "-------------" << endl;
	Set<int> set1, set2;

	assert(set1.empty() == true);
	assert(set2.empty() == true);

	// 测试insert
	for (int i = 1; i <= 6; i++) {
		set1.insert(i);
		set2.insert(7-i);
	}
	printSet("set1: ", set1);
	printSet("set2: ", set2);

	// 测试find
	Set<int>::iterator iter = set1.find(5);
	if (iter == set1.end()) {
		cout << "5 is not in set1" << endl;
	} else {
		cout << "5 is in set1" << endl;
	}
	assert(iter != set1.end());
	assert(*iter == 5);

	// 测试erase
	printSet("before erase, set1: ", set1);
	set1.erase(iter);	
	printSet("after erase, set1: ", set1);

	// 测试nofound
	iter = set1.find(5);
	assert(iter == set1.end());
	if (iter == set1.end()) {
		cout << "5 is not in set1" << endl;
	} else {
		cout << "5 is in set1" << endl;
	}

	// 测试swap
	cout << "before swap\n";
	printSet("set1: ", set1);
	printSet("set2: ", set2);
	set1.swap(set2);
	cout << "after swap\n";
	printSet("set1: ", set1);
	printSet("set2: ", set2);

	// 测试clear
	cout << "clear set1, set2\n";
	set1.clear();
	set2.clear();
	printSet("set1: ", set1);
	printSet("set2: ", set2);

	assert(set1.empty());
	assert(set2.empty());

	cout << "-------------" << __func__ << "-------------" << endl;
}

int main()
{
	test_set_int();

	cout << "SUCCESS testing \"binary_search_tree.h\"" << endl;

	return 0;
}
