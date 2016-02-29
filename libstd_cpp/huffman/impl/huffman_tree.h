// -*- C++ -*-
// HeXu's
// 2014 Apr

#ifndef HX_HUFFMAN_TREE_H
#define HX_HUFFMAN_TREE_H

#include <cassert>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iostream>

#include <vector>

namespace Hx {

template <typename KeyType, typename WeightType>
struct huffman_node {
	int index;
	int left;
	int right;
	int parent;
	KeyType key;
	WeightType weight;

	huffman_node(): index(-1), left(-1), right(-1), parent(-1), weight(0) {}

	bool is_leaf() const { return left == -1; /* && right == -1 */ }

	void clear() 
	{
		index = left = right = parent = -1; 
		weight = 0;
	}
};

template <typename KeyType, typename WeightType>
class huffman_tree {
public:
	typedef KeyType key_type;
	typedef WeightType weight_type;
	typedef huffman_node<key_type, weight_type> node_type;
	typedef std::vector<bool> code_type;
	typedef std::vector<bool> code_list_type;
	typedef std::deque<node_type> node_list_type;
	typedef std::unordered_map<key_type, int> key_node_map_type;
	typedef std::unordered_map<key_type, code_type> key_code_map_type;

private:
	int root_;
	node_list_type node_list_;
	key_node_map_type key_node_map_;
	key_code_map_type key_code_map_;

	struct link_type {
		node_list_type *node_list;
		int index;

		link_type(): node_list(NULL), index(-1) {}

		link_type(node_list_type &lst, int idx): node_list(&lst), index(idx) {}

		node_type *operator ->() { return &node_list->at(index); }
		node_type &operator *() { return node_list->at(index); }
	};

public:
	huffman_tree(): root_(-1) {}

	huffman_tree(const std::unordered_map<key_type, weight_type> &key_set)
	{
		struct weight_greater {
			bool operator ()(link_type a, link_type b) const 
			{
				return a->weight > b->weight;
			}
		};

		std::priority_queue<link_type, std::vector<link_type>, weight_greater> 
			link_queue;

		typename std::unordered_map<key_type, weight_type>::const_iterator pos, end;
		pos = key_set.begin();
		end = key_set.end();
		node_type node;
		for ( ; pos != end; ++pos) {
			node.clear();
			node.index = node_list_.size();
			node.key = pos->first;
			node.weight = pos->second;
			node_list_.push_back(node);
			key_node_map_[node.key] = node.index;
			link_queue.push(link_type(node_list_, node.index));
		}

		size_t n = key_set.size();
		link_type link;
		for (size_t i = 1; i <= n-1; ++i) {
			// init node index
			node.clear();
			node.index = node_list_.size();

			// link left child node
			link = link_queue.top();
			link_queue.pop();
			node.right = link->index;
			link->parent = node.index;
			node.weight = link->weight;

			assert(!link_queue.empty());

			// link right child node
			link = link_queue.top();
			link_queue.pop();
			node.left = link->index;
			link->parent = node.index;
			node.weight += link->weight;

			node_list_.push_back(node);
			link_queue.push(link_type(node_list_, node.index));
		}

		root_ = link_queue.top().index;
		link_queue.pop();

		assert(root_ == node_list_.size()-1);
		assert(link_queue.empty());
	}

	~huffman_tree() {}

	size_t key_count() const { return key_node_map_.size(); }

	bool empty() const { return (root_ == -1 || node_list_.empty()); }

	void clear()
	{
		root_ = -1;
		node_list_.clear();
		key_node_map_.clear();
		key_code_map_.clear();
	}

	const key_code_map_type &get_key_code_map()
	{
		if (key_code_map_.empty()) {
			typename key_node_map_type::iterator pos, end;
			pos = key_node_map_.begin();
			end = key_node_map_.end();
			code_type code;
			link_type link(node_list_, -1);
			link_type parent(node_list_, -1);
			for ( ; pos != end; ++pos) {
				const key_type &key = pos->first;
				link.index = pos->second;
				code.clear();
				assert(link.index == link->index);
				while (link->index != root_) {
					parent.index = link->parent;
					if (link->index == parent->left) {
						code.push_back(0);
					} else {
						code.push_back(1);
					}
					link.index = parent.index;
				}
				std::reverse(code.begin(), code.end());
				key_code_map_[key] = code;
			}
		}
		return key_code_map_;
	}

	void encode(const key_type *key_list, size_t len, code_list_type &code_list)
	{
		const key_code_map_type &key_code_map = get_key_code_map();
		for (size_t i = 0; i < len; ++i) {
			const code_type &code = key_code_map.at(key_list[i]);
			code_list.insert(code_list.end(), code.begin(), code.end());
		}
	}

	size_t decode(const code_list_type &code_list, std::vector<key_type> &key_list)
	{
		size_t end = code_list.size();
		size_t pos = 0;
		size_t keep;
		link_type link(node_list_, -1);
		while (true) {
			link.index = root_;
			keep = pos;
			while (pos < end && !link->is_leaf()) {
				if (code_list[pos]) {
					link.index = link->right;
				} else {
					link.index = link->left;
				}
				++pos;
			}

			if (link->is_leaf()) {
				key_list.push_back(link->key);
			}

			if (pos == end) {
				break;
			}
		}

		return link->is_leaf() ? end : keep;
	}

	void print(std::ostream &out)
	{
		typename key_code_map_type::const_iterator pos, end;
		const key_code_map_type &key_code_map = get_key_code_map();
		pos = key_code_map.begin();
		end = key_code_map.end();
		for ( ; pos != end; ++pos) {
			out << (int) pos->first << '('
				<< (isalnum(pos->first) ? pos->first : '.') 
				<< "):";
			const code_type &code = pos->second;
			size_t len = code.size();
			for (size_t i = 0; i < len; ++i)
				out << code[i]; 
			out << '\n';
		}
	}

	void write(std::ostream &out, char sep = '|') const
	{
		size_t n = node_list_.size();
		for (size_t i = 0; i < n; ++i) {
			const node_type &node = node_list_[i];
			out << node.index << sep
				<< node.left << sep
				<< node.right << sep
				<< node.parent << sep
				<< (node.is_leaf() ? (int) node.key : -1) << '\n';
		}
	}

	void read(std::istream &in, char sep = '|')
	{
		clear();
		std::string str;
		node_type node;
		int key;
		std::string pattern;
		pattern = std::string("%d")+sep+"%d"+sep+"%d"+sep+"%d"+sep+"%d";
		while (std::getline(in, str)) {
			sscanf(str.c_str(), pattern.c_str(), &node.index, &node.left,
				&node.right, &node.parent, &key);
			if (node.is_leaf()) {
				node.key = key;
				key_node_map_[node.key] = node.index;
			}
			assert(node.index == node_list_.size());
			node_list_.push_back(node);
		}
		root_ = node_list_.size()-1;
		assert(root_ == node_list_.back().index);
	}
};

} // namespace Hx

#endif // HX_HUFFMAN_TREE_H
