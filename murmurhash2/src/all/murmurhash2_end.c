#include "common.h"

uint32_t
murmurhash2_end(murmurhash2_t* context)
{
    mmix(context->m_hash, context->m_tail, 0x5bd1e995, 24);
    mmix(context->m_hash, context->m_size, 0x5bd1e995, 24);

    context->m_hash ^= context->m_hash >> 13;
    context->m_hash *= 0x5bd1e995;
    context->m_hash ^= context->m_hash >> 15;

    return context->m_hash;
}
