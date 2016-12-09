#include <assert.h>
#include <stddef.h>
#include <string.h>

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

#include <spooky.h>

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

void
spooky_end_partial(uint64_t* h0,
                   uint64_t* h1,
                   uint64_t* h2,
                   uint64_t* h3,
                   uint64_t* h4,
                   uint64_t* h5,
                   uint64_t* h6,
                   uint64_t* h7,
                   uint64_t* h8,
                   uint64_t* h9,
                   uint64_t* h10,
                   uint64_t* h11)
{
    *h11 += *h1;
    *h2 ^= *h11;
    *h1 = spooky_rot64(*h1, 44);
    *h0 += *h2;
    *h3 ^= *h0;
    *h2 = spooky_rot64(*h2, 15);
    *h1 += *h3;
    *h4 ^= *h1;
    *h3 = spooky_rot64(*h3, 34);
    *h2 += *h4;
    *h5 ^= *h2;
    *h4 = spooky_rot64(*h4, 21);
    *h3 += *h5;
    *h6 ^= *h3;
    *h5 = spooky_rot64(*h5, 38);
    *h4 += *h6;
    *h7 ^= *h4;
    *h6 = spooky_rot64(*h6, 33);
    *h5 += *h7;
    *h8 ^= *h5;
    *h7 = spooky_rot64(*h7, 10);
    *h6 += *h8;
    *h9 ^= *h6;
    *h8 = spooky_rot64(*h8, 13);
    *h7 += *h9;
    *h10 ^= *h7;
    *h9 = spooky_rot64(*h9, 38);
    *h8 += *h10;
    *h11 ^= *h8;
    *h10 = spooky_rot64(*h10, 53);
    *h9 += *h11;
    *h0 ^= *h9;
    *h11 = spooky_rot64(*h11, 42);
    *h10 += *h0;
    *h1 ^= *h10;
    *h0 = spooky_rot64(*h0, 54);
}

void
spooky_end(const uint64_t* data,
           uint64_t* h0,
           uint64_t* h1,
           uint64_t* h2,
           uint64_t* h3,
           uint64_t* h4,
           uint64_t* h5,
           uint64_t* h6,
           uint64_t* h7,
           uint64_t* h8,
           uint64_t* h9,
           uint64_t* h10,
           uint64_t* h11)
{
    *h0 += data[0];
    *h1 += data[1];
    *h2 += data[2];
    *h3 += data[3];
    *h4 += data[4];
    *h5 += data[5];
    *h6 += data[6];
    *h7 += data[7];
    *h8 += data[8];
    *h9 += data[9];
    *h10 += data[10];
    *h11 += data[11];
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
}

void
spooky_short_end(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3)
{
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 15);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 52);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 26);
    *h1 += *h0;
    *h2 ^= *h1;
    *h1 = spooky_rot64(*h1, 51);
    *h2 += *h1;
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 28);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 9);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 47);
    *h1 += *h0;
    *h2 ^= *h1;
    *h1 = spooky_rot64(*h1, 54);
    *h2 += *h1;
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 32);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 25);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 63);
    *h1 += *h0;
}

void
spooky_short_mix(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3)
{
    *h2 = spooky_rot64(*h2, 50);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 52);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 30);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 41);
    *h1 += *h2;
    *h3 ^= *h1;
    *h2 = spooky_rot64(*h2, 54);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 48);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 38);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 37);
    *h1 += *h2;
    *h3 ^= *h1;
    *h2 = spooky_rot64(*h2, 62);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 34);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 5);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 36);
    *h1 += *h2;
    *h3 ^= *h1;
}

