#include "common.h"

#include <assert.h>

void
spooky_hash_init(spooky_hash_t* context, uint64_t seed1, uint64_t seed2)
{
    assert(context);

    context->m_length = 0;
    context->m_remainder = 0;
    context->m_state[0] = seed1;
    context->m_state[1] = seed2;
}
