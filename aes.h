#pragma once

#include <inttypes.h>

extern const uint8_t sbox[256];
extern const uint8_t sbox_inv[256];

extern const uint8_t mix_col_matrix[4][4];
extern const uint8_t mix_col_inv[4][4];

extern const uint8_t round_consts[10];

void rotate_row(uint8_t row[4], uint8_t shift_amount);

void sub_bytes(uint8_t block[4][4]);
void shift_rows(uint8_t block[4][4]);
void mix_columns(uint8_t block[4][4]);
void add_round_key(uint8_t block[4][4], const uint8_t round_key[4][4]);

void sub_bytes_inv(u_int8_t block[4][4]);
void shift_rows_inv(uint8_t block[4][4]);
void mix_columns_inv(uint8_t block[4][4]);

void next_round_key(const uint8_t current[4][4], uint8_t next[4][4], uint8_t round);
void compute_round_keys(const uint8_t key[4][4], uint8_t round_keys[10][4][4]);

void encrypt(uint8_t block[4][4], const uint8_t key[4][4]);
void decrypt(uint8_t block[4][4], const uint8_t key[4][4]);
