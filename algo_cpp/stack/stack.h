#ifndef	__stack_h
#define	__stack_h

#include <stddef.h>
#include <stdexcept>

namespace Hx {

// 栈
template <typename T>
struct Stack {
	int top;	// 栈顶下标
	int length;	// 栈大小
	T *buffer;	// 栈实际空间

public:
	Stack(T *p, int n): top(-1), length(n), buffer(p)
	{
		assert(length > 0);
	}

	// 返回当前栈中元素个数
	size_t size() const
	{
		return top+1;
	}

	// 返回栈中最大存放元素个数
	size_t max_size() const
	{
		return length;
	}

	// 判断栈是否为空
	bool empty() const
	{
		return top == -1;
	}

	// 判断栈是否已满
	bool full() const
	{
		return top == length-1;
	}

	// 入栈
	void push(const T &x)
	{
		if (full())
			throw std::overflow_error("push error: stack is full");
		top = top+1;
		buffer[top] = x;
	}

	// 查看栈顶元素
	T &peek() const
	{
		if (empty())
			throw std::runtime_error("peek error: stack is empty");
		return buffer[top];
	}

	// 出栈
	T pop()
	{
		if (empty())
			throw std::underflow_error("pop error: stack is empty");
		top = top-1;
		return buffer[top+1];
	}
};

}	// namespace Hx

#endif	// __stack_h
