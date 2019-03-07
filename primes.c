#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "error.h"
#include "bit_array.h"
#include "eratosthenes.h"

#define LIMIT 123000000L

int main(void) {
    bit_array_alloc(primes, LIMIT);
    //bit_array_create(primes, LIMIT);
    Eratosthenes(primes);

    unsigned long lastTen[10] = {0};

    for (unsigned long j = 0, i = LIMIT - 1; j < 10; i--) {
        if (!bit_array_getbit(primes, i)) {
            lastTen[j] = i;
            j++;
        }
        if (i == 0)
            break;
    }

    for (int i = 9; i >= 0; i--) {
    	if (lastTen[i] == 0)
            continue;
        printf("%lu\n", lastTen[i]);
    }

    bit_array_free(primes);
    return 0;
}
