#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

// #define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
// #define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
// #define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main() {
    // initialize everything
    init();

    // for(int i = 0; i < NUM_SQ; ++i) {
    //     if(i % 10 == 0) printf("\n");
    //     printf("%5d", SQ64[i]);
    // }
    // printf("\n\n");
    // for(int i = 0; i < 64; ++i) {
    //     if(i % 8 == 0) printf("\n");
    //     printf("%5d", SQ120[i]);
    // }

    // S_BOARD brd;

    // parse_fen(START_FEN, &brd);
    // print_board(&brd);
    // parse_fen(FEN1, &brd);
    // print_board(&brd);
    // parse_fen(FEN2, &brd);
    // print_board(&brd);
    // parse_fen(FEN3, &brd);
    // print_board(&brd);

    return 0;
}
