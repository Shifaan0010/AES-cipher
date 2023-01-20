#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "aes.h"

// void print_block(uint8_t block[4][4])
// {
//     for (int r = 0; r < 4; r += 1)
//     {
//         for (int c = 0; c < 4; c += 1)
//         {
//             printf("%02x ", block[r][c]);
//         }
//         printf("\n");
//     }
// }

// void transpose(uint8_t block[4][4])
// {
//     for (int r = 0; r < 4; r += 1)
//     {
//         for (int c = 0; c <= r; c += 1)
//         {
//             int temp = block[r][c];
//             block[r][c] = block[c][r];
//             block[c][r] = temp;
//         }
//     }
// }

int main()
{
    char key_str[256];
    printf("Enter 16 byte (128 bit) cipher key in utf-8: ");
    scanf(" %s", key_str);

    if (strlen(key_str) != 16)
    {
        printf("Key needs to be exactly 16 bytes in size\n");
        exit(1);
    }

    char msg_str[1024];
    printf("Enter message encoded in utf-8 (len needs to be a multiple of 16): ");
    scanf(" %[^\n]", msg_str);

    int msg_len = strlen(msg_str);
    if (msg_len % 16 != 0)
    {
        printf("Message len needs to be a multiple of 16\n");
        exit(1);
    }

    uint8_t key[4][4];
    uint8_t block[4][4];

    uint8_t enc_msg[1024];
    char dec_msg[1024];

    dec_msg[msg_len] = '\0';

    for (int r = 0; r < 4; r += 1)
    {
        for (int c = 0; c < 4; c += 1)
        {
            key[c][r] = key_str[4 * r + c];
        }
    }

    for (int i = 0; i < msg_len / 16; i += 1)
    {
        for (int r = 0; r < 4; r += 1)
        {
            for (int c = 0; c < 4; c += 1)
            {
                block[c][r] = msg_str[16 * i + 4 * r + c];
            }
        }

        encrypt(block, key);

        for (int r = 0; r < 4; r += 1)
        {
            for (int c = 0; c < 4; c += 1)
            {
                enc_msg[16 * i + 4 * r + c] = block[c][r];
            }
        }

        decrypt(block, key);

        for (int r = 0; r < 4; r += 1)
        {
            for (int c = 0; c < 4; c += 1)
            {
                dec_msg[16 * i + 4 * r + c] = block[c][r];
            }
        }
    }

    printf("\nEncrypted Message (hex): ");
    for (int i = 0; i < msg_len; i += 1)
    {
        printf("%02x ", enc_msg[i]);
    }
    printf("\n");

    printf("\nDecrypted Message: %s\n", dec_msg);
}
