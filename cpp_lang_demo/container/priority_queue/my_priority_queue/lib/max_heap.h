#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <cassert>

/**
 * 最大堆是一个数组, 被看做为一个近似的完全二叉树,
 * 树上的每一个结点对应数组中的一个元素.
 * 除了最底层外, 该树是完全充满的,
 * 而且是从左向右填充.
 * 堆包含两个属性: array_length给出数组元素的个数, 
 * heap_size表示有多少个堆元素存储在该数组中.
 * 注意: 数组下标从[1...array_length]为存放数据元素,
 * 数组下标从[1...heap_size]中存放的是堆的有效数据, 
 * 这么做为了计算parent, left, right方便.
 *
 *                16(1)
 *               /   \
 *             /       \
 *           /           \
 *         14(2)          10(3)
 *        /  \           /  \
 *      /      \       /      \
 *     8(4)     7(5)  9(6)    3(7)
 *   /   \     /  \
 *  2(8) 4(9) 1(10) 
 *
 *  | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|  index
 *  |16|14|10| 8| 7| 9| 3| 2| 4| 1|  array
 */
template <typename T>
struct Max_heap {
	int heap_size;		// 数组中元素个数
	T *array;

	// 给定结点的下标i, 计算父结点的下标
	static int parent(int i) { return i/2; }
	
	// 给定结点的下标i, 计算左子结点的下标
	static int left(int i) { return i*2; }
	
	// 给定结点的下标i, 计算右子结点的下标
	static int right(int i) { return i*2+1; }

	// 维护最大堆性质, 输入时下标i,
	// 在调用max_heapify时, 
	// 我们假定根结点为left(i)和right(i)的二叉树都是最大堆,
	// 这时array[i]有可能小于其孩子, 这样就违背了最大堆的性质.
	// 通过让array[i]的值在最大堆中"逐级下降",
	// 从而使得以下标i为根结点的子树重新遵循最大堆的性质.
	void max_heapify(int i)
	{
		using std::swap;

		int l = left(i);
		int r = right(i);

		// 找到i,left(i),right(i)中最大元素位置
		int largest = i;
		if (l <= heap_size && array[l] > array[largest])
			largest = l;
		if (r <= heap_size && array[r] > array[largest])
			largest = r;

		// 如果最大元素位置不是i, 那么交换元素, 并逐级下降
		if (largest != i) {
			swap(array[i], array[largest]);
			max_heapify(largest);
		}
	}

	// 构建最大堆, 堆元素为array[1...n]
	void build_max_heap(T *buffer, int n)
	{
		array = buffer;
		heap_size = n;
		for (int i = n/2; i >= 1; i--) {
			max_heapify(i);
		}
	}

	// 查找最大元素
	const T &heap_maximum() const
	{
		return array[1];
	}

	// 从最大堆中弹出最大元素, 并维护最大堆性质
	T heap_extract_max()
	{
		if (heap_size < 1) {
			assert(0 && "heap underflow");
		}
		T max = array[1];
		array[1] = array[heap_size];
		heap_size = heap_size - 1;
		max_heapify(1);
		return max;
	}

	// 增加下标i对应元素的值
	void heap_increase_key(int i, const T &key)
	{
		using std::swap;

		assert(i <= heap_size);
		if (key < array[i]) {
			assert(0 && "new key is smaller than current key");
		}
		array[i] = key;
		while (i > 1 && array[parent(i)] < array[i]) {
			swap(array[i], array[parent(i)]);
			i = parent(i);
		}
	}

	// 向最大堆中插入一个新元素
	void max_heap_insert(const T &key)
	{
		heap_size = heap_size + 1;
		array[heap_size] = key;	// 应该是负无穷值, 这里简化了一下
		heap_increase_key(heap_size, key);
	}
};

#endif

