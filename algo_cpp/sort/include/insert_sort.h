#ifndef	HX_INSERT_SORT_H
#define	HX_INSERT_SORT_H

#include <utility>

namespace Hx {

// 插入排序
// A是被排序数组: A[L],...,A[R]
// 在完成排序之后, 它们的值将是有序的, 即有A[L] <= ... <= A[R]
template <typename Array>
void insert_sort(Array &A, const int L, const int R)
{
	// S1.[对i进行循环]: 对于i=L+1,...,R实施步骤S2到S5; 然后终止本算法
	for (int i = L+1; i <= R; i++) {
		// S2.[给j,K赋值]: 置j=i-1, K=A[i](在下列步骤中, 
		// 将通过按j的递减次序比较K和A[j]，来试图把K插入正确的位置)
		auto K = A[i];
		int j = i-1;
		for ( ; j >= L; j--) {
			// S3.[比较K和A[j]]: 如果K>=A[j], 
			// 则转向步骤S5(我们已找到了K所要插入的位置)
			if (K < A[j]) {
				// S4.[移动A[j], j减值]: 置A[j+1]=A[j], 然后i=i-1
				// 如果j>=L, 则返回到步骤S3(如果j=L-1, K是目前找到的最小的值,
				// 所以K属于位置L
				A[j+1] = A[j];
			} else {
				break;
			}
		}
		// S5.[K赋值给A[j+1]]: 置A[j+1]=K
		A[j+1] = K;
	}
}

template <typename Array>
void insert_sort_opt1(Array &A, const int L, const int R)
{
	using std::swap;

	// (i)首先将数组中的最小元素放在第一个位置, 让它作为一个标记
	int min = L;
	for (int i = L+1; i <= R; i++) {
		if (A[i] < A[min])
			min = i;
	}
	if (min != L) {
		swap(A[L], A[min]);
	}

	for (int i = L+2; i <= R; i++) {
		auto K = A[i];
		int j = i-1;
		// (ii) 当正被插入的元素已经就位时, 终止内循环,
		// 由于最左边的元素是最小元素, 所以不需要判断j>=L
		for ( ; K < A[j]; j--) {
			A[j+1] = A[j];
		}
		A[j+1] = K;
	}
}

}	// namespace Hx

#endif
