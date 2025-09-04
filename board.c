#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

void reset_board(S_BOARD *pos) {
    int idx = 0;

    for(idx = 0; idx < NUM_SQ; ++idx) {
        pos->brd120[idx] = NO_SQ;
        if(SQ64_120[idx] != 64) {
            pos->brd120[idx] = EMPTY;
        }
    }

    for(idx = 0; idx < 3; ++idx) {
        pos->pawns[idx] = UINT64_C(0);
        pos->bigPcs[idx] = 0;
        pos->majPcs[idx] = 0;
        pos->minPcs[idx] = 0;
    }

    for(idx = 0; idx < 13; ++idx) {
        pos->numPcs[idx] = 0;
    }

    pos->kingSqs[WHITE] = pos->kingSqs[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPass = NO_SQ;
    pos->fiftyMove = 0;
    pos->castlePerm = 0;

    pos->ply = 0;
    pos->histPly = 0;

    pos->posHash = UINT64_C(0);

    for(idx = 0; idx < MAX_GAME_MOVES; ++idx) {
        pos->history[idx].move = 0;
        pos->history[idx].enPass = 0;
        pos->history[idx].fiftyMove = 0;
        pos->history[idx].castlePerm = 0;
        pos->history[idx].posHash = UINT64_C(0);
    }
}
