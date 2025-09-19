#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "data.h"
#include "macros.h"

// https://www.chessprogramming.org/BitScan
// https://en.wikipedia.org/wiki/De_Bruijn_sequence#Finding_least-_or_most-significant_set_bit_in_a_word
// https://www.reddit.com/r/learnprogramming/comments/v5wrlh/where_do_these_arrays_and_numbers_come_from/

// Source: https://www.chessprogramming.org/Looking_for_Magics
// ***** BEGIN *****
// De Bruijn Sequence + Matt Taylor's folding trick
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
    int sq120 = NO_SQ;
    int sq64 = 0;
    // bb |= (UINT64_C(1) << SQ64[A1]);

    printf("\n");

    for(rank = RANK_8; rank >= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq120 = FR_SQ120(file, rank);
            sq64 = SQ64_120[sq120];
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
