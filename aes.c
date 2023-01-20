#include <inttypes.h>
#include <stdio.h>

#include "aes.h"

void encrypt(uint8_t block[4][4], const uint8_t key[4][4])
{
    uint8_t round_keys[10][4][4];
    compute_round_keys(key, round_keys);

    add_round_key(block, key);

    for (int i = 0; i < 9; i += 1)
    {
        sub_bytes(block);
        shift_rows(block);
        mix_columns(block);
        add_round_key(block, round_keys[i]);
    }

    sub_bytes(block);
    shift_rows(block);
    add_round_key(block, round_keys[9]);
}

void decrypt(uint8_t block[4][4], const uint8_t key[4][4])
{
    uint8_t round_keys[10][4][4];
    compute_round_keys(key, round_keys);

    add_round_key(block, round_keys[9]);
    shift_rows_inv(block);
    sub_bytes_inv(block);

    for (int i = 0; i < 9; i += 1)
    {
        add_round_key(block, round_keys[9 - i - 1]);
        mix_columns_inv(block);
        shift_rows_inv(block);
        sub_bytes_inv(block);
    }

    add_round_key(block, key);
}
