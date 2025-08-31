#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

// transformation arrays
int SQ64[NUM_SQ];
int SQ120[64];

uint64_t setMask[64];
uint64_t clearMask[64];

void init_masks() {
    int idx = 0;
    uint64_t mask = UINT64_C(1);

    for(idx = 0; idx < 64; ++idx) {
        setMask[idx] = (mask << idx);
        clearMask[idx] = ~setMask[idx];
    }
}

// initialize transformation arrays
void init_transformation_arrays() {
    int idx = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = NO_SQ;
    int sq64 = 0; // cheating

    for(idx = 0; idx < NUM_SQ; ++idx) SQ64[idx] = 64;
    for(idx = 0; idx < 64; ++idx) SQ120[idx] = 120;

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR_SQ120(file, rank);
            SQ120[sq64] = sq;
            SQ64[sq] = sq64;
            ++sq64;
        }
    }
}

// initialize all data structures
void init() {
    init_transformation_arrays();
    init_masks();
    return;
}
