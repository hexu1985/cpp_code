// -*- C++ -*-
// HeXu's
// 2013 Nov

#ifndef HX_BINTREE_IMPL_H
#define HX_BINTREE_IMPL_H

#ifdef __cplusplus
#include <cstddef>
#include <cassert>
#else // ! __cplusplus
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#endif // __cplusplus

#ifdef __cplusplus
namespace Hx {
namespace detail {
#endif // __cplusplus

/**
 * Binary tree node
 */
typedef struct bintree_node_t {
	struct bintree_node_t *parent;
	struct bintree_node_t *left;
	struct bintree_node_t *right;
} bintree_node_t;

/**
 * Binary tree 
 */
typedef struct bintree_t {
	bintree_node_t *root;
} bintree_t;

/**
 * Initialize binary tree's root node
 */
inline
void bintree_init(bintree_t *tree)
{
	tree->root = NULL;
}

/**
 * test if binary tree is empty
 */
inline
bool bintree_is_empty(const bintree_t *tree)
{
	return (tree->root == NULL);
}

/**
 * returns a pointer to the minimum element in the subtree 
 * rooted at this node, which we assume to be non-NIL.
 */
inline
bintree_node_t *bintree_minimum(const bintree_node_t *node)
{
	while (node->left != NULL)
		node = node->left;
	return (bintree_node_t *) node;
}

/**
 * returns a pointer to the maximum element in the subtree 
 * rooted at this node, which we assume to be non-NIL.
 */
inline
bintree_node_t *bintree_maximum(const bintree_node_t *node)
{
	while (node->right != NULL)
		node = node->right;
	return (bintree_node_t *) node;
}

/**
 * returns the successor of this node in a binary tree 
 * if it exists, and NIL if this node has the largest key in the tree.
 */
inline
bintree_node_t *bintree_successor(const bintree_node_t *node)
{
	if (node->right != NULL)
		return bintree_minimum(node->right);

	const bintree_node_t *keep = node->parent;
	while (keep != NULL && node == keep->right) {
		node = keep;
		keep = keep->parent;
	}	
	return (bintree_node_t *) keep;
}

/**
 * returns the predecessor of this node in a binary tree 
 * if it exists, and NIL if this node has the smallest key in the tree.
 */
inline
bintree_node_t *bintree_predecessor(const bintree_node_t *node)
{
	if (node->left != NULL)
		return bintree_maximum(node->left);

	const bintree_node_t *keep = node->parent;
	while (keep != NULL && node == keep->left) {
		node = keep;
		keep = keep->parent;
	}	
	return (bintree_node_t *) keep;
}

/**
 * replaces this subtree as a child of its parent with
 * another subtree.
 *         q         
 *         |        |
 *  node-> B        E <-other
 *       /   \    /   \
 *      A     C  D     F
 *             ||
 *             \/
 *         q          
 *         |        |  
 * other-> E        B <-node
 *       /   \    /   \
 *      D     F  A     C
 *
 */
inline
void bintree_transplant(bintree_t *tree, bintree_node_t *node, 
	bintree_node_t *other)
{
	if (node->parent == NULL) {
		tree->root = other;
	} else if (node == node->parent->left) {
		node->parent->left = other;
	} else {
		node->parent->right = other;
	}

	if (other != NULL) {
		other->parent = node->parent;
	}
}

/**
 * remove this node from binary tree 
 * Case 1)
 *        q             q
 *        |             |
 * node-> A    =====>   B
 *       / \           / \
 *     NIL  B 
 *         / \
 *
 * Case 2)
 *          q             q
 *          |             |
 *   node-> B    =====>   A
 *         / \           / \
 *        A  NIL
 *       / \
 *
 * Case 3)
 *           q                       q
 *           |                       |
 *    node-> B                       C <-keep
 *         /   \       =====>      /   \
 *       /       \               /       \
 *      A         C <-keep      A         D 
 *    /   \     /   \         /   \     /   \
 *            NIL    D
 *                  / \
 *
 * Case 4)
 *         q                   q                      q
 *         |                   |                      |
 *  node-> B            node-> B                      C <-keep
 *       /   \    =====>     /            =====>    /   \
 *     /       \           /        C <-keep      /       \
 *    A         E         A       /   \          A         E
 *  /   \     /   \     /   \   NIL    E       /   \     /   \
 *           C <-keep                /   \              D
 *          / \                     D                  / \
 *        NIL  D                   / \
 *            / \
 */
inline
void bintree_remove(bintree_t *tree, bintree_node_t *node)
{
	if (node->left == NULL) {	// case 1: left substree is NIL
		bintree_transplant(tree, node, node->right);
	} else if (node->right == NULL) {	// case 2: right substree is NIL
		bintree_transplant(tree, node, node->left);
	} else {
		bintree_node_t *keep = bintree_minimum(node->right);
		if (keep->parent != node) { // case 4:
			bintree_transplant(tree, keep, keep->right);
			keep->right = node->right;
			keep->right->parent = keep;
		} 
		bintree_transplant(tree, node, keep); // case 3:
		keep->left = node->left;
		keep->left->parent = keep;
	}
}

/**
 * left rotation on this node
 * assume that its right child is non-NIL 
 *        q                     q
 *        |                     |
 * node-> b                     d <-keep
 *       / \       =====>      / \
 *      a   d <-keep   node-> b   e
 *         / \               / \
 *        c   e             a   c
 */
inline
void bintree_left_rotate(bintree_t *tree, bintree_node_t *node)
{
	assert(node->right != NULL);

	// turn keep's left subtree into node's right subtree
	bintree_node_t *keep = node->right;
	node->right = keep->left;
	if (keep->left != NULL)
		keep->left->parent = node;
	keep->parent = node->parent;	// link node's parent to keep

	if (node->parent == NULL)
		tree->root = keep;
	else if (node == node->parent->left)
		node->parent->left = keep;
	else 
		node->parent->right = keep;

	keep->left = node;	// put node on keep's left
	node->parent = keep;
}

/**
 * right rotation on this node
 * assume that its left child is non-NIL 
 *          q                 q
 *          |                 |
 *   node-> d                 b <-keep
 *         / \               / \
 * keep-> b   e    =====>   a   d <-node
 *       / \                   / \
 *      a   c                 c   e
 */
inline
void bintree_right_rotate(bintree_t *tree, bintree_node_t *node)
{
	assert(node->left != NULL);

	// turn keep's right subtree into node's left subtree
	bintree_node_t *keep = node->left;
	node->left = keep->right;
	if (keep->right != NULL)
		keep->right->parent = node;
	keep->parent = node->parent;	// link node's parent to y

	if (node->parent == NULL)
		tree->root = keep;
	else if (node == node->parent->left)
		node->parent->left = keep;
	else
		node->parent->right = keep;

	keep->right = node;	// put node on keep's left
	node->parent = keep;
}

inline
void bintree_count(const bintree_node_t *node, size_t *result)
{
	if (node == NULL) {
		return;
	}
	
	*result += 1;
	if (node->left != NULL)
		bintree_count(node->left, result);	
	if (node->right != NULL)
		bintree_count(node->right, result);
}

inline
size_t bintree_size(const bintree_t *tree)
{
	size_t count = 0;
	bintree_count(tree->root, &count);
	return count;
}

#ifdef __cplusplus
/**
 * search node from this subtree
 */
template <typename T, typename BinaryPredicate, typename UnaryFunction>
bintree_node_t *bintree_search(bintree_node_t *node, 
	const T &key, BinaryPredicate less, UnaryFunction get_key)
{
	while (node != NULL) {
		if (less(key, get_key(node))) {	// key < node->key
			node = node->left;
		} else if (less(get_key(node), key)) {	// node->key < key
			node = node->right;
		} else {
			break;
		}
	}
	return node;
}

/**
 * search node from this subtree
 */
template <typename T, typename BinaryPredicate, typename UnaryFunction>
bintree_node_t *bintree_search(bintree_node_t *node, 
	const T &key, BinaryPredicate less, UnaryFunction get_key, 
	bintree_node_t **hint)
{
	// if nofound, hold node's insert hint
	bintree_node_t *keep = NULL;	
	while (node != NULL) {
		keep = node;
		if (less(key, get_key(node))) {	// key < node->key
			node = node->left;
		} else if (less(get_key(node), key)) {	// node->key < key
			node = node->right;
		} else {
			break;
		}
	}
	if (node == NULL && hint != NULL)
		*hint = keep;
	return node;
}

/**
 * insert node into this substree
 */
template <typename BinaryPredicate, typename UnaryFunction>
void bintree_insert(bintree_t *tree, bintree_node_t *node, 
	BinaryPredicate less, UnaryFunction get_key, bintree_node_t *hint = NULL)
{
	bintree_node_t *keep = NULL;
	bintree_node_t *pos = (hint == NULL) ? tree->root : hint;

	while (pos != NULL) {
		keep = pos;
		if (less(get_key(node), get_key(pos))) {
			pos = pos->left;
		} else {
			pos = pos->right;
		}
	}
	node->parent = keep;
	if (keep == NULL) {		// tree was empty
		tree->root = node;
	} else if (less(get_key(node), get_key(keep))) {
		keep->left = node;
	} else {
		keep->right = node;
	}
	node->left = NULL;
	node->right = NULL;
}

/**
 * preorder walk tree begin with node
 */
template <typename UnaryOperation>
void bintree_preorder_walk(bintree_node_t *node, UnaryOperation op)
{
	if (node == NULL)
		return;

	// travel root node
	op(node);

	// travel left subtree
	if (node->left != NULL)
		bintree_preorder_walk<UnaryOperation>(node->left, op);

	// trvel right subtree
	if (node->right != NULL)
		bintree_preorder_walk<UnaryOperation>(node->right, op);
}

template <typename UnaryOperation, typename Stack>
void bintree_preorder_walk(bintree_node_t *node, UnaryOperation op, 
	Stack &stack)
{
	if (node == NULL)
		return;

	assert(stack.empty());
	stack.push(node);
	while (!stack.empty()) {
		op(node = stack.top()); stack.pop();
		if (node->right != NULL) {
			stack.push(node->right);
		}
		if (node->left != NULL) {
			stack.push(node->left);
		}
	}
}

/**
 * inorder walk tree begin with node
 */
template <typename UnaryOperation>
void bintree_inorder_walk(bintree_node_t *node, UnaryOperation op)
{
	if (node == NULL)
		return;

	// travel left subtree
	if (node->left != NULL)
		bintree_inorder_walk<UnaryOperation>(node->left, op);

	// travel root node
	op(node);

	// travel right subtree
	if (node->right != NULL)
		bintree_inorder_walk<UnaryOperation>(node->right, op);
}

template <typename UnaryOperation, typename Stack>
void bintree_inorder_walk(bintree_node_t *node, UnaryOperation op, Stack &stack)
{
	assert(stack.empty());
	while (!stack.empty() || node != NULL) {
		while (node != NULL) {
			stack.push(node);
			node = node->left;
		}
		op(node = stack.top()); stack.pop();
		if (node->right != NULL) {
			stack.push(node->right);
			node = node->right;
		} else {
			node = NULL;
		}
	}
}

/**
 * postorder walk tree begin with node
 */
template <typename UnaryOperation>
void bintree_postorder_walk(bintree_node_t *node, UnaryOperation op)
{
	if (node == NULL)
		return;

	// travel left subtree
	if (node->left != NULL)
		bintree_postorder_walk<UnaryOperation>(node->left, op);

	// travel right subtree
	if (node->right != NULL)
		bintree_postorder_walk<UnaryOperation>(node->right, op);

	// travel root node
	op(node);
}

template <typename UnaryOperation, typename Stack>
void bintree_postorder_walk(bintree_node_t *node, UnaryOperation op, 
	Stack &stack)
{
	assert(stack.empty());
	bintree_node_t *keep;
	while (!stack.empty() || node != NULL) {
		while (node != NULL) {
			stack.push(node);
			if (node->left != NULL)
				node = node->left;
			else
				node = node->right;
		}
		op(node = stack.top()); stack.pop();
		if (!stack.empty()) {
			bintree_node_t *keep = stack.top();
			if (keep->left == node) {
				node = keep->right;
			} else {
				op(keep); stack.pop();
				node = NULL;
			}
		} else {
			node = NULL;
		} 
	}
}

template <typename UnaryOperation>
bintree_node_t *bintree_clone(const bintree_node_t *node, UnaryOperation clone)
{
	if (node == NULL)
		return NULL;

	// clone root node
	bintree_node_t *new_node = clone(node);

	// clone left subtree
	if (node->left != NULL) {
		new_node->left = bintree_clone<UnaryOperation>(node->left, clone);
		new_node->left->parent = new_node;
	}

	// clone right subtree
	if (node->right != NULL) {
		new_node->right = bintree_clone<UnaryOperation>(node->right, clone);
		new_node->right->parent = new_node;
	}

	return new_node;
}

template <typename UnaryOperation>
void bintree_copy(bintree_t *dst, const bintree_t *src, UnaryOperation clone)
{
	bintree_node_t *node = bintree_clone<UnaryOperation>(src->root, clone);
	dst->root = node;
	if (dst->root != NULL)
		dst->root->parent = NULL;
}

template <typename UnaryOperation>
void bintree_destroy(bintree_t *tree, UnaryOperation destroy)
{
	if (tree->root != NULL)
		bintree_postorder_walk<UnaryOperation>(tree->root, destroy);
	tree->root = NULL;
}
#endif // __cplusplus

#ifdef __cplusplus
} // namespace detail
} // namespace Hx
#endif // __cplusplus

#endif // HX_BINTREE_IMPL_H
