#ifndef	HX_COMPLETE_BINARY_TREE 
#define	HX_COMPLETE_BINARY_TREE 

#include <limits>

namespace Hx {

// 完全二叉树
class Complete_binary_tree {
public:
	// 用数组表示完全二叉树, 数组下标1对应root节点
	// 根据当前节点索引获取父节点索引
	static int parent_index(int this_index) {
		assert(this_index > 1);
		return this_index>>1;	// this_index/2
	}

	// 根据当前节点索引获取左子节点索引
	static int left_index(int this_index) {
		assert(this_index > 0);
		assert(this_index < std::numeric_limits<int>::max()>>1);
		return 2*this_index;
	}

	// 根据当前节点索引获取右子节点索引
	static int right_index(int this_index) {
		assert(this_index > 0);
		assert(this_index < std::numeric_limits<int>::max()>>1);
		return 2*this_index + 1;
	}
};

}	// namespace Hx

#endif	// HX_COMPLETE_BINARY_TREE 
