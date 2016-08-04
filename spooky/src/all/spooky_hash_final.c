#include "common.h"

#include <string.h>

void
spooky_hash_final(spooky_hash_t* context, uint64_t* hash1, uint64_t* hash2)
{
    // init the variables
    if (context->m_length < SPOOKY_HASH_BUFF_SIZE) {
        *hash1 = context->m_state[0];
        *hash2 = context->m_state[1];
        spooky_short(context->m_data, context->m_length, hash1, hash2);
        return;
    }

    const uint64_t* data = (const uint64_t*)context->m_data;
    uint8_t remainder = context->m_remainder;

    uint64_t h0 = context->m_state[0];
    uint64_t h1 = context->m_state[1];
    uint64_t h2 = context->m_state[2];
    uint64_t h3 = context->m_state[3];
    uint64_t h4 = context->m_state[4];
    uint64_t h5 = context->m_state[5];
    uint64_t h6 = context->m_state[6];
    uint64_t h7 = context->m_state[7];
    uint64_t h8 = context->m_state[8];
    uint64_t h9 = context->m_state[9];
    uint64_t h10 = context->m_state[10];
    uint64_t h11 = context->m_state[11];

    if (remainder >= SPOOKY_HASH_BLOCK_SIZE) {
        // context->m_data can contain two blocks; handle any whole first block
        spooky_mix(data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        data += SPOOKY_HASH_NUM_VARS;
        remainder -= SPOOKY_HASH_BLOCK_SIZE;
    }

    // mix in the last partial block, and the length mod SPOOKY_HASH_BLOCK_SIZE
    memset(&((uint8_t*)data)[remainder], 0, (SPOOKY_HASH_BLOCK_SIZE - remainder));

    ((uint8_t*)data)[SPOOKY_HASH_BLOCK_SIZE - 1] = remainder;

    // do some final mixing
    spooky_end(data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);

    *hash1 = h0;
    *hash2 = h1;
}
