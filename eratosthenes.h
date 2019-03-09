/**
 *	@file	eratosthenes.h
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Rozhrani k modulu eratosthenes.c.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef ERATOSTHENES_HEADER
#define ERATOSTHENES_HEADER

/** 
 * @defgroup Eratosthenes Eratosthenes
 */

/**
 * @brief Implementace algoritmu Eratosthenova sita nad bitovym polem.
 *
 * @param pole Pointer na bitove pole, do ktereho budeme zapisovat prvocisla.
 *
 * @return void
 *
 * @ingroup Eratosthenes
 */
void Eratosthenes(bit_array_t pole);

#endif

