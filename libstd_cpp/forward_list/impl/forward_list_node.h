// -*- C++11 -*-
// Hexu's
// 2014-11-21

#ifndef	HX_FORWARD_LIST_NODE_H
#define	HX_FORWARD_LIST_NODE_H

#include <cassert>

namespace Hx {

// 单向链表node, 以NIL结尾
struct Forward_list_node_base {
	Forward_list_node_base() = default;

	// 成员变量
	typedef Forward_list_node_base node_type;
	node_type *next = nullptr;	// next指针

	// 在this node后面插入一个node 
	void insert_after(node_type *node) noexcept {
		assert(node != nullptr);
		node->next = this->next;
		this->next = node;	
	}

	// 删除this node后面的节点, 并返回指向被删除node的指针
	node_type *remove_after() noexcept {
		auto keep = this->next;
		if (keep != nullptr)
			this->next = keep->next;	
		return keep;
	}

	// 将begin node和end node之间的所有node转移到this node后,
	// 被转移的node不包括begin node, 但是包括end node
	node_type *transfer_after(node_type *begin, node_type *end) noexcept {
		assert(begin != nullptr);
		auto keep = begin->next;
		if (end != nullptr) {
			begin->next = end->next;
			end->next = this->next;
		} else {
			assert(this->next == nullptr);
			begin->next = nullptr;
		}
		this->next = keep;
		return end;
	}

	// 将this node后的所有node的反序排列
	void reverse_after() noexcept {
		auto tail = this->next;
		if (tail == nullptr)
			return;
		while (tail->next != nullptr) {
			this->insert_after(tail->next);
		}
	}
};

template <typename T>
struct Forward_list_node: public Forward_list_node_base {
	Forward_list_node() = default;

	// 成员变量
	alignas(alignof(T)) char storage[sizeof(T)];	// 按T类型对齐的raw data

	// 获取指向raw data指针
	T *value_ptr() noexcept {
		return static_cast<T *>(static_cast<void *>(storage));
	}

	// 获取指向const raw data指针
	const T *value_ptr() const noexcept {
		return static_cast<const T *>(static_cast<const void *>(storage));
	}
};

}	// namespace Hx

#endif
