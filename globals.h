#ifndef GLOBALS_H
#define GLOBALS_H

// init.c
extern int SQ64_120[NUM_SQ];
extern int SQ120_64[64];

extern uint64_t setMask[64];
extern uint64_t clearMask[64];

extern uint64_t pceKeys[13][120];
extern uint64_t sideKey;
extern uint64_t castleKeys[16];

// data.c
extern char pceChar[];
extern char fileChar[];
extern char rankChar[];
extern char sideChar[];

#endif
