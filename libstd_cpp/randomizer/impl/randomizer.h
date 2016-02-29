#ifndef __hx_randomizer_h
#define __hx_randomizer_h

#include <stdlib.h>

namespace Hx {

// 随机数生成器
// 封装srand_r
class Randomizer {
	unsigned int seed_;
public:
	Randomizer(): seed_(::time(0)) {}
	Randomizer(unsigned int x): seed_(x) {}

	// 设置seed
	void srand(unsigned int x) { seed_ = x; }
	void srand() { seed_ = ::time(0); }

	// 获取seed
	int seed() const { return seed_; }

	// 返回一个随机整数x, x属于[0, RAND_MAX]
	int rand() { return ::rand_r(&seed_); }

	// 返回一个随机实数x, x属于[0.0, 1.0)
	double random() { return rand()/(static_cast<double>(RAND_MAX)+1); }

	// 返回一个随机整数x, 范围是a <= x <= b
	int randint(int a, int b)
	{
		// n为[0, b-a]之间的随机整数
		int n = (b-a+1)*random();
		return a+n;
	}

	// 返回一个范围在(start, stop, step)之间的随机整数. 不包括结束值
	int randrange(int start, int stop, int step = 1)
	{
		// n为[0, floor((b-a)/step)]之间的随机整数
		int n = ((stop-start+step-1)/step)*random();
		return start+n*step;
	}

	// 从非空序列seq中返回一个随机元素
	template <typename T>
	const T &choice(const T *seq, int seq_size)
	{
		return seq[randrange(0, seq_size, 1)];
	}

	template <typename Seq>
	typename Seq::const_reference choice(const Seq &seq)
	{
		return seq[randrange(0, seq.size(), 1)];
	}

	// 返回序列长度len, 它包含从序列seq中随机选择的元素.
	// 结果序列中的元素按照选择它们时的顺序排列
	template <typename T>
	T *sample(const T *seq, int seq_size, int len)
	{
		T *dst = new T[len];
		for (int i = 0; i < len; i++) {
			dst[i] = choice(seq, seq_size);
		}
	}

	template <typename Seq>
	Seq sample(const Seq &seq, int len)
	{
		Seq dst;
		for (int i = 0; i < len; i++) {
			dst.push_back(choice(seq));
		}
#if __cplusplus >= 201103L	// c++11 or new than c++11
		return std::move(dst);
#else	// c++98
		return dst;
#endif	// __cplusplus
	}

	// 随机打乱序列seq中的项的顺序
	template <typename T>
	void shuffle(T *seq, int seq_size)
	{
		using std::swap;
		for (int i = seq_size-1; i > 0; i--) {
			swap(seq[i], seq[randint(0, i)]);
		}
	}

	template <typename Seq>
	void shuffle(Seq &seq)
	{
		using std::swap;
		for (int i = static_cast<int>(seq.size())-1; i > 0; i--) {
			swap(seq[i], seq[randint(0, i)]);
		}
	}

	template <typename RandomAccessIterator>
	void shuffle(RandomAccessIterator first, RandomAccessIterator last)
	{
		using std::swap;
		for (int i = static_cast<int>((last-first))-1; i > 0; i--) {
			swap(first[i], first[randint(0, i)]);
		}
	}
};

}	// namespace Hx

#endif
