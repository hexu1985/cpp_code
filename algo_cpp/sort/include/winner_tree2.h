#ifndef	HX_WINNER_TREE2_H
#define	HX_WINNER_TREE2_H

#if __cplusplus < 201103L
#error "must be c++11 or new"
#endif

#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <functional>

#include "complete_binary_tree.h"

namespace Hx {

/**
 * 胜者树: 一个完全二叉树, 而且每个非叶子节点都有两个子节点
 * 记录类型为T
 * 记录的比较函数默认为std::less
 * 通过ifstream读取记录
 */
template <typename T, typename Compare = std::less<T>>
class Winner_tree {
private:
	struct Winner_info {
		int index;
		Winner_info(): index(0) {}
	};

	class Sequence_base {
	public:
		virtual ~Sequence_base() {}

		// 获取归并序列的队首元素, 即最小元素
		virtual const T &front() const = 0;

		// 删除当前队首元素, 加载下一个元素
		virtual void pop_front() = 0;

		// 判断当前队列是否为空
		virtual bool is_empty() const = 0;
	};

	class Sequence_file: public Sequence_base {
		std::ifstream file_;	// 包含归并序列数据的外部文件
		std::string line_;		// 一行数据的buffer
		T front_;				// 归并序列的队首元素, 即最小元素
		bool empty_;			// 标识归并序列是否已经没有元素
	public:
		Sequence_file(const std::string path): front_(0) {
			// 设置文件错误时抛异常, 打开文件
			file_.exceptions(std::ios::badbit);
			file_.open(path);
			if (!file_) {
				throw std::ios::failure("open file "+path+" error");
			}

			// 预读一个元素
			std::getline(file_, line_);
			if (file_.eof()) {
				empty_ = true;
			} else {
				std::stringstream is; // 用于将string类型转换成T类型
				is.str(line_);
				is >> front_;

				// 设置empty成员
				empty_ = false;
			}
		}

		~Sequence_file() {}

		// 获取归并序列的队首元素, 即最小元素
		const T &front() const { return front_; }

		// 删除当前队首元素, 加载下一个元素
		void pop_front() {
			if (file_.eof()) {
				empty_ = true;
			} else {
				std::getline(file_, line_);
				if (file_.eof()) {
					empty_ = true;
				} else {
					std::stringstream is; // 用于将string类型转换成T类型
					is.str(line_);
					is >> front_;
				}
			}
		}

		// 判断当前队列是否为空
		bool is_empty() const { return empty_; }
	};
	
	// 所有vector都是从下标1开始有数据
	std::vector<Winner_info> winners_;			// 每个内节点对应一次比赛
	std::vector<Sequence_base *> sequences_;	// 胜者树一个叶子节点, 对应一路归并序列
	int ninners_;
	int nleaves_;
	Compare compare_;

public:
	Winner_tree(const std::vector<std::string> &paths,
		Compare compare = Compare()) try: compare_(compare) {
		// 获取归并序列数
		nleaves_ = paths.size();
		ninners_ = nleaves_-1;

		// 初始化所有归并序列
		sequences_.resize(nleaves_+1);
		sequences_[0] = nullptr;
		for (int i = 1; i <= nleaves_; i++) {
			sequences_[i] = new Sequence_file(paths[i-1]);
		}

		// 初始化内节点, 并且算出第一个冠军
		winners_.resize(ninners_+1);
		for (int i = ninners_; i >= 1; i--) {
			competition(i);
		}
	} catch (...) {
		for (auto p: sequences_) {
			delete p;
		}
	}

	// 根据节点索引获取归并序列的指针
	Sequence_base *sequence(int node_index) {
		assert(node_index > ninners_);
		assert(node_index <= ninners_+nleaves_);
		return sequences_[node_index-ninners_];
	}

	const Sequence_base *sequence(int node_index) const {
		assert(node_index > ninners_);
		assert(node_index <= ninners_+nleaves_);
		return sequences_[node_index-ninners_];
	}

	// 根据节点索引获取Winner_info
	const Winner_info &winner(int node_index) const {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		return winners_[node_index];
	}

	Winner_info &winner(int node_index) {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		return winners_[node_index];
	}

	// 判断节点索引是否是叶子节点
	bool is_leaf(int node_index) {
		assert(node_index >= 1);
		assert(node_index <= ninners_+nleaves_);
		return node_index > ninners_;
	}

	// 更新内节点的winner
	void competition(int node_index) {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		int left_index = Complete_binary_tree::left_index(node_index);
		int right_index = Complete_binary_tree::right_index(node_index);

		// 获取左子树的优胜序列
		if (!is_leaf(left_index)) {
			left_index = winner(left_index).index;
		}
		Sequence_base *left_seq = sequence(left_index);

		// 获取右子树的优胜序列
		if (!is_leaf(right_index)) {
			right_index = winner(right_index).index;
		}
		Sequence_base *right_seq = sequence(right_index);

		// 更新当先winner的index
		Winner_info &curr_winner = winner(node_index);
		if (left_seq->is_empty()) {
			curr_winner.index = right_index;
		} else if (right_seq->is_empty()) {
			curr_winner.index = left_index;
		} else {
			curr_winner.index = 
				compare_(left_seq->front(), right_seq->front()) 
				? left_index : right_index;
		}
	}

	// 如果归并结束, 返回true
	bool is_empty() const {
		return sequence(winner(1).index)->is_empty();
	}

	// 获取winner的值, 即当前多路归并的最小值
	const T &front() const {
		return sequence(winner(1).index)->front();
	}

	// 即当前多路归并的最小值, 获取下一个最小值
	void pop_front() {
		int node_index = winner(1).index;
		sequence(node_index)->pop_front();
		for (int i = Complete_binary_tree::parent_index(node_index);
			i > 1; i = Complete_binary_tree::parent_index(i)) {
			competition(i);
		}
		competition(1);
	}
};

}	// namespace Hx

#endif	// HX_WINNER_TREE_H