void
spooky_short(const void* message, size_t length, uint64_t* hash1, uint64_t* hash2)
{
    uint64_t buf[24];
    union
    {
        const uint8_t* p8;
        uint32_t* p32;
        uint64_t* p64;
        size_t i;
    } u;

    u.p8 = (const uint8_t*)message;

    if (!ALLOW_UNALIGNED_READS && (u.i & 0x7)) {
        memcpy(buf, message, length);
        u.p64 = buf;
    }

    size_t rem = length % 32;
    uint64_t a = *hash1;
    uint64_t b = *hash2;
    uint64_t c = SPOOKY_HASH_CONST;
    uint64_t d = SPOOKY_HASH_CONST;

    if (length > 15) {
        const uint64_t* end = u.p64 + (length / 32) * 4;

        // handle all complete sets of 32 bytes
        for (; u.p64 < end; u.p64 += 4) {
            c += u.p64[0];
            d += u.p64[1];
            spooky_short_mix(&a, &b, &c, &d);
            a += u.p64[2];
            b += u.p64[3];
        }

        // Handle the case of 16+ remaining bytes.
        if (rem >= 16) {
            c += u.p64[0];
            d += u.p64[1];
            spooky_short_mix(&a, &b, &c, &d);
            u.p64 += 2;
            rem -= 16;
        }
    }

    // Handle the last 0..15 bytes, and its length
    d += ((uint64_t)length) << 56;
    switch (rem) {
        case 15:
            d += ((uint64_t)u.p8[14]) << 48;
        case 14:
            d += ((uint64_t)u.p8[13]) << 40;
        case 13:
            d += ((uint64_t)u.p8[12]) << 32;
        case 12:
            d += u.p32[2];
            c += u.p64[0];
            break;
        case 11:
            d += ((uint64_t)u.p8[10]) << 16;
        case 10:
            d += ((uint64_t)u.p8[9]) << 8;
        case 9:
            d += (uint64_t)u.p8[8];
        case 8:
            c += u.p64[0];
            break;
        case 7:
            c += ((uint64_t)u.p8[6]) << 48;
        case 6:
            c += ((uint64_t)u.p8[5]) << 40;
        case 5:
            c += ((uint64_t)u.p8[4]) << 32;
        case 4:
            c += u.p32[0];
            break;
        case 3:
            c += ((uint64_t)u.p8[2]) << 16;
        case 2:
            c += ((uint64_t)u.p8[1]) << 8;
        case 1:
            c += (uint64_t)u.p8[0];
            break;
        case 0:
            c += SPOOKY_HASH_CONST;
            d += SPOOKY_HASH_CONST;
    }
    spooky_short_end(&a, &b, &c, &d);
    *hash1 = a;
    *hash2 = b;
}

void
spooky_mix(const uint64_t* data,
           uint64_t* s0,
           uint64_t* s1,
           uint64_t* s2,
           uint64_t* s3,
           uint64_t* s4,
           uint64_t* s5,
           uint64_t* s6,
           uint64_t* s7,
           uint64_t* s8,
           uint64_t* s9,
           uint64_t* s10,
           uint64_t* s11)
{
    *s0 += data[0];
    *s2 ^= *s10;
    *s11 ^= *s0;
    *s0 = spooky_rot64(*s0, 11);
    *s11 += *s1;
    *s1 += data[1];
    *s3 ^= *s11;
    *s0 ^= *s1;
    *s1 = spooky_rot64(*s1, 32);
    *s0 += *s2;
    *s2 += data[2];
    *s4 ^= *s0;
    *s1 ^= *s2;
    *s2 = spooky_rot64(*s2, 43);
    *s1 += *s3;
    *s3 += data[3];
    *s5 ^= *s1;
    *s2 ^= *s3;
    *s3 = spooky_rot64(*s3, 31);
    *s2 += *s4;
    *s4 += data[4];
    *s6 ^= *s2;
    *s3 ^= *s4;
    *s4 = spooky_rot64(*s4, 17);
    *s3 += *s5;
    *s5 += data[5];
    *s7 ^= *s3;
    *s4 ^= *s5;
    *s5 = spooky_rot64(*s5, 28);
    *s4 += *s6;
    *s6 += data[6];
    *s8 ^= *s4;
    *s5 ^= *s6;
    *s6 = spooky_rot64(*s6, 39);
    *s5 += *s7;
    *s7 += data[7];
    *s9 ^= *s5;
    *s6 ^= *s7;
    *s7 = spooky_rot64(*s7, 57);
    *s6 += *s8;
    *s8 += data[8];
    *s10 ^= *s6;
    *s7 ^= *s8;
    *s8 = spooky_rot64(*s8, 55);
    *s7 += *s9;
    *s9 += data[9];
    *s11 ^= *s7;
    *s8 ^= *s9;
    *s9 = spooky_rot64(*s9, 54);
    *s8 += *s10;
    *s10 += data[10];
    *s0 ^= *s8;
    *s9 ^= *s10;
    *s10 = spooky_rot64(*s10, 22);
    *s9 += *s11;
    *s11 += data[11];
    *s1 ^= *s9;
    *s10 ^= *s11;
    *s11 = spooky_rot64(*s11, 46);
    *s10 += *s0;
}

