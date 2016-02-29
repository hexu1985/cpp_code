#ifndef	HX_BUBBLE_SORT_H
#define	HX_BUBBLE_SORT_H

#include <utility>

namespace Hx {

// 冒泡排序
// A是被排序数组: A[L],...,A[R]
// 在完成排序之后, 它们的值将是有序的, 即有A[L] <= ... <= A[R]
template <typename Array>
void bubble_sort(Array &A, const int L, const int R)
{
	using std::swap;

	// 对于L~R-1内的i值, 内部循环(j)通过从右到左遍历元素, 对连续的元素执行
	// 比较--交换操作, 实现A[i], ..., A[R]最小的元素放到A[i]中.
	// 在所有的比较操作中, 最小的元素都要移动, 所以它就像是泡泡那样"冒"到最前端.
	// 随着索引i从左到右, 在i左边的元素都已处在最后的正确位置上.
	for (int i = L; i <= R-1; i++) {
		for (int j = R-1; j >= i; j--) {
			if (A[j+1] < A[j]) {
				swap(A[j+1], A[j]);
			}
		}
	}
}

}	// namespace Hx

#endif
