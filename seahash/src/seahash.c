#include <seahash.h>

#define BLOCK_SIZE 32

static inline uint64_t
read_u64(const uint8_t* ptr)
{
    return *(uint64_t*)ptr;
}

static inline uint64_t
diffuse(uint64_t x)
{
    x *= 0x6eed0e9da4d94a4f;
    x ^= ((x >> 32) >> (x >> 60));
    x *= 0x6eed0e9da4d94a4f;
    return x;
}

uint64_t
seahash_seeded(const uint8_t* buf, size_t size, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    size_t end = size & ~(BLOCK_SIZE - 1);
    for (size_t i = 0; i < end; i += BLOCK_SIZE) {
        a ^= read_u64(buf + i);
        b ^= read_u64(buf + i + 8);
        c ^= read_u64(buf + i + 16);
        d ^= read_u64(buf + i + 24);

        a = diffuse(a);
        b = diffuse(b);
        c = diffuse(c);
        d = diffuse(d);
    }

    size_t excessive       = size - end;
    const uint8_t* buf_end = buf + end;

    if (excessive > 0) {
        a ^= read_u64(buf_end);

        if (excessive > 8) {
            b ^= read_u64(buf_end);

            if (excessive > 16) {
                c ^= read_u64(buf_end);

                if (excessive > 24) {
                    d ^= read_u64(buf_end);
                    d = diffuse(d);
                }

                c = diffuse(c);
            }

            b = diffuse(b);
        }

        a = diffuse(a);
    }

    a ^= b;
    c ^= d;
    a ^= c;
    a ^= size;

    return diffuse(a);
}

uint64_t
seahash(const uint8_t* buf, size_t size)
{
    return seahash_seeded(buf, size, 0x16f11fe89b0d677cULL, 0xb480a793d8e6c86cULL, 0x6fe2e5aaf078ebc9ULL, 0x14f994a4c5259381ULL);
}