void
spooky_hash128(const void* message, size_t length, uint64_t* hash1, uint64_t* hash2)
{
    if (length < SPOOKY_HASH_BUFF_SIZE) {
        spooky_short(message, length, hash1, hash2);
        return;
    }

    uint64_t h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    uint64_t buf[SPOOKY_HASH_NUM_VARS];
    uint64_t* end;
    union
    {
        const uint8_t* p8;
        uint64_t* p64;
        size_t i;
    } u;
    size_t rem;

    h0 = *hash1;
    h3 = *hash1;
    h6 = *hash1;
    h9 = *hash1;

    h1  = *hash2;
    h4  = *hash2;
    h7  = *hash2;
    h10 = *hash2;

    h2  = SPOOKY_HASH_CONST;
    h5  = SPOOKY_HASH_CONST;
    h8  = SPOOKY_HASH_CONST;
    h11 = SPOOKY_HASH_CONST;

    u.p8 = (const uint8_t*)message;
    end  = u.p64 + (length / SPOOKY_HASH_BLOCK_SIZE) * SPOOKY_HASH_NUM_VARS;

    // handle all whole SPOOKY_HASH_BLOCK_SIZE blocks of bytes
    if (ALLOW_UNALIGNED_READS || ((u.i & 0x7) == 0)) {
        while (u.p64 < end) {
            spooky_mix(u.p64, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    } else {
        while (u.p64 < end) {
            memcpy(buf, u.p64, SPOOKY_HASH_BLOCK_SIZE);
            spooky_mix(buf, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    }

    // handle the last partial block of SPOOKY_HASH_BLOCK_SIZE bytes
    rem = (length - ((const uint8_t*)end - (const uint8_t*)message));
    memcpy(buf, end, rem);
    memset(((uint8_t*)buf) + rem, 0, SPOOKY_HASH_BLOCK_SIZE - rem);
    ((uint8_t*)buf)[SPOOKY_HASH_BLOCK_SIZE - 1] = rem;

    // do some final mixing
    spooky_end(buf, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
    *hash1 = h0;
    *hash2 = h1;
}

uint64_t
spooky_hash64(const void* message, size_t length, uint64_t seed)
{
    uint64_t hash1 = seed;
    spooky_hash128(message, length, &hash1, &seed);
    return hash1;
}

uint32_t
spooky_hash32(const void* message, size_t length, uint32_t seed)
{
    uint64_t hash1 = seed;
    uint64_t hash2 = seed;
    spooky_hash128(message, length, &hash1, &hash2);
    return (uint32_t)hash1;
}

void
spooky_hash_final(spooky_hash_t* context, uint64_t* hash1, uint64_t* hash2)
{
    // init the variables
    if (context->m_length < SPOOKY_HASH_BUFF_SIZE) {
        *hash1 = context->m_state[0];
        *hash2 = context->m_state[1];
        spooky_short(context->m_data, context->m_length, hash1, hash2);
        return;
    }

    const uint64_t* data = (const uint64_t*)context->m_data;
    uint8_t remainder    = context->m_remainder;

    uint64_t h0  = context->m_state[0];
    uint64_t h1  = context->m_state[1];
    uint64_t h2  = context->m_state[2];
    uint64_t h3  = context->m_state[3];
    uint64_t h4  = context->m_state[4];
    uint64_t h5  = context->m_state[5];
    uint64_t h6  = context->m_state[6];
    uint64_t h7  = context->m_state[7];
    uint64_t h8  = context->m_state[8];
    uint64_t h9  = context->m_state[9];
    uint64_t h10 = context->m_state[10];
    uint64_t h11 = context->m_state[11];

    if (remainder >= SPOOKY_HASH_BLOCK_SIZE) {
        // context->m_data can contain two blocks; handle any whole first block
        spooky_mix(data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        data += SPOOKY_HASH_NUM_VARS;
        remainder -= SPOOKY_HASH_BLOCK_SIZE;
    }

    // mix in the last partial block, and the length mod SPOOKY_HASH_BLOCK_SIZE
    memset(&((uint8_t*)data)[remainder], 0, (SPOOKY_HASH_BLOCK_SIZE - remainder));

    ((uint8_t*)data)[SPOOKY_HASH_BLOCK_SIZE - 1] = remainder;

    // do some final mixing
    spooky_end(data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);

    *hash1 = h0;
    *hash2 = h1;
}

void
spooky_hash_init(spooky_hash_t* context, uint64_t seed1, uint64_t seed2)
{
    assert(context);

    context->m_length    = 0;
    context->m_remainder = 0;
    context->m_state[0]  = seed1;
    context->m_state[1]  = seed2;
}

// add a message fragment to the state
void
spooky_hash_update(spooky_hash_t* context, const void* message, size_t length)
{
    uint64_t h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    size_t newLength = length + context->m_remainder;
    uint8_t remainder;
    union
    {
        const uint8_t* p8;
        uint64_t* p64;
        size_t i;
    } u;
    const uint64_t* end;

    // Is this message fragment too short?  If it is, stuff it away.
    if (newLength < SPOOKY_HASH_BUFF_SIZE) {
        memcpy(&((uint8_t*)context->m_data)[context->m_remainder], message, length);

        context->m_length    = length + context->m_length;
        context->m_remainder = (uint8_t)newLength;
        return;
    }

    // init the variables
    if (context->m_length < SPOOKY_HASH_BUFF_SIZE) {
        h0 = h3 = h6 = h9 = context->m_state[0];

        h1 = h4 = h7 = h10 = context->m_state[1];
        h2 = h5 = h8 = h11 = SPOOKY_HASH_CONST;
    } else {
        h0  = context->m_state[0];
        h1  = context->m_state[1];
        h2  = context->m_state[2];
        h3  = context->m_state[3];
        h4  = context->m_state[4];
        h5  = context->m_state[5];
        h6  = context->m_state[6];
        h7  = context->m_state[7];
        h8  = context->m_state[8];
        h9  = context->m_state[9];
        h10 = context->m_state[10];
        h11 = context->m_state[11];
    }
    context->m_length = length + context->m_length;

    // if we've got anything stuffed away, use it now
    if (context->m_remainder) {
        uint8_t prefix = SPOOKY_HASH_BUFF_SIZE - context->m_remainder;
        memcpy(&(((uint8_t*)context->m_data)[context->m_remainder]), message, prefix);

        u.p64 = context->m_data;
        spooky_mix(u.p64, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        spooky_mix(&u.p64[SPOOKY_HASH_NUM_VARS], &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        u.p8 = ((const uint8_t*)message) + prefix;

        length -= prefix;
    } else {
        u.p8 = (const uint8_t*)message;
    }

    // handle all whole blocks of SPOOKY_HASH_BLOCK_SIZE bytes
    end       = u.p64 + (length / SPOOKY_HASH_BLOCK_SIZE) * SPOOKY_HASH_NUM_VARS;
    remainder = (uint8_t)(length - ((const uint8_t*)end - u.p8));
    if (ALLOW_UNALIGNED_READS || (u.i & 0x7) == 0) {
        while (u.p64 < end) {
            spooky_mix(u.p64, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    } else {
        while (u.p64 < end) {
            memcpy(context->m_data, u.p8, SPOOKY_HASH_BLOCK_SIZE);
            spooky_mix(context->m_data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    }

    // stuff away the last few bytes
    context->m_remainder = remainder;
    memcpy(context->m_data, end, remainder);

    // stuff away the variables
    context->m_state[0]  = h0;
    context->m_state[1]  = h1;
    context->m_state[2]  = h2;
    context->m_state[3]  = h3;
    context->m_state[4]  = h4;
    context->m_state[5]  = h5;
    context->m_state[6]  = h6;
    context->m_state[7]  = h7;
    context->m_state[8]  = h8;
    context->m_state[9]  = h9;
    context->m_state[10] = h10;
    context->m_state[11] = h11;
}
