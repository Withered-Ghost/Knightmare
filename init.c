#include "board.h"
#include "functions.h"
#include "data.h"
#include "macros.h"

void init_transformation_arrays() {
    int idx = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq120 = NO_SQ;
    int sq64 = 0; // cheating

    for(idx = 0; idx < NUM_SQ; ++idx) SQ64_120[idx] = 64;
    for(idx = 0; idx < 64; ++idx) SQ120_64[idx] = 120;

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq120 = FR_SQ120(file, rank);
            SQ120_64[sq64] = sq120;
            SQ64_120[sq120] = sq64;
            ++sq64;
        }
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

void init_file_rank_arrays() {
    int idx = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq120 = A1;

    for(idx = 0; idx < NUM_SQ; ++idx) {
        FILE_120[idx] = NO_SQ;
        RANK_120[idx] = NO_SQ;
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq120 = FR_SQ120(file, rank);
            FILE_120[sq120] = file;
            RANK_120[sq120] = rank;
        }
    }
}

// initialize all data structures
void init() {
    srand(80085u);
    init_transformation_arrays();
    init_masks();
    init_keys();
    init_file_rank_arrays();
    return;
}
