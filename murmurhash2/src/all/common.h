#pragma once

#include <murmurhash2.h>

#if defined(_MSC_VER)
#define BIG_CONSTANT(x) (x)
// Other compilers
#else // defined(_MSC_VER)
#define BIG_CONSTANT(x) (x##LLU)
#endif // !defined(_MSC_VER)

void murmurhash2_mix_tail(murmurhash2_t* context, const uint8_t* data, int len);

#define mmix(h, k, m, r)                                                                                               \
    {                                                                                                                  \
        (k) *= (m);                                                                                                      \
        (k) ^= (k) >> (r);                                                                                               \
        (k) *= (m);                                                                                                      \
        (h) *= (m);                                                                                                      \
        (h) ^= (k);                                                                                                    \
    }
