/**
 *	@file	steg-decode.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Program implementuje extrakci zakodovanych dat z obrazku formatu ppm metodou podobnou steganografii.
 *	@note	Reseni: IJC-DU1, priklad b)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ppm.h"
#include "error.h"
#include "bit_array.h"
#include "eratosthenes.h"


int main(int argc, char *argv[]) {
    if (argc != 2) error_exit("Program bere nazev dekodovaneho obrazku jakozto jediny argument");

    struct ppm *p = ppm_read(argv[1]);
    if (p == NULL)
        error_exit("Nepodarilo se nacist data obrazku");

    unsigned long bufferLength = 3 * p->xsize * p->ysize;

    /* Alokujeme pamet pro pole znaku, kam ulozime dekodovane znaky.
     * Pole muze byt minimalne sizeof(unsigned long) * 2 mensi, nez byl originalni
     * pocet znaku v rgb bufferu, vzhledem rozlozeni prvocisel a poctu znaku
     * na jeden unsigned long. */
    char *message = malloc(bufferLength / (sizeof(unsigned long) * 2));
    if (message == NULL)
        error_exit("Nepodarilo se alokovat pamet pro ulozeni dekodovaneho textu");


    bit_array_alloc(primes, bufferLength);

    Eratosthenes(primes);

    char c = 0, byteCycle = 0;
    bool nullByte = false;

    for (unsigned long i = 19, j = 0; i < bufferLength; i++) {
        if (!bit_array_getbit(primes, i)) {
	    
	    /* LSb nejprve ukladame do znaku c, ktery pak ulozime do pole message */
            c |= (p->data[i] & 1) << byteCycle;
            byteCycle++;

            if (byteCycle == 8) {

                /* Znaky nejprve ukladame do pole message pro pripad chyby
                 * v zakonceni zpravy nulovym bytem. */
                message[j++] = c;
                if (c == '\0') {
                    nullByte = true;
                    break;
                }
                c = 0;
                byteCycle = 0;
            }
        }
    }
    
    /* Kontrola zakonceni zpravy nulovym bytem */
    if (nullByte == false) {
        ppm_free(p);
        bit_array_free(primes);
        error_exit("Chyba v nactene zprave, nebyla zakoncena nulovym bytem");
    }

    printf("%s\n", message);

    ppm_free(p);
    bit_array_free(primes);
    free(message);
    return 0;
}
