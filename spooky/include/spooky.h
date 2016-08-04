#pragma once

#include <stddef.h>

#ifdef _MSC_VER
typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
#else
#include <stdint.h>
#endif

typedef struct
{
    /**
     * unhashed data, for partial messages
     */
    uint64_t m_data[24];
    /**
     * internal state of the hash
     */
    uint64_t m_state[12];
    /**
     * total length of the input so far
     */
    size_t m_length;
    /**
     * length of unhashed data stashed in m_data
     */
    uint8_t m_remainder;
} spooky_hash_t;

void spooky_hash_init(spooky_hash_t* spooky, uint64_t seed1, uint64_t seed2);
void spooky_hash_update(spooky_hash_t* context, const void* message, size_t length);
void spooky_hash_final(spooky_hash_t* context, uint64_t* hash1, uint64_t* hash2);

void spooky_hash128(const void* message, size_t length, uint64_t* hash1, uint64_t* hash2);
uint64_t spooky_hash64(const void* message, size_t length, uint64_t seed);
uint32_t spooky_hash32(const void* message, size_t length, uint32_t seed);
