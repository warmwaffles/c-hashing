// metrohash128.cpp
//
// The MIT License (MIT)
//
// Copyright (c) 2015 J. Andrew Rogers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <metrohash.h>

void
metrohash128_1(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xC83A91E1;
    static const uint64_t k1 = 0x8648DBDB;
    static const uint64_t k2 = 0x7BDEC03B;
    static const uint64_t k3 = 0x2F5870A5;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t v[4];

    v[0] = ((((uint64_t)seed) - k0) * k3) + len;
    v[1] = ((((uint64_t)seed) + k1) * k2) + len;

    if (len >= 32) {
        v[2] = ((((uint64_t)seed) + k0) * k2) + len;
        v[3] = ((((uint64_t)seed) - k1) * k3) + len;

        do {
            v[0] += read_u64(ptr) * k0;
            ptr += 8;
            v[0] = rotate_right(v[0], 29) + v[2];
            v[1] += read_u64(ptr) * k1;
            ptr += 8;
            v[1] = rotate_right(v[1], 29) + v[3];
            v[2] += read_u64(ptr) * k2;
            ptr += 8;
            v[2] = rotate_right(v[2], 29) + v[0];
            v[3] += read_u64(ptr) * k3;
            ptr += 8;
            v[3] = rotate_right(v[3], 29) + v[1];
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 26) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 26) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 26) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 30) * k0;
    }

    if ((end - ptr) >= 16) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 33) * k3;
        v[1] += read_u64(ptr) * k2;
        ptr += 8;
        v[1] = rotate_right(v[1], 33) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 17) * k1;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 17) * k0;
    }

    if ((end - ptr) >= 8) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 33) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 20) * k1;
    }

    if ((end - ptr) >= 4) {
        v[1] += read_u32(ptr) * k2;
        ptr += 4;
        v[1] = rotate_right(v[1], 33) * k3;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 18) * k0;
    }

    if ((end - ptr) >= 2) {
        v[0] += read_u16(ptr) * k2;
        ptr += 2;
        v[0] = rotate_right(v[0], 33) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 24) * k1;
    }

    if ((end - ptr) >= 1) {
        v[1] += read_u8(ptr) * k2;
        v[1] = rotate_right(v[1], 33) * k3;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 24) * k0;
    }

    v[0] += rotate_right((v[0] * k0) + v[1], 13);
    v[1] += rotate_right((v[1] * k1) + v[0], 37);
    v[0] += rotate_right((v[0] * k2) + v[1], 13);
    v[1] += rotate_right((v[1] * k3) + v[0], 37);

    memcpy(out, v, 16);
}

void
metrohash128_2(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xD6D018F5;
    static const uint64_t k1 = 0xA2AA033B;
    static const uint64_t k2 = 0x62992FC1;
    static const uint64_t k3 = 0x30BC5B29;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t v[4];

    v[0] = ((((uint64_t)seed) - k0) * k3) + len;
    v[1] = ((((uint64_t)seed) + k1) * k2) + len;

    if (len >= 32) {
        v[2] = ((((uint64_t)seed) + k0) * k2) + len;
        v[3] = ((((uint64_t)seed) - k1) * k3) + len;

        do {
            v[0] += read_u64(ptr) * k0;
            ptr += 8;
            v[0] = rotate_right(v[0], 29) + v[2];
            v[1] += read_u64(ptr) * k1;
            ptr += 8;
            v[1] = rotate_right(v[1], 29) + v[3];
            v[2] += read_u64(ptr) * k2;
            ptr += 8;
            v[2] = rotate_right(v[2], 29) + v[0];
            v[3] += read_u64(ptr) * k3;
            ptr += 8;
            v[3] = rotate_right(v[3], 29) + v[1];
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 33) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 33) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 33) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 33) * k0;
    }

    if ((end - ptr) >= 16) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 29) * k3;
        v[1] += read_u64(ptr) * k2;
        ptr += 8;
        v[1] = rotate_right(v[1], 29) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 29) * k1;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 29) * k0;
    }

    if ((end - ptr) >= 8) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 29) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 29) * k1;
    }

    if ((end - ptr) >= 4) {
        v[1] += read_u32(ptr) * k2;
        ptr += 4;
        v[1] = rotate_right(v[1], 29) * k3;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 25) * k0;
    }

    if ((end - ptr) >= 2) {
        v[0] += read_u16(ptr) * k2;
        ptr += 2;
        v[0] = rotate_right(v[0], 29) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 30) * k1;
    }

    if ((end - ptr) >= 1) {
        v[1] += read_u8(ptr) * k2;
        v[1] = rotate_right(v[1], 29) * k3;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 18) * k0;
    }

    v[0] += rotate_right((v[0] * k0) + v[1], 33);
    v[1] += rotate_right((v[1] * k1) + v[0], 33);
    v[0] += rotate_right((v[0] * k2) + v[1], 33);
    v[1] += rotate_right((v[1] * k3) + v[0], 33);

    memcpy(out, v, 16);
}

