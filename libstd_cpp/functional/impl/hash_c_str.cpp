#include <limits.h>
#include <stddef.h>
#include "hash_c_str.h"

/* corrected per comments in notes.txt
 * #define BITS_IN_size_t ((UINT_MAX + 1) / (UCHAR_MAX + 1)) / CHAR_BIT
 */
#define BITS_IN_size_t (sizeof(size_t) * CHAR_BIT)
#define THREE_QUARTERS ((size_t) ((BITS_IN_size_t * 3) / 4))
#define ONE_EIGHTH     ((size_t) (BITS_IN_size_t / 8))
#define HIGH_BITS      (~((~((size_t) 0)) >> ONE_EIGHTH))

size_t hash_c_str(const char *datum)
{
	size_t hash_value, i;

	for (hash_value = 0; *datum; ++datum) {
		hash_value = (hash_value << ONE_EIGHTH) + *datum;
		if ((i = hash_value & HIGH_BITS) != 0) {
			hash_value = (hash_value ^ (i >> THREE_QUARTERS)) & ~HIGH_BITS;
		}
	}

	return (hash_value);
}

