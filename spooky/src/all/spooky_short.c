#include "common.h"

#include <string.h>

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
