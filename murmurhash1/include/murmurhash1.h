#pragma once

//-----------------------------------------------------------------------------
// murmurhash1 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
// Other compilers
#else // defined(_MSC_VER)
#include <stdint.h>
#endif // !defined(_MSC_VER)

uint32_t murmurhash1(const void* key, int len, uint32_t seed);
uint32_t murmurhash1_aligned(const void* key, int len, uint32_t seed);
