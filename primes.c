/**
 *	@file	primes.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Program nalezne prvocisla na zadanem intervalu a poslednich deset vytiskne na standardni vystup.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "error.h"
#include "bit_array.h"
#include "eratosthenes.h"

//velikost bitoveho pole
#define LIMIT 123000000LU

int main(void) {
    bit_array_alloc(primes, LIMIT);
    //bit_array_create(primes, LIMIT);
    
    Eratosthenes(primes);

    //pole pro ulozeni poslednich deseti prvocisel
    unsigned long lastTen[10] = {0};

    for (unsigned long j = 0, i = LIMIT - 1; j < 10; i--) {
        if (!bit_array_getbit(primes, i)) {
            lastTen[j] = i;
            j++;
        }

        if (i == 0)
            break;
    }

    //tisk poslednich deseti prvocisel
    for (int i = 9; i >= 0; i--) {
    	if (lastTen[i] == 0)
            continue;

        printf("%lu\n", lastTen[i]);
    }

    bit_array_free(primes);
    return 0;
}
