#include <inttypes.h>
#include <memory.h>

#include "aes.h"

void rotate_row(uint8_t row[4], uint8_t shift_amount)
{
    uint8_t temp[4];
    for (int i = 0; i < 4; i += 1)
    {
        temp[(i + shift_amount) % 4] = row[i];
    }
    memcpy(row, temp, 4 * sizeof(uint8_t));
}

void shift_rows(uint8_t block[4][4])
{
    for (int r = 0; r < 4; r += 1)
    {
        rotate_row(block[r], 4 - r);
    }
}

void shift_rows_inv(uint8_t block[4][4])
{
    for (int r = 0; r < 4; r += 1)
    {
        rotate_row(block[r], r);
    }
}
