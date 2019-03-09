/**
 *	@file	error.h
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Rozhrani k modulu error.c.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef ERROR_HEADER
#define ERROR_HEADER

/** 
 * @defgroup Error Error
 */

/**
 * @brief Vypise varovani na stderr.
 *
 * @param fmt Retezec tvorici zaklad zpravy.
 *
 * @return void
 *
 * @ingroup Error
 */
void warning_msg(const char *fmt, ...);

/**
 * @brief Vypise chybovou zpravu a ukonci program s navratovym kodem 1.
 *
 * @param fmt Retezec tvorici zaklad chybove zpravy.
 *
 * @return void
 *
 * @ingroup Error 
 */
void error_exit(const char *fmt, ...);

#endif
