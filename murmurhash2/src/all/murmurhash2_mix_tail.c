#include "common.h"

void
murmurhash2_mix_tail(murmurhash2_t* context, const uint8_t* data, int len)
{
    while (len && ((len < 4) || context->m_count)) {
        context->m_tail |= (*data++) << (context->m_count * 8);

        context->m_count++;
        len--;

        if (context->m_count == 4) {
            mmix(context->m_hash, context->m_tail, 0x5bd1e995, 24);
            context->m_tail = 0;
            context->m_count = 0;
        }
    }
}
