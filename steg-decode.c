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
    //bit_array_alloc(message, bufferLength);

    Eratosthenes(primes);

    char c = 0;
    //char byte = 0;
    char byteCycle = 0;
    //unsigned long j = 0;
    bool nullByte = false;
    //TODO check for null byte

    for (unsigned long i = 19; i < bufferLength; i++) {
        if (!bit_array_getbit(primes, i)) {
            c |= (p->data[i] % 2) << byteCycle;
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

    //for (unsigned long i = 19; i < bufferLength; i++) {
    //    if (bit_array_getbit(primes, i) == 0) {
    //        byte = p->data[i];
    //        bit_array_setbit(message, j, byte % 2);
    //        j++;
    //    }
    //}

    //for (unsigned long i = 1; i < bufferLength / 8; i++) {
    //    if (((char*)message)[i] == '\0') {
    //        nullByte = true;
    //        break;
    //    }
    //}
    
    if (nullByte == false) {
        ppm_free(p);
        bit_array_free(primes);
        //bit_array_free(message);
        error_exit("Chyba v nactene zprave, nebyl nacten nulovy byte");
    }

    //printf("%s\n", (char*)(&(message[1])));

    ppm_free(p);

    bit_array_free(primes);
    //bit_array_free(message);
    return 0;
}
