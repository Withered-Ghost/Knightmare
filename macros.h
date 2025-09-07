#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>
#include <stdio.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) {\
printf("%s - FAILED: ", #n);\
printf("%s %s ", __DATE__, __TIME__);\
printf("in %s:%d", __FILE__, __LINE__);\
exit(EXIT_FAILURE);\
}
#endif
// # to stringize the macro args
// ## to concatenate macro tokens

// transformation macros
#define FR_SQ120(f, r) ((f) + 21 + ((r) * 10))
// #define SQ120_FILE(sq120) (((sq120) - 21) % 10)
// #define SQ120_RANK(sq120) (((sq120) - 21) / 10)
#define IDX_SQ120(i) ((i) + 21 + (2 * ((i) >> 3)))

#define SETBIT(bb, sq64) ((bb) |= setMask[(sq64)])
#define CLRBIT(bb, sq64) ((bb) &= clearMask[(sq64)])
// can use TGLBIT() bb ^= setMask[sq64] for setting and clearing
// but on repeated ops, bb will change
// & | ensure that bb will stay unchanged on repeated ops

#endif
