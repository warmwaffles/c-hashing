#include "common.h"

uint64_t
spooky_hash64(const void* message, size_t length, uint64_t seed)
{
    uint64_t hash1 = seed;
    spooky_hash128(message, length, &hash1, &seed);
    return hash1;
}
