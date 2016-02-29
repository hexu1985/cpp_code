#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "max_heap.h"

// 优先级队列不管理内存
template <typename T>
class Priority_queue {
	Max_heap<T> heap;	// 最大堆
	int buffer_size;	// buffer大小

public:
	// 创建优先级队列
	// buffer为缓存, size为缓存大小
	// buffer[0]废弃不用, heap_size最大值要比size小1
	Priority_queue(T *buffer, int size, int heap_size = 0)
	{
		assert(size > 1 && "buffer_size must larger than 1");	// 至少能存一个元素
		assert(heap_size < size && "heap_size must less than size");
		buffer_size = size;
		heap.build_max_heap(buffer, heap_size);
	}

	// 队列是否为空
	bool empty() const
	{
		return heap.heap_size == 0;
	}

	// 队列是否已满
	bool full() const
	{
		return (heap.heap_size+1) == buffer_size;
	}

	// 返回队列中元素个数
	int size() const
	{
		return heap.heap_size;
	}

	// 返回最大值元素
	const T &top() const
	{
		return heap.heap_maximum();
	}

	// 弹出最大值元素
	void pop()
	{
		if (empty()) {
			assert(0 && "queue is empty, underflow!");
		}
		heap.heap_extract_max();
	}

	// 往队列里插入一个元素
	void push(const T &val)
	{
		if (full()) {
			assert(0 && "queue is full, overflow!");
		}
		heap.max_heap_insert(val);
	}
};

#endif
