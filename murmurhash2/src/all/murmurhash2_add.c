#include "common.h"

void
murmurhash2_add(murmurhash2_t* context, const uint8_t* data, int len)
{
    context->m_size += len;
    murmurhash2_mix_tail(context, data, len);

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;
        mmix(context->m_hash, k, 0x5bd1e995, 24);
        data += 4;
        len -= 4;
    }

    murmurhash2_mix_tail(context, data, len);
}
