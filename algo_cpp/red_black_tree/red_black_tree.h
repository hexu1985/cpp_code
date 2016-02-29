
#include <stddef.h>

namespace Hx {
namespace red_black {

// 红黑树结点, 包含指向父结点的指针,
// 以及指向左右结点的指针,
// 以及颜色属性
typedef struct tree_node_t {
	struct tree_node_t *left;	// 左子树
	struct tree_node_t *rigth;	// 右子树
	struct tree_node_t *parent;	// 父结点
	enum color { red = 0, black = 1, } color;	// 结点颜色
};

// 红黑树, 满足如下性质的二叉搜索树:
// 每个结点或是红色的, 或是黑色的;
// 根结点是黑色的;
// 每个结点(NIL)是黑色的;
// 如果一个结点是红色的, 则它的两个子结点都是黑色的,
// (任何路径上不存在连续的黑色结点);
// 对每个结点, 从该结点到其所有后代叶结点的简单路径上,
// 均包含相同数目的黑色结点.
typedef struct tree_t {
	struct tree_node_t *root;	// 根结点
	struct tree_node_t *nil;	// 哨兵结点
};

// 初始化nil结点
void tree_init(tree_node_t *nil)
{
	assert(nil);
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->color = tree_t::black;
}

// 初始化红黑树
void tree_init(tree_t *tree)
{
	tree_init(tree->nil);
	tree->root = tree->nil;
}

void tree_init(tree_t *tree, tree_node_t *nil)
{
	tree_init(nil);
	tree->nil = nil;
	tree->root = nil; // 设置根结点
}

// 判断tree是否为空, 
// 如果为空返回true,
// 否则返回false.
bool tree_empty(tree_t *tree)
{
	return (tree->root == tree->nil);
}

// 返回以结点x为根的子树的最小元素的指针,
// 这里假设x不为NIL.
tree_node_t *tree_minimum(tree_node_t *x, tree_node_t *nil)
{
	while (x->left != nil)
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

/**
 * 左旋指定结点x,
 * 前置条件: x的右子树不为空, 且根结点的父结点为nil结点
 *        q                     q
 *        |                     |
 *   x -> b                     d <- y
 *       / \       =====>      / \
 *      a   d <- y       x -> b   e
 *         / \               / \
 *        c   e             a   c
 */
void tree_left_rotate(tree_t *tree, tree_node_t *x)
{
	assert(x->right != tree->nil);
	assert(tree->root == tree->nil);

	// 将y结点的左子树挂接成为x结点的右子树
	tree_node_t *y = x->right;
	x->right = y->left;
	if (y->left != tree->nil)
		y->left->parent = x;

	// 将x的父结点连接到y结点
	y->parent = x->parent;
	if (x->parent == tree->nil)
		tree->root = y;
	else if (x == x->parent->left)	// x为父结点的左子树
		x->parent->left = y;
	else
		x->parent->right = y;

	// 将x结点挂接成为y结点的左子树
	y->left = x;
	x->parent = y;
}

/**
 * 右旋指定结点x,
 * 前置条件: x的左子树不为空, 且根结点的父结点为nil结点
 *          q                 q
 *          |                 |
 *     x -> d                 b <- y
 *         / \               / \
 *   y -> b   e    =====>   a   d <- x
 *       / \                   / \
 *      a   c                 c   e
 */
void tree_right_rotate(tree_t *tree, tree_node_t *x)
{
	assert(x->left != tree->nil);
	assert(tree->root == tree->nil);

	// 将y结点的右子树挂接成为x结点的左子树
	tree_node_t *y = x->left;
	x->left = y->right;
	if (y->right != tree->nil)
		y->right->parent = x;

	// 将x的父结点连接到y结点
	y->parent = x->parent;
	if (x->parent == tree->nil)
		tree->root = y;
	else if (x == x->parent->left)	// x为父结点的左子树
		x->parent->left = y;
	else
		x->parent->right = y;

	// 将x结点挂接成为y结点的右子树
	y->right = x;
	x->parent = y;
}



