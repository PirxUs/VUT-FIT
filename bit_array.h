#ifndef BIT_ARRAY_HEADER
#define BIT_ARRAY_HEADER

#include <limits.h>
#include <assert.h>

#include "error.h"


typedef unsigned long *bit_array_t;

#define UL_BITS (sizeof(unsigned long)*CHAR_BIT)

#define convert_size_long(velikost) \
    (velikost % UL_BITS) \
    ? (velikost / UL_BITS + 2) \
    : (velikost / UL_BITS + 1)

#define bit_array_create(jmeno_pole,velikost) \
    unsigned long jmeno_pole[convert_size_long(velikost)] \
    = {velikost}; static_assert(velikost < 640000, "you suck\n");

#define bit_array_alloc(jmeno_pole,velikost) \
    assert(velikost < 125000000 && velikost > 0); bit_array_t jmeno_pole \
    = calloc(convert_size_long(velikost), sizeof(unsigned long)); \
    jmeno_pole != NULL ? jmeno_pole[0] = velikost \
    : (error_exit("bit_array_alloc: Chyba alokace paměti"), 0)

#ifndef USE_INLINE

    #define bit_array_free(jmeno_pole) free(jmeno_pole)

    #define bit_array_size(jmeno_pole) jmeno_pole[0]

    #define bit_array_setbit(jmeno_pole,index,vyraz) \
        (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        vyraz ? (jmeno_pole[index/UL_BITS + 1] \
        |= 1UL << (index % UL_BITS)) : (jmeno_pole[index/UL_BITS + 1] \
        &= ~(1UL << (index % UL_BITS)))

    #define bit_array_getbit(jmeno_pole,index) \
        (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        (jmeno_pole[index/UL_BITS + 1] & \
        (1UL << index % UL_BITS)) ? 1UL : 0UL
#else

    inline void bit_array_free(bit_array_t jmeno_pole) {
        free(jmeno_pole);
    }

    inline unsigned long bit_array_size(bit_array_t jmeno_pole) {
        return jmeno_pole[0];
    }

    inline void bit_array_setbit(bit_array_t jmeno_pole,
        unsigned long index, unsigned long vyraz) {
        (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        vyraz ? (jmeno_pole[index/UL_BITS + 1] \
        |= 1UL << (index % UL_BITS)) : (jmeno_pole[index/UL_BITS + 1] \
        &= ~(1UL << (index % UL_BITS)));
    }

    inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index) {
        return (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        (jmeno_pole[index/UL_BITS + 1] & \
        (1UL << index % UL_BITS)) ? 1UL : 0UL;
    }

#endif
#endif
