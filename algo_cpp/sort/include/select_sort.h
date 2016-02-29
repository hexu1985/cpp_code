#ifndef	HX_SELECT_SORT_H
#define	HX_SELECT_SORT_H

#include <utility>

namespace Hx {

// 选择排序
// A是被排序数组: A[L],...,A[R]
// 在完成排序之后, 它们的值将是有序的, 即有A[L] <= ... <= A[R]
template <typename Array>
void select_sort(Array &A, const int L, const int R)
{
	using std::swap;

	// 对于从下标L到R-1的每个i, 用A[i]与A[i],...,A[R]中的最小元素进行交换.
	// 当索引i从左向右遍历时, 其左边的元素在数组中的位置就是其最终位置
	// (而且再不会被比较), 所以, 当j到达右终端时, 数组已经完全排序完毕
	for (int i = L; i <= R-1; i++) {
		int min = i;
		for (int j = i+1; j <= R; j++) {
			if (A[j] < A[min])
				min = j;
		}
		swap(A[i], A[min]);
	}
}

}	// namespace Hx

#endif
