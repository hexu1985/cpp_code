#include <boost/pool/object_pool.hpp>
#include <iostream>
#include <stdio.h>
#include <assert.h>

using namespace std;
using namespace boost;

struct Demo_class {	// 一个示范用的类
public:
	int a;
	int b;
	int c;
	
	Demo_class(int x = 1, int y = 2, int z = 3): a(x), b(y), c(z)
	{}
};

int main()
{
	object_pool<Demo_class> pl;		// 对象内存池

	Demo_class *p = pl.malloc();	// 分配一个原始内存块
	printf("malloc p at: %p\n", (void *) p);
	assert(pl.is_from(p));

	// p指向的内存未经过初始化
	assert(p->a != 1 || p->b != 2 || p->c != 3);

	p = pl.construct(7, 8, 9);	// 构造一个对象, 可以传递参数
	printf("construct p at: %p\n", (void *) p);
	assert(p->a == 7);

	object_pool<string> pls;	// 定义一个分配string对象的内存池
	for (int i = 0; i < 10; ++i) {	// 连续分配大量string对象
		string *ps = pls.construct("hello object_pool");
		printf("construct ps at: %p\n", (void *) ps);
		cout << *ps << endl;
	}

	return 0;
}	// 所以创建的对象在这里都被正确析构、释放内存
