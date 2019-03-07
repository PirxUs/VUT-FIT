#include <math.h>

#include "bit_array.h"
#include "error.h"
#include "eratosthenes.h"

void Eratosthenes(bit_array_t pole) {
    if (pole == NULL) error_exit("Neplatny ukazatel na bitove pole");

    unsigned long limit = bit_array_size(pole);

    if (limit < 2)
        warning_msg("Na intervalu <0, 1> neexistuji zadna prvocisla, prvni prvocislo je cislo 2");
    
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
