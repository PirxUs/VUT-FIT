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

    if (limit <= 2)
        warning_msg("Na intervalu <0, 1> neexistuji zadna prvocisla, prvni prvocislo je cislo 2");
    
    //nastaveni indexu 0 a 1 jakozto neprvocisel
    if (limit > 0)
        bit_array_setbit(pole, 0, 1);
    if (limit > 1)
        bit_array_setbit(pole, 1, 1);

    for (unsigned long i = 2; i <= sqrt(limit); i++) {
        if (!bit_array_getbit(pole, i)) {
            
            for (unsigned long j = 2 * i; j < limit; j += i) {
                bit_array_setbit(pole, j, 1);
            }
        }
    }
}
