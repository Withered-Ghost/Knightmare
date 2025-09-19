#ifndef DATA_H
#define DATA_H

extern int SQ64_120[NUM_SQ];
extern int SQ120_64[64];

extern uint64_t setMask[64];
extern uint64_t clearMask[64];

extern uint64_t pceKeys[13][NUM_SQ];
extern uint64_t sideKey;
extern uint64_t castleKeys[16];

extern int FILE_120[NUM_SQ];
extern int RANK_120[NUM_SQ];

extern const int BitTable[64];

extern char pceChar[];
extern char fileChar[];
extern char rankChar[];
extern char sideChar[];

extern int pceBig[13];
extern int pceMaj[13];
extern int pceMin[13];
extern int pceVal[13];
extern int pceClr[13];

extern const int nDir[8];
extern const int rDir[4];
extern const int bDir[4];
extern const int qDir[8];

#endif
