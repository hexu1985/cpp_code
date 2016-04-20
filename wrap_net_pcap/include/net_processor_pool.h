#ifndef	NET_PROCESSOR_POOL_H
#define	NET_PROCESSOR_POOL_H

#include <vector>
#include <boost/thread.hpp>
#include <boost/tuple/tuple.hpp>
#include "net_processor.h"
#include "net_task_queue.h"

// 网络处理程序线程池
// 该类只管理Net_task_queue, thread资源申请和释放
template <typename T>
class Net_processor_pool {
private:
	typedef boost::tuple<Net_task_queue<T> *, Net_processor<T> *> thread_arg_type;
	typedef boost::shared_ptr<boost::thread> thread_ptr_type;
	std::vector<thread_arg_type>    m_thread_args;   // 线程的输入参数
	std::vector<thread_ptr_type>    m_threads;       // 运行处理程序的线程

public:
	typedef typename Net_task_queue<T>::node_type node_type;
	enum { TASK_QUEUE = 0, PROCESSOR = 1 };

	Net_processor_pool() {}

	~Net_processor_pool() 
	{
		for (int i = 0; i < (int) m_threads.size(); i++) {
			m_threads[i]->interrupt();
		}

		for (int i = 0; i < (int) m_threads.size(); i++) {
			m_threads[i]->join();
		}
	}

	// 增加一个处理程序和相应的管道
	void add_processor(thread_arg_type arg)
	{
		assert(m_thread_args.size() == m_threads.size());
		m_thread_args.push_back(arg);
		int i = m_threads.size();
		m_threads.push_back(thread_ptr_type(
			new boost::thread(&Net_processor_pool::process_rountine, this, i)));
	}

	// 获取通道个数
	int num_processors()
	{
		return m_thread_args.size();
	}

	// 获取所有的processor
	std::vector<thread_arg_type> get_all_processors() const
	{
		return m_thread_args;
	}

	// 将任务放入第i个通道, 下标从0开始
	void push_task(int i, node_type *node)
	{
		boost::get<TASK_QUEUE>(m_thread_args[i])->push(node);
	}

private:
	// 处理线程
	void process_rountine(int i)
	{
		thread_arg_type arg = m_thread_args.at(i);
		Net_task_queue<T> *queue = boost::get<TASK_QUEUE>(arg);
		Net_processor<T> *processor = boost::get<PROCESSOR>(arg);
		while (true) {
			// 获取一个task
			node_type *node = queue->pop();

			// 处理task
			processor->process(node->task);

			// 释放task
			processor->free(node);
		}
	}
};

#endif
