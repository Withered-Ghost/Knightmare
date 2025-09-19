#include "board.h"
#include "functions.h"
#include "data.h"
#include "macros.h"

int SQ64_120[NUM_SQ]; // which sq from 64 if given an idx from 120
int SQ120_64[64];// which q from 120 if given an idx from 64

uint64_t setMask[64];
uint64_t clearMask[64];

uint64_t pceKeys[13][NUM_SQ]; // each pce on each sq
uint64_t sideKey;
uint64_t castleKeys[16]; // 16 unique castling permissions

int FILE_120[NUM_SQ];
int RANK_120[NUM_SQ];

const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33,
    15, 50, 42, 13, 11, 53, 19, 34,
    61, 29, 2, 51, 21, 43, 45, 10,
    18, 47, 1, 54, 9, 57, 0, 35,
    62, 31, 40, 4, 49, 5, 52, 26,
    60, 6, 23, 44, 46, 27, 56, 16,
    7, 39, 48, 24, 59, 14, 12, 55,
    38, 28, 58, 20, 37, 17, 36, 8
};

char pceChar[] = ".PNBRQKpnbrqk";
char fileChar[] = "abcdefgh";
char rankChar[] = "12345678";
char sideChar[] = "wb-";

int pceBig[13] = { FALSE,
    FALSE, TRUE, TRUE, TRUE, TRUE, TRUE,
    FALSE, TRUE, TRUE, TRUE, TRUE, TRUE
};
int pceMaj[13] = { FALSE,
    FALSE, FALSE, FALSE, TRUE, TRUE, TRUE,
    FALSE, FALSE, FALSE, TRUE, TRUE, TRUE
};
int pceMin[13] = { FALSE,
    FALSE, TRUE, TRUE, FALSE, FALSE, FALSE,
    FALSE, TRUE, TRUE, FALSE, FALSE, FALSE
};
int pceVal[13] = { 0,
    100, 300, 300, 500, 900, 10000,
    100, 300, 300, 500, 900, 10000
};
int pceClr[13] = { BOTH,
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK
};

const int nDir[8] = { -21, -19, -12, -8, 8, 12, 19, 21 };
const int rDir[4] = { -10, -1, 1, 10 };
const int bDir[4] = { -11, -9, 9, 11 };
const int qDir[8] = { -11, -10, -9, -1, 1, 9, 10, 11 };
