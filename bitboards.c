#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

// https://www.chessprogramming.org/BitScan
// https://en.wikipedia.org/wiki/De_Bruijn_sequence#Finding_least-_or_most-significant_set_bit_in_a_word
// https://www.reddit.com/r/learnprogramming/comments/v5wrlh/where_do_these_arrays_and_numbers_come_from/

// Source: https://www.chessprogramming.org/Looking_for_Magics
// ***** BEGIN *****
// De Bruijn Sequence + Matt Taylor's folding trick
const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

int pop_bit(uint64_t *bb) {
    uint64_t b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return BitTable[(fold * 0x783a9b23) >> 26];
}
// ****** END ******

int count_bits(uint64_t bb) {
    int cnt;
    for(cnt = 0; bb; ++cnt, bb &= bb-1);
    // i & i-1 removes LS1B
    return cnt;
}

void print_bitboard(uint64_t bb) {
    uint64_t mask = 1;
    int rank = RANK_1;
    int file = FILE_A;
    int sq = NO_SQ;
    int sq64 = 0;
    // bb |= (UINT64_C(1) << SQ64[A1]);

    printf("\n");

    for(rank = RANK_8; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR_SQ120(file, rank);
            sq64 = SQ64[sq];
            if((mask << sq64) & bb) {
                printf("1");
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}
