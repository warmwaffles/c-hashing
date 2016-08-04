#include "common.h"

void
spooky_short_end(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3)
{
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 15);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 52);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 26);
    *h1 += *h0;
    *h2 ^= *h1;
    *h1 = spooky_rot64(*h1, 51);
    *h2 += *h1;
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 28);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 9);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 47);
    *h1 += *h0;
    *h2 ^= *h1;
    *h1 = spooky_rot64(*h1, 54);
    *h2 += *h1;
    *h3 ^= *h2;
    *h2 = spooky_rot64(*h2, 32);
    *h3 += *h2;
    *h0 ^= *h3;
    *h3 = spooky_rot64(*h3, 25);
    *h0 += *h3;
    *h1 ^= *h0;
    *h0 = spooky_rot64(*h0, 63);
    *h1 += *h0;
}
