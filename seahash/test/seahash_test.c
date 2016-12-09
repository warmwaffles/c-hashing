#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <seahash.h>

void
assert_no_state_seeded(const uint8_t* string, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t left  = seahash_seeded(string, strlen((const char*)string), a, b, c, d);
    uint64_t right = seahash_seeded(string, strlen((const char*)string), a, b, c, d);

    if (left == right) {
        return;
    }

    fprintf(stderr, "Hash failed to match string\n");
    fprintf(stderr, "  string = \"%s\"\n", string);
    fprintf(stderr, "  a      = 0x%lx\n", a);
    fprintf(stderr, "  b      = 0x%lx\n", b);
    fprintf(stderr, "  c      = 0x%lx\n", c);
    fprintf(stderr, "  d      = 0x%lx\n", d);
    fprintf(stderr, "  left   = 0x%lx\n", left);
    fprintf(stderr, "  right  = 0x%lx\n", right);
    fflush(stderr);

    abort();
}

void
assert_no_state(const uint8_t* string)
{
    assert_no_state_seeded(string, 0x16f11fe89b0d677cULL, 0xb480a793d8e6c86cULL, 0x6fe2e5aaf078ebc9ULL, 0x14f994a4c5259381ULL);
    assert_no_state_seeded(string, 1, 1, 1, 1);
    assert_no_state_seeded(string, 0, 0, 0, 0);
    assert_no_state_seeded(string, 500, 2873, 2389, 9283);
    assert_no_state_seeded(string, 238945723984, 872894734, 239478243, 28937498234);
}

void
assert_no_match(const char* a, const char* b)
{
    uint64_t left  = seahash((const uint8_t*)a, strlen(a));
    uint64_t right = seahash((const uint8_t*)b, strlen(b));

    if (left != right) {
        return;
    }

    fprintf(stderr, "Hash was found to be matching\n");
    fprintf(stderr, "  a     = \"%s\"\n", a);
    fprintf(stderr, "  b     = \"%s\"\n", b);
    fprintf(stderr, "  left  = 0x%lx\n", left);
    fprintf(stderr, "  right = 0x%lx\n", right);
    fflush(stderr);

    abort();
}

void
assert_match(const char* a, const char* b)
{
    uint64_t left  = seahash((const uint8_t*)a, strlen(a));
    uint64_t right = seahash((const uint8_t*)b, strlen(b));

    if (left == right) {
        return;
    }

    fprintf(stderr, "Hash was found NOT to be matching\n");
    fprintf(stderr, "  a     = \"%s\"\n", a);
    fprintf(stderr, "  b     = \"%s\"\n", b);
    fprintf(stderr, "  left  = 0x%lx\n", left);
    fprintf(stderr, "  right = 0x%lx\n", right);
    fflush(stderr);

    abort();
}

#define error_occurred(message)                                                                                                            \
    {                                                                                                                                      \
        fprintf(stderr, "ERROR: %s:%d | %s \n", __FILE__, __LINE__, (message));                                                            \
        fflush(stderr);                                                                                                                    \
        abort();                                                                                                                           \
    }

int
main(void)
{
    assert_match("to be or not to be", "to be or not to be");

    assert_no_match("to be or not to be ", "to be or not to be");
    assert_no_match("jkjke", "jkjk");
    assert_no_match("ijkjke", "ijkjk");
    assert_no_match("iijkjke", "iijkjk");
    assert_no_match("iiijkjke", "iiijkjk");
    assert_no_match("iiiijkjke", "iiiijkjk");
    assert_no_match("iiiiijkjke", "iiiiijkjk");
    assert_no_match("iiiiiijkjke", "iiiiiijkjk");
    assert_no_match("iiiiiiijkjke", "iiiiiiijkjk");
    assert_no_match("iiiiiiiijkjke", "iiiiiiiijkjk");
    assert_no_match("ab", "bb");

    {
        const uint8_t a[3] = { 0, 0, 0 };
        const uint8_t b[5] = { 0, 0, 0, 0, 0 };

        uint64_t left  = seahash(a, 3 * sizeof(uint8_t));
        uint64_t right = seahash(b, 5 * sizeof(uint8_t));

        if (left == right) {
            error_occurred("Hash was found to be zero sensitive");
        }
    }

    {
        const uint8_t a[4] = { 1, 2, 3, 4 };
        const uint8_t b[5] = { 1, 0, 2, 3, 4 };

        uint64_t left  = seahash(a, 4 * sizeof(uint8_t));
        uint64_t right = seahash(b, 5 * sizeof(uint8_t));

        if (left == right) {
            error_occurred("Hash was found to be zero sensitive");
        }
    }

    {
        const uint8_t a[4] = { 1, 2, 3, 4 };
        const uint8_t b[6] = { 1, 0, 0, 2, 3, 4 };

        uint64_t left  = seahash(a, 4 * sizeof(uint8_t));
        uint64_t right = seahash(b, 6 * sizeof(uint8_t));

        if (left == right) {
            error_occurred("Hash was found to be zero sensitive");
        }
    }

    {
        const uint8_t a[4] = { 1, 2, 3, 4 };
        const uint8_t b[5] = { 1, 2, 3, 4, 0 };

        uint64_t left  = seahash(a, 4 * sizeof(uint8_t));
        uint64_t right = seahash(b, 5 * sizeof(uint8_t));

        if (left == right) {
            error_occurred("Hash was found to be zero sensitive");
        }
    }

    return EXIT_SUCCESS;
}
