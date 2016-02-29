#ifndef	HX_QUICK_SORT_H
#define	HX_QUICK_SORT_H

#include <fstream>
#include <algorithm>
#include <iterator>

#include "multiple_merge.h"

namespace Hx {

namespace outer_sort_detail {

// 从infile中读取split_size个记录, 排序并输出到outpath指定的路径,
// 如果infile已经读到EOF, 则读取的记录数将小于split_size,
// 返回处理的记录数
template <typename T, typename Compare = std::less<T>>
int split_sort(std::ifstream &infile, const std::string &outpath,
	int split_size, Compare compare) {
	// 排序buffer
	std::vector<T> val_arr;
	val_arr.reserve(split_size);

	// 从infile中读取split_size, 并push_back的buffer中, 以排序用
	T val;
	std::string line;
	for (int i = 0; i < split_size; i++) {	
		std::getline(infile, line);
		if (infile.eof()) {
			break;
		}
		std::stringstream is; // 用于将string类型转换成T类型
		is.str(line);
		is >> val;
		val_arr.push_back(val);
	}
	
	if (val_arr.empty()) {
		return 0;
	}

	std::sort(val_arr.begin(), val_arr.end(), compare); // 排序

	// 打开输出文件
	std::ofstream outfile;
	outfile.exceptions(std::ios::failbit | std::ios::badbit);
	outfile.open(outpath);

	// 输出记录
	std::ostream_iterator<T> out_it(outfile, "\n");
	std::copy(val_arr.begin(), val_arr.end(), out_it);
	outfile.close();

	return val_arr.size();
}

inline
void copy_file(const std::string &src_path, const std::string &dst_path)
{
	std::ifstream ifile(src_path);
	if (!ifile) {
		throw std::runtime_error("open file: "+src_path+" error");
	}

	std::ofstream ofile(dst_path);
	if (!ofile) {
		throw std::runtime_error("open file: "+dst_path+" error");
	}

	ofile << ifile.rdbuf();
}

}	// namespace outer_sort_detail

// 以inpath的文件为输入, 外排序输出到outpath文件
// 前提是输入文件中的数据一行一个记录
// 使用Winner_tree归并
template <typename T, typename Compare = std::less<T>>
void outer_sort(const std::string &inpath, const std::string outpath,
	int split_size = 5000,
	Compare compare = Compare()) {

	// 设置文件错误时抛异常, 打开文件
	std::ifstream infile;
	infile.exceptions(std::ios::badbit);
	infile.open(inpath);
	if (!infile) {
		throw std::ios::failure("open file "+inpath+" error");
	}

	// split and sort file
	using outer_sort_detail::split_sort;
	using outer_sort_detail::copy_file;
	int n;
	std::string tmppath;
	std::vector<std::string> tmppaths;
	do {
		tmppath = tmpnam(NULL);
		n = split_sort<T>(infile, tmppath, split_size, compare);
		if (n != 0) {
			tmppaths.push_back(tmppath);
		}
	} while (n == split_size);

	// merge all
	if (tmppaths.size() > 1) {
		multiple_merge<T>(tmppaths, outpath, compare);
	} else if (tmppaths.size() == 1) {
		copy_file(tmppaths[0], outpath);
	} else {
		copy_file(inpath, outpath);
	}
}

// 以paths的文件为输入, 多路归并输出到outpath文件
// 前提是输入文件中的数据一行一个记录
// 使用Loser_tree归并
template <typename T, typename Compare = std::less<T>>
void outer_sort_opt(const std::string &inpath, const std::string outpath,
	int split_size = 5000,
	Compare compare = Compare()) {

	// 设置文件错误时抛异常, 打开文件
	std::ifstream infile;
	infile.exceptions(std::ios::badbit);
	infile.open(inpath);
	if (!infile) {
		throw std::ios::failure("open file "+inpath+" error");
	}

	// split and sort file
	using outer_sort_detail::split_sort;
	using outer_sort_detail::copy_file;
	int n;
	std::string tmppath;
	std::vector<std::string> tmppaths;
	do {
		tmppath = tmpnam(NULL);
		n = split_sort<T>(infile, tmppath, split_size, compare);
		if (n != 0) {
			tmppaths.push_back(tmppath);
		}
	} while (n == split_size);

	// merge all
	if (tmppaths.size() > 1) {
		multiple_merge_opt<T>(tmppaths, outpath, compare);
	} else if (tmppaths.size() == 1) {
		copy_file(tmppaths[0], outpath);
	} else {
		copy_file(inpath, outpath);
	}
}

}	// namespace Hx

#endif	// HX_QUICK_SORT_H
