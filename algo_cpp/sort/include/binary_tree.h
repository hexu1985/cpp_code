
class Binary_tree {

	// 问题: 一棵二叉树, 计算恰好有N个叶子节点时的总结点数?
	// 解答: 设叶子节点个数为m, 则总节点数为2*m-1
	// 依据: 一棵二叉树有N个内部节点, 有N+1个外部节点
	static int total_node(int nleaves) {
		// nleaves > 0 && nleaves <= MAX/2
		assert(nleaves > 0);
		assert(nleaves <= std::numeric_limits<int>::max()>>1);

		return 2*nleaves+1;
	}

};
