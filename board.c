#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "globals.h"
#include "macros.h"

int parse_fen(char *fen, S_BOARD *pos) {
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = RANK_8;
    int file = FILE_A;
    int pce = EMPTY;
    int count = 0;
    int i = 0;
    int sq64 = 0;
    int sq120 = 0;

    reset_board(pos);

    while((rank >= RANK_1) && *fen) {
        count = 1;
        switch(*fen) {
            case 'p': pce = bP; break;
            case 'r': pce = bR; break;
            case 'n': pce = bN; break;
            case 'b': pce = bB; break;
            case 'q': pce = bQ; break;
            case 'k': pce = bK; break;
            case 'P': pce = wP; break;
            case 'R': pce = wR; break;
            case 'N': pce = wN; break;
            case 'B': pce = wB; break;
            case 'Q': pce = wQ; break;
            case 'K': pce = wK; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                pce = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                --rank;
                file = FILE_A;
                ++fen;
                continue;

            default:
                printf("Error parsing FEN");
                return 1;
        }

        for(i = 0; i < count; ++i, ++file) {
            sq120 = FR_SQ120(file, rank);
            // sq64 = SQ64_120[sq120];
            if(pce != EMPTY) {
                pos->brd120[sq120] = pce;
            }
        }
        ++fen;
    }

    ASSERT(*fen == 'w' || *fen == 'b');
    pos->side = (*fen == 'w') ? WHITE : BLACK;

    fen += 2;

    for(i = 0; i < 4 && *fen != ' '; ++i, ++fen) {
        switch(*fen) {
            case 'K': pos->castlePerm |= wK_short; break;
            case 'Q': pos->castlePerm |= wK_long; break;
            case 'k': pos->castlePerm |= bK_short; break;
            case 'q': pos->castlePerm |= bK_long; break;

            default: break;
        }
    }
    ++fen;
    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    if(*fen != '-') {
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= FILE_A && file <= FILE_H);
        ASSERT(rank == RANK_3 || rank <= RANK_6);

        pos->enPass = FR_SQ120(file, rank);
    }

    pos->posHash = calc_pos_hash(pos);

    return 0;
}

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

void print_board(const S_BOARD *pos) {
    int sq120 = 0;
    int file = FILE_NONE;
    int rank = RANK_NONE;
    int pce = EMPTY;

    printf("\nGame Board:\n\n");

    for(rank = RANK_8; rank >= RANK_1; --rank) {
        printf("%d  ", rank+1);
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq120 = FR_SQ120(file, rank);
            pce = pos->brd120[sq120];
            printf("%3c", pceChar[pce]);
        }
        printf("\n");
    }
    printf("\n   ");
    for(file = FILE_A; file <= FILE_H; ++file) {
        printf("%3c", 'a'+file);
    }
    printf("\n");
    printf("Side: %c\n", sideChar[pos->side]);
    printf("enPass: %d\n", pos->enPass);
    printf("Castle Perms: %c%c%c%c\n",
        pos->castlePerm & wK_short ? 'K' : '-',
        pos->castlePerm & wK_long ? 'Q' : '-',
        pos->castlePerm & bK_short ? 'k' : '-',
        pos->castlePerm & bK_long ? 'q' : '-'
    );
    printf("posHash: %llX\n", pos->posHash);
}
