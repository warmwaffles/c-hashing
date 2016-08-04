#include "common.h"

void
spooky_short_mix(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3)
{
    *h2 = spooky_rot64(*h2, 50);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 52);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 30);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 41);
    *h1 += *h2;
    *h3 ^= *h1;
    *h2 = spooky_rot64(*h2, 54);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 48);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 38);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 37);
    *h1 += *h2;
    *h3 ^= *h1;
    *h2 = spooky_rot64(*h2, 62);
    *h2 += *h3;
    *h0 ^= *h2;
    *h3 = spooky_rot64(*h3, 34);
    *h3 += *h0;
    *h1 ^= *h3;
    *h0 = spooky_rot64(*h0, 5);
    *h0 += *h1;
    *h2 ^= *h0;
    *h1 = spooky_rot64(*h1, 36);
    *h1 += *h2;
    *h3 ^= *h1;
}
