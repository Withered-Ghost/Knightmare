#ifndef GLOBALS_H
#define GLOBALS_H

// init.c
extern int SQ64[NUM_SQ];
extern int SQ120[64];

extern uint64_t setMask[64];
extern uint64_t clearMask[64];

extern uint64_t pceKeys[13][120];
extern uint64_t sideKey;
extern uint64_t castleKeys[16];

#endif
