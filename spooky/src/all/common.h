#pragma once

#include <spooky.h>

#include <stddef.h>

#ifdef _MSC_VER
#define INLINE __forceinline
typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
#else
#include <stdint.h>
#define INLINE inline
#endif

#ifndef ALLOW_UNALIGNED_READS
#define ALLOW_UNALIGNED_READS 1
#endif

// number of uint64_t's in internal state
#define SPOOKY_HASH_NUM_VARS 12

// size of the internal state
#define SPOOKY_HASH_BLOCK_SIZE 96

// size of buffer of unhashed data, in bytes
#define SPOOKY_HASH_BUFF_SIZE 192

//
// SPOOKY_HASH_CONST: a constant which:
//  * is not zero
//  * is odd
//  * is a not-very-regular mix of 1's and 0's
//  * does not need any other special mathematical properties
//
#define SPOOKY_HASH_CONST 0xdeadbeefdeadbeefLL

#define spooky_rot64(x, k) (((x) << (k)) | ((x) >> (64 - (k))))

void spooky_mix(const uint64_t* data, uint64_t* s0, uint64_t* s1, uint64_t* s2, uint64_t* s3, uint64_t* s4, uint64_t* s5,
                uint64_t* s6, uint64_t* s7, uint64_t* s8, uint64_t* s9, uint64_t* s10, uint64_t* s11);
void spooky_end(const uint64_t* data, uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3, uint64_t* h4, uint64_t* h5,
                uint64_t* h6, uint64_t* h7, uint64_t* h8, uint64_t* h9, uint64_t* h10, uint64_t* h11);
void spooky_end_partial(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3, uint64_t* h4, uint64_t* h5,
                        uint64_t* h6, uint64_t* h7, uint64_t* h8, uint64_t* h9, uint64_t* h10, uint64_t* h11);
void spooky_short(const void* message, size_t length, uint64_t* hash1, uint64_t* hash2);
void spooky_short_mix(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3);
void spooky_short_end(uint64_t *h0, uint64_t *h1, uint64_t *h2, uint64_t *h3);
