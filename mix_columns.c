#include <inttypes.h>
#include <memory.h>

#include "aes.h"

const uint8_t mix_col_matrix[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02},
};

const uint8_t mix_col_matrix_inv[4][4] = {
    {0x0e, 0x0b, 0x0d, 0x09},
    {0x09, 0x0e, 0x0b, 0x0d},
    {0x0d, 0x09, 0x0e, 0x0b},
    {0x0b, 0x0d, 0x09, 0x0e},
};

const uint16_t mix_col_mod = 0x11b;

uint16_t finite_field_multiply(uint8_t a, uint8_t b)
{
    uint16_t res = 0;
    for (int i = 0; i < 8; i += 1)
    {
        if (a & 1)
        {
            res ^= ((uint16_t)b << i);
        }
        a >>= 1;
    }
    return res;
}

int count_bits(uint16_t n)
{
    int count = 0;
    while (n > 0)
    {
        n >>= 1;
        count += 1;
    }
    return count;
}

uint16_t finite_field_modulo(uint16_t n, uint16_t mod)
{
    int n_size = count_bits(n);
    int mod_size = count_bits(mod);
    while (n_size >= mod_size)
    {
        uint16_t xor = n ^ (mod << (n_size - mod_size));
        if (xor < n)
        {
            n = xor;
        }
        n_size -= 1;
    }
    return n;
}

void matrix_multiply(const uint8_t a[4][4], const uint8_t b[4][4], uint8_t res[4][4])
{
    memset(res, 0, 4 * 4);
    for (int r = 0; r < 4; r += 1)
    {
        for (int c = 0; c < 4; c += 1)
        {
            uint16_t prod = 0;
            for (int i = 0; i < 4; i += 1)
            {
                prod ^= finite_field_multiply(a[r][i], b[i][c]);
                // printf("%02x * %02x\n", a[r][i], b[i][c]);
            }
            res[r][c] = (uint8_t)finite_field_modulo(prod, mix_col_mod);
            // printf("b[%d][%d] = %02x\n", r, c, res[r][c]);
        }
    }
}

void mix_columns(uint8_t block[4][4])
{
    uint8_t res[4][4];
    matrix_multiply(mix_col_matrix, block, res);
    memcpy(block, res, 4 * 4 * sizeof(uint8_t));
}

void mix_columns_inv(uint8_t block[4][4])
{
    uint8_t res[4][4];
    matrix_multiply(mix_col_matrix_inv, block, res);
    memcpy(block, res, 4 * 4 * sizeof(uint8_t));
}
