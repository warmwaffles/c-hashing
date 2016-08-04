#include "common.h"

void
spooky_end(const uint64_t* data, uint64_t* h0, uint64_t* h1, uint64_t* h2, uint64_t* h3, uint64_t* h4, uint64_t* h5,
           uint64_t* h6, uint64_t* h7, uint64_t* h8, uint64_t* h9, uint64_t* h10, uint64_t* h11)
{
    *h0 += data[0];
    *h1 += data[1];
    *h2 += data[2];
    *h3 += data[3];
    *h4 += data[4];
    *h5 += data[5];
    *h6 += data[6];
    *h7 += data[7];
    *h8 += data[8];
    *h9 += data[9];
    *h10 += data[10];
    *h11 += data[11];
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    spooky_end_partial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
}
