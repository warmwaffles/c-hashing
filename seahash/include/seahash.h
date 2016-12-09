#pragma once

#include <stdint.h>
#include <sys/types.h>

uint64_t seahash_seeded(const uint8_t* buf, size_t size, uint64_t a, uint64_t b, uint64_t c, uint64_t d);
uint64_t seahash(const uint8_t* buf, size_t size);
