#include "common.h"

void
spooky_end_partial(uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3, uint64_t* h4, uint64_t* h5, uint64_t* h6,
                   uint64_t* h7, uint64_t* h8, uint64_t* h9, uint64_t* h10, uint64_t* h11)
{
    *h11 += *h1;
    *h2 ^= *h11;
    *h1 = spooky_rot64(*h1, 44);
    *h0 += *h2;
    *h3 ^= *h0;
    *h2 = spooky_rot64(*h2, 15);
    *h1 += *h3;
    *h4 ^= *h1;
    *h3 = spooky_rot64(*h3, 34);
    *h2 += *h4;
    *h5 ^= *h2;
    *h4 = spooky_rot64(*h4, 21);
    *h3 += *h5;
    *h6 ^= *h3;
    *h5 = spooky_rot64(*h5, 38);
    *h4 += *h6;
    *h7 ^= *h4;
    *h6 = spooky_rot64(*h6, 33);
    *h5 += *h7;
    *h8 ^= *h5;
    *h7 = spooky_rot64(*h7, 10);
    *h6 += *h8;
    *h9 ^= *h6;
    *h8 = spooky_rot64(*h8, 13);
    *h7 += *h9;
    *h10 ^= *h7;
    *h9 = spooky_rot64(*h9, 38);
    *h8 += *h10;
    *h11 ^= *h8;
    *h10 = spooky_rot64(*h10, 53);
    *h9 += *h11;
    *h0 ^= *h9;
    *h11 = spooky_rot64(*h11, 42);
    *h10 += *h0;
    *h1 ^= *h10;
    *h0 = spooky_rot64(*h0, 54);
}
