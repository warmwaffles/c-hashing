#include "common.h"

#include <string.h>

// add a message fragment to the state
void
spooky_hash_update(spooky_hash_t* context, const void* message, size_t length)
{
    uint64_t h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    size_t newLength = length + context->m_remainder;
    uint8_t remainder;
    union
    {
        const uint8_t* p8;
        uint64_t* p64;
        size_t i;
    } u;
    const uint64_t* end;

    // Is this message fragment too short?  If it is, stuff it away.
    if (newLength < SPOOKY_HASH_BUFF_SIZE) {
        memcpy(&((uint8_t*)context->m_data)[context->m_remainder], message, length);

        context->m_length = length + context->m_length;
        context->m_remainder = (uint8_t)newLength;
        return;
    }

    // init the variables
    if (context->m_length < SPOOKY_HASH_BUFF_SIZE) {
        h0 = h3 = h6 = h9 = context->m_state[0];

        h1 = h4 = h7 = h10 = context->m_state[1];
        h2 = h5 = h8 = h11 = SPOOKY_HASH_CONST;
    } else {
        h0 = context->m_state[0];
        h1 = context->m_state[1];
        h2 = context->m_state[2];
        h3 = context->m_state[3];
        h4 = context->m_state[4];
        h5 = context->m_state[5];
        h6 = context->m_state[6];
        h7 = context->m_state[7];
        h8 = context->m_state[8];
        h9 = context->m_state[9];
        h10 = context->m_state[10];
        h11 = context->m_state[11];
    }
    context->m_length = length + context->m_length;

    // if we've got anything stuffed away, use it now
    if (context->m_remainder) {
        uint8_t prefix = SPOOKY_HASH_BUFF_SIZE - context->m_remainder;
        memcpy(&(((uint8_t*)context->m_data)[context->m_remainder]), message, prefix);

        u.p64 = context->m_data;
        spooky_mix(u.p64, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        spooky_mix(&u.p64[SPOOKY_HASH_NUM_VARS], &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
        u.p8 = ((const uint8_t*)message) + prefix;

        length -= prefix;
    } else {
        u.p8 = (const uint8_t*)message;
    }

    // handle all whole blocks of SPOOKY_HASH_BLOCK_SIZE bytes
    end = u.p64 + (length / SPOOKY_HASH_BLOCK_SIZE) * SPOOKY_HASH_NUM_VARS;
    remainder = (uint8_t)(length - ((const uint8_t*)end - u.p8));
    if (ALLOW_UNALIGNED_READS || (u.i & 0x7) == 0) {
        while (u.p64 < end) {
            spooky_mix(u.p64, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    } else {
        while (u.p64 < end) {
            memcpy(context->m_data, u.p8, SPOOKY_HASH_BLOCK_SIZE);
            spooky_mix(context->m_data, &h0, &h1, &h2, &h3, &h4, &h5, &h6, &h7, &h8, &h9, &h10, &h11);
            u.p64 += SPOOKY_HASH_NUM_VARS;
        }
    }

    // stuff away the last few bytes
    context->m_remainder = remainder;
    memcpy(context->m_data, end, remainder);

    // stuff away the variables
    context->m_state[0] = h0;
    context->m_state[1] = h1;
    context->m_state[2] = h2;
    context->m_state[3] = h3;
    context->m_state[4] = h4;
    context->m_state[5] = h5;
    context->m_state[6] = h6;
    context->m_state[7] = h7;
    context->m_state[8] = h8;
    context->m_state[9] = h9;
    context->m_state[10] = h10;
    context->m_state[11] = h11;
}
