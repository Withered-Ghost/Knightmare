#include <stdio.h>
#include "board.h"
#include "functions.h"
#include "globals.h"

int main() {
    // initialize everything
    init();

    for(int i = 0; i < NUM_SQ; ++i) {
        if(i % 10 == 0) printf("\n");
        printf("%5d", SQ120_SQ64[i]);
    }
    printf("\n\n");
    for(int i = 0; i < 64; ++i) {
        if(i % 8 == 0) printf("\n");
        printf("%5d", SQ64_SQ120[i]);
    }

    return 0;
}
