#ifndef	HX_MUTLIPLE_MERGE_H
#define	HX_MUTLIPLE_MERGE_H

#include "winner_tree2.h"
#include "loser_tree2.h"

namespace Hx {

// 以paths的文件为输入, 多路归并输出到outpath文件
// 前提是每个输入文件中的数据是有序的
// 使用Winner_tree归并
template <typename T, typename Compare = std::less<T>>
void multiple_merge(const std::vector<std::string> &paths,
	const std::string outpath, Compare compare = Compare()) {
	// 打开输出文件
	std::ofstream file;
	file.exceptions(std::ios::failbit | std::ios::badbit);
	file.open(outpath);

	// 创建胜者树, 并多路归并, 结果写到输出文件
	Winner_tree<T, Compare> tree(paths, compare);
	while (!tree.is_empty()) {
		file << tree.front() << '\n';
		tree.pop_front();
	}
}

// 以paths的文件为输入, 多路归并输出到outpath文件
// 前提是每个输入文件中的数据是有序的
// 使用Loser_tree归并
template <typename T, typename Compare = std::less<T>>
void multiple_merge_opt(const std::vector<std::string> &paths,
	const std::string outpath, Compare compare = Compare()) {
	// 打开输出文件
	std::ofstream file;
	file.exceptions(std::ios::failbit | std::ios::badbit);
	file.open(outpath);

	// 创建败者树, 并多路归并, 结果写到输出文件
	Loser_tree<T, Compare> tree(paths, compare);
	while (!tree.is_empty()) {
		file << tree.front() << '\n';
		tree.pop_front();
	}
}

}	// namespace Hx

#endif	// HX_MUTLIPLE_MERGE_H