// metrohash128crc.cpp
//
// The MIT License (MIT)
//
// Copyright (c) 2015 J. Andrew Rogers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <nmmintrin.h>

#include <metrohash.h>

void
metrohash128crc_1(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xC83A91E1;
    static const uint64_t k1 = 0x8648DBDB;
    static const uint64_t k2 = 0x7BDEC03B;
    static const uint64_t k3 = 0x2F5870A5;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t v[4];

    v[0] = ((((uint64_t)seed) - k0) * k3) + len;
    v[1] = ((((uint64_t)seed) + k1) * k2) + len;

    if (len >= 32) {
        v[2] = ((((uint64_t)seed) + k0) * k2) + len;
        v[3] = ((((uint64_t)seed) - k1) * k3) + len;

        do {
            v[0] ^= _mm_crc32_u64(v[0], read_u64(ptr));
            ptr += 8;
            v[1] ^= _mm_crc32_u64(v[1], read_u64(ptr));
            ptr += 8;
            v[2] ^= _mm_crc32_u64(v[2], read_u64(ptr));
            ptr += 8;
            v[3] ^= _mm_crc32_u64(v[3], read_u64(ptr));
            ptr += 8;
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 34) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 37) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 34) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 37) * k0;
    }

    if ((end - ptr) >= 16) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 34) * k3;
        v[1] += read_u64(ptr) * k2;
        ptr += 8;
        v[1] = rotate_right(v[1], 34) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 30) * k1;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 30) * k0;
    }

    if ((end - ptr) >= 8) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 36) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 23) * k1;
    }

    if ((end - ptr) >= 4) {
        v[1] ^= _mm_crc32_u64(v[0], read_u32(ptr));
        ptr += 4;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 19) * k0;
    }

    if ((end - ptr) >= 2) {
        v[0] ^= _mm_crc32_u64(v[1], read_u16(ptr));
        ptr += 2;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 13) * k1;
    }

    if ((end - ptr) >= 1) {
        v[1] ^= _mm_crc32_u64(v[0], read_u8(ptr));
        v[1] ^= rotate_right((v[1] * k3) + v[0], 17) * k0;
    }

    v[0] += rotate_right((v[0] * k0) + v[1], 11);
    v[1] += rotate_right((v[1] * k1) + v[0], 26);
    v[0] += rotate_right((v[0] * k0) + v[1], 11);
    v[1] += rotate_right((v[1] * k1) + v[0], 26);

    memcpy(out, v, 16);
}

