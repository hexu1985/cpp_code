#ifndef HX_RADIX_SORT_H
#define HX_RADIX_SORT_H

#include "counting_sort.h"

namespace Hx {

template <typename T>
class get_uint8 {
private:
	int n_;

public:
	get_uint8(int n): n_(n) { assert(n >= 0); }

	uint8_t operator() (const T &ui) const
	{
		uint8_t ret = static_cast<uint8_t>(ui >> (n_*8));
		return ret;
	}
};

inline
void radix_sort(unsigned int *arr, int len)
{
	unsigned int *buf = new unsigned int[len];
	unsigned int *src = arr;
	unsigned int *dst = buf;

	for (int i = 0; i < sizeof(unsigned int); i++) {
		counting_sort<unsigned int, get_uint8<unsigned int> >(
			src, dst, len, get_uint8<unsigned int>(i));
		unsigned int *tmp = src;
		src = dst;
		dst = tmp;
	}

	if (dst != arr) {
		for (int i = 0; i < len; i++) {
			arr[i] = dst[i];
		}
	}

	delete [] buf;
}

}	// namespace Hx

#endif
