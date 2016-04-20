#include <iostream>
#include "net_processor_pool.h"
#include "net_packet.h"
#include "net_processor.h"

using std::cin;
using std::cout;
using std::endl;

class Processor: public Net_processor<int> {
	int m_id;

public:
	Processor(int id): m_id(id) {}

	void process(const int &data)
	{
		std::cout << "processor[" << m_id 
			<< "] get packet " << data << std::endl;
	}

	void free(Net_task_node<int> *task)
	{
		delete task;
	}
};

int main(int argc, char *argv[])
{
	int num_agents = 3;

	Net_task_queue<int> task_queue;

	// 创建处理线程池
	Net_processor_pool<int> processor_pool;
	for (int i = 0; i < num_agents; i++) {
		processor_pool.add_processor(
			boost::make_tuple(&task_queue, new Processor(i)));
	}

	typedef Net_processor_pool<int>::node_type task_type;
	for (int i = 0; i < 100; i++) {
		task_queue.push(new task_type(i));
	}

	cout << "hello world!" << endl;
	int c;
	cin >> c; 
	return 0;
}