void
metrohash128crc_2(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xEE783E2F;
    static const uint64_t k1 = 0xAD07C493;
    static const uint64_t k2 = 0x797A90BB;
    static const uint64_t k3 = 0x2E4B2E1B;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t v[4];

    v[0] = ((((uint64_t)seed) - k0) * k3) + len;
    v[1] = ((((uint64_t)seed) + k1) * k2) + len;

    if (len >= 32) {
        v[2] = ((((uint64_t)seed) + k0) * k2) + len;
        v[3] = ((((uint64_t)seed) - k1) * k3) + len;

        do {
            v[0] ^= _mm_crc32_u64(v[0], read_u64(ptr));
            ptr += 8;
            v[1] ^= _mm_crc32_u64(v[1], read_u64(ptr));
            ptr += 8;
            v[2] ^= _mm_crc32_u64(v[2], read_u64(ptr));
            ptr += 8;
            v[3] ^= _mm_crc32_u64(v[3], read_u64(ptr));
            ptr += 8;
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 12) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 19) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 12) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 19) * k0;
    }

    if ((end - ptr) >= 16) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 41) * k3;
        v[1] += read_u64(ptr) * k2;
        ptr += 8;
        v[1] = rotate_right(v[1], 41) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 10) * k1;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 10) * k0;
    }

    if ((end - ptr) >= 8) {
        v[0] += read_u64(ptr) * k2;
        ptr += 8;
        v[0] = rotate_right(v[0], 34) * k3;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 22) * k1;
    }

    if ((end - ptr) >= 4) {
        v[1] ^= _mm_crc32_u64(v[0], read_u32(ptr));
        ptr += 4;
        v[1] ^= rotate_right((v[1] * k3) + v[0], 14) * k0;
    }

    if ((end - ptr) >= 2) {
        v[0] ^= _mm_crc32_u64(v[1], read_u16(ptr));
        ptr += 2;
        v[0] ^= rotate_right((v[0] * k2) + v[1], 15) * k1;
    }

    if ((end - ptr) >= 1) {
        v[1] ^= _mm_crc32_u64(v[0], read_u8(ptr));
        v[1] ^= rotate_right((v[1] * k3) + v[0], 18) * k0;
    }

    v[0] += rotate_right((v[0] * k0) + v[1], 15);
    v[1] += rotate_right((v[1] * k1) + v[0], 27);
    v[0] += rotate_right((v[0] * k0) + v[1], 15);
    v[1] += rotate_right((v[1] * k1) + v[0], 27);

    memcpy(out, v, 16);
}

// metrohash64.cpp
//
// The MIT License (MIT)
//
// Copyright (c) 2015 J. Andrew Rogers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <metrohash.h>

void
metrohash64_1(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xC83A91E1;
    static const uint64_t k1 = 0x8648DBDB;
    static const uint64_t k2 = 0x7BDEC03B;
    static const uint64_t k3 = 0x2F5870A5;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t hash = ((((uint64_t)seed) + k2) * k0) + len;

    if (len >= 32) {
        uint64_t v[4];
        v[0] = hash;
        v[1] = hash;
        v[2] = hash;
        v[3] = hash;

        do {
            v[0] += read_u64(ptr) * k0;
            ptr += 8;
            v[0] = rotate_right(v[0], 29) + v[2];
            v[1] += read_u64(ptr) * k1;
            ptr += 8;
            v[1] = rotate_right(v[1], 29) + v[3];
            v[2] += read_u64(ptr) * k2;
            ptr += 8;
            v[2] = rotate_right(v[2], 29) + v[0];
            v[3] += read_u64(ptr) * k3;
            ptr += 8;
            v[3] = rotate_right(v[3], 29) + v[1];
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 33) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 33) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 33) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 33) * k0;
        hash += v[0] ^ v[1];
    }

    if ((end - ptr) >= 16) {
        uint64_t v0 = hash + (read_u64(ptr) * k0);
        ptr += 8;
        v0          = rotate_right(v0, 33) * k1;
        uint64_t v1 = hash + (read_u64(ptr) * k1);
        ptr += 8;
        v1 = rotate_right(v1, 33) * k2;
        v0 ^= rotate_right(v0 * k0, 35) + v1;
        v1 ^= rotate_right(v1 * k3, 35) + v0;
        hash += v1;
    }

    if ((end - ptr) >= 8) {
        hash += read_u64(ptr) * k3;
        ptr += 8;
        hash ^= rotate_right(hash, 33) * k1;
    }

    if ((end - ptr) >= 4) {
        hash += read_u32(ptr) * k3;
        ptr += 4;
        hash ^= rotate_right(hash, 15) * k1;
    }

    if ((end - ptr) >= 2) {
        hash += read_u16(ptr) * k3;
        ptr += 2;
        hash ^= rotate_right(hash, 13) * k1;
    }

    if ((end - ptr) >= 1) {
        hash += read_u8(ptr) * k3;
        hash ^= rotate_right(hash, 25) * k1;
    }

    hash ^= rotate_right(hash, 33);
    hash *= k0;
    hash ^= rotate_right(hash, 33);

    memcpy(out, &hash, 8);
}

