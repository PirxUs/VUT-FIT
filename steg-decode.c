#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ppm.h"
#include "error.h"
#include "bit_array.h"

#ifdef USE_INLINE
extern inline void bit_array_free(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, unsigned long vyraz);
extern inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);
#endif

extern void Eratosthenes(bit_array_t pole);


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
    bit_array_alloc(message, bufferLength);

    Eratosthenes(primes);

    char byte;
    unsigned long j = 0;

    for (unsigned long i = 19; i < bufferLength; i++) {
        if (bit_array_getbit(primes, i) == 0) {
            byte = p->data[i];
            bit_array_setbit(message, j, byte % 2);
            j++;
        }
    }

    bool nullByte = false;
    for (unsigned long i = 1; i < bufferLength / 8; i++) {
        if (((char*)message)[i] == '\0') {
            nullByte = true;
            break;
        }
    }
    if (nullByte == false) {
        ppm_free(p);
        bit_array_free(primes);
        bit_array_free(message);
        error_exit("Chyba v nactene zprave, nebyl nacten nulovy byte");
    }

    printf("%s\n", (char*)(&(message[1])));

    ppm_free(p);

    bit_array_free(primes);
    bit_array_free(message);
    return 0;
}
