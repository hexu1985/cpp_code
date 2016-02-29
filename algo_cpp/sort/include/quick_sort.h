#ifndef	HX_QUICK_SORT_H
#define	HX_QUICK_SORT_H

#include "partition.h"

namespace Hx {

// 快速排序
// A是被排序数组: A[L],...,A[R]
// 在完成排序之后, 它们的值将是有序的, 即有A[L] <= ... <= A[R]
template <typename Array>
void quick_sort(Array &A, const int L, const int R)
{
	if (L >= R) return;

	// 数组A[L], ..., A[R]被划分为两个(可能为空)子数组A[L], ..., A[i-1]
	// 和A[i+1], ..., A[R], 使得A[L], ..., A[i-1]中的每一个元素都小于等于A[i],
	// 而A[i+1], ..., A[R]中的每一个元素都大于等于A[i].
	int i = partition(A, L, R);
	quick_sort(A, L, i-1);
	quick_sort(A, i+1, R);
}

template <typename Array>
void quick_sort_opt1(Array &A, const int L, const int R)
{
	if (L >= R) return;

	// 数组A[L], ..., A[R]被划分为两个(可能为空)子数组A[L], ..., A[i-1]
	// 和A[i+1], ..., A[R], 使得A[L], ..., A[i-1]中的每一个元素都小于等于A[i],
	// 而A[i+1], ..., A[R]中的每一个元素都大于等于A[i].
	int i = partition_opt1(A, L, R);
	quick_sort_opt1(A, L, i-1);
	quick_sort_opt1(A, i+1, R);
}

template <typename Array>
void quick_sort_hoare(Array &A, const int L, const int R)
{
	if (L >= R) return;

	// 数组A[L], ..., A[R]被划分为两个(可能为空)子数组A[L], ..., A[i-1]
	// 和A[i+1], ..., A[R], 使得A[L], ..., A[i-1]中的每一个元素都小于等于A[i],
	// 而A[i+1], ..., A[R]中的每一个元素都大于等于A[i].
	int i = hoare_partition(A, L, R);
	quick_sort_hoare(A, L, i);
	quick_sort_hoare(A, i+1, R);
}

}	// namespace Hx

#endif
