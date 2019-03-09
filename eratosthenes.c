/**
 *	@file	eratosthenes.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Modul implementujici Eratosthenovo sito.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <math.h>

#include "bit_array.h"
#include "error.h"
#include "eratosthenes.h"

void Eratosthenes(bit_array_t pole) {
    if (pole == NULL) error_exit("Neplatny ukazatel na bitove pole");

    unsigned long limit = bit_array_size(pole);
    unsigned long lowLimit = sqrt(limit);

    if (limit <= 2)
        warning_msg("Na intervalu <0, 1> neexistuji zadna prvocisla, prvni prvocislo je cislo 2");
    
    //nastaveni indexu 0 a 1 jakozto neprvocisel
    if (limit > 0)
        bit_array_setbit(pole, 0, 1);
    if (limit > 1)
        bit_array_setbit(pole, 1, 1);

    //vyskrtame suda cisla
    for (unsigned long h = 4; h < limit; h += 2)
            bit_array_setbit(pole, h, 1);

    for (unsigned long i = 3; i <= lowLimit; i += 2) {
        if (!bit_array_getbit(pole, i)) {
            for (unsigned long j = i * i ; j < limit; j += i << 1)
                bit_array_setbit(pole, j, 1);
        }
    }
}
