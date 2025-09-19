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
    // int sq64 = 0;
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

    update_pos_stats(pos);

    return 0;
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
    printf("\n\n");
    printf("Side: %c\n", sideChar[pos->side]);
    printf("enPass: %d\n", pos->enPass);
    printf("Castle Perms: %c%c%c%c\n",
        pos->castlePerm & wK_short ? 'K' : '-',
        pos->castlePerm & wK_long ? 'Q' : '-',
        pos->castlePerm & bK_short ? 'k' : '-',
        pos->castlePerm & bK_long ? 'q' : '-'
    );
    printf("posHash: %#llx\n", pos->posHash);
}

void reset_board(S_BOARD *pos) {
    int idx = 0;

    for(idx = 0; idx < NUM_SQ; ++idx) {
        pos->brd120[idx] = NO_SQ;
        if(SQ64_120[idx] >= 0 && SQ64_120[idx] <= 63) {
            pos->brd120[idx] = EMPTY;
        }
    }
    // pceList remaining
    for(idx = 0; idx < 3; ++idx) {
        pos->pawns[idx] = UINT64_C(0);
    }

    for(idx = 0; idx < 13; ++idx) {
        pos->numPcs[idx] = 0;
    }

    for(idx = 0; idx < 2; ++idx) {
        pos->bigPcs[idx] = 0;
        pos->majPcs[idx] = 0;
        pos->minPcs[idx] = 0;
        pos->material[idx] = 0;
    }

    pos->kingSq[WHITE] = pos->kingSq[BLACK] = NO_SQ;

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

void update_pos_stats(S_BOARD *pos) {
    int pce = EMPTY;
    int sq120 = 0;
    int idx = 0;
    int clr = BOTH;

    for(idx = 0; idx < NUM_SQ; ++idx) {
        sq120 = idx;
        pce = pos->brd120[idx];

        if(pce != NO_SQ && pce != EMPTY) {
            clr = pceClr[pce];
            if(pceBig[pce] == TRUE) pos->bigPcs[clr]++;
            if(pceMaj[pce] == TRUE) pos->majPcs[clr]++;
            if(pceMin[pce] == TRUE) pos->minPcs[clr]++;

            pos->material[clr] += pceVal[pce];

            pos->pceList[pce][pos->numPcs[pce]] = sq120;
            pos->numPcs[pce]++;

            if(pce == wK || pce == bK) pos->kingSq[clr] = sq120;

            if(pce == wP || pce == bP) {
                SETBIT(pos->pawns[clr], SQ64_120[sq120]);
                SETBIT(pos->pawns[BOTH], SQ64_120[sq120]);
            }
        }
    }
}

int check_board(const S_BOARD *pos) {
    int t_numPcs[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int t_bigPcs[2] = { 0, 0 };
    int t_majPcs[2] = { 0, 0 };
    int t_minPcs[2] = { 0, 0 };
    int t_material[2] = { 0, 0 };

    uint64_t t_pawns[3] = { UINT64_C(0), UINT64_C(0), UINT64_C(0) };
    t_pawns[WHITE] = pos->pawns[WHITE];
    t_pawns[BLACK] = pos->pawns[BLACK];
    t_pawns[BOTH] = pos->pawns[BOTH];

    int sq64, sq120, t_pce, t_pce_num, clr, p_cnt;

    // check: pceList == brd120
    for(t_pce = wP; t_pce <= bK; ++t_pce) {
        // assume a pce, t_pce
        for(t_pce_num = 0; t_pce_num < pos->numPcs[t_pce]; ++t_pce_num) {
            // for each assumed pce existing on brd
            sq120 = pos->pceList[t_pce][t_pce_num];
            // get sq for assumed pce from pceList
            ASSERT(pos->brd120[sq120] == t_pce);
            // check if on that sq assumed pce exists
        }
    }

    // check: counters
    for(sq64 = 0; sq64 < 64; ++sq64) {
        sq120 = SQ120_64[sq64];
        t_pce = pos->brd120[sq120];
        clr = pceClr[t_pce];

        t_numPcs[t_pce]++;
        if(pceBig[t_pce] == TRUE) t_bigPcs[clr]++;
        if(pceMaj[t_pce] == TRUE) t_majPcs[clr]++;
        if(pceMin[t_pce] == TRUE) t_minPcs[clr]++;
        t_material[clr] += pceVal[t_pce];
    }

    for(t_pce = wP; t_pce <= bK; ++t_pce) {
        ASSERT(t_numPcs[t_pce] == pos->numPcs[t_pce]);
    }

    ASSERT((t_bigPcs[WHITE] == pos->bigPcs[WHITE]) && (t_bigPcs[BLACK] == pos->bigPcs[BLACK]));
    ASSERT((t_majPcs[WHITE] == pos->majPcs[WHITE]) && (t_majPcs[BLACK] == pos->majPcs[BLACK]));
    ASSERT((t_minPcs[WHITE] == pos->minPcs[WHITE]) && (t_minPcs[BLACK] == pos->minPcs[BLACK]));
    ASSERT((t_material[WHITE] == pos->material[WHITE]) && (t_material[BLACK] == pos->material[BLACK]));

    // check: pawn bitboards
    p_cnt = count_bits(t_pawns[WHITE]);
    ASSERT(p_cnt == pos->numPcs[wP]);
    p_cnt = count_bits(t_pawns[BLACK]);
    ASSERT(p_cnt == pos->numPcs[bP]);
    p_cnt = count_bits(t_pawns[BOTH]);
    ASSERT(p_cnt == (pos->numPcs[wP] + pos->numPcs[bP]));

    while(t_pawns[WHITE]) {
        sq64 = pop_bit(&t_pawns[WHITE]);
        ASSERT(pos->brd120[SQ120_64[sq64]] == wP);
    }
    while(t_pawns[BLACK]) {
        sq64 = pop_bit(&t_pawns[BLACK]);
        ASSERT(pos->brd120[SQ120_64[sq64]] == bP);
    }
    while(t_pawns[BOTH]) {
        sq64 = pop_bit(&t_pawns[BOTH]);
        ASSERT((pos->brd120[SQ120_64[sq64]] == wP) || (pos->brd120[SQ120_64[sq64]] == bP));
    }

    // check: remaining
    ASSERT(pos->brd120[pos->kingSq[WHITE]] == wK);
    ASSERT(pos->brd120[pos->kingSq[BLACK]] == bK);

    ASSERT((pos->side == WHITE) || (pos->side == BLACK));
    ASSERT(pos->enPass == NO_SQ || (pos->side == WHITE && RANK_120[pos->enPass] == RANK_6) || (pos->side == BLACK && RANK_120[pos->enPass] == RANK_3));
    // ASSERT(pos->fiftyMove >= 0 && pos->fiftyMove <= 50);
    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);

    ASSERT(calc_pos_hash(pos) == pos->posHash);

    return TRUE;
}
