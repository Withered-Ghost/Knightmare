#include <stdlib.h>
#include "board.h"
#include "functions.h"
#include "data.h"
#include "macros.h"

uint64_t random_uint64() {
    uint64_t u1, u2, u3, u4, u5;
    u1 = (uint64_t)(rand()) & 0x7fff;
    u2 = (uint64_t)(rand()) & 0x7fff;
    u3 = (uint64_t)(rand()) & 0x7fff;
    u4 = (uint64_t)(rand()) & 0x7fff;
    u5 = (uint64_t)(rand()) & 0xf;
    // rand() returns 15-bit random number

    return u1 | (u2 << 15) | (u3 << 30) | (u4 << 45) | (u5 << 60);
}

uint64_t calc_pos_hash(const S_BOARD *pos) {
    int sq120 = 0;
    uint64_t posHash = UINT64_C(0);
    int pce = EMPTY;

    for(sq120 = 0; sq120 < NUM_SQ; ++sq120) {
        pce = pos->brd120[sq120];
        if(pce != NO_SQ && pce != EMPTY) {
            // if pce is in mail and pce != empty
            ASSERT(pce >= wP && pce <= bK);
            // then pce must exist on that sq
            posHash ^= pceKeys[pce][sq120];
            // xor key of pce on sq
        }
    }

    if(pos->enPass != NO_SQ) {
        // if enpass is possible
        ASSERT(SQ64_120[pos->enPass] >= 0 && SQ64_120[pos->enPass] <= 63);
        // then it should be on the board
        posHash ^= pceKeys[EMPTY][pos->enPass];
        // xor empty pce on enpass sq
    }

    if(pos->side == WHITE) posHash ^= sideKey;

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);
    posHash ^= castleKeys[pos->castlePerm];

    return posHash;
}
