#ifndef	HX_LOSER_TREE_H
#define	HX_LOSER_TREE_H

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
 * 败者树: 一个完全二叉树, 而且每个非叶子节点都有两个子节点
 * 记录类型为T
 * 记录的比较函数默认为std::less
 * 通过ifstream读取记录
 */
template <typename T, typename Compare = std::less<T>>
class Loser_tree {
private:
	struct Loser_info {
		int index;
		Loser_info(): index(0) {}
	};

	class Sequence_info {
		std::ifstream file_;	// 包含归并序列数据的外部文件
		std::string line_;		// 一行数据的buffer
		T front_;				// 归并序列的队首元素, 即最小元素
		bool empty_;			// 标识归并序列是否已经没有元素
	public:
		Sequence_info(const std::string path): front_(0) {
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
	std::vector<Loser_info> losers_;			// 每个内节点对应一次比赛
	std::vector<Sequence_info *> sequences_;	// 败者树一个叶子节点, 对应一路归并序列
	int ninners_;
	int nleaves_;
	Compare compare_;

public:
	Loser_tree(const std::vector<std::string> &paths,
		Compare compare = Compare()) try: compare_(compare) {
		// 获取归并序列数
		nleaves_ = paths.size();
		ninners_ = nleaves_-1;

		// 初始化所有归并序列
		sequences_.resize(nleaves_+1);
		sequences_[0] = nullptr;
		for (int i = 1; i <= nleaves_; i++) {
			sequences_[i] = new Sequence_info(paths[i-1]);
		}

		// 初始化内节点, 并且算出第一个冠军
		losers_.resize(ninners_+1);
		std::vector<int> winners;	// 记录胜者
		winners.resize(ninners_+1);
		for (int i = ninners_; i >= 1; i--) {
			competition(i, winners);
		}
		set_winner_index(winners[1]);	// 记录最终的冠军
	} catch (...) {
		for (auto p: sequences_) {
			delete p;
		}
	}

	// 根据节点索引获取归并序列的指针
	Sequence_info *sequence(int node_index) {
		assert(node_index > ninners_);
		assert(node_index <= ninners_+nleaves_);
		return sequences_[node_index-ninners_];
	}

	const Sequence_info *sequence(int node_index) const {
		assert(node_index > ninners_);
		assert(node_index <= ninners_+nleaves_);
		return sequences_[node_index-ninners_];
	}

	// 根据节点索引获取Loser_info
	const Loser_info &loser(int node_index) const {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		return losers_[node_index];
	}

	Loser_info &loser(int node_index) {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		return losers_[node_index];
	}

	// losers_[0]记录最后的胜者
	void set_winner_index(int index) {
		losers_[0].index = index;
	}

	// losers_[0]记录最后的胜者
	const int &winner_index() const {
		return losers_[0].index;
	}

	// 判断节点索引是否是叶子节点
	bool is_leaf(int node_index) {
		assert(node_index >= 1);
		assert(node_index <= ninners_+nleaves_);
		return node_index > ninners_;
	}

	// 更新内节点的loser
	void competition(int node_index, std::vector<int> &winners) {
		assert(node_index >= 1);
		assert(node_index <= ninners_);
		int left_index = Complete_binary_tree::left_index(node_index);
		int right_index = Complete_binary_tree::right_index(node_index);

		// 获取左子树的优胜序列
		if (!is_leaf(left_index)) {
			left_index = winners[left_index];
		}
		Sequence_info *left_seq = sequence(left_index);

		// 获取右子树的优胜序列
		if (!is_leaf(right_index)) {
			right_index = winners[right_index];
		}
		Sequence_info *right_seq = sequence(right_index);

		// 更新当先loser的index
		Loser_info &curr_loser = loser(node_index);
		if (left_seq->is_empty()) {
			winners[node_index] = right_index;
			curr_loser.index = left_index;
		} else if (right_seq->is_empty()) {
			winners[node_index] = left_index;
			curr_loser.index = right_index;
		} else {
			bool is_left_win = compare_(left_seq->front(), right_seq->front());
			winners[node_index] = is_left_win ? left_index : right_index;
			curr_loser.index = is_left_win ? right_index : left_index;
		}
	}

	// 当前节点的胜者和父节点的败者比较, 更新父节点的败者索引, 返回新的胜者索引
	int competition(Loser_info &parent_loser, int node_index) {
		assert(is_leaf(node_index));
		Sequence_info *parent_seq = sequence(parent_loser.index);
		Sequence_info *seq = sequence(node_index);
		int winner_index = parent_loser.index;
		if (seq->is_empty()) {	// parent win
			parent_loser.index = node_index;
		} else if (parent_seq->is_empty()) { // parent lose
			winner_index = node_index;
		} else if (compare_(parent_seq->front(), seq->front())) {	// parent win
			parent_loser.index = node_index;
		} else {	// parent lose
			winner_index = node_index;
		}
		return winner_index;
	}

	// 如果归并结束, 返回true
	bool is_empty() const {
		return sequence(winner_index())->is_empty();
	}

	// 获取loser的值, 即当前多路归并的最小值
	const T &front() const {
		return sequence(winner_index())->front();
	}

	// 即当前多路归并的最小值, 获取下一个最小值
	void pop_front() {
		int node_index = winner_index();
		sequence(node_index)->pop_front();
		for (int i = Complete_binary_tree::parent_index(node_index);
			i > 1; i = Complete_binary_tree::parent_index(i)) {
			node_index = competition(loser(i), node_index);
		}
		set_winner_index(competition(loser(1), node_index));
	}
};

}	// namespace Hx

#endif	// HX_LOSER_TREE_H
