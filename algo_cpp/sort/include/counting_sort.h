#ifndef HX_COUNTING_SORT_H
#define HX_COUNTING_SORT_H

namespace Hx {

inline
void counting_sort(const uint8_t *src, uint8_t *dst, const int len)
{
	const int MAX = 256;
	size_t count[MAX] = {0};

	for (int i = 0; i < len; i++) {
		count[src[i]] = count[src[i]]+1;
	}

	for (int i = 1; i < MAX; i++) {
		count[i] = count[i]+count[i-1];
	}

	for (int i = len-1; i >= 0; i--) {
		dst[count[src[i]]-1] = src[i];
		count[src[i]]--;
	}
}

template <typename T, typename GetUint8Func>
void counting_sort(const T *src, T *dst, const int len, GetUint8Func get_uint8)
{
	const int MAX = 256;
	size_t count[MAX] = {0};

	for (int i = 0; i < len; i++) {
		count[get_uint8(src[i])] = count[get_uint8(src[i])]+1;
	}

	for (int i = 1; i < MAX; i++) {
		count[i] = count[i]+count[i-1];
	}

	for (int i = len-1; i >= 0; i--) {
		dst[get_uint8(count[src[i]])-1] = src[i];
		count[get_uint8(src[i])]--;
	}
}

}	// namespace Hx

#endif
