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

/* Velikost bitoveho pole */
#define SIZE 123000000LU

int main(void) {
    bit_array_create(primes, SIZE);
    
    Eratosthenes(primes);

    /* Pole pro ulozeni poslednich deseti prvocisel */
    unsigned long lastTen[10] = {0};

    /* Postupne ukladame az 10 nejvyssich prvocisel z bitoveho
     * pole do pole lastTen */
    for (unsigned long j = 0, i = SIZE - 1; j < 10; i--) {
        if (!bit_array_getbit(primes, i)) {
            lastTen[j] = i;
            j++;
        }

        if (i == 0)
            break;
    }

    /* Tisk poslednich deseti prvocisel */
    for (int i = 9; i >= 0; i--) {
    	if (lastTen[i] == 0)
            continue;

        printf("%lu\n", lastTen[i]);
    }

    return 0;
}
