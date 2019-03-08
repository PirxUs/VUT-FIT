/**
 *	@file	bit_array.h
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Rozhrani modulu bit_array.c. Obsahuje definice maker a inline funkci pro manipulaci se strukturou bitoveho pole.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef BIT_ARRAY_HEADER
#define BIT_ARRAY_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "error.h"


typedef unsigned long *bit_array_t;

//makro pro vypocet poctu bitu v jednom unsigned long integeru
#define UL_BITS (sizeof(unsigned long)*CHAR_BIT)

//prevadi velikost zadanou v pocut bitu na potrebnou velikost pro
//alokaci v unsigned long
#define convert_size_long(velikost) \
    (velikost % UL_BITS) \
    ? (velikost / UL_BITS + 2) \
    : (velikost / UL_BITS + 1)

#define bit_array_create(jmeno_pole,velikost) \
    unsigned long jmeno_pole[convert_size_long(velikost)] \
    = {velikost}; static_assert(velikost > 0, "Velikost pole musi byt vetsi nez nula\n");

#define bit_array_alloc(jmeno_pole,velikost) \
    assert(velikost > 0); bit_array_t jmeno_pole \
    = calloc(convert_size_long(velikost), sizeof(unsigned long)); \
    jmeno_pole != NULL ? jmeno_pole[0] = velikost \
    : (error_exit("bit_array_alloc: Chyba alokace paměti"), 0)



#ifndef USE_INLINE
    //definice maker pro manipulaci s bitovym polem

    #define bit_array_free(jmeno_pole) free(jmeno_pole)

    #define bit_array_size(jmeno_pole) jmeno_pole[0]

    #define bit_array_setbit(jmeno_pole,index,vyraz) \
        (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        vyraz ? (jmeno_pole[index/UL_BITS + 1] \
        |= 1UL << (index % UL_BITS)) : (jmeno_pole[index/UL_BITS + 1] \
        &= ~(1UL << (index % UL_BITS)))

    #define bit_array_getbit(jmeno_pole,index) \
        (index >= bit_array_size(jmeno_pole) \
        ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)bit_array_size(jmeno_pole)), 0) : \
        (jmeno_pole[index/UL_BITS + 1] & \
        (1UL << index % UL_BITS)) ? 1UL : 0UL)
#else

    //definice inline funkci pro manipulaci s bitovym polem

    inline void bit_array_free(bit_array_t jmeno_pole) {
        free(jmeno_pole);
    }

    inline unsigned long bit_array_size(bit_array_t jmeno_pole) {
        return jmeno_pole[0];
    }

    inline void bit_array_setbit(bit_array_t jmeno_pole,
        unsigned long index, unsigned long vyraz) {
        (index >= bit_array_size(jmeno_pole)) \
        ? (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", \
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
