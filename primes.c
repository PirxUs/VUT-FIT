#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bit_array.h"
#include "error.h"

#ifdef USE_INLINE
extern inline void bit_array_free(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, unsigned long vyraz);
extern inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);
#endif

int main() {
    static bit_array_create(hello, 6000);
    
    //bit_array_alloc(hello, 1);

    bit_array_setbit(hello, 0, 1);
    bit_array_setbit(hello, 1, 1);

    unsigned long size = bit_array_size(hello);
    for (unsigned long i = 0; i < size; i++) {
        printf("%ld: %ld\n", i, bit_array_getbit(hello, i));
    }
    for (int i = 0; i < 2; i++)
        printf("%ld\n", hello[i]);
    //bit_array_free(hello);
    
    return 0;
}
