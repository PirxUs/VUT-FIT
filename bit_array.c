/**
 *	@file	bit_array.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Modul pro externi deklarace inline funkci pro manipulaci s bitovym polem.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include "bit_array.h"

#ifdef USE_INLINE

extern inline void bit_array_free(bit_array_t jmeno_pole);
extern inline unsigned long bit_array_size(bit_array_t jmeno_pole);
extern inline void bit_array_setbit(bit_array_t jmeno_pole, unsigned long index, unsigned long vyraz);
extern inline unsigned long bit_array_getbit(bit_array_t jmeno_pole, unsigned long index);

#endif
