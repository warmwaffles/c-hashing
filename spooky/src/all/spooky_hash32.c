#include "common.h"

uint32_t
spooky_hash32(const void* message, size_t length, uint32_t seed)
{
    uint64_t hash1 = seed;
    uint64_t hash2 = seed;
    spooky_hash128(message, length, &hash1, &hash2);
    return (uint32_t)hash1;
}
