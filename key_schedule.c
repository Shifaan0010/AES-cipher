#include <inttypes.h>

#include "aes.h"

const uint8_t round_consts[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

void add_round_key(uint8_t block[4][4], const uint8_t round_key[4][4])
{
    for (int r = 0; r < 4; r += 1)
    {
        for (int c = 0; c < 4; c += 1)
        {
            block[r][c] ^= round_key[r][c];
        }
    }
}

void next_round_key(const uint8_t current[4][4], uint8_t next[4][4], uint8_t round)
{
    uint8_t col[4];

    for (int r = 0; r < 4; r += 1)
    {
        col[r] = current[r][3];
    }

    rotate_row(col, 3);

    for (int i = 0; i < 4; i += 1)
    {
        col[i] = sbox[col[i]];
    }

    col[0] ^= round_consts[round];
    for (int r = 0; r < 4; r += 1)
    {
        next[r][0] = current[r][0] ^ col[r];
    }

    for (int c = 1; c < 4; c += 1)
    {
        for (int r = 0; r < 4; r += 1)
        {
            next[r][c] = current[r][c] ^ next[r][c - 1];
        }
    }
}

void compute_round_keys(const uint8_t key[4][4], uint8_t round_keys[10][4][4])
{
    for (int i = 0; i < 10; i += 1)
    {
        next_round_key((i == 0) ? key : (const uint8_t(*)[4])round_keys[i - 1], round_keys[i], i);
    }
}
