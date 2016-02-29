#ifndef	HX_PARTITION_H
#define	HX_PARTITION_H

#include <cassert>
#include <utility>

namespace Hx {

// 数组的划分,
// 将数组A[L], ..., A[R]实现原址重排,
// 选取A[R]为主元(划分元素), 使得主元最终位置将数组划分成两个子数组
// 主元最终位置左边的子数组都小于或等于主元的值 
// 主元最终位置右边的子数组都大于或等于主元的值 
// 返回主元的最终位置的索引
template <typename Array>
int partition(Array &A, const int L, const int R)
{
	using std::swap;

	// 在子数组A[L],...,A[R]上, partition维护了4个区域.
	// [L,i]区间内的所有值都小于或等于K,
	// [i+1, j-1]区间内的所有值都大于或等于K,
	// A[R]=K, [j,r-1]区间中的值可能属于任何一种情况.
	//  L        i                 j                    R
	// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][K]
	//  |  <= K  |  |   >= K    |  |      无限制     |  
	auto K = A[R];
	int i = L-1;
	for (int j = L; j <= R-1; j++) {
		if (A[j] <= K) {
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[R]);
	return i+1;
}

template <typename Array>
int partition_opt1(Array &A, const int L, const int R)
{
	using std::swap;

	assert(L < R);

	// 在子数组A[L],...,A[R]上, partition维护了4个区域.
	// [L,i-1]区间内的所有值都小于或等于K,
	// [j+1, R-1]区间内的所有值都大于或等于K,
	// A[R]=K, [i,j]区间中的值可能属于任何一种情况.
	//  L           i                 j                 R
	// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][K]
	//  |  <= K  |  |      无限制     |  |    >= K   |  
	auto K = A[R];	// 变量K保存了划分元素A[R]的值
	int i = L-1;	// i和j分别是左扫描指针和右扫描指针
	int j = R;
	for ( ; ; ) {	// 划分循环使得i增加j减小, while循环保持一个不变的性质--
		do {		// i左侧没有元素比K大, j右侧没有元素比K小.
			i++;
		} while (A[i] < K);

		do {
			j--;
			if (j == L)		// 测试j==L用来防止划分元素是文件中的最小元素,
				break;		// 如果L等于或是大于R, 这个判断就会有问题
		} while (K < A[j]);

		if (i >= j)		// 测试两指针相遇
			break;
		swap(A[i], A[j]);
	}
	swap(A[i], A[R]);	// 一旦两个指针相遇, 我们就交换A[i]和A[R],
						// 这样i左侧的元素都小于等于K, i右侧的元素都大于等于K,
	return i;			// 划分结束, 返回索引i.
}

template <typename Array>
int hoare_partition(Array &A, const int L, const int R)
{
	using std::swap;

	assert(L < R);

	auto K = A[L];	// 变量K保存了划分元素A[L]的值
	int i = L-1;	// i和j分别是左扫描指针和右扫描指针
	int j = R+1;

	// 在子数组A[L],...,A[R]上, partition维护了3个区域.
	// [L,i-1]区间内的所有值都小于或等于K,
	// [j+1, R]区间内的所有值都大于或等于K,
	// A[R]=K, [i,j]区间中的值可能属于任何一种情况.
	//  L           i                 j                 R
	// [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]
	//  |  <= K  |  |      无限制     |  |    >= K      |  
	while (true) {
		// 第一次do-while结束时, j指向第一个小于或等于K的元素下标
		// 由于A[L]为K, 所以do-while会在j小于L之前就停止
		do {
			j--;
		} while (K < A[j]);	

		// 第一次do-while结束时, i=R
		// 从下次while开始, 循环满足3个区域的条件
		do {
			i++;
		} while (A[i] < K);	

		if (i < j)
			swap(A[i], A[j]);
		else 
			return j;
	}
}

}	// namespace Hx

#endif
