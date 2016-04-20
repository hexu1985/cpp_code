#ifndef	NET_TASK_QUEUE_H
#define	NET_TASK_QUEUE_H

#include "net_task_list.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/locks.hpp>

// 双向循环链表实现的队列:
// FIFO,
// 线程安全,
// 无内存管理.
template <typename T>
class Net_task_queue {
private:
	Net_task_list<T> m_list;
	boost::mutex m_mut;
	boost::condition_variable m_cond;

public:
	typedef typename Net_task_list<T>::node_type node_type;

	Net_task_queue() {}

	// 将一个节点置入队列尾
	void push(node_type *new_task)
	{
		boost::lock_guard<boost::mutex> lk(m_mut);
		m_list.insert_tail(new_task);
		m_cond.notify_one();
	}

	// 从队列头移除一个节点, 并返回该节点,
	// 如果队列为空, block
	node_type *pop()
	{
		boost::unique_lock<boost::mutex> lk(m_mut);
		while (m_list.empty()) {
			m_cond.wait(lk);
		}
		return m_list.erase_head();
	}

	// 从队列头移除一个节点, 并返回该节点,
	// 如果队列为空, return NULL
	node_type *try_pop()
	{
		boost::lock_guard<boost::mutex> lk(m_mut);
		if (m_list.empty()) {
			return NULL;
		} else {
			return m_list.erase_head();
		}
	}

	// 测试队列是否为空:
	// 如果队列为空, 返回true, 否则返回false
	bool empty()
	{
		boost::lock_guard<boost::mutex> lk(m_mut);
		return m_list.empty();
	}
};

#endif
