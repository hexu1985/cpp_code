// -*- C++ -*-
// HeXu's
// 2013 Nov

#include "binary_search_tree.h"
#include <stddef.h>
#include <assert.h>

namespace Hx {
namespace binary_search {

// 初始化二叉搜索树
void tree_init(tree_t *tree)
{
	// 设置根结点
	tree->root = NULL;
}

// 判断tree是否为空, 
// 如果为空返回true,
// 否则返回false.
bool tree_empty(tree_t *tree)
{
	return (tree->root == NULL);
}

// 返回以结点x为根的子树的最小元素的指针,
// 这里假设x不为NIL.
tree_node_t *tree_minimum(tree_node_t *x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}

// 返回以结点x为根的子树的最大元素的指针,
// 这里假设x不为NIL.
tree_node_t *tree_maximum(tree_node_t *x)
{
	while (x->right != NULL)
		x = x->right;
	return x;
}

// 返回结点x的后继,
// 如果x是这棵树中的最大关键字, 返回NIL.
tree_node_t *tree_successor(tree_node_t *x)
{
	if (x->right != NULL)
		return tree_minimum(x->right);

	tree_node_t *y = x->parent;
	while (y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}	
	return y;
}

// 返回结点x的前驱,
// 如果x是这棵树中的最大关键字, 返回NIL.
tree_node_t *tree_predecessor(tree_node_t *x)
{
	if (x->left != NULL)
		return tree_maximum(x->left);

	tree_node_t *y = x->parent;
	while (y != NULL && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

/**
 * 移动子树, 
 * 用一棵以v为根的子树来替换一棵以u为根的子树,
 * 结点u的父结点变成结点v的父结点,
 * 最后v成为u的父结点的相应孩子.
 *         q         
 *         |        |
 *    u -> B        E <- v
 *       /   \    /   \
 *      A     C  D     F
 *
 *             ||
 *             \/
 *         q          
 *         |        |  
 *    v -> E        B <- u
 *       /   \    /   \
 *      D     F  A     C
 *
 */
void tree_transplant(tree_t *tree, tree_node_t *u, tree_node_t *v)
{
	if (u->parent == NULL) {
		tree->root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}

	if (v != NULL) {
		v->parent = u->parent;
	}
}

/**
 * 从tree上删除结点z
 * Case 1)
 *        q             q
 *        |             |
 *   z -> A    =====>   B <- r
 *       / \           / \
 *     NIL  B <- r 
 *         / \
 *
 * Case 2)
 *          q             q
 *          |             |
 *     z -> B    =====>   A <- l
 *         / \           / \
 *   l -> A  NIL
 *       / \
 *
 * Case 3)
 *           q                       q
 *           |                       |
 *      z -> B                       C <- y
 *         /   \       =====>      /   \
 *       /       \               /       \
 * l -> A         C <- y   l -> A         D <- x 
 *    /   \     /   \         /   \     /   \
 *            NIL    D <- x
 *                  / \
 *
 * Case 4)
 *           q                   q                      q
 *           |                   |                      |
 *      z -> B              z -> B                      C <- y
 *         /   \    =====>     /            =====>    /   \
 *       /       \           /        C <- y        /       \
 * l -> A    r -> E    l -> A       /   \          A <- l    E <- r
 *    /   \     /   \     /   \   NIL    E <- r  /   \     /   \
 *             C <- y                  /   \              D <- x
 *            / \                x -> D                  / \
 *          NIL  D                   / \
 *              / \
 */
void tree_remove(tree_t *tree, tree_node_t *z)
{
	if (z->left == NULL) {	// case 1: 结点z没有左子树
		tree_transplant(tree, z, z->right);
	} else if (z->right == NULL) {	// case 2: 结点z没有右子树
		tree_transplant(tree, z, z->left);
	} else {
		tree_node_t *y = tree_minimum(z->right);
		if (y->parent != z) { // case 4:
			tree_transplant(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		} 
		tree_transplant(tree, z, y); // case 3:
		y->left = z->left;
		y->left->parent = y;
	}
}

// 获取以结点x为根的子树中结点的个数
size_t tree_size(tree_node_t *x)
{
	assert(x != NULL);

	int n = 1;
	if (x->left != NULL)
		n += tree_size(x->left);

	if (x->right != NULL)
		n += tree_size(x->right);
	
	return n;
}

// 获取二叉搜索树中结点的个数
size_t tree_size(tree_t *tree)
{
	if (tree_empty(tree))
		return 0;

	return tree_size(tree->root);
}

// 交换两个二叉搜索树,
// 保持结点间原有的顺序
void tree_swap(tree_t *x, tree_t *y)
{
	tree_node_t *tmp = x->root;
	x->root = y->root;
	y->root = tmp;
}

}	// namespace binary_serch
}	// namespace Hx