void
metrohash64_2(const uint8_t* key, uint64_t len, uint32_t seed, uint8_t* out)
{
    static const uint64_t k0 = 0xD6D018F5;
    static const uint64_t k1 = 0xA2AA033B;
    static const uint64_t k2 = 0x62992FC1;
    static const uint64_t k3 = 0x30BC5B29;

    const uint8_t* ptr       = key;
    const uint8_t* const end = ptr + len;

    uint64_t hash = ((((uint64_t)seed) + k2) * k0) + len;

    if (len >= 32) {
        uint64_t v[4];
        v[0] = hash;
        v[1] = hash;
        v[2] = hash;
        v[3] = hash;

        do {
            v[0] += read_u64(ptr) * k0;
            ptr += 8;
            v[0] = rotate_right(v[0], 29) + v[2];
            v[1] += read_u64(ptr) * k1;
            ptr += 8;
            v[1] = rotate_right(v[1], 29) + v[3];
            v[2] += read_u64(ptr) * k2;
            ptr += 8;
            v[2] = rotate_right(v[2], 29) + v[0];
            v[3] += read_u64(ptr) * k3;
            ptr += 8;
            v[3] = rotate_right(v[3], 29) + v[1];
        } while (ptr <= (end - 32));

        v[2] ^= rotate_right(((v[0] + v[3]) * k0) + v[1], 30) * k1;
        v[3] ^= rotate_right(((v[1] + v[2]) * k1) + v[0], 30) * k0;
        v[0] ^= rotate_right(((v[0] + v[2]) * k0) + v[3], 30) * k1;
        v[1] ^= rotate_right(((v[1] + v[3]) * k1) + v[2], 30) * k0;
        hash += v[0] ^ v[1];
    }

    if ((end - ptr) >= 16) {
        uint64_t v0 = hash + (read_u64(ptr) * k2);
        ptr += 8;
        v0          = rotate_right(v0, 29) * k3;
        uint64_t v1 = hash + (read_u64(ptr) * k2);
        ptr += 8;
        v1 = rotate_right(v1, 29) * k3;
        v0 ^= rotate_right(v0 * k0, 34) + v1;
        v1 ^= rotate_right(v1 * k3, 34) + v0;
        hash += v1;
    }

    if ((end - ptr) >= 8) {
        hash += read_u64(ptr) * k3;
        ptr += 8;
        hash ^= rotate_right(hash, 36) * k1;
    }

    if ((end - ptr) >= 4) {
        hash += read_u32(ptr) * k3;
        ptr += 4;
        hash ^= rotate_right(hash, 15) * k1;
    }

    if ((end - ptr) >= 2) {
        hash += read_u16(ptr) * k3;
        ptr += 2;
        hash ^= rotate_right(hash, 15) * k1;
    }

    if ((end - ptr) >= 1) {
        hash += read_u8(ptr) * k3;
        hash ^= rotate_right(hash, 23) * k1;
    }

    hash ^= rotate_right(hash, 28);
    hash *= k0;
    hash ^= rotate_right(hash, 29);

    memcpy(out, &hash, 8);
}
