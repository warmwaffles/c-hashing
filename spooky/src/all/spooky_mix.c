#include "common.h"

void
spooky_mix(const uint64_t* data, uint64_t* s0, uint64_t* s1, uint64_t* s2, uint64_t* s3, uint64_t* s4, uint64_t* s5,
           uint64_t* s6, uint64_t* s7, uint64_t* s8, uint64_t* s9, uint64_t* s10, uint64_t* s11)
{
    *s0 += data[0];
    *s2 ^= *s10;
    *s11 ^= *s0;
    *s0 = spooky_rot64(*s0, 11);
    *s11 += *s1;
    *s1 += data[1];
    *s3 ^= *s11;
    *s0 ^= *s1;
    *s1 = spooky_rot64(*s1, 32);
    *s0 += *s2;
    *s2 += data[2];
    *s4 ^= *s0;
    *s1 ^= *s2;
    *s2 = spooky_rot64(*s2, 43);
    *s1 += *s3;
    *s3 += data[3];
    *s5 ^= *s1;
    *s2 ^= *s3;
    *s3 = spooky_rot64(*s3, 31);
    *s2 += *s4;
    *s4 += data[4];
    *s6 ^= *s2;
    *s3 ^= *s4;
    *s4 = spooky_rot64(*s4, 17);
    *s3 += *s5;
    *s5 += data[5];
    *s7 ^= *s3;
    *s4 ^= *s5;
    *s5 = spooky_rot64(*s5, 28);
    *s4 += *s6;
    *s6 += data[6];
    *s8 ^= *s4;
    *s5 ^= *s6;
    *s6 = spooky_rot64(*s6, 39);
    *s5 += *s7;
    *s7 += data[7];
    *s9 ^= *s5;
    *s6 ^= *s7;
    *s7 = spooky_rot64(*s7, 57);
    *s6 += *s8;
    *s8 += data[8];
    *s10 ^= *s6;
    *s7 ^= *s8;
    *s8 = spooky_rot64(*s8, 55);
    *s7 += *s9;
    *s9 += data[9];
    *s11 ^= *s7;
    *s8 ^= *s9;
    *s9 = spooky_rot64(*s9, 54);
    *s8 += *s10;
    *s10 += data[10];
    *s0 ^= *s8;
    *s9 ^= *s10;
    *s10 = spooky_rot64(*s10, 22);
    *s9 += *s11;
    *s11 += data[11];
    *s1 ^= *s9;
    *s10 ^= *s11;
    *s11 = spooky_rot64(*s11, 46);
    *s10 += *s0;
}
