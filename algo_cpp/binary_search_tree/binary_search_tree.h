// -*- C++ -*-
// HeXu's
// 2013 Nov

#ifndef __binary_search_tree_h
#define __binary_search_tree_h

#include <stddef.h>

namespace Hx {
namespace binary_search {

// 二叉搜索树结点, 包含指向父结点的指针,
// 以及指向左右结点的指针.
typedef struct tree_node_t {
	struct tree_node_t *left;	// 左子树
	struct tree_node_t *right;	// 右子树
	struct tree_node_t *parent;	// 父结点
} tree_node_t;

// 二叉搜索树:
// 首先满足二叉树的性质,
// 如果x是二叉树中的一个结点, 
// y是x的左子树中的一个结点, 那么y.key <= x.key,
// y是x的右子树中的一个结点, 那么y.key >= x.key.
typedef struct tree_t {
	struct tree_node_t *root;	// 根结点
} tree_t;

// 初始化二叉搜索树
void tree_init(tree_t *tree);

// 判断tree是否为空, 
// 如果为空返回true,
// 否则返回false.
bool tree_empty(tree_t *tree);

// 返回以结点x为根的子树的最小元素的指针,
// 这里假设x不为NIL.
tree_node_t *tree_minimum(tree_node_t *x);

// 返回以结点x为根的子树的最大元素的指针,
// 这里假设x不为NIL.
tree_node_t *tree_maximum(tree_node_t *x);

// 返回结点x的后继,
// 如果x是这棵树中的最大关键字, 返回NIL.
tree_node_t *tree_successor(tree_node_t *x);

// 返回结点x的前驱,
// 如果x是这棵树中的最大关键字, 返回NIL.
tree_node_t *tree_predecessor(tree_node_t *x);

// 移动子树, 
// 用一棵以v为根的子树来替换一棵以u为根的子树,
// 结点u的父结点变成结点v的父结点,
// 最后v成为u的父结点的相应孩子.
void tree_transplant(tree_t *tree, tree_node_t *u, tree_node_t *v);

// 从tree上删除结点z
void tree_remove(tree_t *tree, tree_node_t *z);

// 获取以结点x为根的子树中结点的个数
size_t tree_size(const tree_node_t *x);

// 获取二叉搜索树中结点的个数
size_t tree_size(const tree_t *tree);

// 交换两个二叉搜索树,
// 保持结点间原有的顺序
void tree_swap(tree_t *x, tree_t *y);

}	// namespace binary_serch
}	// namespace Hx

#endif // __binary_search_tree_h
