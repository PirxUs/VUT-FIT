#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ppm.h"
#include "error.h"
#include "bit_array.h"
#include "eratosthenes.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        error_exit("Program bere nazev dekodovaneho obrazku jakozto jediny argument");
    }

    struct ppm *p = ppm_read(argv[1]);

    if (p == NULL) {
        error_exit("Nepodarilo se nacist data obrazku");
    }

    unsigned long bufferLength = 3 * p->xsize * p->ysize;
    bit_array_alloc(primes, bufferLength);

    Eratosthenes(primes);

    char c = 0;
    char byteCycle = 0;
    bool nullByte = false;

    for (unsigned long i = 19; i < bufferLength; i++) {
        if (!bit_array_getbit(primes, i)) {
            c |= (p->data[i] & 1) << byteCycle;
            byteCycle++;

            if (byteCycle == 8) {
                if (c == '\0') {
                    nullByte = true;
                    break;
                }

                printf("%c", c);
                byteCycle = 0;
                c = 0;
            }
        }
    }
    printf("\n");
    
    if (nullByte == false) {
        ppm_free(p);
        bit_array_free(primes);
        error_exit("Chyba v nactene zprave, nebyla zakoncena nulovym bytem");
    }

    ppm_free(p);

    bit_array_free(primes);
    return 0;
}
