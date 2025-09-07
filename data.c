#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

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
