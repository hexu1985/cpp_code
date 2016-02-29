#include <boost/pool/singleton_pool.hpp>  
#include <assert.h>

using namespace boost;  

struct pool_tag{};                                  //仅仅用于标记的空类  
typedef singleton_pool<pool_tag, sizeof(int)> spl;  //内存池定义  

int main()  
{      
	int *p = (int *)spl::malloc();                      //分配一个整数内存块      
	assert(spl::is_from(p));      
	spl::release_memory();                              //释放所有未被分配的内存  
}                                                       //spl的内存直到程序结束才完 
