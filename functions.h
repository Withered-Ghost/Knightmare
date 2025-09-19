#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// init.c
extern void init_transformation_arrays();
extern void init_masks();
extern void init_keys();
extern void init_file_rank_arrays();
extern void init();

// bitboards.c
extern int pop_bit(uint64_t *bb);
extern int count_bits(uint64_t bb);
extern void print_bitboard(uint64_t bb);

// utils.c
extern uint64_t random_uint64();
extern uint64_t calc_pos_hash(const S_BOARD *pos);

// board.c
extern int parse_fen(char *fen, S_BOARD *pos);
extern void print_board(const S_BOARD *pos);
extern void reset_board(S_BOARD *pos);
extern void update_pos_stats(S_BOARD *pos);
extern int check_board(const S_BOARD *pos);

#endif
