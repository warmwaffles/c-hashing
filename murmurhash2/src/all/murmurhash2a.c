#include "common.h"

//-----------------------------------------------------------------------------
// MurmurHash2A, by Austin Appleby

// This is a variant of MurmurHash2 modified to use the Merkle-Damgard
// construction. Bulk speed should be identical to Murmur2, small-key speed
// will be 10%-20% slower due to the added overhead at the end of the hash.

// This variant fixes a minor issue where null keys were more likely to
// collide with each other than expected, and also makes the function
// more amenable to incremental implementations.

uint32_t
MurmurHash2A(const void* key, int len, uint32_t seed)
{
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t l = len;

    const unsigned char* data = (const unsigned char*)key;

    uint32_t h = seed;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;

        mmix(h, k, m, r);

        data += 4;
        len -= 4;
    }

    uint32_t t = 0;

    switch (len) {
        case 3:
            t ^= data[2] << 16;
        case 2:
            t ^= data[1] << 8;
        case 1:
            t ^= data[0];
    };

    mmix(h, t, m, r);
    mmix(h, l, m, r);

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}
