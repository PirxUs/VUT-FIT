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

/** 
 * @defgroup BitArrayGeneral Bit Array General
 * @{
 */

/**
 * Definice datoveho typu bitoveho pole.
 */
typedef unsigned long *bit_array_t;


/**
 * Makro pro vypocet poctu bitu v jednom unsigned long integeru.
 */
#define UL_BITS (CHAR_BIT * sizeof(unsigned long))

/**
 * Prevadi velikost zadanou v poctu bitu na potrebnou velikost pro
 * alokaci v poctu unsigned long integeru.
 */
#define convert_size_long(velikost) \
    (velikost % UL_BITS ? \
    velikost / UL_BITS + 2 : \
    velikost / UL_BITS + 1)

/**
 * Vytvori automaticke/lokalni pole bitu a inicializuje
 * hodnoty vsech bitu na nulu. Na prvni pozici v poli ulozi
 * delku pole v bitech.
 */
#define bit_array_create(jmeno_pole,velikost) \
    unsigned long jmeno_pole[convert_size_long(velikost)] \
    = {velikost}; static_assert(velikost > 0, "Velikost pole musi byt vetsi nez nula\n");

/**
 * Vytvori dynamicky alokovane pole bitu, pamet
 * je pri alokaci nulovana. Na prvni pozici v poli ulozi
 * delku pole v bitech.
 */
#define bit_array_alloc(jmeno_pole,velikost) \
    assert(velikost > 0); bit_array_t jmeno_pole \
    = calloc(convert_size_long(velikost), sizeof(unsigned long)); \
    jmeno_pole != NULL ? jmeno_pole[0] = velikost \
    : (error_exit("bit_array_alloc: Chyba alokace paměti"), 0)


/** 
 * @}
 * @defgroup BitArrayMacros Bit Array Macros
 * @{
 */
#ifndef USE_INLINE
    /**
     * Definice maker pro manipulaci s bitovym polem.
     */

    /** 
     * Uvolni pamet dynamicky alokovaneho pole.
     */
    #define bit_array_free(jmeno_pole) free(jmeno_pole)

    /** 
     * Vrati velikost bitoveho pole v poctu bitu.
     */
    #define bit_array_size(jmeno_pole) jmeno_pole[0]

    /** 
     * Vyhodnoti vyraz. Pokud je nenulovy, naindexuje bitove pole
     * a pomci bitovych logickych operacia a posuvu nastavi dany bit
     * na hodnotu jedna. V opacnem pripade nastavi dany bit na hodnotu nula.
     */
    #define bit_array_setbit(jmeno_pole,index,vyraz) \
       index < jmeno_pole[0] \
       ? vyraz ? (jmeno_pole[index/UL_BITS + 1] |= 1UL << index % UL_BITS) : \
       (jmeno_pole[index/UL_BITS + 1] &= ~(1UL << index % UL_BITS)) : \
       (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", \
       (unsigned long)index, (unsigned long)jmeno_pole[0] - 1), 0)

    /** 
     * Nalezne korektni index v bitovem poli a pomoci bitovych logickych
     * operaci a posuvu zjisti hodnotu hledaneho bitu.
     */
    #define bit_array_getbit(jmeno_pole,index) \
        (index < jmeno_pole[0] \
        ? jmeno_pole[index/UL_BITS + 1] & \
        1UL << index % UL_BITS ? 1UL : 0UL \
        : (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", \
        (unsigned long)index, (unsigned long)jmeno_pole[0] - 1), 0))

/** 
 * @}
 * @defgroup BitArrayInline Bit Array Inline
 * @{
 */
#else

    /**
     * Definice inline funkci pro manipulaci s bitovym polem.
     */

    /** 
     * @brief Uvolni pamet dynamicky alokovaneho pole.
     *
     * @param jmeno_pole Bitove pole, ktere chceme uvolnit z pameti.
     *
     * @return void
     */
    inline void bit_array_free(bit_array_t jmeno_pole) {
        free(jmeno_pole);
    }

    /** 
     * @brief Zjisti velikost daneho bitoveho pole.
     *
     * @param jmeno_pole Bitove pole, jehoz velikost chceme zjistit.
     *
     * @return Vraci hodnotu velikosti bitoveho pole.
     */
    inline unsigned long bit_array_size(bit_array_t jmeno_pole) {
        return jmeno_pole[0];
    }

    /** 
     * @brief Vyhodnoti vyraz. Pokud je nenulovy, naindexuje bitove pole
     * a pomci bitovych logickych operacia a posuvu nastavi dany bit
     * na hodnotu jedna. V opacnem pripade nastavi dany bit na hodnotu nula.
     *
     * @param jmeno_pole Bitove pole, do ktereho zapisujeme hodnotu daneho bitu.
     * @param index Index bitu, ktery chceme zapsat.
     * @param vyraz Vyraz, ktery po vyhodnoceni determinuje hodnotu daneho bitu.
     *
     * @return void
     */
    inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, unsigned long vyraz) {
       index < jmeno_pole[0]
       ? vyraz ? (jmeno_pole[index/UL_BITS + 1] |= 1UL << index % UL_BITS) : 
       (jmeno_pole[index/UL_BITS + 1] &= ~(1UL << index % UL_BITS)) :
       (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu",
       (unsigned long)index, (unsigned long)jmeno_pole[0] - 1), 0);
    }

    /** 
     * Nalezne korektni index v bitovem poli a pomoci bitovych logickych
     * operaci a posuvu zjisti hodnotu hledaneho bitu.
     *
     * @param jmeno_pole Bitove pole, v nemz hledame hodnotu daneho bitu.
     * @param index Index bitu, jehoz hodnotu chceme zjistit.
     *
     * @return Vraci hodnotu bitu na danem indexu.
     */
    inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index) {
        return index < jmeno_pole[0]
        ? jmeno_pole[index/UL_BITS + 1] &
        1UL << index % UL_BITS ? 1UL : 0UL
        : (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu",
        (unsigned long)index, (unsigned long)jmeno_pole[0] - 1), 0);
    }

/**
 * @}
 */
#endif
#endif
