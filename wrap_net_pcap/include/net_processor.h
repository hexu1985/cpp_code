#ifndef	NET_PROCESSOR_H
#define	NET_PROCESSOR_H

template <typename T>
struct Net_task_node;

// 网络报文处理器
template <typename T>
class Net_processor {
public:
	virtual ~Net_processor() {}

	// 纯虚接口, 处理数据
	virtual void process(const T &data) = 0;

	// 纯虚接口, 释放任务节点
	virtual void free(Net_task_node<T> *task) = 0;
};

#endif
