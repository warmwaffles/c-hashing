#include "common.h"

#include <string.h>

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

    h1 = *hash2;
    h4 = *hash2;
    h7 = *hash2;
    h10 = *hash2;

    h2 = SPOOKY_HASH_CONST;
    h5 = SPOOKY_HASH_CONST;
    h8 = SPOOKY_HASH_CONST;
    h11 = SPOOKY_HASH_CONST;

    u.p8 = (const uint8_t*)message;
    end = u.p64 + (length / SPOOKY_HASH_BLOCK_SIZE) * SPOOKY_HASH_NUM_VARS;

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
