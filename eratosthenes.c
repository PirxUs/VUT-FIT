
#include "bit_array.h"
#include "error.h"

#define LIMIT 123000000

void Eratosthenes(bit_array_t pole) {
    for (unsigned long i = 2; i < LIMIT; i++) {
        if (bit_array_getbit(pole, i) == 0) {
            for (unsigned long j = 2 * i; j < LIMIT; j += i) {
                bit_array_setbit(pole, j, 1);
            }
        }
    }
}
