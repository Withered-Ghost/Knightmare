#include "board.h"
#include "macros.h"

// transformation arrays
int SQ120_SQ64[NUM_SQ];
int SQ64_SQ120[64];

// initialize transformation arrays
void init_transformation_arrays() {
    int idx = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0; // cheating

    for(idx = 0; idx < NUM_SQ; ++idx) SQ120_SQ64[idx] = 64;
    for(idx = 0; idx < 64; ++idx) SQ64_SQ120[idx] = 120;

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = FR_SQ120(file, rank);
            SQ64_SQ120[sq64] = sq;
            SQ120_SQ64[sq] = sq64;
            ++sq64;
        }
    }
}

// initialize all data structures
void init() {
    init_transformation_arrays();
    return;
}
