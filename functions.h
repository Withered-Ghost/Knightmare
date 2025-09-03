#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// init.c
extern void init();

// bitboards.c
extern void print_bitboard(uint64_t bb);
extern int pop_bit(uint64_t *bb);
extern int count_bits(uint64_t bb);

// utils.c
extern uint64_t random_uint64();
extern uint64_t calc_pos_hash(const S_BOARD *pos);

#endif
