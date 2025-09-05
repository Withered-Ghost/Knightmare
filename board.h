#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define NAME "Knightmare v1.0"
#define NUM_SQ 120

#define MAX_GAME_MOVES 2048 // 2048 plies

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
// Board toMove castlePerms enPass fiftyMove moveNum
// (*/*)  w/b     KQkq/-      sq/-    num      num

// pieces
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
// files
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
// ranks
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
// colors
enum { WHITE, BLACK, BOTH };

// board
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8,
    NO_SQ
};

enum { FALSE, TRUE };

// castling permissions
enum { wK_short = 1, wK_long = 2, bK_short = 4, bK_long = 8 };

// move
typedef struct {
    int move;
    int enPass;
    int fiftyMove;
    int castlePerm;
    uint64_t posHash;
} S_MOVE;

// hybrid board representation
// pce list + bitboard(pawns) + 10x20 mailbox
typedef struct {
    int brd120[NUM_SQ]; // board, which sq which pc

    // all color-wise
    uint64_t pawns[3]; // bitmap of pawns on board of both colors
    int bigPcs[3]; // anything not a pawn
    int majPcs[3]; // rooks, queens
    int minPcs[3]; // bishops, knights
    int numPcs[13]; // how many of each pc on board

    // faster than looping thru lots of empty squares
    // piece list: pce type, num of pcs (max is 10, eg. 2 rooks + 8 promoted pawns)
    int pceList[13][10]; // default val is NO_SQ

    int kingSqs[2]; // pos of Kings

    int side; // whose turn
    int enPass; // track en passant sqr
    int fiftyMove; // 50 moves w/o any captures/pawn moves, then draw
    int castlePerm;

    int ply;
    int histPly;

    uint64_t posHash;

    S_MOVE history[MAX_GAME_MOVES]; // store move history
} S_BOARD;

#endif
