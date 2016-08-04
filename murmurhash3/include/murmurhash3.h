#pragma once

#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
// Other compilers
#else // defined(_MSC_VER)
#include <stdint.h>
#endif // !defined(_MSC_VER)

void murmurhash3_32(const void* key, int len, uint32_t seed, void* out);
void murmurhash3_128(const void* key, int len, uint32_t seed, void* out);
