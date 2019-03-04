#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bit_array.h"
#include "error.h"

#ifdef USE_INLINE
extern inline void bit_array_free(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, unsigned long vyraz);
extern inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);
#endif

extern void Eratosthenes(bit_array_t pole);

#define LIMIT 123000000L

int main(void) {
    bit_array_alloc(primes, LIMIT);
    Eratosthenes(primes);

    unsigned long lastTen[10];
    unsigned long prime;

    for (unsigned long j = 0, i = LIMIT - 1; j < 10; i--) {
        prime = bit_array_getbit(primes, i);
        if (prime == 0) {
            lastTen[j] = i;
            j++;
        }
    }

    for (int i = 9; i >= 0; i--) {
        printf("%lu\n", lastTen[i]);
    }

    bit_array_free(primes);
    return 0;
}
