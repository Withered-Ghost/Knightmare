#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>

#define NAME "ChessBot v1.0"
#define BRD_SQ_NUM 120

// anonymous enums
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK }; // pieces
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE }; // files
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE }; // ranks
enum { WHITE, BLACK, BOTH }; // colors

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
}; // board

enum { FALSE, TRUE };

typedef struct {
    int pcs[BRD_SQ_NUM]; // board, which sq which pc
    uint64_t pawns[3]; // bitmap of pawns on board of both colors

    int KingSqs[2]; // pos of Kings

    int side; // whose turn
    int enPass; // track en passant sqr
    int fiftyMove; // 50 moves w/o any captures/pawn moves, then draw

    int ply;
    int histPly;

    uint64_t posHash;

    int numPcs[13]; // how many of each pc on board

    // all color-wise
    int bicPcs[3]; // anything not a pawn
    int majPcs[3]; // rooks, queens
    int minPcs[3]; // bishops, knights

} S_BOARD;

#endif
