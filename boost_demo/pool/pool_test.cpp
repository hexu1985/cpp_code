#include <boost/pool/pool.hpp>
#include <assert.h>

using namespace boost;

int main()
{
	pool<> pl(sizeof(int));		// 一个可分配int的内存池
	int *p = static_cast<int *>(pl.malloc());	// 必须把void *转换成需要的类型
	assert(pl.is_from(p));

	pl.free(p);		// 释放内存池分配的内存块
	for (int i = 0; i < 100; ++i) {	// 连续分配大量的内存
		pl.ordered_malloc(10);
	}

	return 0;
}

