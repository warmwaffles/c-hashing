#include <seahash.h>

const uint64_t block_size = 32;

static inline uint64_t
read_u64(uint8_t* ptr)
{
    return *(uint64_t*)ptr;
}

static inline uint64_t
diffuse(uint64_t x)
{
    x = x * 0x6eed0e9da4d94a4f;
    x = x ^ ((x >> 32) >> (x >> 60));
    x = x * 0x6eed0e9da4d94a4f;
    return x;
}

uint64_t
seahash(uint8_t* buf, size_t size)
{
    uint64_t a = 0x16f11fe89b0d677cULL;
    uint64_t b = 0xb480a793d8e6c86cULL;
    uint64_t c = 0x6fe2e5aaf078ebc9ULL;
    uint64_t d = 0x14f994a4c5259381ULL;

    size_t end = size & ~(block_size - 1);
    for (size_t i = 0; i < end; i += block_size) {
        a ^= read_u64(buf + i);
        b ^= read_u64(buf + i + 8);
        c ^= read_u64(buf + i + 16);
        d ^= read_u64(buf + i + 24);

        a = diffuse(a);
        b = diffuse(b);
        c = diffuse(c);
        d = diffuse(d);
    }

    size_t excessive = size - end;
    uint8_t* buf_end = buf + end;

    if (excessive > 0) {
        a = a ^ read_u64(buf_end);

        if (excessive > 8) {
            b = b ^ read_u64(buf_end);

            if (excessive > 16) {
                c = c ^ read_u64(buf_end);

                if (excessive > 24) {
                    d = d ^ read_u64(buf_end);
                    d = diffuse(d);
                }

                c = diffuse(c);
            }

            b = diffuse(b);
        }

        a = diffuse(a);
    }

    a = a ^ b;
    c = c ^ d;
    a = a ^ c;
    a = a ^ size;

    return diffuse(a);
}
