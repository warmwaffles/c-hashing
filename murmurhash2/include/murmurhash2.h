#pragma once

#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
// Other compilers
#else // defined(_MSC_VER)
#include <stdint.h>
#endif // !defined(_MSC_VER)

uint32_t murmurhash2(const void* key, int len, uint32_t seed);
uint64_t murmurhash64a(const void* key, int len, uint64_t seed);
uint64_t murmurhash64b(const void* key, int len, uint64_t seed);
uint32_t murmurhash2a(const void* key, int len, uint32_t seed);
uint32_t murmurhash_neutral2(const void* key, int len, uint32_t seed);
uint32_t murmurhash_aligned2(const void* key, int len, uint32_t seed);

//-----------------------------------------------------------------------------
// CMurmurHash2A, by Austin Appleby

// This is a sample implementation of MurmurHash2A designed to work
// incrementally.

// Usage -

// CMurmurHash2A hasher
// hasher.Begin(seed);
// hasher.Add(data1,size1);
// hasher.Add(data2,size2);
// ...
// hasher.Add(dataN,sizeN);
// uint32_t hash = hasher.End()

typedef struct
{
    uint32_t m_hash;
    uint32_t m_tail;
    uint32_t m_count;
    uint32_t m_size;
} murmurhash2_t;

void murmurhash2_begin(murmurhash2_t* context, uint32_t seed);
void murmurhash2_add(murmurhash2_t* context, const uint8_t* data, int len);
uint32_t murmurhash2_end(murmurhash2_t* context);
