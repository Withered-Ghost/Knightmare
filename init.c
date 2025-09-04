#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

// transformation arrays
int SQ64_120[NUM_SQ]; // which sq from 64 if given an idx from 120
int SQ120_64[64];// which q from 120 if given an idx from 64

uint64_t setMask[64];
uint64_t clearMask[64];

uint64_t pceKeys[13][NUM_SQ]; // each pce on each sq
uint64_t sideKey;
uint64_t castleKeys[16]; // 16 unique castling permissions

void init_keys() {
    int idx = 0;
    int idx2 = 0;

    for(idx = 0; idx < 13; ++idx) {
        for(idx2 = 0; idx2 < 120; ++idx2) {
            pceKeys[idx][idx2] = random_uint64();
        }
    }

    sideKey = random_uint64();

    for(idx = 0; idx < 16; ++idx) {
        castleKeys[idx] = random_uint64();
    }
}

void init_masks() {
    int idx = 0;
    uint64_t mask = UINT64_C(1);

    for(idx = 0; idx < 64; ++idx) {
        setMask[idx] = UINT64_C(0);
        clearMask[idx] = UINT64_C(0);
    }

    for(idx = 0; idx < 64; ++idx) {
        setMask[idx] |= (mask << idx);
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

    for(idx = 0; idx < NUM_SQ; ++idx) SQ64_120[idx] = 64;
    for(idx = 0; idx < 64; ++idx) SQ120_64[idx] = 120;

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR_SQ120(file, rank);
            SQ120_64[sq64] = sq;
            SQ64_120[sq] = sq64;
            ++sq64;
        }
    }
}

// initialize all data structures
void init() {
    srand(80085u);
    init_transformation_arrays();
    init_masks();
    init_keys();
    return;
}
