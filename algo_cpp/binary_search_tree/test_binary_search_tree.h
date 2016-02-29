#ifndef __test_binary_search_tree_h
#define __test_binary_search_tree_h

#include "binary_search_tree.h"
#include <assert.h>
#include <iterator>

using namespace Hx::binary_search;

template <typename T>
struct Set_node: public tree_node_t {
	T key;

	Set_node() {}
	Set_node(const T &key_): key(key_) {}
};

template <typename T>
struct Set_iterator {
	tree_t *tree;
	tree_node_t *link;

	typedef tree_t tree_type;
	typedef tree_node_t link_type;
	typedef Set_node<T> node_type;
	typedef Set_iterator self_type;
	typedef	std::bidirectional_iterator_tag iterator_category;

	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T *pointer;
	typedef T &reference;

	Set_iterator(): tree(NULL), link(NULL) {}

	explicit Set_iterator(tree_type *tree_, link_type *link_): 
		tree(tree_), link(link_) {}

	T &operator *() const	// 解引用
	{
		return static_cast<node_type *>(link)->key;
	}

	T *operator ->() const
	{
		return &static_cast<node_type *>(link)->key;
	}

	self_type &operator ++()	// ++i
	{
		link = (link ? tree_successor(link) : tree_minimum(tree->root)); 
		return *this;
	}

	self_type operator ++(int)	// i++
	{
		self_type tmp(*this);
		link = (link ? tree_successor(link) : tree_minimum(tree->root)); 
		return tmp;
	}

	self_type &operator --()	// --i
	{
		link = (link ? tree_predecessor(link) : tree_maximum(tree->root));
		return *this;
	}

	self_type operator --(int)	// i--
	{
		self_type tmp(*this);
		link = (link ? tree_predecessor(link) : tree_maximum(tree->root));
		return tmp;
	}

	bool operator ==(const self_type &x)
	{
		return tree == x.tree && link == x.link;
	}

	bool operator !=(const self_type &x)
	{
		return !(*this == x);
	}
};

template <typename T>
class Set: public tree_t {
public:
	typedef tree_node_t link_type;
	typedef Set_node<T> node_type;
	typedef	Set_iterator<T> iterator;
	typedef Set self_type;
	typedef T value_type;

	inline static self_type *remove_const(const self_type *ptr)
	{
		return const_cast<self_type *>(ptr);
	}

	Set() { tree_init(this); }

	~Set()
	{ 
		if (!empty())
			tree_destroy(this);
	}

	bool empty() const { return tree_empty(remove_const(this)); }

	size_t size() const { return tree_size(remove_const(this)); }

	iterator begin() const
	{
		if (empty())
			return iterator(remove_const(this), NULL);
		else
			return iterator(remove_const(this), tree_minimum(this->root));
	}

	iterator end() const
	{
		return iterator(remove_const(this), NULL);
	}

	void clear()
	{
		if (empty())
			return;

		tree_destroy(this);
		tree_init(this);
	}

	std::pair<iterator, bool> insert(const value_type &k)
	{
		std::pair<link_type *, bool> res = tree_insert(this, k);
		return std::make_pair(iterator(this, res.first), res.second);
	}

	iterator find(const T &k) const
	{
		return iterator(remove_const(this), tree_search(this->root, k));
	}

	void erase(iterator x)
	{
		assert(this == x.tree);
		assert(x.link != NULL);
		tree_remove(this, x.link);
	}

	void swap(Set &x)
	{
		tree_swap(this, &x);
	}

private:
	static void tree_destroy(tree_t *tree)
	{
		tree_destroy(tree->root);
	}

	// 后序遍历二叉树, 递归删除树结点
	static void tree_destroy(link_type *link)
	{
		assert(link != NULL);
		// 后序遍历
		if (link->left)
			tree_destroy(link->left);
		if (link->right)
			tree_destroy(link->right);
		delete static_cast<node_type *>(link);
	}

	// 插入一个值为key的结点到树中
	static std::pair<link_type *, bool> tree_insert(
		tree_t *tree, const value_type &k)
	{
		link_type *y = NULL;		// 记录插入结点的父结点
		link_type *x = tree->root;
		while (x != NULL) {
			y = x;
			if (k < static_cast<node_type *>(x)->key)		// 寻找左子树
				x = x->left;
			else if (static_cast<node_type *>(x)->key < k)	// 寻找右子树
				x = x->right;
			else											// 已经存在
				return std::make_pair(x, false);
		}
		node_type *z = new node_type(k);	// 创建一个新节点
		z->parent = y;
		if (y == NULL)		// 树为空
			tree->root = z;
		else if (z->key < static_cast<node_type *>(y)->key)
			y->left = z;
		else
			y->right = z;

		return std::make_pair(z, false);
	}

	static link_type *tree_search(link_type *x, const value_type &k)
	{
		while (x != NULL) { 
			if (k < static_cast<node_type *>(x)->key)
				x = x->left;
			else if ( static_cast<node_type *>(x)->key < k)
				x = x->right;
			else
				break;
		}
		return x;
	}
};

#endif
