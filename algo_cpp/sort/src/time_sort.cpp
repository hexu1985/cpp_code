#include <chrono>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

#include "insert_sort.h"
#include "select_sort.h"
#include "bubble_sort.h"
#include "quick_sort.h"
#include "radix_sort.h"

using namespace Hx;
using namespace std::chrono;

void print_vector(const vector<unsigned int> &v, const string &prefix)
{
	if (prefix.empty()) 
		cout << "vector:\n";
	else
		cout << prefix << ":\n";
	int count = 1;
	for (auto i: v) {
		cout << i << ' ';
		if (count++ % 5 == 0)
			cout << '\n';
	}
	cout << endl;
}

template <typename Test>
void time_test(Test test)
{
	auto t1 = high_resolution_clock::now();
	test();
	auto t2 = high_resolution_clock::now();
	cout << "It took " << duration_cast<duration<double>>(t2-t1).count() 
		<< " seconds.\n";
}

// 用法: a.out max-num
// 生成0,1,2,...,max-num-1的vector
// 打乱vector中元素顺序
// 调用sort排序, 并记录用时
int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "usage: " << argv[0] << " max-num\n";
		exit(1);
	}
	
	int max_num = stoi(argv[1]);
	vector<unsigned int> arr;
	arr.reserve(max_num);

	for (int i = 1; i < max_num+1; i++) {
		arr.push_back(i);
	}

	random_shuffle(arr.begin(), arr.end());

#if 0
	cout << "before sort:\n";
	print_vector(arr);
#endif

	vector<unsigned int> clone_arr;

	cout << "---------------------------\n";
	// time std::sort
	clone_arr = arr;
	cout << "std::sort:\n";
	time_test([&clone_arr](){ sort(clone_arr.begin(), clone_arr.end()); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";

#if 0
	// time insert_sort
	clone_arr = arr;
	cout << "insert_sort:\n";
	time_test([&clone_arr]() { insert_sort(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
	
	// time insert_sort_opt1
	clone_arr = arr;
	cout << "insert_sort_opt1:\n";
	time_test([&clone_arr]() { insert_sort_opt1(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
	
	// time insert_sort_opt1
	clone_arr = arr;
	cout << "select_sort:\n";
	time_test([&clone_arr]() { select_sort(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
	
	// time bubble
	clone_arr = arr;
	cout << "bubble_sort:\n";
	time_test([&clone_arr]() { bubble_sort(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
#endif

	// time quick
	clone_arr = arr;
	cout << "quick_sort:\n";
	time_test([&clone_arr]() { quick_sort(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
	
	// time quick
	clone_arr = arr;
	cout << "quick_sort_opt1:\n";
	time_test([&clone_arr]() { quick_sort_opt1(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";
	
	// time quick
	clone_arr = arr;
	cout << "quick_sort_hoare:\n";
	time_test([&clone_arr]() { quick_sort_hoare(clone_arr, 0, clone_arr.size()-1); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";

	// time quick
	clone_arr = arr;
	cout << "radix sort:\n";
	time_test([&clone_arr]() { radix_sort(&clone_arr[0], clone_arr.size()); });
	assert(is_sorted(clone_arr.begin(), clone_arr.end()));
	cout << "---------------------------\n";

#if 0
	print_vector(arr, "arr");
	print_vector(clone_arr, "after sort arr:");
#endif
	return 0;
}
