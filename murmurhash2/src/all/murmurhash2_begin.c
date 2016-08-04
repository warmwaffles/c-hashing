#include "common.h"

#include <assert.h>

void
murmurhash2_begin(murmurhash2_t* context, uint32_t seed)
{
	assert(context);

    context->m_hash = seed;
    context->m_tail = 0;
    context->m_count = 0;
    context->m_size = 0;
}
