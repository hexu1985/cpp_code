#ifndef	__queue_h
#define	__queue_h

#include <stddef.h>
#include <stdexcept>

namespace Hx {

// 队列
template <typename T>
struct Queue {
	int head;	// 队列首下标索引
	int tail;	// 队列尾下标索引
	int length;	// 队列长度
	T *buffer;	// 队列实际空间

public:
	Queue(T *p, int n): head(0), tail(0), length(n), buffer(p)
	{
		assert(length > 1);
	}
	
	// 返回当前队列中元素个数
	size_t size() const
	{
		if (head <= tail)
			return tail-head;
		else 
			return tail+length-head;
	}

	// 返回队列中最大存放元素个数
	size_t max_size() const
	{
		return length-1;
	}

	// 判断队列是否为空
	bool empty() const
	{
		return head == tail;
	}

	// 判断队列是否已满
	bool full() const
	{
		return (tail+1)%length == head;
	}

	// 入栈
	void enqueue(const T &x)
	{
		if (full())
			throw std::overflow_error("enqueue error: queue is full");
		buffer[tail] = x;
		tail = (tail+1)%length;
	}

	// 查看队首元素
	T &peek() const
	{
		if (empty())
			throw std::runtime_error("peek error: queue is empty");
		return buffer[head];
	}

	// 出队
	T dequeue()
	{
		if (empty())
			throw std::underflow_error("dequeue error: queue is empty");
		T x = buffer[head];
		head = (head+1)%length;
		return x;
	}
};

}	// namespace Hx

#endif	// __stack_h
